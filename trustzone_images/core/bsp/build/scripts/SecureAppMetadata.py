#!/usr/bin/env python
# Copyright (c) 2019 Qualcomm Technologies, Inc.  All Rights Reserved.
# Qualcomm Technologies Proprietary and Confidential.

"""
This module contains python functions used by the SCons build system.

Currently, there is only one exported function, generate_metadata.
generate_metadata is used to implement the AddSecureAppMetadata SCons function
available in SConscript files under the qsapps directory.  generate_metadata adds
metadata about the app to the app binary.

This module includes a self test based on the python UnitTest framework.
To run the self test, execute "python SecureAppMetadata.py" from the command
line.  The self test needs to be run in a TZ build tree.  (The code searches the
build tree to get numbers for ID strings associated with privilege and service names.)
"""

import copy
import operator
import os
import re
import sys
import types
import unittest
import ast

#-------------------------------------------------------------------------------
#  Globals
#-------------------------------------------------------------------------------

# The default set of privilege IDs.  The IDs will be mapped to values
# once the values are known.  Notable (but not complete) excludes are:
# HwFuse, I2C, SPI, OEMBuf, IntMask, PVC, TransNSAddr and ResetTimer.

_kDefaultPrivilegeIds = {
    'AppMessage',
    'CipherAES128',
    'CipherAES256',
    'CipherTripleDES',
    'Crypto',
    'DataCache',
    'DeviceId',
    'HashNone',
    'HashSHA1',
    'HashSHA256',
    'HmacSHA1',
    'HmacSHA256',
    'Listener',
    'NSMem',
    'PRNGSource',
    'Sync',
    'SecureChannel',
    'SharedBuffer',
	'DebugPolicySource',
}

# The directories, relative to the build root, that contains the .h
# files that define class ids.

_kClassIdDirs = ['trustzone_images/core/securemsm/trustzone/qsee/include',
                 'trustzone_images/core/securemsm/trustzone/qsapps',
                 'trustzone_images/apps/securemsm/trustzone/qsapps',
                ]

# Marker string for applications that can be loaded in unprotected memory.

_kMarker1 = '\0p+s}-#Pxh7Z!<+`'

# Marker string for applications that can be loaded in protected memory.

_kMarker2 = '\0obL$`P*8L)~s3L}'

# Maps strings, e.g. "I2C", to class IDs.

_classIdMap = None

# The default privilege set (numbers).  This is the translation to numbers
# of the elements in the _kDefaultPrivilegeIds set.

_defaultPrivileges = None

_metadataHandlers = None

is_protected_memory = True;

#-------------------------------------------------------------------------------
#  _searchTree
#-------------------------------------------------------------------------------

def _searchTree(target):

    # Search up the directory hierarchy until we find the target directory
    # (or path).

    start = os.getcwd();
    while start:
        path = os.path.join(start, target)

        if os.path.isdir(path):
            return path

        # Go up one directory.  If we're at the root of the
        # file system, break out.

        next = os.path.dirname(start)
        if next == start:
            break;
        start = next

    return None

#-------------------------------------------------------------------------------
#  _isClassDefFile
#-------------------------------------------------------------------------------

def _isClassDefFile(path):

    # Looking only for file names that match C*.h and don't match C*_open.h.

    name = os.path.basename(path)

    if not re.match('^C.*\.h', name):
        return False

    if re.match('^C.*_open\.h', name):
        return False

    if not os.path.isfile(path):
        return False

    return True

#-------------------------------------------------------------------------------
#  _extractIds
#-------------------------------------------------------------------------------

def _extractIds(path):

    # Looking for lines that match something like this:
    #
    #   #define CPVC_UID UINT32_C(14)
    #
    # Some older files have entries that look like this:
    #
    #   #define CNSMem_UID ((uint32_t) 15)
    #
    # A hexadecimal value as a UID is also supported, like this;
    #
    #   #define CPVC_UID UINT32_C(0x0000ACDC)
    #

    idmap = {}

    re1 = re.compile(r'^\s*#\s*define\s+C(\w+)_UID\s+')
    re2 = re.compile(r'_UID\s+(UINT32_C\(|\(\(uint32_t\))\s*([xX0-9a-fA-F]+)\s*\)')

    with open(path) as f:
        for line in f:
            m = re1.match(line)

            if m:
                n= re2.search(line)

                # TODO: error checking to see if there are duplicate id values?

                if n:
                    id = m.group(1).lower()
                    value = int(n.group(2), 0)
                    idmap[id] = value

    return idmap

#-------------------------------------------------------------------------------
#  _dumpClassMapById
#-------------------------------------------------------------------------------

def _dumpClassMapById():

    _initGlobalData()

    header = "=" * 80
    print header
    print "Class map by id (%d ids)" % ( len(_classIdMap))
    print header

    max = 0;
    for id in _classIdMap:
        if len(id) > max:
            max = len(id)

    formatString = "%%-%d.%ds %%6d" % ( max, max )
    for id in sorted( _classIdMap.keys()):
        print formatString % ( id, _classIdMap[id] )
    print ""

