# ===============================================================================
#
#  Copyright (c) 2013-2016 Qualcomm Technologies, Inc.
#  All Rights Reserved.
#  Confidential and Proprietary - Qualcomm Technologies, Inc.
#
# ===============================================================================
"""

@author: coryf

Entry point for Sectools Builder. Supports both command line execution
as well as execution from SCons/Make build files.

"""

import os
import sys

SECTOOLS_DIR = os.path.dirname(os.path.realpath(__file__))
sys.path.append(SECTOOLS_DIR)

from sectools.common.utils import c_path
from sectools.common.utils.c_logging import logger
from sectools.features.isc.builder import sectools_builder_core
from sectools.features.isc.builder.sectools_builder_core import SectoolsBuilderCore
from sectools.common.utils.c_base import CoreOptionParser

# Name & version of the tool
SECTOOLS_BUILDER_TOOL_NAME = 'Sectools Builder'
SECTOOLS_BUILDER_TOOL_VERSION = 'v3.0'
__version__ = SECTOOLS_BUILDER_TOOL_NAME + ' ' + SECTOOLS_BUILDER_TOOL_VERSION

DEFAULT_CONFIG_FILE = c_path.join(SECTOOLS_DIR, 'config', 'integration', 'secimage.xml')
DEFAULT_POLICY_FILE = c_path.join(SECTOOLS_DIR, 'config', 'integration', 'sectools_policy.xml')

# Key of SCons environment variable
INPUT = "INPUT"

BUILDER_FUNC_HANDLER = "builder_function_handler"

TRUE_STRINGS = ["1", "t", "true"]
FALSE_STRINGS = ["0", "f", "false"]


def convert_to_bool(val):
    if isinstance(val, str):
        if val.lower().strip() in TRUE_STRINGS:
            return True
        elif val.lower().strip() in FALSE_STRINGS:
            return False
        else:
            return val
    else:
        return val


def validate_bool(val, var_name, error_list):
    if not (val is None or isinstance(val, bool) or (isinstance(val, str) and val.lower().strip() in TRUE_STRINGS + FALSE_STRINGS)):
        error_list.append("Provided {0} value \"{1}\" is invalid.".format(var_name, val))


