# repo GitHub Booster

repo使用及GitHub加速

## 参考

* https://github.com/ZengjfOS/manifest
* [Git Repo 镜像使用帮助](https://mirrors.tuna.tsinghua.edu.cn/help/git-repo/)
* [提高ubuntu下访问github的速度](https://blog.csdn.net/hn_tzy/article/details/88903642)
* [Ubuntu改host提速Github](https://www.jianshu.com/p/92ae42e998d5)

## http buffer

* git config --global http.postBuffer 524288000
* git config --list

## GitHub DNS Booster

* sudo apt-get install dnsutils
* nslookup github.com
  ```
  Server:         8.8.8.8
  Address:        8.8.8.8#53
  
  Non-authoritative answer:
  Name:   github.com
  Address: 52.74.223.119
  ```
* nslookup github.global.ssl.fastly.net
  ```
  Server:         8.8.8.8
  Address:        8.8.8.8#53
  
  Non-authoritative answer:
  Name:   github.global.ssl.fastly.net
  Address: 31.13.80.1
  Name:   github.global.ssl.fastly.net
  Address: 2001::1f0d:5601
  ```
* nslookup codeload.github.com
  ```
  Server:         8.8.8.8
  Address:        8.8.8.8#53
  
  Non-authoritative answer:
  Name:   codeload.github.com
  Address: 54.251.140.56
  ```
* vim /etc/hosts
  ```
  127.0.0.1       localhost
  ::1             localhost ip6-localhost ip6-loopback
  ff02::1         ip6-allnodes
  ff02::2         ip6-allrouters
  
  127.0.1.1               raspberrypi
  
  52.74.223.119   http://github.com
  52.74.223.119   https://github.com
  31.13.80.1      http://github.global.ssl.fastly.net
  31.13.80.1      https://github.global.ssl.fastly.net
  54.251.140.56   http://codeload.github.com
  54.251.140.56   https://codeload.github.com
  ```
* /etc/init.d/networking restart
* github目前测试有些仓库提高20倍下载速度，当然有些没有


## 基本使用方法

* export REPO_URL='https://mirrors.tuna.tsinghua.edu.cn/git/git-repo'
* mkdir ../git-repo
* curl https://mirrors.tuna.tsinghua.edu.cn/git/git-repo -o ../git-repo/repo
* chmod +x ../git-repo/repo
* ../git-repo/repo init -u https://github.com/NXPNFCLinux/nxpnfc_android_lollipop.git -m nxpnfc_manifest.xml
  ```bash
  Downloading Repo source from https://mirrors.tuna.tsinghua.edu.cn/git/git-repo
  remote: Counting objects: 5575, done.
  remote: Compressing objects: 100% (2736/2736), done.
  remote: Total 5575 (delta 3602), reused 4609 (delta 2774)
  Receiving objects: 100% (5575/5575), 2.02 MiB | 2.75 MiB/s, done.
  Resolving deltas: 100% (3602/3602), done.
  Downloading manifest from https://github.com/NXPNFCLinux/nxpnfc_android_lollipop.git
  remote: Enumerating objects: 58, done.
  remote: Total 58 (delta 0), reused 0 (delta 0), pack-reused 58
  fatal: manifest 'nxpnfc_manifest.xml' not available
  fatal: remove-project element specifies non-existent project: platform/external/libnfc-nci
  ```
* vim .repo/manifests/nxpnfc_manifest.xml
  ```xml
    <!-- ...省略 -->
  
    <!-- <remove-project name="platform/external/libnfc-nci" /> -->
    <project path="external/libnfc-nci" name="NXPNFCProject/NFC_NCIHAL_libnfc-nci" remote="github_nfc" revision="refs/tags/NFC_NCIHALx_AR0F.3.5.0_L_OpnSrc"/>
    
    <!-- <remove-project name="platform/packages/apps/Nfc" /> -->
    <project path="packages/apps/Nfc" name="NXPNFCProject/NFC_NCIHAL_Nfc" remote="github_nfc" revision="refs/tags/NFC_NCIHALx_AR0F.3.5.0_L_OpnSrc"/>
  
    <!-- ...省略 -->
  ```
  * diff文件
    ```diff
    diff --git a/nxpnfc_manifest.xml b/nxpnfc_manifest.xml
    index 757c9a5..75ebcec 100644
    --- a/nxpnfc_manifest.xml
    +++ b/nxpnfc_manifest.xml
    @@ -2,10 +2,10 @@
     <manifest>
       <remote name="github_nfc" fetch="https://github.com" />
    
    -  <remove-project name="platform/external/libnfc-nci" />
    +  <!-- <remove-project name="platform/external/libnfc-nci" /> -->
       <project path="external/libnfc-nci" name="NXPNFCProject/NFC_NCIHAL_libnfc-nci" remote="github_nfc" revision="refs/tags/NFC_NCIHALx_AR0F.3.5.0_L_OpnSrc"/>
    
    -  <remove-project name="platform/packages/apps/Nfc" />
    +  <!-- <remove-project name="platform/packages/apps/Nfc" /> -->
       <project path="packages/apps/Nfc" name="NXPNFCProject/NFC_NCIHAL_Nfc" remote="github_nfc" revision="refs/tags/NFC_NCIHALx_AR0F.3.5.0_L_OpnSrc"/>
    
       <project path="NxpNfcAndroid/NXPNFC_Reference" name="NXPNFCProject/NXPNFC_Reference" remote="github_nfc" revision="refs/tags/NFC_NCIHALx_AR0F.3.5.0_L_OpnSrc">
    ```
* ../git-repo/repo init -u https://github.com/NXPNFCLinux/nxpnfc_android_lollipop.git -m nxpnfc_manifest.xml
  ```bash
  
  Your identity is: ZengjfOS <zengjf42@163.com>
  If you want to change this, please re-run 'repo init' with --config-name
  
  repo has been initialized in /home/pi/zengjf/NFC
  ```
* ../git-repo/repo sync
  ```bash
  remote: Enumerating objects: 58, done.
  remote: Total 58 (delta 0), reused 0 (delta 0), pack-reused 58
  Fetching projects:  20% (1/5) NXPNFCLinux/nxpnfc_android_lollipopremote: Enumerating objects: 125, done.
  remote: Counting objects: 100% (125/125), done.
  remote: Compressing objects: 100% (80/80), done.
  remote: Total 1441 (delta 43), reused 86 (delta 22), pack-reused 1316
  Receiving objects: 100% (1441/1441), 1.09 MiB | 910.00 KiB/s, done.
  Resolving deltas: 100% (674/674), done.
  Fetching projects:  40% (2/5) NXPNFCProject/NFC_NCIHAL_baseremote: Enumerating objects: 56, done.
  remote: Counting objects: 100% (56/56), done.
  remote: Compressing objects: 100% (49/49), done.
  Receiving objects:  32% (431/1344), 980.01 KiB | 20.00 KiB/s
  ...省略
  ```