#-------------------------------------------------------------------------------
#  _dumpClassMapByValue
#-------------------------------------------------------------------------------

def _dumpClassMapByValue():

    _initGlobalData()

    revmap = {}
    for id in _classIdMap:
        revmap[_classIdMap[id]] = id;

    header = "=" * 80
    print header
    print "Class map by value (%d values)" % ( len(revmap))
    print header

    for value in sorted( revmap.keys()):
        print "%-6d %s" % ( value, revmap[value] )
    print ""

#-------------------------------------------------------------------------------
#  _initGlobalData
#-------------------------------------------------------------------------------

def _initGlobalData():

    global _defaultPrivileges
    global _classIdMap
    global _kDefaultPrivilegeIds
    global _kClassIdDirs
    global _metadataHandlers

   # Metadata field handlers.
   #    Each field name includes:
   #        - single letter abbreviation
   #        - processing function
   #        - default value if not specified
    _metadataHandlers = {
        'privileges':    ('p', _gen_class_set_string, set(['default'])),
        'services':      ('s', _gen_class_set_string, None),
        'appName':       ('n', lambda val: _check_str(r'.{1,31}', val), None),
        'UUID':          ('u', _encode_uuid, None),
        'objectLimit':   ('o', lambda val: _get_non_negative(val), None),
        'memoryType':    ('m', lambda val: _get_memory_type(val), 'protected'),
        'acceptBufSize': ('b', lambda val: _get_accept_buf_size(val), 4096),
        'legacy_sandbox':('e', lambda val: _check_boolean(val), None),
        'multiSession':  ('l', lambda val: _get_multi_session(val), 'true'),
        'properties':    ('r', lambda val: _get_properties(val), None),
        'version':       ('v', lambda val: _check_str(r'.{1,15}', val), '1.0'),
        'description':   ('d', lambda val: _get_description(val), None),
    }


    if _classIdMap:
        return

    # Get all of the class IDs.  Create the _classIdMap.

    _classIdMap = {}
    for rel in _kClassIdDirs:
        root = _searchTree(rel)
        if not root:
            raise Exception('Class ID directory %s not found.  Are you in the build tree?' % ( rel ))

        for dirName, subdirList, fileList in os.walk(root):

            for fname in fileList:

                # Check if this file is likely to hold IDL ids.

                path = os.path.join(dirName, fname)
                if not _isClassDefFile(path):
                    continue

                idmap = _extractIds(path)

                # Add the ids we just found to the global id map.
                # Do some error checking along the way.

                for key in idmap:

                    for key2, value in _classIdMap.items():

                        # The key is duplicate.  This is OK as long as the value is the same in both cases.

                        if key == key2:
                            if idmap[key] != value:
                                raise Exception('Duplicate values for class id %s (%d and %d).' % ( key, value, idmap[key] ))
                            else:
                                continue

                        #  The value is in both maps with a different key.  This is an error.

                        if idmap[key] == value:
                            raise Exception('Duplicate definitions for value %d (%s and %s).' % ( value, key, key2 ))

                    # No errors?  Add it.

                    _classIdMap[key] = idmap[key]

    # Create the default privilege set.

    _defaultPrivileges = _gen_class_set(_kDefaultPrivilegeIds)

#-------------------------------------------------------------------------------
#  generate_metadata
#-------------------------------------------------------------------------------

def extractField(data, field):
    global is_protected_memory
    _initGlobalData()

    global metadata_current_field
    metadata_current_field = field
    if field in _metadataHandlers:
        func = _metadataHandlers[field][1]
        # Fetch the data for the given field if it exists, otherwise use the
        # default.
        if field in data:
            value = data[field]
        else:
            value = _metadataHandlers[field][2]

        # If we have a value, process it now.  If no value exists, such as the
        # case where there is no default, then return the value which is None
        if value != None:
            s = func(value)
        else:
            s = value
        return s
    else:
        for valid_name in _metadataHandlers:
            if valid_name.lower()[:3] == field.lower()[:3]:
                raise Exception('Invalid metadata field name "%s" - should be "%s"' %
                                 (field, valid_name))

        valid_names = ', '.join(sorted(_metadataHandlers))
        raise Exception('Invalid metadata field name "%s" - should be one of: %s' %
                        (field, valid_names))