class BuilderInputPackage(object):

    def __init__(self,
                 execute_sectools,
                 environment,
                 source,
                 target_base_dir,
                 sectools_install_base_dir,
                 install_file_name,
                 build_policy_id,
                 additional_secimage_policy_ids,
                 sign_id,
                 app_id,
                 jtag_id,
                 soc_hw_version,
                 soc_vers,
                 signer,
                 qti_sign,
                 uie_qti,
                 image_entry,
                 relocatable,
                 config,
                 pilsplitter_target_base_dir,
                 hash_table_algo,
                 signature_digest_algo,
                 build_policy=None,
                 target_image_type_filter=None):

        self.execute_sectools = execute_sectools
        self.environment = environment
        self.source = c_path.normalize(source)
        self.target_base_dir = c_path.normalize(target_base_dir)
        self.sectools_install_base_dir = c_path.normalize(sectools_install_base_dir)
        self.install_file_name = install_file_name
        self.build_policy = build_policy
        self.build_policy_id = build_policy_id
        self.additional_secimage_policy_ids = additional_secimage_policy_ids
        self.sign_id = sign_id
        self.app_id = app_id
        self.jtag_id = jtag_id
        self.soc_hw_version = soc_hw_version
        self.soc_vers = soc_vers
        self.signer = signer
        self.qti_sign = convert_to_bool(qti_sign)
        self.uie_qti = uie_qti
        self.image_entry = image_entry
        self.relocatable = convert_to_bool(relocatable)
        self.config = c_path.normalize(config)
        self.policy_file = DEFAULT_POLICY_FILE
        self.pilsplitter_target_base_dir = pilsplitter_target_base_dir
        self.hash_table_algo = hash_table_algo
        self.signature_digest_algo = signature_digest_algo
        self.target_image_type_filter = target_image_type_filter

    def __str__(self):

        def to_string(var, default=None):
            if var is None and default is None:
                return "None"
            elif var is None and default is not None:
                return default
            elif isinstance(var, str):
                return var
            else:
                return str(var)

        return "~~~~~~~~~~~~~~~BuilderInputPackage~~~~~~~~~~~~~~~" + "\n" + \
               "execute_sectools: " + to_string(self.execute_sectools) + "\n" + \
               "source: " + to_string(self.source) + "\n" + \
               "target_base_dir: " + to_string(self.target_base_dir) + "\n" + \
               "pilsplitter_target_base_dir: " + to_string(self.pilsplitter_target_base_dir) + "\n" + \
               "sectools_install_base_dir: " + to_string(self.sectools_install_base_dir, "Not set. Installation of files will be skipped") + "\n" + \
               "install_file_name: " + to_string(self.install_file_name, os.path.split(self.source)[1]) + "\n" + \
               "build_policy_id: " + to_string(self.build_policy_id) + "\n" + \
               "additional_secimage_policy_ids: " + to_string(None if not self.additional_secimage_policy_ids else ", ".join(self.additional_secimage_policy_ids)) + "\n" + \
               "sign_id: " + to_string(self.sign_id) + "\n" + \
               "app_id: " + to_string(self.app_id, "Not being used") + "\n" + \
               "jtag_id: " + to_string(self.jtag_id, "Using default value 0x00000000") + "\n" + \
               "soc_hw_version: " + to_string(self.soc_hw_version, "Not set. Using jtag_id " + (self.jtag_id if self.jtag_id else "0x00000000")) + "\n" + \
               "soc_vers: " + to_string(self.soc_vers) + "\n" + \
               "signer: " + to_string(self.signer) + "\n" + \
               "qti_sign: " + to_string(self.qti_sign) + "\n" + \
               "uie_qti: " + to_string(self.uie_qti) + "\n" + \
               "image_entry: " + to_string(self.image_entry, "Using value from config file") + "\n" + \
               "relocatable: " + to_string(self.relocatable, "Using value from config file") + "\n" + \
               "config: " + to_string(self.config) + "\n" + \
               "policy_file: " + to_string(self.policy_file) + "\n" + \
               "build_policy:\n" + to_string(self.build_policy, "BuildPolicy object is not yet created") + "\n" + \
               "target_image_type_filter: " + to_string(sectools_builder_core.target_name_map[self.target_image_type_filter], "Targets will not be filtered") + "\n" + \
               "hash_table_algo: " + to_string(self.hash_table_algo) + "\n" + \
               "signature_digest_algo: " + to_string(self.signature_digest_algo) + "\n" + \
               "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"


def build(is_scons_build, environment, **kwargs):
    # builder was called from SCons
    if is_scons_build:
        # get verbosity level from environment
        verbosity = environment.get("SECTOOLS_BUILDER_VERBOSITY", "info")
        if verbosity == "z":
            logger.verbosity = logger.WARN
        elif "zz" in verbosity:
            logger.verbosity = logger.ERROR
        elif verbosity == "info":
            logger.verbosity = logger.INFO
        else:
            logger.verbosity = logger.DEBUG
        init_logging = True
        args = get_env_args(environment, init_logging, **kwargs)

        logger.debug(SECTOOLS_BUILDER_TOOL_NAME + " was called from a build file")
    # builder was called from the command line
    else:
        args = get_command_line_args()

        logger.debug(SECTOOLS_BUILDER_TOOL_NAME + " was called from the command line")

        # if args.build_policy_id is None try to get build policy from environment
        build_policy_id = args.build_policy_id
        if build_policy_id is None:
            logger.debug("A build policy was not provided as an argument. Attempting to retrieve build policy from environment...")
            build_policy_id = get_env_build_policy(environment)

        if build_policy_id is not None:
            build_policy_id = build_policy_id.lower()

        # attempt to retrieve secimage policies from environment
        enabled_env_secimage_policies = get_env_secimage_policies(environment)

        # package all inputs and pass them to the builder
        logger.debug("Completed argument parsing")
        logger.debug("Wrapping parsed inputs into a package")

        args = BuilderInputPackage(True,
                                   environment,
                                   args.source,
                                   args.target_base_dir,
                                   args.sectools_install_base_dir,
                                   args.install_file_name,
                                   build_policy_id,
                                   enabled_env_secimage_policies,
                                   args.sign_id,
                                   args.app_id,
                                   args.jtag_id,
                                   args.soc_hw_version,
                                   args.soc_vers,
                                   args.signer,
                                   args.qti_sign,
                                   args.uie_qti,
                                   args.image_entry,
                                   args.relocatable,
                                   args.config,
                                   args.pilsplitter_target_base_dir,
                                   args.hash_table_algo,
                                   args.signature_digest_algo)

    return SectoolsBuilderCore(args).build()


