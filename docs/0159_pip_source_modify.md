# pip source modify

pip安装软件的时候经常会出现超时导致无法安装

## 参考文档

* [pypi 镜像使用帮助](https://mirrors.tuna.tsinghua.edu.cn/help/pypi/)
* [Updating the pip.conf file to use https](https://stackoverflow.com/questions/24353459/updating-the-pip-conf-file-to-use-https)
* [树莓派 pip 手动安装 和使用阿里云源](https://blog.csdn.net/weixin_30809173/article/details/96627513)

## 换源

* 安装一些python软件出现超时现象的时候，可能是国内访问国外服务器太慢了，可以切换一些国内的源
  * [pypi 镜像使用帮助](https://mirrors.tuna.tsinghua.edu.cn/help/pypi/)
    * pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple
    * pip config set global.extra-index-url https://pypi.tuna.tsinghua.edu.cn/simple
    * cat ~/.config/pip/pip.conf
* 如果使用上面的国内的源出问题，可以切换回默认的源
  * pip config set global.index-url https://pypi.org/simple
  * pip config set global.extra-index-url https://www.piwheels.org/simple

## 超时

* 如果上面的换源还是不行，那么就把timeout时间改大：
  * vim ~/.config/pip/pip.conf
    ```
    [global]
    timeout = 600
    index-url = https://pypi.tuna.tsinghua.edu.cn/simple
    extra-index-url = https://pypi.tuna.tsinghua.edu.cn/simple
    ```
  * vim /etc/pip.conf
