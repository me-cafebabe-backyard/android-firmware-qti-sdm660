# ----------------------------------------------------------------------------
# Copyright (c) 2016 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ----------------------------------------------------------------------------

import fnmatch
import os.path
import re
from hashlib import sha256

FILE_EXCEPT = getattr(__builtins__, 'FileNotFoundError', IOError)


def ammend_file_path(file_path):
    if '/' in file_path and '/' != os.path.sep:
        file_path = file_path.replace('/', os.path.sep)
    elif '\\' in file_path and '\\' != os.path.sep:
        file_path = file_path.replace('\\', os.path.sep)
    return file_path 

class ConfigReadWriter:
    HASH_SEP = '::'
    SYSCALL_SEP = ';;'


    def __init__(self, cfg_name, base_directory):
        if not os.path.exists(cfg_name):
            self.error(['Mink Audit: Config file "' + cfg_name + '" not found'], cfg_name)
            exit(1)
        else:
            self.cfg_file = cfg_name
        base_directory = os.path.normpath(base_directory)
        self.cc = InterfaceAudit(base_directory)
        self.sa = SyscallAudit(base_directory)
        self.ir = InterfaceReader(base_directory)

    def read_and_dispatch(self):
        with open(self.cfg_file, 'r') as in_file:
            for line in iter(in_file):
                line = line.strip()
                if line == '':
                    continue
                elif line.find(self.HASH_SEP) != -1:
                    self.cc.compare(line)
                elif line.find(self.SYSCALL_SEP) != -1:
                    self.sa.compare(''.join(line.split()))
        return(self.print_errors())

    def find_and_update_interfaces(self):
        self.gather_known_paths()
        self.add_interface(self.ir.get_processed_interface_file_list(self.ir.get_interfaces_from_directory()))

    def gather_known_paths(self):
        basename_to_path = {}
        with open(self.cfg_file, 'r') as in_file:
            for line in iter(in_file):
                line = line.strip()
                if line != '':
                    split_line = line.split(self.HASH_SEP)
                    if len(split_line) == 1:
                        split_line = line.split(self.SYSCALL_SEP)
                    if len(split_line) > 1:
                        basename_to_path[os.path.basename(split_line[0])] = split_line[0]
        self.ir.add_known_paths(basename_to_path)

    def add_interface(self, file_path):
        """
        adds new interface file and sha256 hash of file to config file in name:hash format
        """
        if type(file_path) is tuple or type(file_path) is list:  # if receiving list of files, add one by one
            for f in file_path:
                self.add_interface(f)
        else:  # add individual file
            self.remove_interface(file_path)  # updating, so remove existing entry if exists
            try:
                file_path = os.path.normpath(ammend_file_path(file_path))
                with open(self.cfg_file, 'a+') as out_file:
                    hash_str = self.cc.get_hash_str(file_path)
                    if hash_str is not None:
                        start_idx = hash_str.find('trustzone_images')
                        if start_idx != -1:
                            out_file.write(hash_str[hash_str.find('trustzone_images')+17:])
                        else:
                            out_file.write(hash_str)
            except FILE_EXCEPT:
                self.error(['Unable to read file "' + file_path + '", please check the path/permissions'],
                           'Add Mink Interface')

    def remove_interface(self, file_path):
        """
        removes line pertaining to given file name from config file
        """
        if type(file_path) is tuple or type(file_path) is list:  # if receiving list of files, remove one by one
            for f in file_path:
                self.remove_interface(f)
        else:  # remove individual file
            try:
                file_path = os.path.normpath(ammend_file_path(file_path))
                start_idx = file_path.find('trustzone_images')
                if start_idx != -1:
                    file_path = file_path[file_path.find('trustzone_images')+17:]
                with open(self.cfg_file, 'r+') as out_file:
                    content = out_file.readlines()
                    out_file.seek(0)
                    for line in content:
                        line = ammend_file_path(line)
                        if line.find(file_path) != 0:
                            out_file.write(line)
                    out_file.truncate()
            except FILE_EXCEPT:
                self.error(['Unable to read file "' + file_path + '", please check the path/permissions'],
                           'Remove Mink Interface')

    def print_errors(self):
        """
        Print error messages and exit with error code.  Messages are tagged to
        mark this as a build failure and to identify the script that is
        generating the error.
        """
        if self.cc.error_description:
            self.cc.error_description = self.cc.ERROR_DESCRIPTION_HEADER + ['    ' + err for err in
                                                                            self.cc.error_description]
            self.error(self.cc.error_description, 'Interface Audit')
        if self.sa.error_description:
            self.sa.error_description = self.sa.ERROR_DESCRIPTION_HEADER + ['    ' + err for err in
                                                                            self.sa.error_description]
            self.error(self.sa.error_description, 'Syscall Audit')
        if self.cc.error_description or self.sa.error_description:
            return False
        return True

    @staticmethod
    def error(descriptions, filename=""):
        """
        :param descriptions: list of strings of error output (each on new line)
        :param filename: string describing what failed
        """
        print("ERROR: When running %s ..." % filename)
        for line in descriptions:
            print("ERROR: " + line)


