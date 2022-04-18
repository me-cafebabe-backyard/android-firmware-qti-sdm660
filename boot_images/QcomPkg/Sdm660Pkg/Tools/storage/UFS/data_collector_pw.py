#!/usr/bin/python
'''
 Copyright (c) 2015
 Qualcomm Technologies Incorporated.
 All Rights Reserved.
 Qualcomm Confidential and Proprietary

Script to track usage of the tools using piwik

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Tools/storage/UFS/data_collector_pw.py#1 $
$DateTime: 2016/05/23 02:27:48 $
$Author: pwbldsvc $

when        who       what, where, why
----------  --------  -----------------------------------------------------
2015-10-23  wkimberl  Create.

'''

import socket
import getpass
import random
import string
import hashlib
import urllib
import urllib2
import uuid
import logging

#Example how to call it from cURL command line tool
#curl --insecure  "http://www.google-analytics.com/collect?v=1&tid=UA-67288231-1&ds=app&sc=start&cd=flash_throug_gdbpy&an=flash_through_gdb_py3&av=1.0&cid=f6a73bcc-09f5-4699-a235-606531c6499f&t=event&ec=execute&ea=run&el=flash_gdb&ev=2" --output curl_out.bin


#curl --insecure  'http://wkimberl-linux.qualcomm.com:8338/analytics/piwik/piwik.php?_cvar={"1":["OS","Linux"],"2":["Tool","flash_through_gdb_jlink"],"3":["version","1.0.0.1"]}&action_name=Run&url=http://wkimberl-linux.qualcomm.com:8338/flash_through_gdb/jlink/1.0.0.1&idsite=3&rand=351459&rec=1&apiv=1&_id=af344a398df83874&res=320x480&e_c=flash_through_gdb.1.0.0.1&e_n=flash_through_gdb&e_a=write_bytes&e_v=4096'

#curl --insecure -X POST -d '_cvar={"1":["OS","Linux"],"2":["Tool","flash_through_gdb_jlink"],"3":["version","1.0.0.1"]}&action_name=Run&url=http://wkimberl-linux.qualcomm.com:8338/flash_through_gdb/jlink/1.0.0.1/write&idsite=2&rand=351459&rec=1&apiv=1&_id=af344a398df83872&res=320x480&e_c=flash_through_gdb.1.0.0.1&e_n=flash_through_gdb&e_a=write_bytes&e_v=4096' http://wkimberl-linux.qualcomm.com:8338/analytics/piwik/piwik.php

#curl --insecure -X POST -d '_cvar={"1":["OS","Linux"],"2":["Tool","flash_through_gdb_jlink"],"3":["version","1.0.0.1"]}&action_name=Run&url=http://wkimberl-linux.qualcomm.com:8338/flash_through_gdb/jlink/1.0.0.1/erase&idsite=2&rand=351459&rec=1&apiv=1&_id=af344a398df83872&res=320x480&e_c=flash_through_gdb.1.0.0.1&e_n=flash_through_gdb&e_a=erase_bytes&e_v=4096' http://wkimberl-linux.qualcomm.com:8338/analytics/piwik/piwik.php

#curl --insecure -X POST -d '_cvar={"1":["OS","Linux"],"2":["Tool","flash_through_gdb_jlink"],"3":["version","1.0.0.1"]}&action_name=Run&url=http://wkimberl-linux.qualcomm.com:8338/flash_through_gdb/jlink/1.0.0.1/read&idsite=2&rand=351459&rec=1&apiv=1&_id=af344a398df83872&res=320x480&e_c=flash_through_gdb.1.0.0.1&e_n=flash_through_gdb&e_a=read_bytes&e_v=4096' http://wkimberl-linux.qualcomm.com:8338/analytics/piwik/piwik.php



# e_c : Event Category
# e_a : Event Action
# e_n : Event Name
# e_v : Event Value
# _rcn : Campaing Name
# _rck : Campaing Keyword


import platform
def gen_useragent ():
    ''' Generate a user agent for the current platform '''
    useragent = 'Python-urllib/2.7 (' + platform.system() + '; U; ' + platform.system() + '; en-US; ' + platform.platform() + ') Python-urllib (KHTML, like Gecko)'
    return useragent


class Data_Collector:
    ''' Collects usage data and logs it into google analytics '''
    def __init__ (self, application, app_version, screen, disable = False):
        ''' '''
        self.disable = disable
        if disable == True:
            return

        # Get the hostname and check if it is within qualcomm
        hostname = None
        try:
            hostname = socket.getfqdn()
        except:
            # On error, bail, since we can't tell if it Qualcomm domain or not.
            self.disable = True
            return

        if 'qualcomm' not in hostname:
            self.disable = True
            return

        self.app_name = str(application)
        self.app_version = str(app_version)
        self.target = str(screen)
        self.site_id = "6"

        try:
            username = getpass.getuser()
        except:
            username = ''.join(random.choice(string.ascii_lowercase) for i in range(8))

        h = hashlib.sha256()
        h.update(str(hostname) + str(username))
        hash_uid = h.hexdigest()[:16]
        self.user_id = str(hash_uid)

        # e_c : Event Category
        # e_a : Event Action
        # e_n : Event Name
        # e_v : Event Value
        # _rcn : Campaing Name
        # _rck : Campaing Keyword
        # idsite : Site ID for tracking different sites.
        # rec : Must be 1 (record?)
        # apiv : API Version, set to 1.
        # res : Resolution, inaccurate, set to see if it can be used to classify data.
        # _id : Unique user ID.
        # _cvar : Custom Variables.
        self.event_category = self.app_name

        data = '{"1":["username","' + username + '"],"2":["host","' + hostname + '"],"3":["Target","' + self.target + '"],"4":["version","' + self.app_version + '"]}'
        data = urllib.quote(data)
        self.base_url = 'http://wkimberl-linux.qualcomm.com:8338/analytics/piwik/piwik.php?idsite=' + self.site_id + '&rec=1&apiv=1&_id=' + self.user_id + '&_rcn=' + self.app_version + '&_rck=' + self.app_name + '&_cvar=' + data

        self.useragent = gen_useragent()

