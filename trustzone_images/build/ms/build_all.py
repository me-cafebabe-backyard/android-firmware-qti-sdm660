
#===============================================================================
#
# CBSP Build system
#
# Copyright (c) 2015-2016 Qualcomm Technologies, Inc. All Rights Reserved.
# Qualcomm Technologies Proprietary and Confidential.
#
#===============================================================================
'''
    Created on Jan. 14, 2016
    @authors: c_jacke, lenhardw

    Python Script for creating Builds

    Syntax: run with --help for syntax

'''

import logging

VERBOSE = 5
logging.basicConfig()
logger = logging.getLogger("build_all")
logger.setLevel(logging.INFO)

import glob
import multiprocessing
import optparse
import os
import platform
import re
import signal
import shutil
import socket
import sys
import threading
import time
import traceback
import Queue

from subprocess import call
from xml.dom import minidom
from xml.etree import ElementTree

import BuildConfigParser

try:
    import cleanpack_tz2 as cleanpack_tz # FIXME rename file to cleanpack_tz
except ImportError:
    cleanpack_tz = None # pylint: disable=C0103

# directory containing this script
EXEC_DIR = os.path.dirname(os.path.realpath(__file__))

# Flags
FORBID_UNDOCUMENTED_ARTIFACTS = False
PARALLELIZE_BUILD = False

# TODO - move these to XML config as well if possible
# root of the TZ build (two levels up from this script)
BUILD_ROOT = os.path.abspath(os.path.join(EXEC_DIR, os.pardir, os.pardir))
PACKAGE_ROOT = os.path.abspath(os.path.join(BUILD_ROOT, os.pardir))
TOOLS_SCONS_PATH = os.path.join("tools", "build", "scons")
SCONS_BUILD_PATH = "build"
BUILD_PATH = os.path.join("build", "ms")
LOGFILE_ROOT = os.path.join(BUILD_ROOT, BUILD_PATH)
TEMP_DIR = os.path.join(PACKAGE_ROOT, "temp")
CONFIG_FILE = os.path.join(LOGFILE_ROOT, "build_config.xml")
REPORT_GENERATOR_SCRIPT = os.path.join(BUILD_ROOT, TOOLS_SCONS_PATH, \
        "linker_reporter", "report_generator.py")
REPORT_GENERATOR_PATH = os.path.join("linker_reporter", "report_generator.py")

MANIFEST_FILE = os.path.join(BUILD_ROOT, "build", "manifest.xml")
BUILD_LOG_PREFIX = "build-log"
UNIFIED_LOG = "LOGFILE"
COV_FILE_NAME="core_tz_bullseye.cov"
COV_LOG_FILE="core_tz_bullseye.log"

DEFAULT_ARGS = [
    "-f",
    "target.scons",
]

CLEANPACK_ARGS = [
    "-c",
    "--implicit-deps-unchanged",
    "--cleanpack",
]

CLEANPACK_COPY_TARGETS = [
    os.path.join("trustzone_images", "core", "securemsm", "trustzone", \
            "monitor"),
    os.path.join("trustzone_images", "core", "securemsm", "trustzone", "qsee"),
]

# TODO - clean these directory references up somehow
HK11_DIR = os.path.join(PACKAGE_ROOT, "HK11")
HY11_DIR = os.path.join(PACKAGE_ROOT, "HY11_1")

DEFAULT_MAPREPORT = False
DEFAULT_OS = "default"

CRM_CLIENT_LOG = "crm_client.log"
CRM_INFO_FILE = "crm_info.txt"

ENVIRONMENT_DUMP_SHELL = "envdump.sh"
ENVIRONMENT_DUMP_BATCH = "envdump.cmd"

SHORT_DELAY = 1
MEDIUM_DELAY = 2
LONG_DELAY = 5
DEQUEUE_RETRY_DELAY = 2
WORKER_WAIT_TIME = 60
FAST_BUILD = False
SEPARATOR = 40 * "-"
CLEAN_FLAG = "-c"

# worker response types
WORKER_SUCCESS = 0
WORKER_FAILURE = 1
WORKER_EXITED = 2
WORKER_EXCEPTION = 3

# error codes
# TODO: for now, every line using one of these has a pylint suppression comment.
# However, this mechanism should be redesigned to allow proper checking of
# variable definitions as bugs could sneak past the checker.
ERROR_CODES = {
    "ERROR_OK" : 0,
    "ERROR_INVALID_ARG" : -1,
    "ERROR_BAD_CONFIG" : -2,
    "ERROR_INVALID_ARTIFACT" : -3,
    "ERROR_SYS_ERR" : -4,
    "ERROR_BAD_PATH" : -5,
    "ERROR_WORKER_EXCEPTION" : -6,
    "ERROR_INTERRUPTED" : -7,
    "ERROR_UNKNOWN" : -8,
}

def _setErrors(mapping):
    """Translate ERROR_CODES into usable variables"""
    _globals = globals()
    for key in mapping:
        val = mapping[key]
        _globals[key] = val
        for key2 in mapping:
            if key == key2:
                continue
            assert mapping[key2] != val, \
                    "%s & %s cannot have the same value" % (key, key2)

_setErrors(ERROR_CODES)

def strerr(err):
    """Return human-readable strings for error codes"""
    for key in ERROR_CODES:
        if ERROR_CODES[key] == err:
            return key
    logger.debug("%d is not a recognized error code" % err)
    return str(err)

class BuildQueue(Queue.Queue, object):
    """Class handling build dependency ordering"""
    LOGGER = logging.getLogger("BuildQueue")
    LOGGER.setLevel(logging.INFO)
    def __init__(self, fileList, fileMetadata, fillInDependencies = True):
        super(BuildQueue, self).__init__()
        self._lock = threading.Lock()
        # dummy initializers
        self._completed = None
        self._filesRemaining = None
        self._meta = None
        self._nodeMap = None
        self._requiredFiles = None
        self._tree = None
        # trigger actual init
        self._initQueue(fileList, fileMetadata, fillInDependencies)
#
    def _initQueue(self, fileList, fileMetadata, fillInDependencies = True):
        """BuildQueue initializer"""
        BuildQueue.verbose("Given files: %s" % ", ".join(fileList))
        self._meta = fileMetadata
        fileSet = set(fileList)
        missingKeys = list(fileSet.difference(set(self._meta.keys())))
        missingKeys.sort()
        assert len(missingKeys) == 0, "No metadata entries found for: %s" \
                % ", ".join(missingKeys)
        getdeps = lambda f, n = None: f["dependencies"]
        self._tree = BuildConfigParser.buildDictDependencyTree(self._meta, \
                getdeps, False, None)
        traversalList = self._tree.getTraversalList()
        requiredFiles = set(fileSet)
        for node in traversalList:
            if node.name in requiredFiles:
                requiredFiles.update( \
                        set([ n.name for n in node.dependencies ]))
        BuildQueue.debug("Complete list of required files: %s" \
                    % ", ".join(sorted(list(requiredFiles))))
        missingDeps = requiredFiles.difference(fileSet)
        if len(missingDeps) > 0:
            missing = [ d for d in missingDeps ]
            missing.sort()
            assert fillInDependencies, \
                    "Provided files are missing required dependencies: %s" \
                    % ", ".join(missing)
            BuildQueue.info("Filling in missing file dependencies: %s" \
                    % ", ".join(missing))
            # no need to update fileSet as requiredFiles already has the list
        self._nodeMap = {}
        initial = []
        for node in traversalList:
            if node.name not in requiredFiles:
                # Since we filled in all dependencies, anything left is
                # either part of our tree or completely disjoint from it.
                # There is no point in removing any of these disjoint nodes.
                continue
            self._nodeMap[node.name] = node
            if node.parentCount == 0:
                self.put(node) # put is already thread-safe
                initial.append(node.name)
        self._filesRemaining = len(requiredFiles)
        self._requiredFiles = requiredFiles
        self._completed = set([])
        BuildQueue.debug("Initial queue (%d items): %s" % (len(initial), \
                ", ".join(initial)))
#
    def markComplete(self, filename):
        """Indicate that a file has been successfully built"""
        BuildQueue.debug("Mark complete: %s" % filename)
        assert filename in self._requiredFiles, \
                "Cannot mark completion of unexpected file %s" % filename
        assert filename not in self._completed, \
                "%s cannot be completed twice" % filename
        self._lock.acquire()
        node = self.getNode(filename)
        for child in node.children:
            # technically, we only have to acquire the lock within this scope,
            # but lock/release overhead is substantially higher than the
            # performance impact of this function, so we only acquire/release
            # once above
            if child.parentCount > 0:
                child.removeParent(node)
            parentCount = child.parentCount
            # could technically release here
            if parentCount == 0 and child.name in self._requiredFiles:
                # locking ensures that we can never double-queue this node
                self.put(child)
        self._completed.add(filename)
        if self._filesRemaining > 0:
            # only decrease if we are positive; since stop() sets this to 0, it
            # is possible for parallel jobs to drop this below zero, incorrectly
            # negating the 'complete' check
            self._filesRemaining -= 1
        self._lock.release()
#
    def stop(self):
        """Terminate/complete the build in progress"""
        # TODO - add code to safely flush queue on stop (or allow pause/resume)
        self._filesRemaining = 0
        BuildQueue.debug("stopped")
#
    def getNode(self, filename):
        """Return dependency node for a filename"""
        return self._nodeMap[filename]
