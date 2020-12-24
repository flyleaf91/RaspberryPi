# Android HIDL

突然想再弄一下HIDL，总感觉以前漏了啥 :)

## 参考文档

* https://github.com/ZengjfOS/Android/blob/master/docs/0004_Sensor_HAL.md
* https://github.com/ZengjfOS/Android/tree/hal-zengjf
* [Android P HAL层添加HIDL实例（详细实现步骤）](https://blog.csdn.net/sinat_18179367/article/details/95940030)

## 添加make自动编译

* device/mediatek/system/common/device.mk
  ```Makefile
  PRODUCT_PACKAGES += \
      android.hardware.zengjf@1.0-service
  ```