def generate_metadata(data):
    """
    Turns a set of program attributes in human readable form into a
    string parsed by the mink subsystem.

    Args:

        There is one required argument, md (metadata).  The md argument
        contains program attributes in a human readable form.  md is a
        dictionary that contains the following fields:

        md = {
          'privileges':  <iterable of string ids>,
          'services':    <iterable of string ids>,
          'appName':     <string containing 1-31 characters>
          'UUID':        <string containing 1-32 hex digits>
          'objectLimit': <non-negative number>
          'memoryType':  <Protected|Unprotected>,
        }

        Description of each of the fields:

            privileges:  Iterable of strings corresponding to class IDs or
                         services IDs.

                         There are some pseudo IDs that correspond to a
                         set of IDs.  There is currently only one pseudo ID,
                         'default'.  'default' contains a minimal set of sensible
                         privileges.  There may be more pseudo IDs in the future,
                         e.g. 'crypto'.

                         The ID fields are are the same as the corresponding
                         define for the class ID, minus the leading 'C' and
                         trailing '_UID'.  The ID for the CI2C_UID is 'I2C';
                         the ID for the CDeviceID_UID is 'DeviceID', etc.

                         If the privileges field is ommitted, it will
                         behave as if 'privileges': {'default'} is passed
                         in.

            services:    Iterable of strings corresponding to class IDs of services.
                         It's the set of IDs of services that the app exports.
                         Other apps requesting access to the service will need
                         to add the same ID to its list of privileges.

            appName:     A string of 1 to 31 characters.

            UUID:        A UUID in cannonical format (8-4-4-4-12), for example:

                             12345678-1234-1234-1234-123456789abc

                         The string is 32 hex digits and uses 4 hyphens for
                         a total string length of 36 characters.

            objectLimit: A non-negative integer.

            memoryType:  The string 'Protected' or 'Unprotected'.

                         If the privileges field is ommitted, it will
                         behave as if 'memoryType': 'Protected' is passed
                         in.

        None of the fields is required.  If a field is present, the name
        must be exactly as above, including the case.

        The IDs used in the privileges and services fields are case independent -
        'DEVICEID', 'deviceid', and 'DeviceId' are all the same ID.

        Likewise, the value for memoryType, either 'Protected' or 'Unprotected',
        is case independent.

    Examples:

        md = {
            'appName':     'SampleApp',
            'privileges':  ['default','I2C'],
            'services':    ['OEMUnwrapKeys'],
            'UUID':        '12345678-9abc-def0-1234-56789abcdef0',
            'objectLimit': 10,
            'memoryType':  'Protected',
        }

        md = {
            'appName':     'SampleApp2',
            'privileges':  ['I2C'],
        }

    Returns:

        A string that is only meaningful to the mink subsystem.  It's basically the same
        information that's in the input metadata but in a more easily parseable, although
        more cryptic, format.  Some sample values:

            p=2b;s=3c;n=SampleApp;u=78563412bc9af0de123456789abcdef0;o=10

            p=2b;n=SampleApp2

    Raises:

        The base level Exception class is the only exception raised by this function.

        This function tries to do as much validation as possible.  Some conditions
        that will raise an Exception:

            1) If the input metadata has an attribute that is not recognized.
            2) If a field has a value that is not of the correct type.
            2) If a field has a value that is not in range.
            3) If any ID in the privileges or services field is not recognized.
            4) Other conditions.

    """

    global is_protected_memory
    _initGlobalData()

    metadata = {}

    # If no privileges have been specified then give the app the default
    # privileges.
    #
    # "By default, applications are loaded into PIMEM, which is backed by DDR
    # but employs encryption to protect against physical attacks."
    #
    # Add the default privileges to the input md object.  Create a copy
    # because it's bad practice to change the user's input data.

    if (not 'privileges' in data) or (not 'memoryType' in data) or \
       (not 'acceptBufSize' in data):
        data = copy.copy(data)
        if (not 'privileges' in data):
            data['privileges'] = _metadataHandlers['privileges'][2]
        if (not 'memoryType' in data):
            data['memoryType'] = _metadataHandlers['memoryType'][2]
        if (not 'acceptBufSize' in data):
            data['acceptBufSize'] = _metadataHandlers['acceptBufSize'][2]

    # Process the metadata.
    for field in data:
        # Buffer size not added to metadata string for now
        if field == 'acceptBufSize':
           continue

        if field in _metadataHandlers:
            abbr = _metadataHandlers[field][0]
            s = extractField(data, field)
            if s == None:
                continue
            if abbr in metadata:
                raise Exception('Field "%s" appears multiple times.' % ( field ))
            metadata[abbr] = s
        else:
            for valid_name in _metadataHandlers:
                if valid_name.lower()[:3] == field.lower()[:3]:
                    raise Exception('Invalid metadata field name "%s" - should be "%s"' %
                                     (field, valid_name))

            valid_names = ', '.join(sorted(_metadataHandlers))
            raise Exception('Invalid metadata field name "%s" - should be one of: %s' %
                            (field, valid_names))

    # Concatenate the result for each metadata field into one big string.

    output_values = ['%s=%s' % (abbr, metadata[abbr]) for abbr in sorted(metadata.keys())]

    str = ';'.join(output_values)

    if is_protected_memory:
        str += _kMarker2;
    else:
        str += _kMarker1;

    return str

