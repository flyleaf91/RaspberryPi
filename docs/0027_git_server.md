# git server

搭建git服务器

## 参考文档

* [Setting up Your Raspberry Pi as a Git Server](https://www.sitepoint.com/setting-up-your-raspberry-pi-as-a-git-server/)

## steps

* `sudo adduser git`
* `su git`
* `mkdir helloworld.git`
* `cd helloworld.git`
* `git init --bare`
* `git clone git@192.168.31.189:/home/git/helloworld.git`
  ```
  Cloning into 'helloworld'...
  The authenticity of host '192.168.31.189 (192.168.31.189)' can't be established.
  ECDSA key fingerprint is SHA256:8RCzBU02hBV/GA7E9tJpgvpKRDbauZ1dlfQg9FVmOUs.
  Are you sure you want to continue connecting (yes/no/[fingerprint])? yes
  Warning: Permanently added '192.168.31.189' (ECDSA) to the list of known hosts.
  git@192.168.31.189's password:
  warning: You appear to have cloned an empty repository.
  ```
* 树莓重装系统之后ssh指纹修改了
  ```
  $ git push git@192.168.137.2:RaspberryPI.git master
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  @    WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!     @
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  IT IS POSSIBLE THAT SOMEONE IS DOING SOMETHING NASTY!
  Someone could be eavesdropping on you right now (man-in-the-middle attack)!
  It is also possible that a host key has just been changed.
  The fingerprint for the ECDSA key sent by the remote host is
  SHA256:RxQb/R2LbS5J8V/srH68+F+7wmZU2kSWD9vYd4OHW0Q.
  Please contact your system administrator.
  Add correct host key in /c/Users/zengjianfeng/.ssh/known_hosts to get rid of this message.
  Offending ECDSA key in /c/Users/zengjianfeng/.ssh/known_hosts:1
  ECDSA host key for 192.168.137.2 has changed and you have requested strict checking.
  Host key verification failed.
  fatal: Could not read from remote repository.
  
  Please make sure you have the correct access rights
  and the repository exists.
  ```
  * [How to fix warning about ECDSA host key](https://superuser.com/questions/421004/how-to-fix-warning-about-ecdsa-host-key)
  * ssh-keygen -R 192.168.137.2
