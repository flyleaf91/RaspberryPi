# Jenkins

用Jenkins来定时编译源代码

## 参考文档

* [Installing Jenkins on your Raspberry Pi](https://pimylifeup.com/jenkins-raspberry-pi/)

## Java

`java --version`

```
openjdk 11.0.6 2020-01-14
OpenJDK Runtime Environment (build 11.0.6+10-post-Raspbian-1deb10u1)
OpenJDK Server VM (build 11.0.6+10-post-Raspbian-1deb10u1, mixed mode)
```

## Install

* wget -q -O - https://pkg.jenkins.io/debian/jenkins.io.key | sudo apt-key add -
* sudo sh -c 'echo deb https://pkg.jenkins.io/debian binary/ > /etc/apt/sources.list.d/jenkins.list'
* sudo apt-get update
* sudo apt-get install jenkins
* hostname -I
* sudo cat /var/lib/jenkins/secrets/initialAdminPassword
  * 8dfec453d7f04b2998d02c6ce6791793
* http://192.168.137.2:8080  
  ![Jenkins_Login_Page.png](images/Jenkins_Login_Page.png)
  * 8dfec453d7f04b2998d02c6ce6791793
  * 登录之后，安装默认推荐的Plugin
  * 设置一个管理员信息
  * 进入系统界面  
    ![Jenkins_Welcome.png](images/Jenkins_Welcome.png)