#-------------------------------------------------------------------------------
#  _gen_class_set
#-------------------------------------------------------------------------------

def _gen_class_set(idset):
    """
    Returns a set of class numbers
    """
    global metadata_current_field
    global _classIdMap
    global _defaultPrivileges

    values = set()
    for id in idset:
        #  Identifier - alphanumeric beginning with a non-digit.
        classId = _check_str(r'[a-zA-Z_][a-zA-Z_0-9]*', id)
        key = classId.lower()

        if key == 'default':
            values.update(_defaultPrivileges)
        elif key in _classIdMap:
            classNum = _classIdMap[key]
            values.add(classNum)
        else:
            raise Exception('Invalid metadata class id: %s' % (id))

    return values

#-------------------------------------------------------------------------------
#  _hex_str
#-------------------------------------------------------------------------------

def _hex_str(val):
    return '%x' % (val)

#-------------------------------------------------------------------------------
#  _encode_id_set
#-------------------------------------------------------------------------------

def _encode_id_set(iterable):
    """Encode numeric IDs as a metadata ID set value"""
    s = ''
    # The ID represented by the first bit in the next mask digit (if any)
    mask_pos = 0
    # Current value for the next mask digit to be emitted.  When non-zero,
    # we can assume that we are in mask mode (following a ':').
    mask_digit = 0

    for id in sorted(set(iterable)):

        # Each ID may be emitted as a hex number or as a mask bit.  We
        # estimate the "cost" of each in terms of bytes emitted.  The "cost"
        # of using a mask is not known entirely at this point, since
        # subsequent IDs might benefit from mask encoding, so we apply a
        # small bias toward masks.

        id_text = _hex_str(id)
        num_cost = len(id_text) + (1 if mask_digit else -1)
        mask_cost = (id - mask_pos) // 4

        if s == '' or mask_cost > num_cost:
            # Output id as a hex number.
            if mask_digit:
                s += _hex_str(mask_digit)
            if s != '':
                s += ','
            s += id_text
            mask_pos = id + 1
            mask_digit = 0              # not in a mask

        else:
            # Add id as a mask bit.
            if mask_digit == 0:
               s += ':'
            while id >= mask_pos + 4:
               s += _hex_str(mask_digit)
               mask_digit = 0
               mask_pos += 4
            mask_digit |= 1 << (id - mask_pos)
            # now:  mask_digit > 0   (in a mask)

    if mask_digit:
        s += _hex_str(mask_digit)

    return s

#-------------------------------------------------------------------------------
#  _gen_class_set_string
#-------------------------------------------------------------------------------

def _gen_class_set_string(idset):

    values = _gen_class_set(idset)

    if len(values) == 0:
        return None

    return _encode_id_set(values)

#-------------------------------------------------------------------------------
#  _get_non_negative
#-------------------------------------------------------------------------------

def _get_non_negative(value):
    _check_number(value)
    if value < 0:
        raise Exception('Metadata %s value "%s" is not non-negative' %
            (metadata_current_field, str(value)))
    return value

#-------------------------------------------------------------------------------
#  _get_accept_buf_size
#-------------------------------------------------------------------------------

def _get_accept_buf_size(value):
    _check_number(value)
    # We have to have enough buffer to survive, go with minimum of 1k
    if value < 1024:
       raise Exception('Accept buffer size %s is less than the minimum of 1024' % str(value))
    return value

#-------------------------------------------------------------------------------
#  _get_multi_session
#-------------------------------------------------------------------------------

def _get_multi_session(value):
    if value.lower() == "true":
        return "true"
    if value.lower() == "false":
        return "false"

    # true/false are the only accepted values
    raise Exception('multiSession %s is invalid, it can only be "true" or "false"' % str(value))

#-------------------------------------------------------------------------------
#  _get_properties
#-------------------------------------------------------------------------------

def _get_properties(value):
    props = ast.literal_eval(str(value))
    if not isinstance(props, dict):
        raise Exception('properties has to be a dictionary')
    # properties is a dictionary {<string>: <string>}
    for k in props:
        if props[k] == None:
            raise Exception('Empty element for key %s' % str(k))
        if (not isinstance(k, basestring)) or (not isinstance(props[k], basestring)):
            raise Exception('Only string keys/values supported: %s: %s' % (str(k), str(props[k])))
        if k.startswith("gpd."):
            raise Exception('"gpd." is a reserved domain: %s' % str(k))
    return props

#-------------------------------------------------------------------------------
#  _get_description
#-------------------------------------------------------------------------------

def _get_description(value):
    if value == None:
        return None
    return _check_str(r'.{1,31}', value)

#-------------------------------------------------------------------------------
#  _get_memory_type
#-------------------------------------------------------------------------------

def _get_memory_type(value):

    global is_protected_memory

    if value.lower() == "unprotected":
        is_protected_memory = False;
        return 'x'

    if value.lower() == "protected":
        is_protected_memory = True
        return None

    raise Exception('Metadata %s value "%s" is invalid.  Valid values are "protected", "unprotected"' %
            (metadata_current_field, value))

