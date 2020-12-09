# tcp dump

TCP Server抓包

## wireshark

### 不显示抓包网口

* 参考资料：
  ```
  Please check to make sure you have sufficient permissions.
  On Debian and Debian derivatives such as Ubuntu, if you have installed Wireshark from a package, try running
      sudo dpkg-reconfigure wireshark-common
  selecting "<Yes>" in response to the question
      Should non-superusers be able to capture packets?
  adding yourself to the "wireshark" group by running
      sudo usermod -a -G wireshark {your username}
  and then logging out and logging back in again.
  ```
* `sudo dpkg-reconfigure wireshark-common`
  ```
  Package configuration
  
  
   ┌─────────────────────┤ Configuring wireshark-common ├──────────────────────┐
   │                                                                           │ 
   │ Dumpcap can be installed in a way that allows members of the "wireshark"  │ 
   │ system group to capture packets. This is recommended over the             │ 
   │ alternative of running Wireshark/Tshark directly as root, because less    │ 
   │ of the code will run with elevated privileges.                            │ 
   │                                                                           │ 
   │ For more detailed information please see                                  │ 
   │ /usr/share/doc/wireshark-common/README.Debian.                            │ 
   │                                                                           │ 
   │ Enabling this feature may be a security risk, so it is disabled by        │ 
   │ default. If in doubt, it is suggested to leave it disabled.               │ 
   │                                                                           │ 
   │ Should non-superusers be able to capture packets?                         │ 
   │                                                                           │ 
   │                    <Yes>                       <No>                       │ 
   │                                                                           │ 
   └───────────────────────────────────────────────────────────────────────────┘ 
  ```                                                                               
  * YES
* sudo usermod -a -G wireshark {your username}

### wireshark过滤

* tcp.port == 8088
* ip.addr == 192.168.43.65
* tcp.port == 8088 or ip.addr == 192.168.43.65

## Android tcpdump

### 启动测试

* tcpdump dst 192.168.43.89
  ```
  tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
  listening on wlan0, link-type EN10MB (Ethernet), capture size 262144 bytes
  17:56:09.329539 ARP, Request who-has raspberrypi tell 192.168.43.65, length 28
  17:56:10.104057 ARP, Request who-has raspberrypi tell 192.168.43.65, length 28
  17:56:10.872083 ARP, Request who-has raspberrypi tell 192.168.43.65, length 28
  17:56:11.150076 IP 192.168.43.65.38792 > raspberrypi.omniorb: Flags [S], seq 3469319095, win 65535, options [mss 1460,sackOK,TS val 4294920598 ecr 0,nop,wscale 8], length 0
  17:56:11.185749 IP 192.168.43.65.38792 > raspberrypi.omniorb: Flags [.], ack 4209210275, win 343, options [nop,nop,TS val 4294921062 ecr 3923795617], length 0
  17:56:11.190540 IP 192.168.43.65.38792 > raspberrypi.omniorb: Flags [P.], seq 0:4, ack 1, win 343, options [nop,nop,TS val 4294921063 ecr 3923795617], length 4
  17:56:11.207902 IP 192.168.43.65.38792 > raspberrypi.omniorb: Flags [P.], seq 4:13, ack 1, win 343, options [nop,nop,TS val 4294921067 ecr 3923795660], length 9
  17:56:11.209058 IP 192.168.43.65.53060 > raspberrypi.omniorb: Flags [R], seq 2819342342, win 0, length 0
  17:56:16.311957 ARP, Reply 192.168.43.65 is-at 54:81:2d:7a:50:e2 (oui Unknown), length 28
  ```
* tcpdump dst 192.168.43.89 -vv

### 正常断开数据

* tcpdump dst 192.168.43.89
  ```
  tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
  listening on wlan0, link-type EN10MB (Ethernet), capture size 262144 bytes
  17:53:34.011229 IP 192.168.43.65.53060 > raspberrypi.omniorb: Flags [P.], seq 2819342332:2819342334, ack 3404418791, win 343, options [nop,nop,TS val 27223 ecr 3923587930], length 2
  17:53:34.059368 IP 192.168.43.65.53060 > raspberrypi.omniorb: Flags [P.], seq 2:9, ack 1, win 343, options [nop,nop,TS val 27235 ecr 3923638668], length 7
  17:53:36.909255 IP 192.168.43.65.53060 > raspberrypi.omniorb: Flags [F.], seq 9, ack 1, win 343, options [nop,nop,TS val 27947 ecr 3923638677], length 0
  17:53:37.342031 IP 192.168.43.65.53060 > raspberrypi.omniorb: Flags [F.], seq 9, ack 1, win 343, options [nop,nop,TS val 28056 ecr 3923638677], length 0
  17:53:39.176540 ARP, Reply 192.168.43.65 is-at 54:81:2d:7a:50:e2 (oui Unknown), length 28
  ```
* tcpdump dst 192.168.43.89 -vv


## server

```python
#!/usr/bin/env python3
# coding=utf-8

import socket, select
from datetime import datetime

now = datetime.now()
print(now)

s=socket.socket()
host=socket.gethostname()
port=8088
s.bind(("0.0.0.0",port))

fdmap={s.fileno():s}
s.listen(5)
# 得到poll对象
p=select.poll()
p.register(s)

while True:
        events=p.poll()
        for fd,event in events:
                if fd==s.fileno():
                        c,addr = s.accept()
                        now = datetime.now()
                        print(now)
                        print('got connection from ' + str(addr))
                        p.register(c)
                        fdmap[c.fileno()] = c
                elif event & select.POLLIN:
                        now = datetime.now()
                        print(now)
                        data=fdmap[fd].recv(1024)
                        if not data:
                                print(str(fdmap[fd].getpeername()) + ' disconnected')
                                p.unregister(fd)
                                del fdmap[fd]
                        else:   print(str(data))
                                fdmap[fd].send(data)
                                print(str(data))

```