class InterfaceReader:
    INCLUDE_REGEX = '#include "(\w+.h)"'
    INVOKE_STR = '_DEFINE_INVOKE('
    FILENAME_FILTER = 'I*.h'

    def __init__(self, base_directory):
        self.invokers = {}
        self.files_to_hash = set()
        self.found_paths = {}
        self.BASE_D = base_directory
        self.SEARCH_D = os.path.join(self.BASE_D, 'core', 'securemsm')

    def add_known_paths(self, paths):
        self.found_paths.update(paths)

    def get_interfaces_from_directory(self, search_dir=None):
        """
        Get list of interface files by file name pattern (I*.h)
        walk directory, add file path of each I*.h file
        """
        if search_dir is None:
            search_dir = self.SEARCH_D
        return [os.path.join(dirpath.split(self.BASE_D, 1)[1], f)
                for dirpath, dirnames, files in os.walk(search_dir)
                for f in fnmatch.filter(files, self.FILENAME_FILTER)]

    def get_processed_interface_file_list(self, files_to_parse):
        """
        Find files with macro definition pattern (*_DEFINE_INVOKE)
        Find each #included file (TODO search once for all unknowns instead of searching for each)
        Return list of these files
        """
        for file_name in files_to_parse:
            file_name = os.path.normpath(file_name)
            if file_name[0] == '\\' or file_name[0] == '/':
                file_name = file_name[1:]
            with open(os.path.join(self.BASE_D, file_name), 'r') as in_file:
                lines = in_file.read()
                if lines.find(self.INVOKE_STR) != -1:
                    self.invokers[file_name] = []
                    self.files_to_hash.update([file_name])
                    matches = re.findall(self.INCLUDE_REGEX, lines)
                    if matches:
                        direct = os.path.dirname(file_name)
                        matches = [os.path.join(direct, match) for match in matches]
                        matches = [match if os.path.exists(os.path.join(self.BASE_D, match)) else self.find_file(
                            os.path.basename(match), self.SEARCH_D) for match in matches]
                        self.invokers[file_name] = matches
                        self.files_to_hash.update(matches)
        return list(self.files_to_hash)

    def find_file(self, name, path):
        """
        finds all files of given name in a given file-tree path
        (https://stackoverflow.com/questions/1724693/find-a-file-in-python)
        """
        if name in self.found_paths:
            return self.found_paths[name]
        result = []
        for root, dirs, files in os.walk(path):
            if name in files:
                result.append(os.path.join(root, name))
        if len(result) == 1:  # FOUND MATCH
            print 'Found ' + name + ' at ' + result[0].split(self.BASE_D, 1)[1]
            self.found_paths[name] = result[0].split(self.BASE_D, 1)[1]
            return result[0].split(self.BASE_D, 1)[1]
        elif len(result) == 0:  # DID NOT FIND MATCH
            print 'Did not find ' + name + ' in ' + path
            return ''
        else:  # FOUND MULTIPLE MATCHES
            print 'Found multiple files named ' + name + ' in ' + path + ': ' + str(result)
            # use the first one
            self.found_paths[name] = result[0].split(self.BASE_D, 1)[1]
            return result[0].split(self.BASE_D, 1)[1]
        # else error


class InterfaceAudit:
    ERROR_DESCRIPTION_HEADER = ['Interface changes detected:',
                                'Changes to QSEE TA interfaces must be reviewed for compatibility '
                                'and security concerns. Please send an email to security.minkapi ',
                                'and/or ssg.eco.tz and describe the required change.'
                                'Also include a link to the code review.']

    def __init__(self, base_directory):
        self.error_description = []
        self.BASE_D = base_directory

    def compare(self, line):
        known_file = line.split(ConfigReadWriter.HASH_SEP)
        if not self.check_hash(ammend_file_path(known_file[0]), known_file[1]):
            self.error_description.append(' ! Hash mismatch for "%s"' % known_file[0])

    def check_hash(self, file_path, known_hash):
        """
        performs sha256 hash on given file and compares to reference hash
        Returns true if hashes are equal
        """
        try:
            with open(os.path.join(self.BASE_D, file_path), 'r') as in_file:
                return known_hash == sha256(in_file.read()).hexdigest()
        except FILE_EXCEPT:
            self.error_description.append(' - Missing file "%s"' % file_path)
            return True  # don't add a file mismatch

    def get_hash_str(self, file_path):
        """ return string in path::hash format """
        try:
            with open(os.path.join(self.BASE_D, file_path), 'r') as in_file:
                return file_path + ConfigReadWriter.HASH_SEP + sha256(in_file.read()).hexdigest() + '\n'
        except FILE_EXCEPT:
            self.error_description.append(' - Missing file "%s"' % file_path)