#-------------------------------------------------------------------------------
#  _check_number
#-------------------------------------------------------------------------------

def _check_number(value):
    return _check_str(r'-?\d+', str(value))

#-------------------------------------------------------------------------------
#  _check_str
#-------------------------------------------------------------------------------

def _check_str(regex, str):
    global metadata_current_field
    if re.match('^(' + regex + ')$', str):
        return _escape(str)
    else:
        raise Exception('Metadata %s value "%s" does not conform to pattern /%s/' %
            (metadata_current_field, str, regex))

#-------------------------------------------------------------------------------
#  _check_boolean
#-------------------------------------------------------------------------------

def _check_boolean(value):
    if not isinstance(value, bool):
        raise Exception('Metadata %s value is not of boolean type' %
            (metadata_current_field))

    if (value):
        return 1

    return 0

#-------------------------------------------------------------------------------
#  _escape
#-------------------------------------------------------------------------------

def _escape(value):
    return value.replace('%', '%25'). \
                 replace(',', '%2C'). \
                 replace(';', '%3B'). \
                 replace('=', '%3D')

#-------------------------------------------------------------------------------
#  _hex_byte_swap
#-------------------------------------------------------------------------------

def _hex_byte_swap(str):
    """Reverse the bytes (pairs of hex digits) in a hex-encoded string"""
    return ''.join(re.findall('..', str)[::-1])

#-------------------------------------------------------------------------------
#  _encode_uuid
#-------------------------------------------------------------------------------

def _encode_uuid(str):
    """Encode a canonical UUID string as a metadata UUID value"""

    m = re.match(r'^([0-9a-fA-F]{8})-([0-9a-fA-F]{4})-([0-9a-fA-F]{4})-([0-9a-fA-F]{4})-([0-9a-fA-F]{12})$', str)

    if m is None:
        raise Exception('UUID syntax invalid; expected "8-4-4-4-12" format:\n'
                        + ' XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX')

    return (_hex_byte_swap(m.group(1)) +
            _hex_byte_swap(m.group(2)) +
            _hex_byte_swap(m.group(3)) +
            m.group(4) +
            m.group(5))

#-------------------------------------------------------------------------------
#  _MetadataTest
#-------------------------------------------------------------------------------

#  We can turn off interpretation / running of the unit tests completely
#  if we're running in the SConscript environment.  If we're running as
#  a standalone script, add the following code.