def validate_args(arguments, err_strings, init_logging):

    # configure logger to log to filesystem
    if init_logging:
        if arguments.target_base_dir:
            folder = c_path.normalize(arguments.target_base_dir)
            try:
                c_path.create_dir(folder)
            except Exception as e:
                raise RuntimeError('Unable to create directory for logging: ' + folder + '\n' + 'Error: ' + str(e))
            if arguments.sign_id:
                logging_file_name = SECTOOLS_BUILDER_TOOL_NAME.replace(" ", "_") + "_" + arguments.sign_id
            else:
                logging_file_name = SECTOOLS_BUILDER_TOOL_NAME.replace(" ", "_")
            logger.enable_file_logging(logging_file_name, num_logs=1, log_dir=folder)
        else:
            raise RuntimeError(err_strings[0])

    err = []
    # validate that the required fields were provided
    if not arguments.target_base_dir:
        err.append(err_strings[0])
    if not arguments.source:
        err.append(err_strings[1])
    if not arguments.sign_id:
        err.append(err_strings[2])
    if arguments.jtag_id and arguments.soc_hw_version:
        err.append(err_strings[3])
    sectools_builder_core.validate_file(arguments.config, err_strings[4], err)
    validate_bool(arguments.qti_sign, err_strings[5], err)
    validate_bool(arguments.relocatable, err_strings[6], err)
    if hasattr(arguments, "target_image_type_filter") and arguments.target_image_type_filter is not None and arguments.target_image_type_filter not in [sectools_builder_core.INTEGRITY, sectools_builder_core.SIGN, sectools_builder_core.ENCRYPT, sectools_builder_core.SIGN_AND_ENCRYPT]:
        err.append(err_strings[7])

    err_string = ""
    for e in err:
        err_string += "\n" + e

    return err_string


