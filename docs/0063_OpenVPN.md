# OpenVPN

OpenVPN搭建

## 参考文档

* [烂泥：ubuntu 14.04搭建OpenVPN服务器](https://my.oschina.net/lanni654321/blog/484494?_t=t)
* [SSL Certificate-自行產生 SSL 憑證](http://wiki.weithenn.org/cgi-bin/wiki.pl?SSL_Certificate-%E8%87%AA%E8%A1%8C%E7%94%A2%E7%94%9F_SSL_%E6%86%91%E8%AD%89)

## Ubuntu VPS

* apt-get install openvpn easy-rsa
* 制作CA
  * sudo mkdir /etc/openvpn/easy-rsa/
  * sudo cp -r /usr/share/easy-rsa/* /etc/openvpn/easy-rsa/  
    我们也可以直接在/usr/share/easy-rsa/制作相关的证书，但是为了后续的管理证书的方便，我们还是把easy-rsa放在了openvpn的启动目录下。
  * /etc/openvpn/easy-rsa/vars
    ```
    [...省略]
    # These are the default values for fields
    # which will be placed in the certificate.
    # Don't leave any of these fields blank.
    export KEY_COUNTRY="CN"
    export KEY_PROVINCE="GZ"
    export KEY_CITY="SZ"
    export KEY_ORG="ShenZhen"
    export KEY_EMAIL="zengjf42@163.com"
    export KEY_OU="zengjf"
  
    # X509 Subject Field
    export KEY_NAME="zengjf"
    [...省略]
    ```
  * source /etc/openvpn/easy-rsa/vars
  * ./clean-all
    如果有必要，可以先删除当前目录下的keys所有内容，防止混淆
  * cd /etc/openvpn/easy-rsa
  * ./build-ca
    ```
    Generating a 2048 bit RSA private key
    ......................................................+++
    ....................+++
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
    State or Province Name (full name) [GZ]:
    Locality Name (eg, city) [SZ]:
    Organization Name (eg, company) [ShenZhen]:
    Organizational Unit Name (eg, section) [zengjf]:
    Common Name (eg, your name or your server's hostname) [ShenZhen CA]:
    Name [zengjf]:
    Email Address [zengjf42@163.com]:
    ```
  * tree keys/
    ```
    keys/
    ├── ca.crt
    ├── ca.key
    ├── index.txt
    └── serial
    
    0 directories, 4 files
    ```
  * cp keys/ca.crt /etc/openvpn/
* 制作Server证书
  * cd /etc/openvpn/easy-rsa
  * ./build-key-server zengjf
    ```
    Generating a 2048 bit RSA private key
    ..........+++
    .................................................................+++
    writing new private key to 'zengjf.key'
    -----
    You are about to be asked to enter information that will be incorporated
    into your certificate request.
    What you are about to enter is what is called a Distinguished Name or a DN.
    There are quite a few fields but you can leave some blank
    For some fields there will be a default value,
    If you enter '.', the field will be left blank.
    -----
    Country Name (2 letter code) [CN]:
    State or Province Name (full name) [GZ]:
    Locality Name (eg, city) [SZ]:
    Organization Name (eg, company) [ShenZhen]:
    Organizational Unit Name (eg, section) [zengjf]:
    Common Name (eg, your name or your server's hostname) [zengjf]:
    Name [zengjf]:
    Email Address [zengjf42@163.com]:
    
    Please enter the following 'extra' attributes
    to be sent with your certificate request
    A challenge password []:
    An optional company name []:
    Using configuration from /etc/openvpn/easy-rsa/openssl-1.0.0.cnf
    Check that the request matches the signature
    Signature ok
    The Subject's Distinguished Name is as follows
    countryName           :PRINTABLE:'CN'
    stateOrProvinceName   :PRINTABLE:'GZ'
    localityName          :PRINTABLE:'SZ'
    organizationName      :PRINTABLE:'ShenZhen'
    organizationalUnitName:PRINTABLE:'zengjf'
    commonName            :PRINTABLE:'zengjf'
    name                  :PRINTABLE:'zengjf'
    emailAddress          :IA5STRING:'zengjf42@163.com'
    Certificate is to be certified until Nov 23 01:15:18 2029 GMT (3650 days)
    Sign the certificate? [y/n]:y
    
    
    1 out of 1 certificate requests certified, commit? [y/n]y
    Write out database with 1 new entries
    Data Base Updated
    ```
  * tree keys/
    ```
    keys/
    ├── 01.pem
    ├── ca.crt
    ├── ca.key
    ├── index.txt
    ├── index.txt.attr
    ├── index.txt.old
    ├── serial
    ├── serial.old
    ├── zengjf.crt
    ├── zengjf.csr
    └── zengjf.key
    
    0 directories, 11 files
    ```
  * zengjf.crt、zengjf.csr、zengjf.key
* Diffie-Hellman文件
  * cd /etc/openvpn/easy-rsa
  * ./build-dh
    ```
    Generating DH parameters, 2048 bit long safe prime, generator 2
    This is going to take a long time
    ..................................................................................................................................................................................................................+...............................+....................................................................................................................................+...........................................+..........+................+.................+................+.................................................................................................................................................................................................................+..............................+...................................+...............+...........................................................................................................................................................................+.......................................................+......................................+.................................+.................................+.............................................................................+....................................................................+..................+.........................................................................................................................+.........................................+..........................+.+....................................................+.......................................................................................................................................................................................................................................................+.................................+...............................+...............................................................+...........................................................................................................................................................................................+................................................................................................+...........................................................+.......................................................+......................................................................................+......................................................................+........................................................................................+...........................................................................................................................................................................................................................................+................................................................................................................................................................+.......................................................................................................................................................+....................................................................................+.................................................................................................................................................................................................................................................................+..................................................................+.......................................................................................................................+...........................................................++*++*
    ```
  * tree keys/
    ```
    keys/
    ├── 01.pem
    ├── ca.crt
    ├── ca.key
    ├── dh2048.pem
    ├── index.txt
    ├── index.txt.attr
    ├── index.txt.old
    ├── serial
    ├── serial.old
    ├── zengjf.crt
    ├── zengjf.csr
    └── zengjf.key
    
    0 directories, 12 files
    ```
  * dh2048.pem
* cp keys/zengjf.crt keys/zengjf.key keys/dh2048.pem /etc/openvpn/
* 制作Client证书
  * cd /etc/openvpn/easy-rsa
  * ./build-key client
    ```
    Generating a 2048 bit RSA private key
    ................................................................................                                                                                                                             ......................+++
    ........................+++
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
    State or Province Name (full name) [GZ]:
    Locality Name (eg, city) [SZ]:
    Organization Name (eg, company) [ShenZhen]:
    Organizational Unit Name (eg, section) [zengjf]:
    Common Name (eg, your name or your server's hostname) [client]:
    Name [zengjf]:
    Email Address [zengjf42@163.com]:
    
    Please enter the following 'extra' attributes
    to be sent with your certificate request
    A challenge password []:
    An optional company name []:
    Using configuration from /etc/openvpn/easy-rsa/openssl-1.0.0.cnf
    Check that the request matches the signature
    Signature ok
    The Subject's Distinguished Name is as follows
    countryName           :PRINTABLE:'CN'
    stateOrProvinceName   :PRINTABLE:'GZ'
    localityName          :PRINTABLE:'SZ'
    organizationName      :PRINTABLE:'ShenZhen'
    organizationalUnitName:PRINTABLE:'zengjf'
    commonName            :PRINTABLE:'client'
    name                  :PRINTABLE:'zengjf'
    emailAddress          :IA5STRING:'zengjf42@163.com'
    Certificate is to be certified until Nov 23 01:38:11 2029 GMT (3650 days)
    Sign the certificate? [y/n]:y
    
    
    1 out of 1 certificate requests certified, commit? [y/n]y
    Write out database with 1 new entries
    Data Base Updated
    ```
  * tree keys/
    ```
    root@instance-xezfkc6l:/etc/openvpn/easy-rsa# tree keys/
    keys/
    ├── 01.pem
    ├── 02.pem
    ├── ca.crt
    ├── ca.key
    ├── client.crt
    ├── client.csr
    ├── client.key
    ├── dh2048.pem
    ├── index.txt
    ├── index.txt.attr
    ├── index.txt.attr.old
    ├── index.txt.old
    ├── serial
    ├── serial.old
    ├── zengjf.crt
    ├── zengjf.csr
    └── zengjf.key
    
    0 directories, 17 files
    ```
  * client.crt、client.csr、client.key
* 配置Server
  * cd /etc/openvpn/
  * cp /usr/share/doc/openvpn/examples/sample-config-files/server.conf.gz /etc/openvpn/
  * gzip -d server.conf.gz  
    上述命令的意思是解压server.conf.gz文件后，然后删除原文件。
  * 查看当前server.conf文件默认配置：grep -vE "^#|^;|^$" server.conf
    ```
    port 1194
    proto udp
    dev tun
    ca ca.crt
    cert server.crt
    key server.key  # This file should be kept secret
    dh dh1024.pem
    server 10.8.0.0 255.255.255.0
    ifconfig-pool-persist ipp.txt
    keepalive 10 120
    comp-lzo
    persist-key
    persist-tun
    status openvpn-status.log
    verb 3
    ```
  * 修改server.conf完成后：grep -vE "^#|^;|^$" server.conf
    ```
    port 1194
    proto tcp
    dev tun
    ca ca.crt
    cert zengjf.crt
    key zengjf.key  # This file should be kept secret
    dh dh2048.pem
    server 10.8.0.0 255.255.255.0
    ifconfig-pool-persist ipp.txt
    keepalive 10 120
    comp-lzo
    persist-key
    persist-tun
    status openvpn-status.log
    verb 3
    ```
* /etc/init.d/openvpn start
  ```
   * Starting virtual private network daemon(s)...
   *   Autostarting VPN 'server'   
  ```
* netstat -tunlp |grep 1194
  ```
  tcp        0      0 0.0.0.0:1194            0.0.0.0:*               LISTEN      3003/openvpn
  ```
* grep -vE "^#|^;|^$" client.conf
  ```
  client
  dev tun
  proto tcp
  remote 180.76.160.193 1194
  resolv-retry infinite
  nobind
  persist-key
  persist-tun
  ca ca.crt
  cert client.crt
  key client.key
  ns-cert-type server
  comp-lzo
  verb 3
  ```
* `client.ovpn`和`client.conf`是一样的

## OpenVPN Windows

* openvpn --version
  ```
  OpenVPN 2.3.2 x86_64-pc-linux-gnu [SSL (OpenSSL)] [LZO] [EPOLL] [PKCS11] [eurephia] [MH] [IPv6] built on Jun 22 2017
  ```
* https://build.openvpn.net/downloads/releases/
* 下载2.3.2版本的OpenVPN，安装，管理员权限运行；
* 连接百度BCC服务器
  ```
  Tue Nov 26 10:21:05 2019 OpenVPN 2.3.2 x86_64-w64-mingw32 [SSL (OpenSSL)] [LZO] [PKCS11] [eurephia] [IPv6] built on Aug  7 2014
  Tue Nov 26 10:21:05 2019 MANAGEMENT: TCP Socket listening on [AF_INET]127.0.0.1:25340
  Tue Nov 26 10:21:05 2019 Need hold release from management interface, waiting...
  Tue Nov 26 10:21:06 2019 MANAGEMENT: Client connected from [AF_INET]127.0.0.1:25340
  Tue Nov 26 10:21:06 2019 MANAGEMENT: CMD 'state on'
  Tue Nov 26 10:21:06 2019 MANAGEMENT: CMD 'log all on'
  Tue Nov 26 10:21:06 2019 MANAGEMENT: CMD 'hold off'
  Tue Nov 26 10:21:06 2019 MANAGEMENT: CMD 'hold release'
  Tue Nov 26 10:21:06 2019 Socket Buffers: R=[8192->8192] S=[8192->8192]
  Tue Nov 26 10:21:06 2019 Attempting to establish TCP connection with [AF_INET]180.76.160.193:1194
  Tue Nov 26 10:21:06 2019 MANAGEMENT: >STATE:1574734866,TCP_CONNECT,,,
  Tue Nov 26 10:21:06 2019 TCP connection established with [AF_INET]180.76.160.193:1194
  Tue Nov 26 10:21:06 2019 TCPv4_CLIENT link local: [undef]
  Tue Nov 26 10:21:06 2019 TCPv4_CLIENT link remote: [AF_INET]180.76.160.193:1194
  Tue Nov 26 10:21:06 2019 MANAGEMENT: >STATE:1574734866,WAIT,,,
  Tue Nov 26 10:21:06 2019 MANAGEMENT: >STATE:1574734866,AUTH,,,
  Tue Nov 26 10:21:06 2019 TLS: Initial packet from [AF_INET]180.76.160.193:1194, sid=676f1fad eba10ac6
  Tue Nov 26 10:21:08 2019 VERIFY OK: depth=1, C=CN, ST=GZ, L=SZ, O=ShenZhen, OU=zengjf, CN=ShenZhen CA, name=zengjf, emailAddress=zengjf42@163.com
  Tue Nov 26 10:21:08 2019 VERIFY OK: nsCertType=SERVER
  Tue Nov 26 10:21:08 2019 VERIFY OK: depth=0, C=CN, ST=GZ, L=SZ, O=ShenZhen, OU=zengjf, CN=zengjf, name=zengjf, emailAddress=zengjf42@163.com
  Tue Nov 26 10:21:11 2019 Data Channel Encrypt: Cipher 'BF-CBC' initialized with 128 bit key
  Tue Nov 26 10:21:11 2019 Data Channel Encrypt: Using 160 bit message hash 'SHA1' for HMAC authentication
  Tue Nov 26 10:21:11 2019 Data Channel Decrypt: Cipher 'BF-CBC' initialized with 128 bit key
  Tue Nov 26 10:21:11 2019 Data Channel Decrypt: Using 160 bit message hash 'SHA1' for HMAC authentication
  Tue Nov 26 10:21:11 2019 Control Channel: TLSv1, cipher TLSv1/SSLv3 DHE-RSA-AES256-SHA, 2048 bit RSA
  Tue Nov 26 10:21:11 2019 [zengjf] Peer Connection Initiated with [AF_INET]180.76.160.193:1194
  Tue Nov 26 10:21:12 2019 MANAGEMENT: >STATE:1574734872,GET_CONFIG,,,
  Tue Nov 26 10:21:13 2019 SENT CONTROL [zengjf]: 'PUSH_REQUEST' (status=1)
  Tue Nov 26 10:21:13 2019 PUSH: Received control message: 'PUSH_REPLY,route 10.8.0.1,topology net30,ping 10,ping-restart 120,ifconfig 10.8.0.6 10.8.0.5'
  Tue Nov 26 10:21:13 2019 OPTIONS IMPORT: timers and/or timeouts modified
  Tue Nov 26 10:21:13 2019 OPTIONS IMPORT: --ifconfig/up options modified
  Tue Nov 26 10:21:13 2019 OPTIONS IMPORT: route options modified
  Tue Nov 26 10:21:13 2019 do_ifconfig, tt->ipv6=0, tt->did_ifconfig_ipv6_setup=0
  Tue Nov 26 10:21:13 2019 MANAGEMENT: >STATE:1574734873,ASSIGN_IP,,10.8.0.6,
  Tue Nov 26 10:21:13 2019 open_tun, tt->ipv6=0
  Tue Nov 26 10:21:13 2019 TAP-WIN32 device [ѾµØl½Ó 5] opened: \\.\Global\{F36D0C71-5A32-4FCC-9327-2687B567F66C}.tap
  Tue Nov 26 10:21:13 2019 TAP-Windows Driver Version 9.9 
  Tue Nov 26 10:21:13 2019 Notified TAP-Windows driver to set a DHCP IP/netmask of 10.8.0.6/255.255.255.252 on interface {F36D0C71-5A32-4FCC-9327-2687B567F66C} [DHCP-serv: 10.8.0.5, lease-time: 31536000]
  Tue Nov 26 10:21:13 2019 Successful ARP Flush on interface [33] {F36D0C71-5A32-4FCC-9327-2687B567F66C}
  Tue Nov 26 10:21:18 2019 TEST ROUTES: 1/1 succeeded len=1 ret=1 a=0 u/d=up
  Tue Nov 26 10:21:18 2019 MANAGEMENT: >STATE:1574734878,ADD_ROUTES,,,
  Tue Nov 26 10:21:18 2019 C:\Windows\system32\route.exe ADD 10.8.0.1 MASK 255.255.255.255 10.8.0.5
  Tue Nov 26 10:21:18 2019 ROUTE: CreateIpForwardEntry succeeded with dwForwardMetric1=30 and dwForwardType=4
  Tue Nov 26 10:21:18 2019 Route addition via IPAPI succeeded [adaptive]
  Tue Nov 26 10:21:18 2019 Initialization Sequence Completed
  Tue Nov 26 10:21:18 2019 MANAGEMENT: >STATE:1574734878,CONNECTED,SUCCESS,10.8.0.6,180.76.160.193
  ```
* ipconfig
  ```
  Windows IP 配置
  
  
  以太网适配器 本地连接 5:
  
     连接特定的 DNS 后缀 . . . . . . . :
     本地链接 IPv6 地址. . . . . . . . : fe80::c044:468f:a878:85a%33
     IPv4 地址 . . . . . . . . . . . . : 10.8.0.6
     子网掩码  . . . . . . . . . . . . : 255.255.255.252
     默认网关. . . . . . . . . . . . . :
  
  [...省略]
  ```

## OpenVPN Linux

* sudo apt-get -y install openvpn
* sudo su
* openvpn --config client.ovpn
  ```
  Tue Nov 26 02:39:51 2019 WARNING: file 'client.key' is group or others accessible
  Tue Nov 26 02:39:51 2019 OpenVPN 2.4.7 arm-unknown-linux-gnueabihf [SSL (OpenSSL)] [LZO] [LZ4] [EPOLL] [PKCS11] [MH/PKTINFO] [AEAD] built on Feb 20 2019
  Tue Nov 26 02:39:51 2019 library versions: OpenSSL 1.1.1c  28 May 2019, LZO 2.10
  Tue Nov 26 02:39:51 2019 WARNING: --ns-cert-type is DEPRECATED.  Use --remote-cert-tls instead.
  Tue Nov 26 02:39:51 2019 TCP/UDP: Preserving recently used remote address: [AF_INET]180.76.160.193:1194
  Tue Nov 26 02:39:51 2019 Socket Buffers: R=[87380->87380] S=[16384->16384]
  Tue Nov 26 02:39:51 2019 Attempting to establish TCP connection with [AF_INET]180.76.160.193:1194 [nonblock]
  Tue Nov 26 02:39:52 2019 TCP connection established with [AF_INET]180.76.160.193:1194
  Tue Nov 26 02:39:52 2019 TCP_CLIENT link local: (not bound)
  Tue Nov 26 02:39:52 2019 TCP_CLIENT link remote: [AF_INET]180.76.160.193:1194
  Tue Nov 26 02:39:52 2019 TLS: Initial packet from [AF_INET]180.76.160.193:1194, sid=64e1d566 0c96172d
  Tue Nov 26 02:39:53 2019 TLS error: Unsupported protocol. This typically indicates that client and server have no common TLS version enabled. This can be caused by mismatched tls-version-min and tls-version-max options on client and server. If your OpenVPN client is between v2.3.6 and v2.3.2 try adding tls-version-min 1.0 to the client configuration to use TLS 1.0+ instead of TLS 1.0 only
  Tue Nov 26 02:39:53 2019 OpenSSL: error:1425F102:SSL routines:ssl_choose_client_version:unsupported protocol
  Tue Nov 26 02:39:53 2019 TLS_ERROR: BIO read tls_read_plaintext error
  Tue Nov 26 02:39:53 2019 TLS Error: TLS object -> incoming plaintext read error
  Tue Nov 26 02:39:53 2019 TLS Error: TLS handshake failed
  Tue Nov 26 02:39:53 2019 Fatal TLS error (check_tls_errors_co), restarting
  Tue Nov 26 02:39:53 2019 SIGUSR1[soft,tls-error] received, process restarting
  Tue Nov 26 02:39:53 2019 Restart pause, 5 second(s)
  Tue Nov 26 02:39:58 2019 WARNING: --ns-cert-type is DEPRECATED.  Use --remote-cert-tls instead.
  Tue Nov 26 02:39:58 2019 TCP/UDP: Preserving recently used remote address: [AF_INET]180.76.160.193:1194
  Tue Nov 26 02:39:58 2019 Socket Buffers: R=[87380->87380] S=[16384->16384]
  Tue Nov 26 02:39:58 2019 Attempting to establish TCP connection with [AF_INET]180.76.160.193:1194 [nonblock]
  Tue Nov 26 02:39:59 2019 TCP connection established with [AF_INET]180.76.160.193:1194
  Tue Nov 26 02:39:59 2019 TCP_CLIENT link local: (not bound)
  Tue Nov 26 02:39:59 2019 TCP_CLIENT link remote: [AF_INET]180.76.160.193:1194
  Tue Nov 26 02:39:59 2019 TLS: Initial packet from [AF_INET]180.76.160.193:1194, sid=099aafa3 6241ac67
  Tue Nov 26 02:39:59 2019 TLS error: Unsupported protocol. This typically indicates that client and server have no common TLS version enabled. This can be caused by mismatched tls-version-min and tls-version-max options on client and server. If your OpenVPN client is between v2.3.6 and v2.3.2 try adding tls-version-min 1.0 to the client configuration to use TLS 1.0+ instead of TLS 1.0 only
  Tue Nov 26 02:39:59 2019 OpenSSL: error:1425F102:SSL routines:ssl_choose_client_version:unsupported protocol
  Tue Nov 26 02:39:59 2019 TLS_ERROR: BIO read tls_read_plaintext error
  Tue Nov 26 02:39:59 2019 TLS Error: TLS object -> incoming plaintext read error
  Tue Nov 26 02:39:59 2019 TLS Error: TLS handshake failed
  Tue Nov 26 02:39:59 2019 Fatal TLS error (check_tls_errors_co), restarting
  Tue Nov 26 02:39:59 2019 SIGUSR1[soft,tls-error] received, process restarting
  Tue Nov 26 02:39:59 2019 Restart pause, 5 second(s)
  ```
* [Debian openvpn client TLS handshake failed](https://community.sophos.com/products/xg-firewall/f/vpn/108514/debian-openvpn-client-tls-handshake-failed)
  * confirmed - the workaround of adding "tls-version-min 1.0" in the .opvn config file allows the connection to establish successfully. 
* grep -vE "^#|^;|^$" client.ovpn
  ```
  client
  dev tun
  proto tcp
  remote 180.76.160.193 1194
  resolv-retry infinite
  nobind
  persist-key
  persist-tun
  ca ca.crt
  cert client.crt
  key client.key
  ns-cert-type server
  tls-version-min 1.0
  comp-lzo
  verb 3
  ```
* openvpn --config client.ovpn &
  ```
  root@raspberrypi:/home/pi/zengjf/vps_openvpn# Tue Nov 26 02:41:07 2019 WARNING: file 'client.key' is group or others accessible
  Tue Nov 26 02:41:07 2019 OpenVPN 2.4.7 arm-unknown-linux-gnueabihf [SSL (OpenSSL)] [LZO] [LZ4] [EPOLL] [PKCS11] [MH/PKTINFO] [AEAD] built on Feb 20 2019
  Tue Nov 26 02:41:07 2019 library versions: OpenSSL 1.1.1c  28 May 2019, LZO 2.10
  Tue Nov 26 02:41:07 2019 WARNING: --ns-cert-type is DEPRECATED.  Use --remote-cert-tls instead.
  Tue Nov 26 02:41:07 2019 TCP/UDP: Preserving recently used remote address: [AF_INET]180.76.160.193:1194
  Tue Nov 26 02:41:07 2019 Socket Buffers: R=[87380->87380] S=[16384->16384]
  Tue Nov 26 02:41:07 2019 Attempting to establish TCP connection with [AF_INET]180.76.160.193:1194 [nonblock]
  Tue Nov 26 02:41:08 2019 TCP connection established with [AF_INET]180.76.160.193:1194
  Tue Nov 26 02:41:08 2019 TCP_CLIENT link local: (not bound)
  Tue Nov 26 02:41:08 2019 TCP_CLIENT link remote: [AF_INET]180.76.160.193:1194
  Tue Nov 26 02:41:08 2019 TLS: Initial packet from [AF_INET]180.76.160.193:1194, sid=30e5d600 a480a658
  Tue Nov 26 02:41:09 2019 VERIFY OK: depth=1, C=CN, ST=GZ, L=SZ, O=ShenZhen, OU=zengjf, CN=ShenZhen CA, name=zengjf, emailAddress=zengjf42@163.com
  Tue Nov 26 02:41:09 2019 VERIFY OK: nsCertType=SERVER
  Tue Nov 26 02:41:09 2019 VERIFY OK: depth=0, C=CN, ST=GZ, L=SZ, O=ShenZhen, OU=zengjf, CN=zengjf, name=zengjf, emailAddress=zengjf42@163.com
  Tue Nov 26 02:41:09 2019 Control Channel: TLSv1, cipher SSLv3 DHE-RSA-AES256-SHA, 2048 bit RSA
  Tue Nov 26 02:41:09 2019 [zengjf] Peer Connection Initiated with [AF_INET]180.76.160.193:1194
  Tue Nov 26 02:41:11 2019 SENT CONTROL [zengjf]: 'PUSH_REQUEST' (status=1)
  Tue Nov 26 02:41:11 2019 PUSH: Received control message: 'PUSH_REPLY,route 10.8.0.1,topology net30,ping 10,ping-restart 120,ifconfig 10.8.0.6 10.8.0.5'
  Tue Nov 26 02:41:11 2019 OPTIONS IMPORT: timers and/or timeouts modified
  Tue Nov 26 02:41:11 2019 OPTIONS IMPORT: --ifconfig/up options modified
  Tue Nov 26 02:41:11 2019 OPTIONS IMPORT: route options modified
  Tue Nov 26 02:41:11 2019 Outgoing Data Channel: Cipher 'BF-CBC' initialized with 128 bit key
  Tue Nov 26 02:41:11 2019 WARNING: INSECURE cipher with block size less than 128 bit (64 bit).  This allows attacks like SWEET32.  Mitigate by using a --cipher with a larger block size (e.g. AES-256-CBC).
  Tue Nov 26 02:41:11 2019 Outgoing Data Channel: Using 160 bit message hash 'SHA1' for HMAC authentication
  Tue Nov 26 02:41:11 2019 Incoming Data Channel: Cipher 'BF-CBC' initialized with 128 bit key
  Tue Nov 26 02:41:11 2019 WARNING: INSECURE cipher with block size less than 128 bit (64 bit).  This allows attacks like SWEET32.  Mitigate by using a --cipher with a larger block size (e.g. AES-256-CBC).
  Tue Nov 26 02:41:11 2019 Incoming Data Channel: Using 160 bit message hash 'SHA1' for HMAC authentication
  Tue Nov 26 02:41:11 2019 WARNING: cipher with small block size in use, reducing reneg-bytes to 64MB to mitigate SWEET32 attacks.
  Tue Nov 26 02:41:11 2019 ROUTE_GATEWAY 192.168.20.254/255.255.255.0 IFACE=wlan0 HWADDR=dc:a6:32:17:47:92
  Tue Nov 26 02:41:11 2019 TUN/TAP device tun0 opened
  Tue Nov 26 02:41:11 2019 TUN/TAP TX queue length set to 100
  Tue Nov 26 02:41:11 2019 /sbin/ip link set dev tun0 up mtu 1500
  Tue Nov 26 02:41:11 2019 /sbin/ip addr add dev tun0 local 10.8.0.6 peer 10.8.0.5
  Tue Nov 26 02:41:11 2019 /sbin/ip route add 10.8.0.1/32 via 10.8.0.5
  Tue Nov 26 02:41:11 2019 WARNING: this configuration may cache passwords in memory -- use the auth-nocache option to prevent this
  Tue Nov 26 02:41:11 2019 Initialization Sequence Completed
  ```
* ifconfig
  ```
  [...省略]
  tun0: flags=4305<UP,POINTOPOINT,RUNNING,NOARP,MULTICAST>  mtu 1500
          inet 10.8.0.6  netmask 255.255.255.255  destination 10.8.0.5
          inet6 fe80::33a6:c03b:c53a:bed7  prefixlen 64  scopeid 0x20<link>
          unspec 00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00  txqueuelen 100  (UNSPEC)
          RX packets 0  bytes 0 (0.0 B)
          RX errors 0  dropped 0  overruns 0  frame 0
          TX packets 7  bytes 336 (336.0 B)
          TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
  [...省略]
  ```
* rc.local中添加开机启动：openvpn --config <path to your client.ovpn> >/var/log/openvpn.log &
* [OpenVPN client on Raspberry Pi](http://kernelreloaded.com/openvpn-client-on-raspberry-pi/)
  * 树莓派设置默认开机自动启动连接，使用`systemctl`进行操作，注意修改`client.conf`中的路径：
    * /etc/openvpn
      ```
      .
      ├── client
      │   ├── ca.crt
      │   ├── client.conf
      │   ├── client.crt
      │   ├── client.csr
      │   ├── client.key
      │   ├── client_keys.tar.bz2
      │   ├── client.ovpn
      │   └── login.conf
      ├── client.conf
      ├── server
      └── update-resolv-conf
      
      2 directories, 10 files
      ```
      * 注意上面`client.conf`和`client.ovpn`的IP，上面的IP都是随便写的；
    * systemctl enable openvpn.service
    * systemctl restart openvpn.service
    * systemctl status openvpn.service
    * ifconfig