#curl --insecure -X POST -d 'action_name=Run&url=http://wkimberl-linux.qualcomm.com:8338/flash_through_gdb/jlink/1.0.0.1/read&e_c=flash_through_gdb.1.0.0.1&e_n=flash_through_gdb&e_a=read_bytes&e_v=4096'

#curl --insecure -X POST -d '_cvar={"1":["OS","Linux"],"2":["Tool","flash_through_gdb_jlink"],"3":["version","1.0.0.1"]}&action_name=Run&url=http://wkimberl-linux.qualcomm.com:8338/flash_through_gdb/jlink/1.0.0.1/read&idsite=2&rand=351459&rec=1&apiv=1&_id=af344a398df83872&res=320x480&e_c=flash_through_gdb.1.0.0.1&e_n=flash_through_gdb&e_a=read_bytes&e_v=4096' http://wkimberl-linux.qualcomm.com:8338/analytics/piwik/piwik.php


    def _hit(self, url):
        ''' Call the URL given with a timeout of 2 seconds. '''
        # Generate a random number to avoid the proxy cache
        if self.disable == True:
            return

        cache_buster = random.randint(0,1048576)
        url = url + "&rand=" + str(cache_buster)
        logging.debug ("Will open URL: " + url)
        useragent = self.useragent
        try:
            request = urllib2.Request(url)
            opener = urllib2.build_opener()
            request.add_header('User-Agent' ,useragent)
            data = opener.open(request).read()
        except urllib2.URLError as e:
            logging.warning("URL Error " + str(e) + " on URL " + url)
        except:
            logging.debug ("Failed to open URL: " + url)

    def log_use(self):
        ''' Log that the tools was called and is beeing used.'''
        # Check if we should log.
        if self.disable == True:
            return

        urldata = "&url=http://wkimberl-linux.qualcomm.com:8338/%s/%s/%s/run&action_name=Run&res=320x480" % (self.target, self.app_name, self.app_version)
        url = self.base_url + urldata
        self._hit(url)

    def _add_url_action (self, action):
        url_data = "&url=http://wkimberl-linux.qualcomm.com:8338/%s/%s/%s/%s&action_name=%s" % (self.target, self.app_name, self.app_version, action, action)
        return url_data

    def total_write(self, byte_count):
        ''' Log the number of bytes written by the tool. '''
        # Check if we should log.
        if self.disable == True:
            return

        if byte_count == 0:
            return

        value = str(byte_count)
        urldata = self._add_url_action('write_bytes')
        urldata = urldata + '&res=320x481&e_c=' + self.event_category + '&e_n=total_bytes&e_a=write_bytes&e_v=' + value
        url = self.base_url + urldata
        self._hit(url)

    def total_read(self, byte_count):
        ''' Log the number of bytes read by the tool. '''
        # Check if we should log.
        if self.disable == True:
            return

        if byte_count == 0:
            return

        #change the resolution so it looks to piwik as a new session.
        value = str(byte_count)
        urldata = self._add_url_action('read_bytes')
        urldata = urldata + '&res=320x482&e_c=' + self.event_category + '&e_n=total_bytes&e_a=read_bytes&e_v=' + value
        url = self.base_url + urldata
        self._hit(url)

    def total_erase(self, byte_count):
        ''' Log the number of bytes erased by the tool. '''
        # Check if we should log.
        if self.disable == True:
            return

        if byte_count == 0:
            return

        value = str(byte_count)
        urldata = self._add_url_action('erase_bytes')
        urldata = urldata + '&res=320x483&e_c=' + self.event_category + '&e_n=total_bytes&e_a=erase_bytes&e_v=' + value
        url = self.base_url + urldata
        self._hit(url)

    def total_time(self, time_seconds):
        ''' Log the number of bytes erased by the tool. '''
        # Check if we should log.
        if self.disable == True:
            return

        if time_seconds == 0:
            return

        value = str(time_seconds)
        urldata = self._add_url_action('time_run')
        urldata = urldata + '&res=320x484&e_c=' + self.event_category + '&e_n=total_time&e_a=time_secs&e_v=' + value
        url = self.base_url + urldata
        self._hit(url)

    def log_error(self, error_code):
        ''' Log errors that occurr in the tool. '''
        # Check if we should log.
        if self.disable == True:
            return

        value = str(time_seconds)
        url_data = "&url=http://wkimberl-linux.qualcomm.com:8338/%s/%s/%s/%s/%d&action_name=%s" % (self.target, self.app_name, self.app_version, action, value, action)
        urldata = urldata + '&res=320x485'
        url = self.base_url + urldata
        self._hit(url)