#
    def getMeta(self):
        """Return map of file metadata"""
        return self._meta
#
    def complete(self):
        """Indicates whether there are any files left to build"""
        return self.filesRemaining == 0
#
    @classmethod
    def verbose(cls, msg):
        """verbose BuildQueue logging"""
        cls.LOGGER.log(VERBOSE, msg)
#
    @classmethod
    def debug(cls, msg):
        """debug-level BuildQueue logging"""
        cls.LOGGER.debug(msg)
#
    @classmethod
    def info(cls, msg):
        """info-level BuildQueue logging"""
        cls.LOGGER.info(msg)
#
    @classmethod
    def warn(cls, msg):
        """warning-level BuildQueue logging"""
        cls.LOGGER.warn(msg)
#
    @classmethod
    def error(cls, msg):
        """error-level BuildQueue logging"""
        cls.LOGGER.error(msg)
#
    @property
    def filesRemaining(self):
        """number of files that must be built before build completion"""
        return self._filesRemaining

def buildAll():
    """main build function"""
    # TODO - @redesign to reduce returns, branches, local vars & statements
    #pylint: disable=R0911, R0912, R0914, R0915
    startTime = time.time()
    (options, args) = parseArguments()

    if options.verbose:
        if logger.getEffectiveLevel() > logging.DEBUG:
            logger.setLevel(logging.DEBUG)
            BuildQueue.LOGGER.setLevel(logging.DEBUG)
        DEFAULT_ARGS.append("--verbose=5")

    assert not (options.sequential_build and options.parallelize_build), \
            "Build cannot be both sequential & parallelized"

    global PARALLELIZE_BUILD #pylint: disable=W0603
    global FORBID_UNDOCUMENTED_ARTIFACTS #pylint: disable=W0603
    if options.sequential_build:
        PARALLELIZE_BUILD = False

    if options.parallelize_build:
        PARALLELIZE_BUILD = True

    if options.fast_build:
        global FAST_BUILD #pylint: disable=W0603
        FAST_BUILD = True
        if not options.sequential_build:
            PARALLELIZE_BUILD = True

    jobs = 1
    if PARALLELIZE_BUILD:
        jobs = getCpuCount()
        # In parallel builds, it is expected that extra artifacts will be
        # present as multiple files will probably be built at once, thus
        # messing up our concept of what was in the bin directory before
        # starting to build the current target file.
        FORBID_UNDOCUMENTED_ARTIFACTS = False

    cleanBuild = options.clean or options.clean_build
    makeBuild = not options.clean

    # change to build/ms directory for config stage
    os.chdir(LOGFILE_ROOT)

    # load the XML config
    config = BuildConfigParser.loadXml(options.config_file)
    if len(config) == 0:
        logger.critical("failed to load %s" % options.config_file)
        return ERROR_BAD_CONFIG #pylint: disable=E0602

    if options.detect_branch:
        branch = detectBranch(config)
        if branch != None:
            print(branch)
            return ERROR_OK #pylint: disable=E0602
        else:
            logger.error("Could not auto-detect branch")
            return ERROR_INVALID_ARG #pylint: disable=E0602

    # get a mapping of branch aliases to actual branch names
    aliasMap = BuildConfigParser.loadAliasMap(config)

    autoSelectedBranch = False
    if options.branch == None:
        branch = detectAndLogBranch(config)
        if branch == None:
            # we are guaranteed to have at least one non-virtual branch in xml
            productionBranches = []
            for branchName in config:
                if config[branchName]["virtual"]:
                    continue
                # return an actual branch, not an alias
                if branchName not in aliasMap:
                    productionBranches.append(branchName)
            productionBranches.sort()
            availableBranches = "Available branches are:\n%s" \
                    % "\n".join(productionBranches)
            logger.critical( \
                    #pylint: disable=C0301
                    "Could not detect branch. Please pass it explicitly:\nEg: -b %s\n\n%s" \
                    % (productionBranches[0], availableBranches))
            return ERROR_INVALID_ARG #pylint: disable=E0602
        autoSelectedBranch = True
    else:
        branch = options.branch
        logger.debug("Branch '%s' explicitly passed via command line" % branch)

    branchConfig = config.get(branch)
    if branchConfig == None:
        logger.critical("Branch '%s' not found in %s" % (branch, options.config_file))
        return ERROR_BAD_CONFIG #pylint: disable=E0602
    if branchConfig["virtual"] == True:
        logger.critical( \
                "Branch '%s' is virtual (non-production) and cannot be built" \
                % branch)
        return ERROR_BAD_CONFIG #pylint: disable=E0602

    # We have a legitimate branch; now translate any alias to its real name
    rawBranch = branch
    branch = aliasMap.get(branch, rawBranch)
    if rawBranch != branch:
        logger.debug("Translate branch alias '%s' --> '%s'" \
                % (rawBranch, branch))

    # Now that we have our config & branch, parse any leftover arguments to
    # establish additional params (eg X=Y), target files (eg tz), or pass-though
    # args (anything leftover after the others)
    buildInput = parseExtraArguments(args, branchConfig)
    cmdParams = buildInput["params"]

    # IMPORTANT NOTE:
    # While 'chipset' & 'target' may appear overloaded, there is a distinct
    # difference: 'target' represents a buildable target name, as represented in
    # build_config.xml by <target> tags. A target's 'chipset' is USUALLY but NOT
    # ALWAYS its name. Differences may occur for special targets like
    # pre-silicon build targets (eg rumi/virtio) or targets with binary
    # compatibility (eg msm8976 uses the 'msm8956' chipset).
    #
    # This difference is abstracted away from the user via the CHIPSET param
    # which actually references a 'target', letting the build script perform any
    # necessary translation. Errors to the user will always reflect 'chipset'.
    targets = []
    target = cmdParams.get("CHIPSET")
    autoSelectedTarget = False
    if target == None:
        if options.use_default_target:
            defaultTarget = branchConfig["default_target"]
            if defaultTarget == None:
                logger.critical( \
                        #pylint: disable=C0301
                        "No default target found for branch '%s' - must provide a valid chipset (eg CHIPSET=%s)" \
                        % defaultTarget)
                return ERROR_INVALID_ARG #pylint: disable=E0602
            targets = [ defaultTarget ]
        else:
            # build all valid targets for this branch
            for target in branchConfig["targets"]:
                targetInfo = branchConfig["targets"][target]
                if targetInfo["buildable"] and not targetInfo["exclusive"]:
                    targets.append(target)
            #pylint: disable=C0301
            assert len(targets) > 0, \
                    "%s is invalid - no buildable targets listed for branch %s" \
                    % (options.config_file, branch)
        autoSelectedTarget = True
    else:
        logger.debug("Chipset '%s' explicitly passed via command line" % target)
        if options.use_default_target:
            logger.critical( \
                    "Cannot both specify a chipset & request the default")
            return ERROR_INVALID_ARG #pylint: disable=E0602
        # Now, remove the 'CHIPSET' param so that the given target gets properly
        # translated to a chipset later via our build config
        del cmdParams["CHIPSET"]
        targets = [ target ]
    targets.sort() # sort the targets for more consistent build behavior
    del target # we no longer need this & redefine it immediately below

    # validate selected targets
    for target in targets:
        targetConfig = branchConfig["targets"].get(target)
        if targetConfig == None:
            logger.critical("Chipset '%s' not defined in %s" \
                    % (target, options.config_file))
            return ERROR_BAD_CONFIG #pylint: disable=E0602
        if targetConfig["buildable"] == False:
            logger.critical("Chipset '%s' is not a buildable target" % target)
            return ERROR_BAD_CONFIG #pylint: disable=E0602
        if targetConfig["exclusive"] == True and len(targets) > 1:
            logger.critical( \
                    "Chipset '%s' cannot be built with other targets" % target)
            return ERROR_BAD_CONFIG #pylint: disable=E0602
        # if files were specified via the command line, verify that they apply
        # to the selected targets
        for f in buildInput["files"]:
            fileMeta = targetConfig["files"].get(f)
            if fileMeta == None:
                logger.critical("'%s' is not supported on %s on branch %s" \
                        % (f, target, branch))
                return ERROR_BAD_CONFIG #pylint: disable=E0602
            elif fileMeta["disable"]:
                logger.warn( \
                        #pylint: disable=C0301
                        "'%s' (disabled in config) is explicitly enabled by the user" \
                        % f)
        if targetConfig["chipset"] != target:
            logger.debug("Target '%s' maps to chipset '%s'" \
                    % (target, targetConfig["chipset"]))

    addCustomBuildTargets(options, branchConfig, buildInput)

    if options.list_targets:
        print(", ".join(targets))
        return ERROR_OK #pylint: disable=E0602

    osType = getOsType()
    setupEnv(targetConfig, osType, options.dump_environment)

    if options.code_coverage:
        setCodeCoverageEnvironment() 
                
    if checkEnv(osType) != 0:
        logger.critical( \
                #pylint: disable=C0301
                "Environment settings are incorrect - please see previous error message. Exiting ...")
        return ERROR_BAD_CONFIG #pylint: disable=E0602

    targetCount = len(targets)
    if targetCount > 1:
        if cmdParams.get("BUILD_ID") != None:
            logger.critical( \
                    #pylint: disable=C0301
                    "Cannot use custom build id (%s) when building multiple chipsets (%s)" \
                    % (cmdParams.get("BUILD_ID"), ", ".join(targets)))
            return ERROR_INVALID_ARG #pylint: disable=E0602
        if cmdParams.get("TARGET_FAMILY") != None:
            logger.critical( \
                    #pylint: disable=C0301
                    "Cannot use custom target family (%s) when building multiple chipsets (%s)" \
                    % (cmdParams.get("TARGET_FAMILY"), ", ".join(targets)))
            return ERROR_INVALID_ARG #pylint: disable=E0602
        if cmdParams.get("SOC_HW_VERSION") != None:
            logger.critical( \
                    #pylint: disable=C0301
                    "Cannot use custom SOC_HW_VERSION (%s) when building multiple chipsets (%s)" \
                    % (cmdParams.get("SOC_HW_VERSION"), ", ".join(targets)))
            return ERROR_INVALID_ARG #pylint: disable=E0602
        if cmdParams.get("SOC_VERS") != None:
            logger.critical( \
                    #pylint: disable=C0301
                    "Cannot use custom SOC_VERS (%s) when building multiple chipsets (%s)" \
                    % (cmdParams.get("SOC_VERS"), ", ".join(targets)))
            return ERROR_INVALID_ARG #pylint: disable=E0602

    os.chdir(BUILD_ROOT) # ensure that we start in the BUILD_ROOT directory
    printDiagnosticInfo(branch, targets, options, buildInput, \
            autoSelectedBranch)
    # The user is relying on some default arguments & auto-detection and may not
    # expect the config that has been chosen. Pause to give them a chance to
    # identify any errors and cancel the build.
    if (autoSelectedBranch or autoSelectedTarget) and not FAST_BUILD:
        time.sleep(LONG_DELAY)

    # create the manifest after the delay (in case the user aborts)
    if createManifestIfNeeded(branch):
        logger.debug("Generated updated manifest file")

    # TODO - add logic forbidding combinations of some flags, such as clean +
    # recompile only or cleanpack + clean-and-build
    retCode = ERROR_OK #pylint: disable=E0602
    loadableParamNames = [
        "BUILD_ASIC",
        "BUILD_ID",
        "BUILD_VER",
        "CHIPSET", # handles the translation from target -> chipset
        "HAL_PLATFORM",
        "MSM_ID",
        "TARGET_FAMILY",
        "SOC_HW_VERSION",
        "SOC_VERS",
    ]
    for target in targets:
        # Each target's config was already validated above
        targetConfig = branchConfig["targets"][target]
        targetParams = dict(cmdParams) # shallow copy to preserve the original
        targetArgs = list(DEFAULT_ARGS) # shallow copy
        targetArgs.extend(buildInput["args"])

        for paramName in loadableParamNames:
            if targetParams.get(paramName) == None:
                value = targetConfig[paramName.lower()]
                logger.debug("%s = %s" % (paramName, value))
                targetParams[paramName] = value

        printParams(targetParams, "build")

        # An empty list evaluates to false; fileList becomes None in this case
        # TODO - need to ensure that all dependencies are also added & that they
        # are in an acceptable order, although since SCons handles most of this,
        # it is a minor problem for now
        fileList = buildInput["files"] or None

        if options.test_mode:
            if cleanBuild or options.recompile_only or options.clean_pack \
                    or not makeBuild:
                logger.error("Test mode can only be used with a normal build")
                return ERROR_INVALID_ARG #pylint: disable=E0602
            # force full artifact verification
            FORBID_UNDOCUMENTED_ARTIFACTS = True
            # force sequential build
            PARALLELIZE_BUILD = False

        if not FAST_BUILD:
            time.sleep(MEDIUM_DELAY)

        if cleanBuild:
            logger.info("Cleaning %s for %s" % (branch, target))
            # Preserve the last log by renaming it from "build-log.txt" to
            # "build-log-[0-9]+.txt"
            renameLog(LOGFILE_ROOT, BUILD_LOG_PREFIX)
            # must maintain our original args for later, so copy them
            cleanArgs = list(targetArgs)
            cleanArgs.append(CLEAN_FLAG)
            # Don't check artifacts since clean should remove them
            retCode = buildTargetFiles(targetConfig, targetParams, cleanArgs, \
                    fileList = fileList, checkArtifacts = False, jobs = jobs)
            if retCode != ERROR_OK: #pylint: disable=E0602
                logger.error("Error encountered when cleaning %s for %s" \
                        % (branch, target))
                break
        if not makeBuild:
            continue
        if options.recompile_only:
            logger.info("Triggering recompilation only of %s for %s" \
                    % (branch, target))
            # TODO - does recompilation need to rename the build log too?
            retCode = recompileTargetFiles(targetConfig, \
                    targetParams, targetArgs)
            if retCode != ERROR_OK: #pylint: disable=E0602
                logger.error("Error encountered in recompilation of %s for %s" \
                        % (branch, target))
                break
            continue
        elif options.clean_pack:
            logger.info("Triggering cleanpack of %s for %s" % (branch, target))
            # TODO - does cleanpack need to rename the build log too?
            retCode = cleanpack(branch, targetConfig, targetParams, \
                    targetArgs)
            if retCode != ERROR_OK: #pylint: disable=E0602
                logger.error("Error encountered in cleanpack of %s for %s" \
                        % (branch, target))
                break
            continue
        # Finally, we're ready to make a normal build
        # Preserve the last log by renaming it from "build-log.txt" to
        # "build-log-[0-9]+.txt"
        renameLog(LOGFILE_ROOT, BUILD_LOG_PREFIX)
        retCode = buildTargetFiles(targetConfig, targetParams, targetArgs, \
                fileList = fileList, checkArtifacts = True, \
                mapreport = options.map_report, testMode = options.test_mode,
                jobs = jobs)
        if retCode != ERROR_OK: #pylint: disable=E0602
            logger.error("Error encountered when building %s for %s" \
                    % (branch, target))
            break
    completionTime = time.time()
    elapsedTime = completionTime - startTime
    logger.info("Build %s" % ("completed successfully" if retCode == 0 \
            else "encountered errors"))
    logger.info("Total elapsed time: %d minutes, %d seconds" % \
            (elapsedTime // 60, elapsedTime % 60))
    return retCode

def createManifestIfNeeded(branch):
    """Some files in the build tree rely on trustzone_images/build/manifest.xml
       for the branch. Generate one if it does not exist to prevent a build
       failure. Adds a custom flag indicating that the manifest was created
       by build_all.py so that we can re-create it if the branch changes."""
    if checkManifest(MANIFEST_FILE, checkCreator = True):
        # manifest exists and is valid as-is
        return False
    # Generate actual XML
    configXml = ElementTree.Element("config")
    imageTreeXml = ElementTree.SubElement(configXml, "image_tree")
    nameXml = ElementTree.SubElement(imageTreeXml, "name")
    nameXml.text = branch
    revisionXml = ElementTree.SubElement(imageTreeXml, "revision")
    revisionXml.text = "00000"
    creatorXml = ElementTree.SubElement(configXml, "creator")
    creatorXml.set("name", os.path.realpath(__file__))
     # Write results to file
    try:
        outfile = open(MANIFEST_FILE, "w")
    except (IOError, OSError) as e:
        logger.warn("[%s] failed to write to %s" % (str(e), MANIFEST_FILE))
        assert os.path.exists(MANIFEST_FILE), \
                "Could not create manifest - build will fail if we continue"
        return False # if it already exists, just hope for the best
    declaration = minidom.Document().toxml()
    reparsedXML = minidom.parseString(ElementTree.tostring(configXml, "utf-8"))
    outfile.write(reparsedXML.toprettyxml(indent = "  ")[len(declaration) + 1:])
    outfile.close()
    assert checkManifest(MANIFEST_FILE), "BUG: created invalid manifest"
    return True

def checkManifest(filename, checkCreator = False):
    """Returns True if this is valid manifest XML file, False otherwise. If
       'checkCreator' is True, also validates whether the file was created by
       this script, returning 'False' (invalid file) if so."""
    if not os.path.exists(filename):
        return False
    try:
        tree = ElementTree.parse(filename)
    except ElementTree.ParseError as e:
        logger.warn("[%s] failed to parse %s" % (str(e), filename))
        return False
    root = tree.getroot()
    if checkCreator:
        creator = root.find("creator")
        if creator != None:
            name = creator.get("name")
            if name == os.path.realpath(__file__):
                return False
    imageTree = root.find("image_tree")
    if imageTree == None:
        logger.debug("Missing <image_tree>")
        return False
    name = imageTree.findall("name")
    if name == None:
        logger.debug("Missing <name> in <image_tree>")
        return False
    revision = imageTree.findall("revision")
    if revision == None:
        logger.debug("Missing <revision> in <image_tree>")
        # missing return is intentional - we don't really care about revision
    return True

def setupEnv(config, osType, dump = False):
    """
    Sets up the environment variables used by programs
    that are called from this python code. Sets them up
    differently for Windows, Linux and MAC.

    """
    logger.debug("Setting environment variables")
    sys.stdout.flush()

    defaultEnv = config["environment"].get(DEFAULT_OS, {})
    if len(defaultEnv) == 0:
        logger.warn("No default environment found!")
    environmentConfig = config["environment"].get(osType, defaultEnv)

    outfile = None
    if dump:
        if(isWindows()):
            outfile = open(ENVIRONMENT_DUMP_BATCH,"w")
            outfile.write("@ECHO Environment Variables \n")
        else:
            outfile = open(ENVIRONMENT_DUMP_SHELL,"w")
            outfile.write("#!/bin/bash\n")


    for varName in environmentConfig["variables"]:
        varInfo = environmentConfig["variables"][varName]
        if varInfo["export"]:
            # 'value' must always be present; don't worry about KeyError
            value = varInfo["value"]
            logger.debug("Setting %s=%s" % (varName, value))
            os.environ[varName] = value
            if outfile:
                if(isWindows()):
                    outfile.write("SET %s=%s\n" % (varName, value))
                else:
                    outfile.write("export %s=%s\n" % (varName, value))
    if outfile:
        outfile.close()

def checkEnv(osType):
    """Checks for the presense of mandatory build tools and environment
       variables. Returns an error if a needed tool or env var is missing."""
    logV("%s environment appears ok" % osType)
    return ERROR_OK #pylint: disable=E0602

def getOsType():
    """
    Determines the OS type:
    """
    return platform.system()

def isWindows():
    """Returns True if the system is a Windows variant & False otherwise"""
    return "win" in getOsType().lower()

def getCpuCount():
    """Returns the number of available CPUs in the current system"""
    cpuCount = 1
    if hasattr(os, "sysconf") and \
            os.sysconf_names.has_key("SC_NPROCESSORS_ONLN"):
        # Unix
        cpuCount = os.sysconf("SC_NPROCESSORS_ONLN")
    elif os.environ.has_key("NUMBER_OF_PROCESSORS"):
        # Windows
        cpuCount = int(os.environ["NUMBER_OF_PROCESSORS"])
    logger.debug("Detected %d CPUs" % cpuCount)
    return cpuCount

def detectAndLogBranch(config):
    """Attempts to auto-detect the branch & logs the result"""
    branch = detectBranch(config)
    if branch:
        logger.debug("Auto-detected branch '%s'" % branch)
    return branch

def detectBranch(config):
    """Attempts to auto-detect the current branch"""
    vceFolder = os.path.join(PACKAGE_ROOT, "vce")
    if os.path.exists(vceFolder):
        branch = detectVceBranch(vceFolder, config)
        if branch != None:
            return branch
    #if os.path.exists(repoFolder):
    # We could not find any metadata indicating the branch, so attempt to get it
    # directly from the root folder's name, as this is our 'best guess'
    branchOptions = list(config.keys())
    # sort our potential branches (with aliases mixed in) by descending length
    # so that we check for longest match first
    branchOptions.sort(key = len, reverse = True)
    dirName = os.path.basename(os.path.normpath(PACKAGE_ROOT))
    for branch in branchOptions:
        if branch in dirName:
            logger.debug("Guessed branch '%s' from path name '%s'" \
                    % (branch, dirName))
            return branch
    return None

def detectVceBranch(vceDir, config):
    """Attempts to auto-detect the current branch via VCE sync logs"""
    productionBranches = []
    for key in config:
        branchInfo = config[key]
        if branchInfo["virtual"]:
            continue
        elif key in branchInfo["aliases"]:
            # this is an alias; skip it
            continue
        productionBranches.append(key)
    # sort branch names by longest-first for matching purposes
    productionBranches.sort(key = len, reverse = True)
    # check the crm_client_log file first as it is usually most accurate
    crmLog = os.path.join(vceDir, CRM_CLIENT_LOG)
    branch = parseCrmClientLog(crmLog, productionBranches)
    if branch != None:
        return branch
    # we still haven't found a branch so try the crm_info file
    crmInfo = os.path.join(vceDir, CRM_INFO_FILE)
    branch = parseCrmInfoFile(crmInfo, productionBranches)
    return branch

def parseCrmClientLog(path, branches):
    """Attempts to read the branch from a CRM client log file"""
    crmLogLines = readLines(path) or []
    branch = None
    for line in crmLogLines:
        line = line.strip()
        if not line.startswith("+"):
            continue
        logger.debug("Candidate line for branch: %s" % line)
        branchCandidates = matchBranches(line, branches)
        if len(branchCandidates) == 0:
            continue
        branch = branchCandidates[-1]
        logger.debug("Detected branch %s in crm log" % branch)
        break
    return branch

def parseCrmInfoFile(path, branches):
    """Attempts to read the branch from a CRM info file"""
    crmInfoLines = readLines(path)
    if crmInfoLines == None:
        return None
    plfCandidate = None
    crmCandidate = None
    imageCandidate = None
    for line in crmInfoLines:
        line = line.strip()
        if "=" not in line:
            continue
        parts = line.split("=")
        potentialBranch = "=".join(parts[1:])
        if parts[0].startswith("PLF_USED") and "=" in line:
            branchCandidates = matchBranches(potentialBranch, branches)
            if len(branchCandidates) == 0:
                continue
            plfCandidate = branchCandidates[-1]
            logger.debug("Detected branch %s in crm info plf" % plfCandidate)
        elif parts[0].startswith("CRM_Append") and "=" in line:
            branchCandidates = matchBranches(potentialBranch, branches)
            if len(branchCandidates) == 0:
                continue
            crmCandidate = branchCandidates[-1]
            logger.debug("Detected branch %s in crm info append" % crmCandidate)
        elif parts[0].startswith("Software Image") and "=" in line:
            if potentialBranch not in branches:
                logger.debug( \
                        #pylint: disable=C0301
                        "Found SI %s in %s, but it does not match any production branch" \
                        % (potentialBranch, CRM_INFO_FILE))
                continue
            if imageCandidate != None:
                logger.warn( \
                        #pylint: disable=C0301
                        "Found multiple Software Images in %s; replacing %s with %s" \
                        % (CRM_INFO_FILE, imageCandidate, potentialBranch))
            else:
                logger.debug("Found SI %s in crm info" % potentialBranch)
            imageCandidate = potentialBranch
    return plfCandidate or crmCandidate or imageCandidate

def matchBranches(line, branchList):
    """Matches text against a list of known branches"""
    ret = []
    for branch in branchList:
        # there should not be many candidate lines, so on-the-fly regex
        # compilation should never be a notable performance issue
        branchRegex = re.compile("/%s_" % branch)
        match = branchRegex.search(line)
        if match == None:
            continue
        logger.debug("Detected branch %s in %s" % (branch, CRM_CLIENT_LOG))
        ret.append(branch)
    if len(ret) > 1:
        logger.debug("Multiple branch candidates found in line: %s" \
                % ", ".join(ret))
    return ret

def readLines(filename):
    """Reads text from a file as a list of lines"""
    if not os.path.isfile(filename):
        logger.warn("'%s' is not a valid file" % filename)
        return None
    try:
        infile = open(filename)
    except (IOError, OSError) as e:
        logger.error("[%s] could not read %s" % (str(e), filename))
        return None
    ret = infile.readlines()
    infile.close()
    return ret

def renameLog(dirPath, logfilename):
    """
    Renames the build-log.txt file to build-log-[0-9]+.txt where
    the number is one larger than the highest existing log number.
    """
    filename = logfilename + ".txt"
    buildLog = os.path.join(LOGFILE_ROOT, filename)
    if not os.path.exists(buildLog):
        logger.debug("No previous build log found @%s" % buildLog)
        return
    # glob will handle the unix-path '/' here; don't need to use os.path.join
    dirList = glob.glob(dirPath + "/%s-*[0-9].txt"%logfilename)
    if len(dirList) > 0:
        dirList.sort()
        lastLog = dirList[-1]
        logRegex = re.compile("%s-([0-9]+)\\.txt"%re.escape(logfilename))
        match = logRegex.search(lastLog)
        # this should always match, based on our glob string
        assert match != None, "BUG: %s did not handle %s correctly" % \
                (__file__, lastLog)
        logNum = int(match.group(1))
        logNum += 1
        newLogName = (("%s-" + str(logNum).zfill(3) + ".txt")%logfilename)
    else:
        newLogName = "%s-001.txt"% logfilename
    logger.info("Log: %s" % newLogName)
    try:
        fin = open(buildLog, 'rb')
        fin.close()
        os.rename(buildLog, os.path.join(LOGFILE_ROOT, newLogName))
    except (IOError, OSError) as e:
        logger.error("[%s] could not open %s" % (str(e), buildLog))

def generateReport(reportFiles):
    """Generates a mapping report for the given files"""
    for f in reportFiles:
        filePath = os.path.join(BUILD_ROOT, f)
        reportCmd = "python %s %s" % (REPORT_GENERATOR_SCRIPT, filePath)
        logger.debug("Mapreport command: %s" % reportCmd)
        retCode = call(reportCmd, shell = True)
        if retCode != ERROR_OK: #pylint: disable=E0602
            logger.error("failure occured while generating '%s' report" % f)
            return retCode
    return ERROR_OK #pylint: disable=E0602

# takes string(filename), dict(params), optional list(args)
def buildCmd(filename, params, args = None, mapreportFiles = None):
    """Calls the build.cmd or build.sh batch/shell file."""
    args = args or []
    mapreportFiles = mapreportFiles or []
    assert params.get("CHIPSET") != None, "params must contain CHIPSET"
    buildScript = "build" + (".cmd" if isWindows() else ".sh")
    buildScriptPath = os.path.join(getSConsDir(), SCONS_BUILD_PATH, buildScript)
    buildCommandParts = [ buildScriptPath ]
    buildCommandParts.extend(args)
    for param in params:
        buildCommandParts.append("%s=%s" % (param, params[param]))
    buildCommandParts.append(filename) # finally, add the target file
    buildCommand = " ".join(buildCommandParts)
    # the target.scons script is located within build/ms, so cd there
    buildDir = os.path.join(os.getcwd(), BUILD_PATH)
    if not os.path.exists(buildDir):
        logger.error("%s does not exist; cannot trigger build" % buildDir)
        return ERROR_BAD_PATH #pylint: disable=E0602
    curDir = os.getcwd()
    try:
        os.chdir(buildDir)
#        logger.debug("pwd = %s" % os.getcwd())
        logger.debug("build command: %s" % buildCommand)
        logger.info("\n\nStarting to build %s ...\n\n" % filename)
        sys.stdout.flush() # ensure that all messages are printed before start
        if not FAST_BUILD:
            # give time for the build command to be seen by the user
            time.sleep(SHORT_DELAY)
        retCode = call(buildCommand, shell = True)
        if retCode != ERROR_OK: #pylint: disable=E0602
            logger.error("build command encountered errors: %s" % buildCommand)
            return retCode
        if len(mapreportFiles) == 0:
            return ERROR_OK #pylint: disable=E0602
        # if mapreportFiles has elements, we have 1+ report file(s) to populate
        retCode = generateReport(mapreportFiles)
        if retCode != ERROR_OK: #pylint: disable=E0602
            logger.error("error during mapreport generation")
    finally:
        os.chdir(curDir)
    return retCode

def recompileTargetFiles(config, params, args, jobs = 1):
    """Triggers recompilation of key binaries from binaries, not source"""
    logger.info("\n\nRecompile %s ...\n\n" % os.getcwd())
    buildId = params.get("BUILD_ID")
    assert buildId != None, "params must contain BUILD_ID"
    targetFiles = config["files"]
    filesToRebuild = selectFiles(config, recompile = True)
    for f in filesToRebuild:
        artifacts = targetFiles[f]["artifacts"]
        for artifact in artifacts:
            artifactPath = getBinDir(buildId, artifact)
            logger.info("Removing artifact: %s" % artifactPath)
            if not os.path.isfile(artifactPath):
                logger.warn("Cannot remove %s (artifact not found in bin dir)" \
                        % artifact)
                continue
            try:
                os.remove(artifactPath)
            except (IOError, OSError) as e:
                logger.error("[%s] failed to remove artifact: %s" \
                        % (str(e), artifactPath))
                return ERROR_SYS_ERR #pylint: disable=E0602
    retCode = buildTargetFiles(config, params, args, \
            fileList = filesToRebuild, checkArtifacts = True, \
            ignoreParams = True, ignoreArgs = True, jobs = jobs)
    return retCode

def cleanpack(branch, config, params, args, jobs = 1):
    """Creates HY11 & HK11 builds from binaries"""
    logger.info("\n\nIn cleanpack ...\n\n")
    assert cleanpack_tz != None, "cleanpack module not available"
    chipset = params.get("CHIPSET")
    assert chipset != None, "params must contain CHIPSET"
    # TODO - consider adding logic to detect if previous build artifacts are
    # present and squash them to ensure that nothing improper gets packed into
    # the build
    retCode = 0
    for i in range(3):
        stepArgs = list(args) # copy original args so we don't overwrite them
        if i == 0 or i == 2:
            # first and last build are normal
            stepName = "build" if i == 0 else "pack"
        elif i == 1:
            # second build strips
            stepArgs.extend(CLEANPACK_ARGS)
            stepName = "strip"
        fileList = selectFiles(config, strip = True, firstBuild = (i == 0))
        # check artifacts only for first & third builds (i = 0 & i = 2)
        # 'strip' omits files that do not apply to cleanpack builds, but it is
        # entirely redundant as we have already explicitly selected our files
        retCode = buildTargetFiles(config, params, stepArgs, fileList, \
                checkArtifacts = (i != 1), ignoreParams = True, \
                ignoreArgs = True, jobs = jobs)
        if retCode != ERROR_OK: #pylint: disable=E0602
            logger.error("build failure detected in %s step" % stepName)
            return retCode
        if i == 0:
            retCode = copyOutput(TEMP_DIR)
            if retCode != ERROR_OK: #pylint: disable=E0602
                return retCode
    retCode = cleanpack_tz.cleanpack(branch, chipset, PACKAGE_ROOT)
    if retCode != ERROR_OK: #pylint: disable=E0602
        logger.error("Failed in cleanpack_tz")
        return retCode
    os.chdir(os.path.join(HY11_DIR, "trustzone_images"))
    retCode = recompileTargetFiles(config, params, args)
    if retCode != ERROR_OK: #pylint: disable=E0602
        logger.error("Failed to recompile HY11")
        return retCode
    os.chdir(os.path.join(HK11_DIR, "trustzone_images"))
    retCode = recompileTargetFiles(config, params, args)
    if retCode != ERROR_OK: #pylint: disable=E0602
        logger.error("Failed to recompile HK11")
        return retCode
    return ERROR_OK #pylint: disable=E0602

def copyOutput(dest):
    """Copies some essential files for cleanpack to HY11 & HK11 folders"""
    for copyTarget in CLEANPACK_COPY_TARGETS:
        srcPath = os.path.join(PACKAGE_ROOT, copyTarget)
        destPath = os.path.join(dest, copyTarget)
        if os.path.exists(destPath):
            try:
                if os.path.isdir(destPath):
                    shutil.rmtree(destPath)
                else:
                    os.remove(destPath)
            except (IOError, OSError) as e:
                logger.error("[%s] failed to remove existing dir: %s" \
                        % (str(e), destPath))
                return ERROR_SYS_ERR #pylint: disable=E0602
        logger.info("Copy %s -> %s" % (srcPath, destPath))
        try:
            if os.path.isdir(srcPath):
                shutil.copytree(srcPath, destPath, symlinks = True)
            else:
                shutil.copy2(srcPath, destPath)
        except (IOError, OSError) as e:
            logger.error("[%s] failed to copy %s -> %s" \
                    % (str(e), srcPath, destPath))
            return ERROR_SYS_ERR #pylint: disable=E0602
    return ERROR_OK #pylint: disable=E0602

def selectFiles(config, strip = False, recompile = False, firstBuild = True):
    """Determines which files to build based on the input arguments.
       Ignores disabled files."""
    targetFiles = config["files"]
    ret = []
    # use the target-specific file list for this target
    for f in targetFiles:
        fileMeta = targetFiles[f]
        if fileMeta["disable"]:
            continue # skip disabled files
        elif strip and fileMeta["strip"]:
            continue # omit stripped files
        elif (not firstBuild) and fileMeta["build-once"]:
            continue # don't build 'build-once' files after the first time
        elif recompile and not fileMeta["recompile"]:
            continue # skip files that should not be recompiled
        ret.append(f)
    return ret

# It is the caller's responsibility what files are passed in. If no file list is
# passed, all applicable files will be automatically selected from the current
# target's config. For features like 'strip', selectFiles() should be explicitly
# called by the calling function & have its result passed as 'fileList'.
def buildTargetFiles(config, params, args, fileList = None, \
        checkArtifacts = True, ignoreParams = False, ignoreArgs = False, \
        mapreport = False, testMode = False, jobs = 1):
    """Main build function"""
    # TODO - @redesign to reduce arguments & local vars
    #pylint: disable=R0913, R0914
    assert jobs > 0, "Must use at least 1 job"
    if jobs > 1:
        logger.info("Attempting to parallelize build with %d jobs" % jobs)
    retCode = ERROR_OK #pylint: disable=E0602
    if fileList == None:
        fileList = selectFiles(config)
    buildQueue = BuildQueue(fileList, config["files"])
    jobQueue = multiprocessing.Queue()
    completionQueue = multiprocessing.Queue()
    if jobs > buildQueue.filesRemaining:
        logger.info("Only %d files to build - limiting jobs from %d -> %d" \
                % (buildQueue.filesRemaining, jobs, buildQueue.filesRemaining))
        jobs = buildQueue.filesRemaining
    workers = []
    for _ in range(jobs):
        proc = multiprocessing.Process(target = buildWorker, args = \
                (jobQueue, completionQueue, config["files"], params, args, \
                checkArtifacts, ignoreParams, ignoreArgs, mapreport, testMode, \
                (jobs > 1)))
        proc.daemon = True # enable killing of subproceses via exit()
        workers.append(proc)
    # the scheduler populates this dictionary with each worker's info
    # including return status
    pinfo = {}
    scheduler(workers, buildQueue, jobQueue, completionQueue, pinfo)
    # Process worker results
    for proc in workers:
        pid = proc.ident
        rc = pinfo[pid]["retCode"]
        if rc == ERROR_WORKER_EXCEPTION: #pylint: disable=E0602
            e = pinfo[pid]["exception"]
            logger.error("Worker %d encountered exception:\n%s" % (pid, str(e)))
        elif rc == ERROR_INTERRUPTED: #pylint: disable=E0602
            logger.warn("Worker %d was interrupted" % pid)
            if retCode == ERROR_OK: #pylint: disable=E0602
                retCode = rc
        elif rc != ERROR_OK: #pylint: disable=E0602
            logger.error("Worker %d failed with error %s" % (pid, strerr(rc)))
            retCode = rc
    return retCode

def scheduler(workers, buildQueue, jobQueue, completionQueue, pinfo):
    """Handles scheduling of worker processes"""
    # TODO - @redesign to reduce number of branches
    #pylint: disable=R0912, R0914
    pendingJobs = len(workers)
    error = False
    eos = False
    timer = None
    stats = {
        "completed" : 0,
        "queued" : 0,
    }
    for worker in workers:
        worker.start()
        logger.debug("Started worker %d" % worker.ident)
    while pendingJobs > 0:
        while True:
            # dequeue all completed jobs to update the build queue
            try:
                workerRsp = completionQueue.get(timeout = DEQUEUE_RETRY_DELAY)
            except Queue.Empty:
                break
            workerInfo = pinfo.get(workerRsp.get("pid", -1), {})
            if workerRsp["type"] == WORKER_SUCCESS:
                logger.debug("Worker %d completed %s" \
                        % (workerRsp["pid"], workerRsp["target-file"]))
                buildQueue.markComplete(workerRsp["target-file"])
                workerInfo["completed"] = workerInfo.get("completed", [])
                workerInfo["completed"].append(workerRsp["target-file"])
                stats["completed"] += 1
                logger.debug("Files remaining in build queue: %d" \
                        % buildQueue.filesRemaining)
                if buildQueue.filesRemaining < pendingJobs:
                    # We no longer need all of the worker threads for the files
                    # we have left. Ramp them down now to reduce stop latency.
                    jobQueue.put(None)
            elif workerRsp["type"] == WORKER_EXITED:
                logger.debug("Worker %d stopped successfully" \
                        % workerRsp["pid"])
                pendingJobs -= 1
                workerInfo["retCode"] = workerRsp["retCode"]
            elif workerRsp["type"] == WORKER_FAILURE:
                if workerRsp["target-file"] == None:
                    when = "during setup"
                else:
                    when = "while building %s" % workerRsp["target-file"]
                logger.error(
                        "%s in worker %d %s - stopping build" \
                        % (strerr(workerRsp["retCode"]), \
                        workerRsp.get("pid", -1), when))
                pendingJobs -= 1
                buildQueue.stop()
                error = True
                workerInfo["retCode"] = workerRsp["retCode"]
            elif workerRsp["type"] == WORKER_EXCEPTION:
                logger.error("Exception in worker %d, stopping build" \
                        % workerRsp.get("pid", -1))
                pendingJobs -= 1
                buildQueue.stop()
                error = True
                workerInfo["exception"] = workerRsp["exception"]
                workerInfo["retCode"] = \
                        ERROR_WORKER_EXCEPTION #pylint: disable=E0602
            else:
                logger.error(
                        "Received unknown response of type %d from worker %d" \
                        % (workerRsp["type"], workerRsp["pid"]))
                buildQueue.stop()
                error = True
            pinfo[workerRsp["pid"]] = workerInfo
        # there should no longer be any worker response in the completion queue
        # so perform a sanity check to ensure that all of our expected workers
        # are still active
        activeWorkers = 0
        for worker in workers:
            if worker.is_alive():
                activeWorkers += 1
        if activeWorkers < pendingJobs:
            # it is possible that the latest worker notified us simultaneously
            # with this check and we just have not processed it yet. Wait 1
            # minute before reporting the error & killing the build.
            if timer != None and time.time() - timer > WORKER_WAIT_TIME:
                logger.error("Worker exited unexpectedly - aborting build")
                buildQueue.stop()
                error = True
            else:
                logger.debug("Worker terminated without notification")
                timer = time.time()
        else:
            # everything looks good so reset the timer
            timer = None
        if buildQueue.complete() and not eos:
            # add termination signals to the queue; we add an extra signal
            # since this thread will also ensure that the queue is flushed
            logger.debug("Signaling EOS")
            for _ in range(pendingJobs + 1):
                jobQueue.put(None)
            eos = True
#            if error:
#                logger.debug("flushing job queue")
#                while True:
#                    try:
#                        node = jobQueue.get(timeout = DEQUEUE_RETRY_DELAY)
#                    except Queue.Empty:
#                        break
#                    if node == None:
#                        break
        if error:
            logger.info("Terminating all workers")
            for worker in workers:
                logger.debug("Killing worker %d" % worker.ident)
                worker.terminate()
                workerInfo = pinfo.get(worker.ident, {})
                workerInfo["retCode"] = workerInfo.get("retCode", \
                        ERROR_INTERRUPTED) #pylint: disable=E0602
                pinfo[worker.ident] = workerInfo
            break
        try:
            node = buildQueue.get(timeout = 0)
        except Queue.Empty:
            logger.debug("no new files ready for build")
            logger.debug("queued = %d, completed = %d, blocked on deps = %d" \
                    % (stats["queued"], stats["completed"], \
                    buildQueue.filesRemaining))
            time.sleep(DEQUEUE_RETRY_DELAY)
            continue
        logger.debug("%s is ready to be built" % node.name)
        jobQueue.put(node)
        stats["queued"] += 1
    # Wait for other workers to complete & consolidate results
    for worker in workers:
        logger.debug("Waiting for worker %d to finish" % worker.ident)
        worker.join()
    logger.info("All %d jobs complete" % len(workers))

def buildWorker(jobQueue, completionQueue, fileMetadata, params, args, \
        checkArtifacts, ignoreParams, ignoreArgs, mapreport, testMode, \
        singleThreaded = True):
    """Exception-handling wrapper for the main worker function"""
    # TODO - @redesign to reduce number of arguments
    #pylint: disable=R0913
    try:
        retCode = builderLoop(jobQueue, completionQueue, fileMetadata, params, \
                args, checkArtifacts, ignoreParams, ignoreArgs, mapreport, \
                testMode, singleThreaded)
    except Exception as e: #pylint: disable=W0703
        traceback.print_exc()
        ret = {
            "type" : WORKER_EXCEPTION,
            "pid" : os.getpid(),
            "exception" : e,
        }
        completionQueue.put(dict(ret))
        return ERROR_UNKNOWN #pylint: disable=E0602
    return retCode

def concatLogs(file1, file2):  
    '''Function to concatenate build logs into the Logfile''' 

    try:
        with open(file2, 'a') as outfile:
            with open(file1) as infile:
                for lines in infile:
                    outfile.write(lines)
    except IOError as e:
        logger.error("I/O error({0}): {1}".format(e.errno, e.strerror))


def builderLoop(jobQueue, completionQueue, fileMetadata, params, args, \
        checkArtifacts, ignoreParams, ignoreArgs, mapreport, testMode, \
        singleThreaded = True):
    """Main build worker function"""
    # TODO - @redesign to reduce arguments, local vars & branches
    #pylint: disable=R0912, R0913, R0914
    ret = {
        "type" : WORKER_SUCCESS,
        "pid" : os.getpid(),
        "retCode" : ERROR_OK, #pylint: disable=E0602
        "target-file" : None,
    }
    # begin worker execution
    if params.get("BUILD_ID") == None:
        logger.error("params must contain BUILD_ID")
        ret["type"] = WORKER_FAILURE
        ret["retCode"] = ERROR_INVALID_ARG #pylint: disable=E0602
        completionQueue.put(dict(ret))
        return ret["retCode"]
    artifactsDir = getBinDir(params["BUILD_ID"])
    # despite the memory waste, we need a copy of the file dependency tree here
    # since our BuildQueue actively modifies the tree as dependencies are built
    # TODO - find a clean way to avoid recreating the DependencyTree object
    getdeps = lambda f, n = None: f["dependencies"]
    traversalList = BuildConfigParser.buildDictDependencyTree(fileMetadata, \
            getdeps, False, None).getTraversalList()
    depMap = {}
    for node in traversalList:
        depMap[node.name] = node
    try:
        existingArtifacts = set([ uri for uri in os.listdir(artifactsDir) \
                if os.path.isfile(os.path.join(artifactsDir, uri)) ])
    except OSError:
        logger.debug("%s not created yet" % artifactsDir)
        existingArtifacts = set([]) # directory does not exist yet
    while True:
        try:
            logger.debug("[%d] DEQUEUE from jobQueue starting" % ret["pid"])
            node = jobQueue.get(timeout = DEQUEUE_RETRY_DELAY)
        except Queue.Empty:
            logger.debug("[%d] jobQueue is empty!" % ret["pid"])
#            time.sleep(DEQUEUE_RETRY_DELAY)
            continue
        if node == None:
            # jobQueue has signaled termination
            logger.debug("[%d] received stop request" % ret["pid"])
            break
        logger.debug("[%d] dequeued '%s' from jobQueue" \
                % (ret["pid"], node.name))
        ret["target-file"] = node.name
        fileMeta = node.data
        logger.info("[%d] Building %s" % (ret["pid"], ret["target-file"]))
        if testMode and os.path.exists(artifactsDir):
            logger.debug("[%d] Removing %s" % (ret["pid"], artifactsDir))
            try:
                shutil.rmtree(artifactsDir)
            except (IOError, OSError) as e:
                logger.error( \
                        "[%d] Failed to remove artifacts dir in test mode: %s" \
                        % (ret["pid"], artifactsDir))
                ret["retCode"] = ERROR_SYS_ERR #pylint: disable=E0602
                break
            existingArtifacts = set([])
        fileParams = dict(params)
        fileArgs = list(args)
        if singleThreaded:
            # if we are parallelizing, force a single job
            fileArgs.extend(["-j", "1"])
        if not ignoreParams:
            # use file-specific params from XML if not explicitly suppressed
            fileParams.update(fileMeta["params"])
        argumentMap = fileMeta["arguments"]
        if not ignoreArgs:
            # use file-specific args from XML if not explicitly suppressed
            for arg in argumentMap:
                if singleThreaded and arg == "-j":
                    # do not allow setting job count if we are parallelizing
                    continue
                fileArgs.append(arg)
                val = argumentMap[arg]
                if len(val) > 0:
                    fileArgs.append(val)
        logger.debug("[%d] Params: %s" % (ret["pid"], ", ".join( \
                [ "%s=%s" % (key, fileParams[key]) for key in fileParams])))
        logger.debug("[%d] Args: %s" % (ret["pid"], ", ".join(fileArgs)))
        
        sconsLog = os.path.join(LOGFILE_ROOT, BUILD_LOG_PREFIX + ".txt")
        fullLog = os.path.join(LOGFILE_ROOT, UNIFIED_LOG + ".txt")

        if(os.path.isfile(sconsLog) and os.path.isfile(fullLog)):
            concatLogs(sconsLog, fullLog)

        ret["retCode"] = buildCmd(ret["target-file"], fileParams, fileArgs, \
                mapreportFiles = \
                list(fileMeta["mapreport"] if mapreport else []))
        if ret["retCode"] != ERROR_OK: #pylint: disable=E0602
            logger.error("[%d] error %s while building %s" \
                    % (ret["pid"], strerr(ret["retCode"]), ret["target-file"]))
            break
        expectedArtifacts = getExpectedArtifacts(ret["target-file"], \
                fileMetadata, dependencyList = \
                [ n.name for n in depMap[ret["target-file"]].dependencies ])
        if checkArtifacts and len(expectedArtifacts) > 0:
            try:
                artifactSet = set([ uri for uri in os.listdir(artifactsDir) \
                        if os.path.isfile(os.path.join(artifactsDir, uri)) ])
            except OSError as e:
                logger.debug(str(e))
                logger.error("[%d] Artifact output dir '%s' does not exist" \
                        % (ret["pid"], artifactsDir))
                ret["retCode"] = ERROR_BAD_PATH #pylint: disable=E0602
                break
            # Check for missing & extra artifacts. Note that the set
            # constructed above only contains valid files.
            newArtifacts = artifactSet.difference(existingArtifacts)
            # We diff against the full set instead of 'newArtifacts' since the
            # artifacts might already exist from a previous build.
            missing = expectedArtifacts.difference(artifactSet)
            extra = newArtifacts.difference(expectedArtifacts)
            expected = len(expectedArtifacts)
            logger.info("[%d] Found %d of %d expected artifacts for %s" \
                    % (ret["pid"], expected - len(missing) + len(extra), \
                    expected, ret["target-file"]))
            artifactsOk = True
            if len(missing) > 0:
                missingList = list(missing)
                missingList.sort()
                logger.error("[%d] Missing %s artifacts: %s" \
                        % (ret["pid"], ret["target-file"], \
                        ", ".join(missingList)))
                artifactsOk = False
            if len(extra) > 0:
                extraList = list(extra)
                extraList.sort()
                msg = "[%d] %s %s artifacts: %s" \
                        % (ret["pid"], \
                        "New" if PARALLELIZE_BUILD else "Extra", \
                        ret["target-file"], ", ".join(extraList))
                if FORBID_UNDOCUMENTED_ARTIFACTS:
                    logger.error(msg)
                    artifactsOk = False
                else:
                    logger.warn(msg)
            if not artifactsOk:
                ret["retCode"] = ERROR_INVALID_ARTIFACT #pylint: disable=E0602
                break
            existingArtifacts = artifactSet
        logger.debug("[%d] %s built successfully" \
                % (ret["pid"], ret["target-file"]))
        completionQueue.put(dict(ret))
    if ret["retCode"] != ERROR_OK: #pylint: disable=E0602
        # terminate build for all workers on error
        ret["type"] = WORKER_FAILURE
        completionQueue.put(dict(ret))
    else:
        ret["type"] = WORKER_EXITED
        completionQueue.put(dict(ret))
    return ret["retCode"]

def getExpectedArtifacts(filename, fileMetadata, dependencyList = None):
    """Returns the expected artifacts for a file (current + dependencies)"""
    dependencyList = dependencyList or []
    if len(dependencyList) == 0:
        logger.debug("%s has no listed dependencies" % filename)
    else:
        logger.debug("%s has listed dependencies: %s" \
                % (filename, ", ".join(dependencyList)))
    artifacts = set(fileMetadata[filename]["artifacts"])
    for dep in dependencyList:
        artifacts.update(set(fileMetadata[dep]["artifacts"]))
    return artifacts

def getBinDir(buildId, artifact = None):
    """Gets the bin output folder for the current target"""
    buildDir = os.path.join(os.getcwd(), BUILD_PATH)
    if artifact == None:
        return os.path.join(buildDir, 'bin', buildId)
    return os.path.join(buildDir, 'bin', buildId, artifact)

class PassthroughOptionParser(optparse.OptionParser):
    """Extends OptionParser to support pass-through of unknown args to SCons"""
    def _process_args(self, largs, rargs, values):
        originalArgs = list(rargs)
        while rargs:
            try:
                logV("Remaining args: %s" % ", ".join(rargs))
                optparse.OptionParser._process_args(self, largs, rargs, values)
            except (optparse.BadOptionError, optparse.AmbiguousOptionError) \
                    as e:
                logV("parse error on '%s'" % e.opt_str)
                # The OptionParser may not return the raw argument (eg '-j4'
                # will be declared invalid and returned as '-j'), so we have to
                # determine which original argument caused the problem & add it
                # to largs instead of e.opt_str. We are guaranteed that
                # _process_args has removed at least 1 item from rargs UNLESS
                # we had a special '=' argument where the value was added as an
                # additional rarg (eg --jobs=4). We check for this corner case
                # first, then decrement if it does not appear to be the case.
                failureIndex = len(originalArgs) - len(rargs) - 1
                paramValue = ""
                try:
                    # doubles as an implicit
                    # "if failureIndex + 1 < len(originalArgs)"
                    badArg = originalArgs[failureIndex + 1]
                    if badArg[0] == "-":
                        # doubles as an implicit "if '=' in badArg"
                        paramValue = "=".join(badArg.split("=")[1:])
                except IndexError:
                    badArg = originalArgs[failureIndex]
                logV("paramValue = '%s'; rargs = [ %s ]" \
                        % (paramValue, ", ".join(rargs)))
                # paramValue will only match rargs[0] if that arg is (a) empty
                # or (b) the value of an invalid <key>=<value> param
                if len(rargs) > 0 and rargs[0] == paramValue:
                    logV("Pop redundant arg '%s' from args list" \
                            % rargs.pop(0))
                else:
                    badArg = originalArgs[failureIndex]
                logger.debug("passthrough arg: %s (parsed as %s)" \
                        % (badArg, e.opt_str))
                largs.append(badArg)

def parseArguments():
    """Basic argument definition & parsing"""
    parser = PassthroughOptionParser()
    parser.add_option("-b", "--branch", \
            action = "store", \
            type = "string", \
            dest = "branch", \
            help = "Build this branch")
    parser.add_option("--cfg", "--config-file", \
            action = "store", \
            type = "string", \
            dest = "config_file", \
            default = CONFIG_FILE, \
            help = "Specify the build config xml file")
    parser.add_option("-c", "--clean", \
            action = "store_true", \
            dest = "clean", \
            default = False, \
            help = "Clean the build ONLY")
    parser.add_option("--cleanpack", \
            action = "store_true", \
            dest = "clean_pack", \
            default = False, \
            help="Clean and Pack")
    parser.add_option("--cnb", "--clean-and-build", \
            action = "store_true", \
            dest = "clean_build", \
            default = False, \
            help = "Clean and Build")
    parser.add_option("--cbt", "--custom-build-targets", \
            action = "store", \
            type = "string", \
            dest = "custom_build_targets", \
            #pylint: disable=C0301
            help = "Request build of the given SCons target(s) / alias(es), even if they don't appear in build_config.xml")
    parser.add_option("-d", "--default", \
            action = "store_true", \
            default = False, \
            dest = "use_default_target", \
            help = "Build only the branch's default chipset")
    parser.add_option("--detect-branch", \
            action = "store_true", \
            default = False, \
            dest = "detect_branch", \
            help = "Try to detect current branch, print, & exit")
    parser.add_option("--dumpenv", \
            action = "store_true", \
            default = False, \
            dest = "dump_environment", \
            help = "Dump the environment to a shell script")
    parser.add_option("--enable_cc", \
                      action="store_true", \
                      dest="code_coverage", \
                      default=False, \
                      #pylint: disable=C0301
                      help="Build a code coverage enabled image.This is applicable for tz tz_with_test and tztestexec image only for now.")    
    parser.add_option("--fast", \
            action = "store_true", \
            default = False,
            dest = "fast_build", \
            help = "Suppress scripted prompts & delays")
    parser.add_option("--list-targets", \
            action = "store_true", \
            default = False, \
            dest = "list_targets", \
            help = "List supported targets for the current branch & exit")
    parser.add_option("-m", "--map-report", \
            action = "store_true", \
            dest = "map_report", \
            default = DEFAULT_MAPREPORT, \
            help = "Mapreport")
    parser.add_option("--parallelize", \
            action = "store_true", \
            dest = "parallelize_build", \
            default = False, \
            #pylint: disable=C0301
            help = "Attempt to speed up build by building independent files in parallel with -j 1")
    parser.add_option("-r", "--recompile", \
            action = "store_true", \
            dest = "recompile_only", \
            default = False, \
            help = "Recompile only")
    parser.add_option("--sequential", \
            action = "store_true", \
            dest = "sequential_build", \
            default = False, \
            #pylint: disable=C0301
            help = "Force single-threaded build execution where one file is built at a time & SCons decides the number of jobs for each file.")
    parser.add_option("--test-mode", \
            action = "store_true", \
            dest = "test_mode", \
            default = False, \
            #pylint: disable=C0301
            help = "Remove the current target's entire bin dir before building each file in order to verify that dependencies & artifacts are exactly as expected.")
    parser.add_option("-v", "--verbose", \
            action = "store_true", \
            dest = "verbose", \
            default = False, \
            help = "Verbose output")
    return parser.parse_args()

def parseExtraArguments(args, branchConfig):
    """Performs additional parsing of command line args like requested files"""
    ret = {
        "args" : [],
        "files" : set([]), # converted to a list before returning
        "params" : {},
    }
    # build a list of all <file>s from all targets to validate what is
    # considered a 'file' vs a pass-through argument. Acceptable files will be
    # validated on each target once targets are determined, but this parsing
    # can include CHIPSET=<target>, so we cannot perform this validation yet
    allFiles = set([])
    for target in branchConfig["targets"]:
        targetFiles = set(branchConfig["targets"][target]["files"].keys())
        allFiles.update(targetFiles)
    for arg in args:
        if len(arg.strip()) == 0:
            logger.warn("Received empty arg '%s'" % arg)
            continue
        logV("Parse arg '%s" % arg)
        if arg in allFiles:
            logger.debug("Found supported file '%s' in command line args" % arg)
            if arg in ret["files"]:
                logger.critical("file '%s' is provided twice" % arg)
                sys.exit(ERROR_INVALID_ARG) #pylint: disable=E0602
            ret["files"].add(arg)
        elif "=" in arg and arg[0] != "-":
            # param notation ignores any argument prefixed by '-' or '--' since
            # these are likely passthrough arguments
            paramParts = arg.split("=")
            key = paramParts[0]
            value = "=".join(paramParts[1:])
            logger.debug("Found param %s = %s in command line args" \
                    % (key, value))
            existingParam = ret["params"].get(key)
            if existingParam != None:
                logger.critical("param '%s' is provided twice" % key)
                sys.exit(ERROR_INVALID_ARG) #pylint: disable=E0602
            ret["params"][key] = value
        else:
            logger.debug( \
                    "Passing '%s' from command line directly to build script" \
                    % arg)
            ret["args"].append(arg)
    ret["files"] = list(ret["files"]) # convert set to list before returning
    return ret

def addCustomBuildTargets(options, branchConfig, buildInput):
    """Adds custom build targets to the list of command line files. Creates
       dummy references for the build targets (as if they had entries within
       build_config.xml) if they are not already present. Also enforces strict
       dependency in the order that custom build targets are given. Applies to
       all chipsets, although only the specified chipset(s) will be built."""
    if not options.custom_build_targets:
        return
    logger.debug("Custom build targets: %s" % options.custom_build_targets)
    customTargets = options.custom_build_targets.split()
    for chipset in branchConfig["targets"]:
        chipsetConfig = branchConfig["targets"][chipset]
        for i in range(len(customTargets)):
            buildTarget = customTargets[i]
            if buildTarget in chipsetConfig["files"]:
                continue # an entry is already present for this chipset
            dummyEntry = BuildConfigParser.fileTemplate()
            # make this entry explicitly dependent on all previous entries to
            # ensure that we never violate an implicit dependency
            dummyEntry["dependencies"] = customTargets[:i]
            chipsetConfig["files"][buildTarget] = dummyEntry.dict()
    buildInput["files"].extend([ buildTarget \
            for buildTarget in options.custom_build_targets.split() \
            if buildTarget not in buildInput["files"] ])

def printParams(params, title = None, exclude = None):
    """Prints the given params (KEY=VALUE)"""
    exclude = exclude or []
    if title == None:
        title = "Parameters:"
    else:
        title = "%s parameters:" % title.capitalize()
    logger.info(title)
    keys = params.keys()
    keys.sort()
    for key in keys:
        if key in exclude:
            continue
        logger.info("%s: %s" % (key, params[key]))
    sys.stdout.flush()

def getSConsDir():
    """Returns the current SCons dir"""
    return os.path.join(os.getcwd(), TOOLS_SCONS_PATH)

def printDiagnosticInfo(branch, targets, options, buildInput, \
        branchWarning = False):
    """Prints essential build info before beginning build"""
    logger.info("")
    logger.info("Diagnostic info")
    logger.info(SEPARATOR)
    logger.info("Platform: %s" % sys.platform)
    logger.info("Python version: %s" % sys.version)
    logger.info("Current directory: %s" % os.getcwd())
    logger.info("Build root: %s" % BUILD_ROOT)
    logger.info("SCons root: %s" % getSConsDir())
    logger.info("OS version : %s" % (platform.system()+" "+platform.release()))
    logger.info("Host Name : %s" % socket.gethostname())
    logger.info("Build Command Line: %s" % " ".join(sys.argv))
    logger.info(SEPARATOR)
    logger.info("Command line options:")
    logger.info("Clean: %s" % str(options.clean))
    logger.info("Clean and build: %s" % str(options.clean_build))
    logger.info("Clean and pack: %s" % str(options.clean_pack))
    logger.info("Use default target: %s" % str(options.use_default_target))
    logger.info("Mapreport: %s" % str(options.map_report))
    logger.info("Verbose: %s" % str(options.verbose))
    logger.info(SEPARATOR)
    if len(buildInput["files"]) > 0:
        logger.info("Command line files:")
        logger.info(" ".join(buildInput["files"]))
        logger.info(SEPARATOR)
    if len(buildInput["params"]) > 0:
        printParams(buildInput["params"], "command line", \
                exclude = [ "CHIPSET" ])
        logger.info(SEPARATOR)
    if len(buildInput["args"]) > 0:
        logger.info("Additional command line arguments:")
        logger.info(" ".join(buildInput["args"]))
        logger.info(SEPARATOR)
    logger.info("BRANCH:\t\t%s" % branch)
    targetCount = len(targets)
    logger.info("%d %s:\t%s" % (targetCount, \
            "CHIPSET" if targetCount == 1 else "CHIPSETS", \
            ", ".join(targets)))
    logger.info(SEPARATOR)
    if branchWarning:
        logger.info("")
        logger.info("Auto-detected branch '%s'" % branch)
        logger.info("If this is not correct, please explicitly give -b <branch>") #pylint: disable=C0301
    if targetCount > 1:
        logger.info("")
        logger.info("Multiple chipsets (%d) will be built for %s" \
                % (targetCount, branch))
    logger.info("")
    logger.info("Preparing to build...")
    logger.info("")
    sys.stdout.flush()

def logV(msg):
    """verbose module-level logging"""
    logger.log(VERBOSE, msg)

def delete_BuildProductFile():
    """" Function used to delete BuildProducts.txt file if build fails"""
    os.chdir(PACKAGE_ROOT)
    if os.path.isfile('BuildProducts.txt'):
        os.remove("BuildProducts.txt")

def signal_handler(sig, frame): #pylint: disable=W0613
    """Handles <Ctrl> + C"""
    logger.warn("Received <Ctrl> + C - killing all processes")
    sys.exit(ERROR_INTERRUPTED) #pylint: disable=E0602
    
def setCodeCoverageEnvironment():
    """Set-up environment for code coverage enabled build"""
    cctBinPath=os.environ["CCBIN"]
    os.environ["BULLSEYE_PATH"] = os.environ.get("LLVMBIN")
    os.environ["LLVMBIN"]=cctBinPath
    os.environ["COVFILE"] = os.path.join(BUILD_ROOT,COV_FILE_NAME)
    os.environ["COVERR"] = os.path.join(BUILD_ROOT, COV_LOG_FILE)
    DEFAULT_ARGS.extend(["tzbsp_cc=1","tzbsp_no_pimem=1", "tzbsp_quadmb=1"])
    enableCodeCovCmd=str(os.path.join(cctBinPath,'cov01')) + " -1"
    call(enableCodeCovCmd)

if os.path.exists(UNIFIED_LOG+".txt"):
    renameLog(LOGFILE_ROOT, UNIFIED_LOG)
handler = logging.FileHandler(UNIFIED_LOG+".txt") 
handler.setLevel(logging.DEBUG)
logger.addHandler(handler)

BuildConfigParser.logger.addHandler(handler)

if cleanpack_tz != None:
    cleanpack_tz.logger.addHandler(handler)

if __name__ == '__main__':
    signal.signal(signal.SIGINT, signal_handler)
    try:
        EXIT_CODE = buildAll()
    except:
        delete_BuildProductFile()
        raise
    if EXIT_CODE != 0:
        delete_BuildProductFile()

    sys.exit(EXIT_CODE)