class BuilderParser(CoreOptionParser):
    """Parser for command line arguments supported by Sectools Builder."""

    _LIST_TAG = 'LIST'

    @property
    def c_description(self):
        """(str) Returns the description of the program."""
        return SECTOOLS_BUILDER_TOOL_NAME + " executes Sectools Secimage and installs the output files."

    @property
    def c_version(self):
        """(str) Returns the version of the program."""
        return SECTOOLS_BUILDER_TOOL_VERSION

    def c_add_options(self):
        """Adds the command line args supported by sectools builder."""
        self.add_option("-i", "--source", dest="source", metavar="<file>", help="REQUIRED. Source file to sign.")
        self.add_option("-t", "--target_base_dir", metavar="<directory>", help="REQUIRED. Target base directory to store signed image outputs.")
        self.add_option("--pilsplitter_target_base_dir", metavar="<directory>", default=None, help="Base directory for pilsplit. Pilsplit will not be performed if not specified.")
        self.add_option("-o", "--sectools_install_base_dir", metavar="<directory>", default=None, help="Base directory for installation. No installation will be performed if not specified.")
        self.add_option("--install_file_name", metavar="<file>", default=None, help="File name for installation. Original filename will be used if not specified.")
        self.add_option("--build_policy_id", metavar="<build_policy_id>", default=None, help="The ID of the desired build policy to apply. This ID must match a build policy ID specified in sectools_policy.xml.")
        self.add_option("-g", "--sign_id", metavar="<sign_id>", help="REQUIRED. Sign ID to execute.")
        self.add_option("--app_id", metavar="<app_id>", default=None, help="APP_ID to sign TZapps image.")
        self.add_option("--jtag_id", metavar="<jtag_id>", default=None, help="JTAG_ID to sign image. Cannot be used with --soc_hw_version option. JTAG_ID=0x00000000 will be used if neither JTAG_ID nor SOC_HW_VERSION is specified.")
        self.add_option("--soc_hw_version", metavar="<soc_hw_version>", default=None, help="SOC_HW_VERSION to sign image. Cannot be used with --jtag_id option. JTAG_ID=0x00000000 will be used if neither JTAG_ID nor SOC_HW_VERSION is specified.")
        self.add_option("--soc_vers", metavar="<soc_vers>", default=None, help="Value to override config file's soc_vers value.")
        self.add_option("--signer", metavar="<signer>", default=None, help="Sectools signer to use for signing.")
        self.add_option("--qti_sign", action="store_true", default=False, help="Flag to sign image as QTI. If not provided, defaults to FALSE")
        self.add_option("--uie_qti", metavar="<uie_qti>", default=None, help="Value to override config file's uie_capability value.")
        self.add_option("--image_entry", metavar="<image_entry>", default=None, help="Value to override config file's image_entry value. If not provided, config value will not be overridden")
        self.add_option("--relocatable", metavar="<relocatable>", default=None, help="Value to override config file's relocatable value. If not provided, config value will not be overridden")
        self.add_option("--config", metavar="<file>", dest="config", default=DEFAULT_CONFIG_FILE, help="Path to the secimage config file. When not provided, defaults to: " + DEFAULT_CONFIG_FILE)
        self.add_option("--hash_table_algo", metavar="<hash_table_algo>", default=None, help="SHA algorithm to use for generating and validating the segment hash table.")
        self.add_option("--signature_digest_algo", metavar="<signature_digest_algo>", default=None, help="SHA algorithm to use for generating and validating the signature digest.")

    def c_validate(self):
        """Validates the command line args provided by the user."""

        # configure verbosity level
        if self.parsed_args.quiet == 1:
            logger.verbosity = logger.WARN
        elif self.parsed_args.quiet > 1:
            logger.verbosity = logger.ERROR
        elif self.parsed_args.verbose == 0:
            logger.verbosity = logger.INFO
        else:
            logger.verbosity = logger.DEBUG

        err_strings = ["--target_base_dir (-t) is a required option and must be provided.",
                       "--source (-i) is a required option and must be provided.",
                       "--sign_id (-g) is a required option and must be provided.",
                       "--jtag_id and --soc_hw_version are mutually exclusive options and cannot both be provided. Provide neither or provide only one.",
                       "config",
                       "qti_sign",
                       "relocatable"]

        init_logging = True
        err_message = validate_args(self.parsed_args, err_strings, init_logging)

        if err_message:
            logger.error(err_message)
            self.error(err_message)


def get_env_build_policy(environment):
    # get the supported build policies from the policy file
    supported_build_policies = sectools_builder_core.BuildPolicy.get_supported_build_policies(DEFAULT_POLICY_FILE)
    enabled_env_build_policies = []
    # get the enabled build policy from the environment using the ids from the supported build policies
    for policy in supported_build_policies:
        if environment.get("USES_SEC_POLICY_" + policy.upper()):
            logger.debug("Found build policy environment variable {0}".format("USES_SEC_POLICY_" + policy.upper()))
            enabled_env_build_policies.append(policy)
        elif environment.get("SEC_POLICY_" + policy.upper()):
            logger.debug("Found build policy environment variable {0}".format("SEC_POLICY_" + policy.upper()))
            enabled_env_build_policies.append(policy)
        elif environment.get(policy.upper()):
            logger.debug("Found build policy environment variable {0}".format(policy.upper()))
            enabled_env_build_policies.append(policy)
        elif environment.get(policy):
            logger.debug("Found build policy environment variable {0}".format(policy))
            enabled_env_build_policies.append(policy)
    if not enabled_env_build_policies:
        logger.info("No environmental build policy variable was enabled nor was one provided as a command line argument. Sectools will not be executed.")
        logger.info("If execution of Sectools is desired, a build policy must be set in the environment or passed as a command line argument. Supported build policies are: {0}".format(", ".join(supported_build_policies).upper()))
        return None
    elif len(enabled_env_build_policies) > 1:
        error_message = "The following environmental build policy variables are enabled: {0}. Only one build policy can be enabled at a time.".format(", ".join(enabled_env_build_policies).upper())
        logger.error(error_message)
        raise RuntimeError(error_message)
    else:
        logger.debug("Successfully retrieved build policy {0} from environment".format(enabled_env_build_policies[0].upper()))
        return enabled_env_build_policies[0]


