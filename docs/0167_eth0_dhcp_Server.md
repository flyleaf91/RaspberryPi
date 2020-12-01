# eth0 dhcp Server

搭建dhcp服务用于测试

## 命令行操作

* sudo apt-get update
* sudo apt-get install isc-dhcp-server
* sudo systemctl enable isc-dhcp-server.service
* sudo systemctl restart isc-dhcp-server.service
* ifconfig eth0 192.168.40.0/24

## 配置网卡

cat /etc/default/isc-dhcp-server

```
# Defaults for isc-dhcp-server (sourced by /etc/init.d/isc-dhcp-server)

# Path to dhcpd's config file (default: /etc/dhcp/dhcpd.conf).
#DHCPDv4_CONF=/etc/dhcp/dhcpd.conf
#DHCPDv6_CONF=/etc/dhcp/dhcpd6.conf

# Path to dhcpd's PID file (default: /var/run/dhcpd.pid).
#DHCPDv4_PID=/var/run/dhcpd.pid
#DHCPDv6_PID=/var/run/dhcpd6.pid

# Additional options to start dhcpd with.
#       Don't use options -cf or -pf here; use DHCPD_CONF/ DHCPD_PID instead
#OPTIONS=""

# On what interfaces should the DHCP server (dhcpd) serve DHCP requests?
#       Separate multiple interfaces with spaces, e.g. "eth0 eth1".
INTERFACESv4="eth0"
INTERFACESv6=""
```

## dhcp配置

`cat /etc/dhcp/dhcpd.conf`

```
subnet 192.168.40.0 netmask 255.255.255.0 {
        range 192.168.40.2 192.168.40.30;
        option domain-name-servers 192.168.40.1;
        option domain-name "internal.example.org";
        option routers 192.168.40.1;
        option broadcast-address 192.168.40.255;
        default-lease-time 600;
        max-lease-time 7200;
}
```

## 配置静态IP

`/etc/dhcpcd.conf`

```
interface eth0
static ip_address=192.168.40.0/24
# static routers=192.168.137.1
static domain_name_servers=8.8.8.8
```

## 启动

* sudo systemctl enable isc-dhcp-server.service
* sudo systemctl start isc-dhcp-server.service
  * 由于网卡静态IP只有连接的时候才会设置，导致dhcp server无法再开机的时候自启动
