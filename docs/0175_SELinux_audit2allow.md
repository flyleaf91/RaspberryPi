# SELinux audit2allow

使用audit2allow处理avc权限

## 参考文档

* https://github.com/ZengjfOS/Android/blob/master/docs/0002_Writing_selinuxswitch_SELinux_Policy.md
* [SELinux avc权限--audit2allow](https://blog.csdn.net/u012944254/article/details/103090753)

## 手动avc修改

```
01-04 23:31:26.925  3622  3622 I auditd  : type=1400 audit(0.0:146): avc: denied { search } for comm="bt_hal_msg_hand" name="/" dev="mmcblk0p35" ino=2 scontext=u:r:mtk_hal_bluetooth:s0 tcontext=u:object_r:cache_file:s0 tclass=dir permissive=0
01-04 23:31:26.925  3622  3622 W bt_hal_msg_hand: type=1400 audit(0.0:146): avc: denied { search } for name="/" dev="mmcblk0p35" ino=2 scontext=u:r:mtk_hal_bluetooth:s0 tcontext=u:object_r:cache_file:s0 tclass=dir permissive=0
```

原因分析

* 文件属性(报错原因)分类：search
* 应用(进程)分类：mtk_hal_bluetooth
* 文件系统分类：cache_file
* 文件分类：dir

根据上面应用分类查找文件，一般应用分类就是文件名，源代码目录下查找应用`.te`文件

* device/mediatek/sepolicy/basic/non_plat/mtk_hal_bluetooth.te
  * allow mtk_hal_bluetooth cache_file:dir search;

## 脚本处理avc

* 抓取log
  * adb logcat -b all | grep "avc:" > avc.txt
* 处理log
  * source build/envsetup.sh
  * lunch
    * 选择项目
  * whereis audit2allow
  * cat avc.txt
    ```
    01-04 23:31:26.921  3622  3622 I auditd  : type=1400 audit(0.0:145): avc: denied { search } for comm="bt_hal_msg_hand" name="/" dev="mmcblk0p10" ino=2 scontext=u:r:mtk_hal_bluetooth:s0 tcontext=u:object_r:metadata_file:s0 tclass=dir permissive=0
    01-04 23:31:26.921  3622  3622 W bt_hal_msg_hand: type=1400 audit(0.0:145): avc: denied { search } for name="/" dev="mmcblk0p10" ino=2 scontext=u:r:mtk_hal_bluetooth:s0 tcontext=u:object_r:metadata_file:s0 tclass=dir permissive=0
    01-04 23:31:26.925  3622  3622 I auditd  : type=1400 audit(0.0:146): avc: denied { search } for comm="bt_hal_msg_hand" name="/" dev="mmcblk0p35" ino=2 scontext=u:r:mtk_hal_bluetooth:s0 tcontext=u:object_r:cache_file:s0 tclass=dir permissive=0
    01-04 23:31:26.925  3622  3622 W bt_hal_msg_hand: type=1400 audit(0.0:146): avc: denied { search } for name="/" dev="mmcblk0p35" ino=2 scontext=u:r:mtk_hal_bluetooth:s0 tcontext=u:object_r:cache_file:s0 tclass=dir permissive=0
    ```
  * audit2allow -i avc.txt
    ```
    
    #============= mtk_hal_bluetooth ==============
    allow mtk_hal_bluetooth cache_file:dir search;
    allow mtk_hal_bluetooth metadata_file:dir search;
    ```
* find * -iname mtk_hal_bluetooth*
  ```
  device/mediatek/sepolicy/basic/r_non_plat/mtk_hal_bluetooth.te
  device/mediatek/sepolicy/basic/non_plat/mtk_hal_bluetooth.te
  ```
* diff
  ```diff
  diff --git a/device/mediatek/sepolicy/basic/non_plat/mtk_hal_bluetooth.te b/device/mediatek/sepolicy/basic/non_plat/mtk_hal_bluetooth.te
  index e08fb56dd7b..d60bb399c57 100644
  --- a/device/mediatek/sepolicy/basic/non_plat/mtk_hal_bluetooth.te
  +++ b/device/mediatek/sepolicy/basic/non_plat/mtk_hal_bluetooth.te
  @@ -50,3 +50,7 @@ hal_server_domain(mtk_hal_bluetooth,hal_bluetooth);
  
   # Purpose: Allow BT Driver to insmod
   allow mtk_hal_bluetooth wmt_prop:property_service set;
  +
  +allow mtk_hal_bluetooth cache_file:dir search;
  +allow mtk_hal_bluetooth metadata_file:dir search;
  +
  diff --git a/device/mediatek/sepolicy/basic/r_non_plat/mtk_hal_bluetooth.te b/device/mediatek/sepolicy/basic/r_non_plat/mtk_hal_bluetooth.te
  index e08fb56dd7b..d60bb399c57 100644
  --- a/device/mediatek/sepolicy/basic/r_non_plat/mtk_hal_bluetooth.te
  +++ b/device/mediatek/sepolicy/basic/r_non_plat/mtk_hal_bluetooth.te
  @@ -50,3 +50,7 @@ hal_server_domain(mtk_hal_bluetooth,hal_bluetooth);
  
   # Purpose: Allow BT Driver to insmod
   allow mtk_hal_bluetooth wmt_prop:property_service set;
  +
  +allow mtk_hal_bluetooth cache_file:dir search;
  +allow mtk_hal_bluetooth metadata_file:dir search;
  +
  ```

## sepolicy domain修改

* https://github.com/ZengjfOS/Android/blob/master/docs/0002_Writing_selinuxswitch_SELinux_Policy.md#selinux
  * type selinuxswitch, domain;  
    * selinuxswitch继承domain的安全策略
* 用这条命令去套下面的命令，下面的命令只是同时设置多个目标的方法：`allow mtk_hal_bluetooth cache_file:dir search;`
* `libsepol.report_failure: neverallow on line 854 of system/sepolicy/public/domain.te (or line 12515 of policy.conf) violated by allow mtk_hal_bluetooth cache_file:file { read };`
  * system/sepolicy/public/domain.te
    ```te
    full_treble_only(`
      # vendor domains may only access files in /data/vendor, never core_data_file_types
      neverallow {
        domain
        -appdomain # TODO(b/34980020) remove exemption for appdomain
        -coredomain
        -data_between_core_and_vendor_violators # TODO(b/34980020) Remove once all violators have been cleaned up
        -vendor_init
      } {
        core_data_file_type
        # libc includes functions like mktime and localtime which attempt to access
        # files in /data/misc/zoneinfo/tzdata and /system/usr/share/zoneinfo/tzdata.
        # These functions are considered vndk-stable and thus must be allowed for
        # all processes.
        -zoneinfo_data_file
        -cache_file
        with_native_coverage(`-method_trace_data_file')
      }:file_class_set ~{ append getattr ioctl read write map };
      neverallow {
        vendor_init
        -data_between_core_and_vendor_violators
      } {
        core_data_file_type
        -unencrypted_data_file
        -zoneinfo_data_file
        with_native_coverage(`-method_trace_data_file')
      }:file_class_set ~{ append getattr ioctl read write map };
      # vendor init needs to be able to read unencrypted_data_file to create directories with FBE.
      # The vendor init binary lives on the system partition so there is not a concern with stability.
      neverallow vendor_init unencrypted_data_file:file ~r_file_perms;
    ')
    ```
    * neverallow
      ```te
      neverallow {
        domain
        -appdomain # TODO(b/34980020) remove exemption for appdomain
        -coredomain
        -data_between_core_and_vendor_violators # TODO(b/34980020) Remove once all violators have been cleaned up
        -vendor_init
      } {
        core_data_file_type
        # libc includes functions like mktime and localtime which attempt to access
        # files in /data/misc/zoneinfo/tzdata and /system/usr/share/zoneinfo/tzdata.
        # These functions are considered vndk-stable and thus must be allowed for
        # all processes.
        -zoneinfo_data_file
        -cache_file
        with_native_coverage(`-method_trace_data_file')
      }:file_class_set ~{ append getattr ioctl read write map };
      ```
      * `{}`中的`-`号: 不包含
        * -cache_file
      * `file_class_set ~{ append getattr ioctl read write map };`
        * `~`：表示不包括该操作；
* `/bin/bash -c "(diff -rq -x bug_map system/sepolicy/prebuilts/api/29.0/public system/sepolicy/public ) && (diff -rq -x bug_map system/sepolicy/prebuilts/api/29.0/private system/sepolicy/private ) && (touch out/target/product/k61v1_64_bsp_pax/obj/ETC/sepolicy_freeze_test_intermediates/sepolicy_freeze_test )"`  
  `Files system/sepolicy/prebuilts/api/29.0/public/domain.te and system/sepolicy/public/domain.te differ`
  * cp system/sepolicy/public/domain.te system/sepolicy/prebuilts/api/29.0/public/domain.te
  * 要保证API策略文件和系统策略文件一样，否则会报错；

## file file_contexts说明

* devices/mediatek/sepolicy/basic/r_non_plat/file_contexts/file.te: 定义文件类型，如果是自己的可执行程序、文件，可以自己另外编写te文件；
  ```
  type custom_file, file_type, data_file_type;
  type lost_found_data_file, file_type, data_file_type;
  type dontpanic_data_file, file_type, data_file_type;
  type resource_cache_data_file, file_type, data_file_type;
  type http_proxy_cfg_data_file, file_type, data_file_type;
  type acdapi_data_file, file_type, data_file_type;
  type ppp_data_file, file_type, data_file_type;
  type wpa_supplicant_data_file, file_type, data_file_type;
  type radvd_data_file, file_type, data_file_type;
  ```
* device/mediatek/sepolicy/basic/r_non_plat/file_contexts: 定义文件节点与文件类型关系，一般直接在file_contexts中写；
  ```
  #############################
  # Data files
  #
  /data/vendor/.tp(/.*)?  u:object_r:thermal_manager_data_file:s0
  /data/vendor_de/meta(/.*)?    u:object_r:mddb_data_file:s0
  /data/aee_exp(/.*)?  u:object_r:aee_exp_data_file:s0
  /data/vendor/aee_exp(/.*)?  u:object_r:aee_exp_vendor_file:s0
  /data/vendor/agps_supl(/.*)?    u:object_r:agpsd_data_file:s0
  #/data/mnl_flp(/.*)?    u:object_r:mnld_data_file:s0
  #/data/mnl_gfc(/.*)?    u:object_r:mnld_data_file:s0
  /data/vendor/gps(/.*)?   u:object_r:gps_data_file:s0
  /data/anr/SF_RTT(/.*)? u:object_r:sf_rtt_file:s0
  /data/vendor/ccci_cfg(/.*)? u:object_r:ccci_cfg_file:s0
  /data/vendor/mdlpm(/.*)? u:object_r:ccci_data_md1_file:s0
  /data/vendor/flashless(/.*)? u:object_r:c2k_file:s0
  /data/core(/.*)? u:object_r:aee_core_data_file:s0
  /data/vendor/core(/.*)? u:object_r:aee_core_vendor_file:s0
  ```
* 以上两个文件修改需要，在文件系统检索，看情况修改，管理者思路不一样，操作不同；