def get_env_secimage_policies(environment):
    logger.debug("Attempting to get additional secimage policies from environment...")
    # get the supported secimage policies from the policy file
    supported_secimage_policies = sectools_builder_core.BuildPolicy.get_supported_secimage_policies(DEFAULT_POLICY_FILE)
    enabled_env_secimage_policies = []
    # get the enabled secimage polices from the environment using the ids from the supported secimage policies
    for policy in supported_secimage_policies:
        if environment.get("USES_SEC_POLICY_" + policy.upper()):
            logger.debug("Found secimage policy environment variable {0}".format("USES_SEC_POLICY_" + policy.upper()))
            enabled_env_secimage_policies.append(policy)
        elif environment.get("SEC_POLICY_" + policy.upper()):
            logger.debug("Found secimage policy environment variable {0}".format("SEC_POLICY_" + policy.upper()))
            enabled_env_secimage_policies.append(policy)
        elif environment.get(policy.upper()):
            logger.debug("Found secimage policy environment variable {0}".format(policy.upper()))
            enabled_env_secimage_policies.append(policy)
        elif environment.get(policy):
            logger.debug("Found secimage policy environment variable {0}".format(policy))
            enabled_env_secimage_policies.append(policy)
    if enabled_env_secimage_policies:
        if len(enabled_env_secimage_policies) > 1:
            logger.debug("Successfully retrieved secimage policies {0} from environment".format(", ".join(enabled_env_secimage_policies).upper()))
        else:
            logger.debug("Successfully retrieved secimage policy {0} from environment".format(", ".join(enabled_env_secimage_policies).upper()))
    else:
        logger.debug("Did not find any additional secimage policies")
    return enabled_env_secimage_policies


def get_command_line_args():
    return BuilderParser(sys.argv).parsed_args


"""
Main function. Entry point into Sectools Builder when calling it from the command line.
"""
if __name__ == "__main__":
    build(False, os.environ)


""" ~~~~~~~~~~~~~~~~ Below is SCons implementation of argument parsing & processing ~~~~~~~~~~~~~~~~ """
def resolve(environment, value):
    if value:
        return environment.subst(value)
    else:
        return value


def get_env_args(environment, init_logging, **kwargs):

    for key, val in kwargs.items():
        kwargs[key] = resolve(environment, val)
    kwargs["build_policy_id"] = get_env_build_policy(environment)
    kwargs["additional_secimage_policy_ids"] = get_env_secimage_policies(environment)

    arg_package = BuilderInputPackage(False, environment, **kwargs)

    err_strings = ["target_base_dir is a required value and must be provided.",
                   "source is a required value and must be provided.",
                   "sign_id is a required value and must be provided",
                   "jtag_id and soc_hw_version are mutually exclusive values and cannot both be provided. Provide neither or provide only one.",
                   "config",
                   "qti_sign",
                   "relocatable",
                   "Provided target_image_type_filter value is invalid."]

    err_message = validate_args(arg_package, err_strings, init_logging)

    if err_message:
        logger.error(err_message)
        raise RuntimeError(err_message)
    else:
        logger.debug("Completed argument parsing")
        logger.debug("Wrapping parsed inputs into a package")
        return arg_package