class SyscallAudit:
    """
    This script scans QSEE's syscall handler for additions or removals
    of system calls.

    We have a moratorium on adding system calls.  When new kernel functionality
    needs to be exposed to secure apps, a Mink service should be defined.

    Removal of existing system calls can break binary compatibility with
    applications. We need to carefully manage such changes to synchronize them
    with major version changes in QSEE.
    """

    def __init__(self, base_directory):
        self.error_description = []
        self.BASE_D = base_directory

    SYSCALL_FUNCTION_HEADER = 'qsee_handle_common_syscalls'
    ERROR_DESCRIPTION_HEADER = ['Changes detected in %s:' % SYSCALL_FUNCTION_HEADER,
                                'Changes to QSEE TA interfaces must be reviewed for compatibility '
                                'and security concerns. Please send an email to security.minkapi ',
                                'and/or ssg.eco.tz and describe the required change.'
                                'Also include a link to the code review.']

    def compare(self, line):
        split_line = line.split(ConfigReadWriter.SYSCALL_SEP)
        file_name = ammend_file_path(split_line[0])
        # This array represents the set of syscalls that should not set off a warning.
        golden_syscalls = filter(None, split_line[1].split(','))  # filter for trailing/extra commas in cfg file
        self.verify_syscalls(file_name, golden_syscalls)

    @staticmethod
    def extract_cases(lines):
        """
        Return a list of all values names in `case` statements in source file-content string.
        """
        cases = []
        for line in lines:
            m = re.match(r'^[ ]*case[ ]+([^:]*?) *:', line)
            if m is not None:
                cases.append(m.group(1))
        return cases

    def extract_syscall_handler(self, f):
        handler_lines = []
        while True:  # These 3 lines replace 'for line in header:'
            line = f.readline()  # This way does not rely on the python for loop iteration
            if not line:
                break  # And 2.7 won't throw "ValueError: Mixing iterations and read methods would lose data"
            if self.SYSCALL_FUNCTION_HEADER in line:  # find function header
                while 'default:' not in line:  # gather switch case lines (RELIES ON DEFAULT BEING LAST)
                    if line.strip() != '':  # skip whitespace lines
                        if '/*' in line:  # skip non-nested multiline comments
                            while '*/' not in line:
                                line = f.readline()
                        elif '//' in line:  # skip single/same line comments
                            handler_lines.append(line[:line.find('//')])
                        else:
                            handler_lines.append(line)
                    line = f.readline()
                return handler_lines
        return handler_lines

    def verify_syscalls(self, src, gold):
        """
        Check whether the syscalls implemented in `handler_src` match the
        golden list.
        :param src: source file containing syscall switch case statements
        :param gold: list of known syscall defs to check against
        """
        try:
            with open(os.path.join(self.BASE_D, src)) as src_lines:
                syscalls = self.extract_cases(self.extract_syscall_handler(src_lines))
        except FILE_EXCEPT:
            self.error_description.append('File "%s" not found.' % src)
            return
        syscalls.sort()
        gold.sort()
        diffs = self.diff_lists(gold, syscalls)
        if len(diffs) == 0:
            return
        self.error_description.append('In %s:' % src)
        self.error_description.extend([" %s %s" % diff for diff in diffs])

    @staticmethod
    def diff_lists(a, b):
        """Diff two sorted lists. Returns list of pairs:
       ('-', entry) : `entry` was present in A, not B
       ('+', entry) : `entry` was present in B, not A"""
        diffs = []
        bi = 0
        ai = 0
        while ai < len(a) or bi < len(b):
            if ai < len(a) and (bi >= len(b) or b[bi] > a[ai]):
                diffs.append(('-', a[ai]))
                ai += 1
            elif bi < len(b) and (ai >= len(a) or a[ai] > b[bi]):
                diffs.append(('+', b[bi]))
                bi += 1
            else:
                ai += 1
                bi += 1
        return diffs


class TestRunner:
    @staticmethod
    def assert_eq(a, b):
        if a != b:
            raise Exception('Assertion failed:\nA: %s\nB: %s\n' % (a, b))

    #def __init__(self):
    #    cc = InterfaceAudit()
    #    sa = SyscallAudit()

    def test_diff_lists(self):
        # Test diff_lists
        self.assert_eq([], SyscallAudit.diff_lists([], []))
        self.assert_eq([], SyscallAudit.diff_lists([1, 2, 3], [1, 2, 3]))
        self.assert_eq([('-', 1)], SyscallAudit.diff_lists([1], []))
        self.assert_eq([('+', 1)], SyscallAudit.diff_lists([], [1]))
        self.assert_eq([('+', 2), ('+', 3), ('-', 4), ('-', 5), ('+', 7)],
                       SyscallAudit.diff_lists([1, 4, 5, 6], [1, 2, 3, 6, 7]))

    def test_extract_cases(self):
        self.assert_eq(['1', '2'], SyscallAudit.extract_cases(['// Example',
                                                               '   case   1: ',
                                                               '   case   2 : ']))
 