if __name__ == '__main__':

    #  Some of the unit tests expressions, e.g. with self.assertRaises(Exception),
    #  are relying on 2.7 features of the python unit test framework.  It causes
    #  python interpreter errors on 2.6.8.

    if sys.hexversion >= 0x2070000:

        class _MetadataTest(unittest.TestCase):

            #  If privileges is not specified, you get the default privileges.
            #  Specify them so it's easier to write tests.

            kDefault = {'privileges':['I2C']}

            #-------------------------------------------------------------------
            #  test_privileges
            #-------------------------------------------------------------------

            def test_privileges(self):

                # Test generating the default.
                self.assertEqual('p=2b', generate_metadata( self.kDefault ))

                # Test default is added if no privileges specified.
                md = {}
                self.assertEqual('p=b:da9008f709', generate_metadata( md ))

                # Test adding some valid privileges.
                md = {'privileges': ['DeviceID','NSMem']}
                self.assertEqual('p=c:4', generate_metadata( md ))

                # Test empty privilege list.
                md = { 'privileges': [],}
                self.assertEqual('', generate_metadata( md ))

                # Test using an invalid id.
                with self.assertRaises(Exception):
                    generate_metadata({ 'privileges': ['invalid']})

                # Test using an invalid type for the privileges.  It should be a set of strings, not a string.
                with self.assertRaises(Exception):
                    generate_metadata({ 'privileges': '1:a1'})

                # Test using an invalid type for the privileges.  It should be a set of strings, not a set of int.
                with self.assertRaises(Exception):
                    generate_metadata({ 'privileges': [100]})

            #-------------------------------------------------------------------
            #  test_services
            #-------------------------------------------------------------------

            def test_services(self):

                # Test some valid services.  Explicitly add privileges so default is not added.
                md = copy.copy( self.kDefault )
                md.update({'services': ['OEMUnwrapKeys']})
                self.assertEqual('p=2b;s=3c', generate_metadata( md ))

                # Test empty services list.
                md = copy.copy( self.kDefault )
                md.update({'services': []})
                self.assertEqual('p=2b', generate_metadata( md ))

                # Test adding an invalid service.
                with self.assertRaises(Exception):
                    generate_metadata({ 'services': ['invalid']})

                # Test services type is valid.  It should be a set of strings, not a string.
                with self.assertRaises(Exception):
                    generate_metadata({ 'services': 'abc' })

                # Test services type is valid.  It should be a set of strings, not a set of int.
                with self.assertRaises(Exception):
                    generate_metadata({ 'services': [100]})

            #-------------------------------------------------------------------
            #  test_appname
            #-------------------------------------------------------------------

            def test_appname(self):

                # Test valid appName.
                md = copy.copy( self.kDefault )
                md.update({'appName': 'Foo'})
                self.assertEqual('n=Foo;p=2b', generate_metadata( md ))

                # Test valid appName with min length.
                md = copy.copy( self.kDefault )
                md.update({'appName': 'X'})
                self.assertEqual('n=X;p=2b', generate_metadata( md ))

                # Test valid appName with max length.
                md = copy.copy( self.kDefault )
                md.update({'appName': '1234567890123456789012345678901'})
                self.assertEqual('n=1234567890123456789012345678901;p=2b', generate_metadata( md ))

                # Test invalid appName - name too short.
                with self.assertRaises(Exception):
                    generate_metadata({ 'appName': '' })

                # Test invalid appName - name too long.
                with self.assertRaises(Exception):
                    generate_metadata({ 'appName': '12345678901234567890123456789012' })

            #-------------------------------------------------------------------
            #  test_uuid
            #-------------------------------------------------------------------

            def test_uuid(self):

                # Test valid UUID data.
                md = copy.copy( self.kDefault )
                md.update({'UUID': '12345678-1234-1234-1234-123456789abc'})
                self.assertEqual('p=2b;u=78563412341234121234123456789abc', generate_metadata( md ))

                # Test invalid data - invalid hex digit.
                with self.assertRaises(Exception):
                    generate_metadata({ 'UUID': 'X2345678-1234-1234-1234-123456789abc' })

                # Test invalid data - invalid format
                with self.assertRaises(Exception):
                    generate_metadata({ 'UUID': '1234-5678-1234-1234-1234-123456789abc' })

            #-------------------------------------------------------------------
            #  test_object_limit
            #-------------------------------------------------------------------

            def test_object_limit(self):

                # Test valid data.
                md = copy.copy( self.kDefault )
                md.update({'objectLimit': 100 })
                self.assertEqual('o=100;p=2b', generate_metadata( md ))

                # Test valid data - min value.
                md = copy.copy( self.kDefault )
                md.update({'objectLimit': 0 })
                self.assertEqual('o=0;p=2b', generate_metadata( md ))

                # Test invalid data - less than min.
                with self.assertRaises(Exception):
                    generate_metadata({ 'objectLimit': -20 })

                # Test invalid data - invalid type.
                with self.assertRaises(Exception):
                    generate_metadata({ 'objectLimit': 'ABC' })

            #-------------------------------------------------------------------
            #  test_memory_type
            #-------------------------------------------------------------------

            def test_memory_type(self):

                global _kMarker1

                # Test valid data.
                md = copy.copy( self.kDefault )
                md.update({'memoryType': 'Unprotected'})
                expected = 'm=x;p=2b' + _kMarker1
                self.assertEqual( expected, generate_metadata( md ))

                # Test valid data.  If memoryType not specified, then it's protected (i.e. not m=x).
                self.assertEqual('p=2b', generate_metadata({ 'privileges': ['I2C']}))

                # Test invalid data.  'Unprotected' (case independent) is the only valid value.
                with self.assertRaises(Exception):
                    generate_metadata({ 'memoryType': 'invalid' })

            #-------------------------------------------------------------------
            #  test_bad_fields
            #-------------------------------------------------------------------

            def test_bad_fields(self):

                with self.assertRaises(Exception) as context:
                    generate_metadata({ 'appname': 'Foo' })
                self.assertEquals('Invalid metadata field name "appname" - should be "appName"', context.exception.message)

                with self.assertRaises(Exception) as context:
                    generate_metadata({ 'MEM': 'x' })
                self.assertEquals('Invalid metadata field name "MEM" - should be "memoryType"', context.exception.message)

                with self.assertRaises(Exception) as context:
                    generate_metadata({ 'random': 'Foo' })
                self.assertEquals('Invalid metadata field name "random" - should be one of: UUID, acceptBufSize, appName, description, memoryType, multiSession, objectLimit, privileges, properties, services, version', context.exception.message)

            #-------------------------------------------------------------------
            #  test_all_fields
            #-------------------------------------------------------------------

            def test_all_fields(self):

                md = {
                    'privileges':  ['I2C','DeviceId'],
                    'services':    ['OEMUnwrapKeys'],
                    'appName':     'SampleApp',
                    'UUID':        '12345678-1234-1234-1234-123456789ABC',
                    'objectLimit': 100,
                    'memoryType':  'protected'
                }

                self.assertEqual('n=SampleApp;o=100;p=c,2b;s=3c;u=78563412341234121234123456789ABC', generate_metadata( md ))

            #-------------------------------------------------------------------
            #  test_escaping
            #-------------------------------------------------------------------

            def test_escaping(self):

                md = copy.copy( self.kDefault )
                md.update({'appName': '=%,;ZZZ' })
                self.assertEqual('n=%3D%25%2C%3BZZZ;p=2b', generate_metadata( md ))

            #-------------------------------------------------------------------
            #  test_extract_field
            #-------------------------------------------------------------------
            def test_extract_field(self):
                md = {
                    'privileges':  ['I2C','DeviceId'],
                    'services':    ['OEMUnwrapKeys'],
                    'appName':     'FooBar',
                    'UUID':        '12345678-1234-1234-1234-123456789ABC',
                    'objectLimit': 100,
                    'memoryType':  'protected',
                    'acceptBufSize': 8192,
                    'multiSession': 'false',
                    'version': '2.1',
                    'description': 'My TA',
                    'properties': { 'key0': 'value0', 'key1': 'value1'}
                }
                self.assertEqual('FooBar', extractField( md, 'appName' ))
                self.assertEqual(None, extractField( md, 'memoryType' ))
                self.assertEqual('c,2b', extractField( md, 'privileges' ))
                self.assertEqual('3c', extractField( md, 'services' ))
                self.assertEqual(8192, extractField( md, 'acceptBufSize' ))
                self.assertEqual('false', extractField( md, 'multiSession' ))
                self.assertEqual(100, extractField( md, 'objectLimit' ))
                self.assertEqual('78563412341234121234123456789ABC', extractField( md, 'UUID' ))
                self.assertEqual('2.1', extractField( md, 'version' ))
                self.assertEqual('My TA', extractField( md, 'description' ))

                md.update({'memoryType': 'Unprotected' })
                self.assertEqual('x', extractField( md, 'memoryType' ))

                md = {}
                self.assertEqual(None, extractField( md, 'memoryType' ))
                self.assertEqual('b:da9008f701', extractField( md, 'privileges' ))
                self.assertEqual(4096, extractField( md, 'acceptBufSize' ))
                self.assertEqual('true', extractField( md, 'multiSession' ))
                md.update({'multiSession': 'FaLsE' })
                self.assertEqual('false', extractField( md, 'multiSession' ))
                self.assertEqual(None, extractField( md, 'properties' ))
                self.assertEqual('1.0', extractField( md, 'version' ))
                self.assertEqual(None, extractField( md, 'description' ))

            #-------------------------------------------------------------------
            #  test_extract_field_fail
            #-------------------------------------------------------------------
            def test_extract_field_fail(self):
                md = {
                    'privileges':  ['I2C','DeviceId'],
                    'services':    ['OEMUnwrapKeys'],
                    'appName':     'FooBar',
                    'UUID':        '12345678-1234-1234-1234-123456789ABC',
                    'objectLimit': 100,
                    'memoryType':  'protected',
                    'acceptBufSize': 8192,
                    'multiSession': 'false',
                    'version': '2.1',
                    'description': 'My TA',
                    'properties': { 'key0': 'value0', 'key1': 'value1'}
                }
                with self.assertRaises(Exception) as context:
                    extractField( md, 'appname' )
                self.assertEquals('Invalid metadata field name "appname" - should be "appName"', context.exception.message)

                with self.assertRaises(Exception) as context:
                    extractField( md, 'appnaMe' )
                self.assertEquals('Invalid metadata field name "appnaMe" - should be "appName"', context.exception.message)

                with self.assertRaises(Exception) as context:
                    extractField( md, 'memory_type' )
                self.assertEquals('Invalid metadata field name "memory_type" - should be "memoryType"', context.exception.message)

                md.update({'acceptBufSize': 20 })
                with self.assertRaises(Exception) as context:
                    extractField( md, 'acceptBufSize' )
                self.assertEquals('Accept buffer size 20 is less than the minimum of 1024', context.exception.message)

                md.update({'multiSession': 'false_' })
                with self.assertRaises(Exception) as context:
                    extractField( md, 'multiSession' )
                self.assertEquals('multiSession false_ is invalid, it can only be "true" or "false"', context.exception.message)

                md.update({'properties': ['test'] })
                with self.assertRaises(Exception) as context:
                    extractField( md, 'properties' )
                self.assertEquals('properties has to be a dictionary', context.exception.message)

                md.update({'properties': {'key0': None }})
                with self.assertRaises(Exception) as context:
                    extractField( md, 'properties' )
                self.assertEquals('Empty element for key key0', context.exception.message)

                md.update({'properties': {'key0': 42 }})
                with self.assertRaises(Exception) as context:
                    extractField( md, 'properties' )
                self.assertEquals('Only string keys/values supported: key0: 42', context.exception.message)

                md.update({'properties': {42: 'value0' }})
                with self.assertRaises(Exception) as context:
                    extractField( md, 'properties' )
                self.assertEquals('Only string keys/values supported: 42: value0', context.exception.message)

                md.update({'properties': {'gpd.testProp': 'value0' }})
                with self.assertRaises(Exception) as context:
                    extractField( md, 'properties' )
                self.assertEquals('"gpd." is a reserved domain: gpd.testProp', context.exception.message)

            #-------------------------------------------------------------------
            #  test_encode_id_set
            #-------------------------------------------------------------------

            def test_encode_id_set(self):

                self.assertEqual('1,a,14', _encode_id_set({1,10,20}))

                #  Just for grins, verify that you can use a list or
                #  a tuple (any iterable really) instead of a set.
                #
                #  Make sure _encode_id_set is well behaved if you use
                #  non set properties (e.g. the you can have multiple
                #  copies of a given element.)

                self.assertEqual('1,a,14', _encode_id_set( [1,10,20,1,10,20] ))
                self.assertEqual('1,a,14', _encode_id_set( (1,10,20,1,10,20) ))

                self.assertEqual('1:1',    _encode_id_set({1,2}))
                self.assertEqual('1:2',    _encode_id_set({1,3}))
                self.assertEqual('1:4',    _encode_id_set({1,4}))
                self.assertEqual('1:8',    _encode_id_set({1,5}))
                self.assertEqual('1,6',    _encode_id_set({1,6}))
                self.assertEqual('1:18',   _encode_id_set({1,2,9}))
                self.assertEqual('1:28',   _encode_id_set({1,3,9}))
                self.assertEqual('1:48',   _encode_id_set({1,4,9}))
                self.assertEqual('1:88',   _encode_id_set({1,5,9}))
                self.assertEqual('1,6:4',  _encode_id_set({1,6,9}))
                self.assertEqual('1,7:2',  _encode_id_set({1,7,9}))
                self.assertEqual('1,8:1',  _encode_id_set({1,8,9}))

                # Many encodings are equivalent and acceptable, but since we know
                # the implementation, we can simply check for one expected output.

                self.assertEqual('102',            _encode_id_set({258}))
                self.assertEqual('100,200:1',      _encode_id_set({256, 512, 513}))
                self.assertEqual('1:2,20',         _encode_id_set({1, 3, 32}))
                self.assertEqual('1:981101',       _encode_id_set({1,2,5,9,10,14,22}))
                self.assertEqual('10000000:0001',  _encode_id_set({0x10000000, 0x1000000d}))

                # TODO: out of range (IDs negative, too large)

            #-------------------------------------------------------------------
            #  test_encode_uuid
            #-------------------------------------------------------------------

            def test_encode_uuid(self):
                #  Test some UUIDs in the GP apps.
                self.assertEqual('52414d532d5453434c542d54412d3031', _encode_uuid('534d4152-542d-4353-4c54-2d54412d3031'))
                self.assertEqual('52414d5343544c535441544346494341', _encode_uuid('534d4152-5443-534c-5441-544346494341'))
                self.assertEqual('52414d5343544c535454434649434132', _encode_uuid('534d4152-5443-534c-5454-434649434132'))
                self.assertEqual('52414d5343544c534d4c54494e535443', _encode_uuid('534d4152-5443-534c-4d4c-54494e535443'))
                self.assertEqual('52414d5343544c5353474c494e535443', _encode_uuid('534d4152-5443-534c-5347-4c494e535443'))
                self.assertEqual('4205d1cae4342d456156e979aa6e61bc', _encode_uuid('cad10542-34e4-452d-6156-e979aa6e61bc'))

                self.assertEqual('52414d532d5453434c542d54412d4552', _encode_uuid('534d4152-542d-4353-4c54-2d54412d4552'))
                self.assertEqual('52414d5343544c5354455252544f4f53', _encode_uuid('534d4152-5443-534c-5445-5252544f4f53'))
                self.assertEqual('52414d532d5453434c542d54412d5355', _encode_uuid('534d4152-542d-4353-4c54-2d54412d5355'))
                self.assertEqual('52414d5343544c53544f53345041524d', _encode_uuid('534d4152-5443-534c-544f-53345041524d'))
                self.assertEqual('52414d532d5453434c542d54412d5354', _encode_uuid('534d4152-542d-4353-4c54-2d54412d5354'))
                self.assertEqual('52414d5343544c535443525950544f31', _encode_uuid('534d4152-5443-534c-5443-525950544f31'))
                self.assertEqual('52414d5343544c535444415441535431', _encode_uuid('534d4152-5443-534c-5444-415441535431'))
                self.assertEqual('52414d5343544c535f54494d45415049', _encode_uuid('534d4152-5443-534c-5f54-494d45415049'))

    #---------------------------------------------------------------------------
    #  Run unit tests
    #---------------------------------------------------------------------------

    _dumpClassMapById()
    _dumpClassMapByValue()

    if sys.hexversion >= 0x2070000:
        unittest.main()
    else:
        print 'Need python >= 2.7 to run unit tests'