"""
    Main function: entry point into Sectools Builder when calling it from SCons.\n
    Only environment, target_base_dir, source, sign_id, jtag_id, soc_hw_version,
    app_id, sectools_install_base_dir, install_file_name, config, pilsplitter_target_base_dir,
    image_entry, relocatable, soc_vers, signer, qti_sign, uie_qti, target_image_type_filter,
    hash_table_algo, & signature_digest_algo are utilized by builder. The remaining
    parameters are ignored and are only present to preserve backwards compatibility
    with build scripts using previous versions of Sectools Builder. target_image_type_filter
    allows target filtering so only images of the specified type will be present in
    the returned target list. This has no effect on which files are actually generated.
    That is still controlled by build policy and additional secimage policies.

"""
def register_build_method(environment,
                          target_base_dir,
                          source,
                          sign_id,
                          jtag_id=None,
                          soc_hw_version=None,
                          app_id=None,
                          sectools_install_base_dir=None,
                          install_file_name=None,
                          msmid=None,
                          msmid_jtagid_dict=None,
                          msm_jtag_mapping_file=None,
                          disable_featureflags=None,
                          config=DEFAULT_CONFIG_FILE,
                          policy_file=None,
                          pilsplitter_target_base_dir=None,
                          pilsplitter_path=None,
                          pilsplitter_featureflag=None,
                          image_entry=None,
                          relocatable=None,
                          soc_vers=None,
                          signer=None,
                          qti_sign=False,
                          uie_qti=None,
                          target_image_type_filter=None,
                          hash_table_algo=None,
                          signature_digest_algo=None):

    kwargs = {"target_base_dir": target_base_dir,
              "source": str(source[0]),
              "sign_id": sign_id,
              "jtag_id": jtag_id,
              "soc_hw_version": soc_hw_version,
              "app_id": app_id,
              "sectools_install_base_dir": sectools_install_base_dir,
              "install_file_name": install_file_name,
              "config": config,
              "pilsplitter_target_base_dir": pilsplitter_target_base_dir,
              "image_entry": image_entry,
              "relocatable": relocatable,
              "soc_vers": soc_vers,
              "signer": signer,
              "qti_sign": qti_sign,
              "uie_qti": uie_qti,
              "target_image_type_filter": target_image_type_filter,
              "hash_table_algo": hash_table_algo,
              "signature_digest_algo": signature_digest_algo
              }
    return build(True, environment, **kwargs)


def action(target, source, env):
    # targets will be determined again by SectoolsBuilderCore so there is no need to pass along target.
    # source is already packaged in args.
    args = env.get(INPUT)
    args.execute_sectools = True
    SectoolsBuilderCore(args).build()


def get_unsigned_install_path(env,
                              install_base_dir,
                              subfolder=None,
                              featureflags=None,
                              disable_featureflags=None,
                              policy_file=None):
    """
    Only environment, install_base_dir and subfolder are utilized by builder.
    The remaining parameters are ignored and are only present to preserve backwards compatibility
    with build scripts using previous versions of Sectools Builder.
    """
    if get_env_build_policy(env):
        if subfolder:
            install_base_dir = os.path.join(install_base_dir, subfolder)
        else:
            install_base_dir = os.path.join(install_base_dir, "unsigned")
    return install_base_dir


# image_type values that can be passed to register_build_method
def image_type_integrity(env):
    return sectools_builder_core.INTEGRITY


def image_type_sign(env):
    return sectools_builder_core.SIGN


def image_type_encrypt(env):
    return sectools_builder_core.ENCRYPT


def image_type_sign_and_encrypt(env):
    return sectools_builder_core.SIGN_AND_ENCRYPT


def exists(environment):
    return environment.Detect('sectools_builder')


def generate(environment):
    environment.AddMethod(get_unsigned_install_path, "SectoolGetUnsignedInstallPath")
    environment.AddMethod(image_type_integrity, "SectoolImageTypeIntegrity")
    environment.AddMethod(image_type_sign, "SectoolImageTypeSign")
    environment.AddMethod(image_type_encrypt, "SectoolImageTypeEncrypt")
    environment.AddMethod(image_type_sign_and_encrypt, "SectoolImageTypeSignEncrypt")
    environment.AddMethod(register_build_method, "SectoolBuilder")
    builder_action = environment.GetBuilderAction(action)
    builder = environment.Builder(action=builder_action)
    environment.Append(BUILDERS={BUILDER_FUNC_HANDLER: builder})
