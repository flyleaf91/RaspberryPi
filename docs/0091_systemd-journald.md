# systemd-journald

系统日志

* [一、参考文档](#一参考文档)
* [二、功能说明](#二功能说明)
* [三、配置](#三配置)

## 一、参考文档

* [systemd/Journal (简体中文)](https://wiki.archlinux.org/index.php/Systemd/Journal_(%E7%AE%80%E4%BD%93%E4%B8%AD%E6%96%87))

## 二、功能说明

systemd 提供了自己的日志系统（logging system），称为 journal。使用 systemd 日志，无需额外安装日志服务（syslog）。读取日志的命令：`journalctl`

## 三、配置

* /etc/systemd/journald.conf