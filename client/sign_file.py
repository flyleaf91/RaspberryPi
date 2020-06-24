#!/usr/bin/env python3

import os
import sys
import struct
import hashlib
import zipfile
import time
import shutil
import paramiko
import requests
import json
import binascii
from requests.packages.urllib3.exceptions import InsecureRequestWarning

def sign_file(src_file):
    f = open(src_file,"rb+")
    f_content = f.read()
    f.close()

    h = hashlib.new("sha256")
    h.update(f_content)
    digest = h.digest()

    ascii_data = binascii.b2a_hex(digest)
    src_json_data = {'data' : ascii_data}
    # print (src_json_data)
    requests.packages.urllib3.disable_warnings(InsecureRequestWarning)
    ret = requests.post("http://127.0.0.1:8000", data=src_json_data, verify=False)
    # print (ret.json())
    ret_json_data = ret.json()
    if ret_json_data['success'] is True:
        # print (ret_json_data['data'])
        signed_data = binascii.a2b_hex(ret_json_data['data'])
    else:
        signed_data = None
        print (ret_json_data['message'])
        print ("data return error")
        exit(-1)

    f = open("pack_content.sig", "wb+")
    f.write(signed_data)
    f.close()

if __name__ == '__main__':
    print (sys.argv)
    file_list = sys.argv[1:]
    file_list.sort()
    for input_file in file_list:
        sign_file(input_file)

