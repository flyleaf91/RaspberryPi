# pyusb MTK PL Mode

尝试搭建自己签名服务器和访问的证书

## 参考文档

* [0063_OpenVPN.md](0063_OpenVPN.md)

## vars配置

```
# These are the default values for fields
# which will be placed in the certificate.
# Don't leave any of these fields blank.
export KEY_COUNTRY="CN"
export KEY_PROVINCE="GD"
export KEY_CITY="SZ"
export KEY_ORG="zengjf"
export KEY_EMAIL="zengjf42@163.com"
export KEY_OU="base part"

# X509 Subject Field
export KEY_NAME="zengjf"
```

## 生成证书

* cd easy-rsa
* cp openssl-1.0.0.cnf openssl.cnf
* source vars
* ./build-ca
* ./build-key-server server
* ./build-key client
* cd keys
  * cp client.csr client.pem
  * cat client.crt >> client.pem
  * cp server.csr server.pem
  * cat server.crt >> server.pem
* cp keys/client.pem ../HTTPPost/keys/
* cp keys/server.pem ../HTTPPost/keys/


```bash
pi@raspberrypi:easy-rsa $ source  vars
**************************************************************
  No /home/pi/zengjf/https-ssl/easy-rsa/openssl.cnf file could be found
  Further invocations will fail
**************************************************************
NOTE: If you run ./clean-all, I will be doing a rm -rf on /home/pi/zengjf/https-                                                                                                                               ssl/easy-rsa/keys
pi@raspberrypi:easy-rsa $ ./build-ca
grep: /home/pi/zengjf/https-ssl/easy-rsa/openssl.cnf: No such file or directory
pkitool: KEY_CONFIG (set by the ./vars script) is pointing to the wrong
version of openssl.cnf: /home/pi/zengjf/https-ssl/easy-rsa/openssl.cnf
The correct version should have a comment that says: easy-rsa version 2.x
pi@raspberrypi:easy-rsa $ cp openssl-1.0.0.cnf openssl.cnf
pi@raspberrypi:easy-rsa $ ./build-ca
Can't load /home/pi/.rnd into RNG
3070189584:error:2406F079:random number generator:RAND_load_file:Cannot open file:../crypto/rand/randfile.c:98:Filename=/home/pi/.rnd
Generating a RSA private key
....................................................+++++
................+++++
writing new private key to 'ca.key'
-----
You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.
-----
Country Name (2 letter code) [CN]:
State or Province Name (full name) [GD]:
Locality Name (eg, city) [SZ]:
Organization Name (eg, company) [zengjf]:
Organizational Unit Name (eg, section) [base part]:
Common Name (eg, your name or your server's hostname) [zengjf CA]:
Name [zengjf]:
Email Address [zengjf42@163.com]:
pi@raspberrypi:easy-rsa $ ./build-key-server server
Generating a RSA private key
....+++++
..............................................................+++++
writing new private key to 'server.key'
-----
You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.
-----
Country Name (2 letter code) [CN]:
State or Province Name (full name) [GD]:
Locality Name (eg, city) [SZ]:
Organization Name (eg, company) [zengjf]:
Organizational Unit Name (eg, section) [base part]:
Common Name (eg, your name or your server's hostname) [server]:
Name [zengjf]:server
Email Address [zengjf42@163.com]:

Please enter the following 'extra' attributes
to be sent with your certificate request
A challenge password []:
An optional company name []:
Using configuration from /home/pi/zengjf/https-ssl/easy-rsa/openssl.cnf
Check that the request matches the signature
Signature ok
The Subject's Distinguished Name is as follows
countryName           :PRINTABLE:'CN'
stateOrProvinceName   :PRINTABLE:'GD'
localityName          :PRINTABLE:'SZ'
organizationName      :PRINTABLE:'zengjf'
organizationalUnitName:PRINTABLE:'base part'
commonName            :PRINTABLE:'server'
name                  :PRINTABLE:'server'
emailAddress          :IA5STRING:'zengjf42@163.com'
Certificate is to be certified until Jul  4 15:24:39 2030 GMT (3650 days)
Sign the certificate? [y/n]:y


1 out of 1 certificate requests certified, commit? [y/n]y
Write out database with 1 new entries
Data Base Updated
pi@raspberrypi:easy-rsa $ ./build-key client
Generating a RSA private key
................................................................+++++
.......................................................................................................................................+++++
writing new private key to 'client.key'
-----
You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.
-----
Country Name (2 letter code) [CN]:
State or Province Name (full name) [GD]:
Locality Name (eg, city) [SZ]:
Organization Name (eg, company) [zengjf]:
Organizational Unit Name (eg, section) [base part]:
Common Name (eg, your name or your server's hostname) [client]:
Name [zengjf]:client
Email Address [zengjf42@163.com]:

Please enter the following 'extra' attributes
to be sent with your certificate request
A challenge password []:
An optional company name []:
Using configuration from /home/pi/zengjf/https-ssl/easy-rsa/openssl.cnf
Check that the request matches the signature
Signature ok
The Subject's Distinguished Name is as follows
countryName           :PRINTABLE:'CN'
stateOrProvinceName   :PRINTABLE:'GD'
localityName          :PRINTABLE:'SZ'
organizationName      :PRINTABLE:'zengjf'
organizationalUnitName:PRINTABLE:'base part'
commonName            :PRINTABLE:'client'
name                  :PRINTABLE:'client'
emailAddress          :IA5STRING:'zengjf42@163.com'
Certificate is to be certified until Jul  4 15:26:17 2030 GMT (3650 days)
Sign the certificate? [y/n]:y


1 out of 1 certificate requests certified, commit? [y/n]y
Write out database with 1 new entries
Data Base Updated
pi@raspberrypi:easy-rsa $ ls
```

## 应用证书

* cd HTTPPost/
* cp keys/ca.crt server/
* cp keys/server.pem server/
  * cd server
  * ./server.py
* cp keys/ca.crt client/
* cp keys/client.pem client/
  * cd client
  * ./sign_file.py

## 示例

https://github.com/ZengjfOS/RSAEncryptDecrypt/tree/https-pem-ssl/urllibPost
