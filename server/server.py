#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from http.server import HTTPServer, BaseHTTPRequestHandler

from io import BytesIO
import json
import subprocess
import os
import binascii
import ssl


def hash_gen(in_file, hash_file):
    if not in_file:
        print('hash_gen error: intput file path is missing')
        return -1
    if not os.path.isfile(in_file):
        print('hash_gen error: ' + in_file + ' is missing')
        return -1
    cmd = 'openssl dgst'
    cmd += ' -binary -sha256'
    cmd += ' -out ' + hash_file
    cmd += ' ' + in_file
    try:
        subprocess.check_call(cmd, shell=True)
    except subprocess.CalledProcessError as e:
        print('hash_gen error')
        return -1

    return 0


def rsa_sign_pss(data, prvk, sig):
    cmd = ''
    cmd += 'openssl pkeyutl -sign'
    cmd += ' -in ' + data
    cmd += ' -inkey ' + prvk
    cmd += ' -out ' + sig
    cmd += ' -pkeyopt digest:sha256'
    cmd += ' -pkeyopt rsa_padding_mode:pss'
    cmd += ' -pkeyopt rsa_pss_saltlen:32'
    try:
        subprocess.check_call(cmd, shell=True)
        return 0
    except subprocess.CalledProcessError as e:
        print('rsa_sign error(pss)')
        return -1



class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        self.send_response(200)
        self.end_headers()
        self.wfile.write(b'Hello, world!')

    def do_POST(self):
        content_hash = "content_hash.bin"
        content_sig = "content_hash.sig"
        rsa_private_key = "rsa_private_key.pem"

        content_length = int(self.headers['Content-Length'])
        body = self.rfile.read(content_length)
        self.send_response(200)
        self.end_headers()

        print("receive data:")
        print(body)

        data = body.decode("utf-8").split("=")

        f = open(content_hash, "wb+")
        f.write(binascii.a2b_hex(data[1]))
        f.close()

        rsa_sign_pss(content_hash, rsa_private_key, content_sig)

        f = open(content_sig, "rb+")
        f_content = f.read()
        f.close()

        print("response data:")
        print(f_content.hex())

        ret = None
        if len(data) == 2:
            ret = {"success": True, "data": f_content.hex()}
        else:
            ret = {"success": True, "message": "can't work"}

        response = BytesIO()
        response.write(json.dumps(ret).encode("utf-8"))
        self.wfile.write(response.getvalue())


httpd = HTTPServer(('localhost', 8000), SimpleHTTPRequestHandler)
print('Started httpserver on port ' , 8000)
# httpd.socket = ssl.wrap_socket (httpd.socket, certfile='./server.pem', server_side=True)
httpd.serve_forever()

