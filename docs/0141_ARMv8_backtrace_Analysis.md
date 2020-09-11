# ARMv8 backtrace Analysis

ARMv8汇编分析，Android backtrace分析


## 参考文档

* [Armv8-A Instruction Set Architecture - Arm Developer](https://developer.arm.com/-/media/Arm%20Developer%20Community/PDF/Learn%20the%20Architecture/Armv8-A%20Instruction%20Set%20Architecture.pdf?revision=818c7869-3849-4e5d-bde2-710e69defb57)
* [View野指针问题分析报告](https://www.cnblogs.com/yypapa/p/6850939.html)
* [Android导出Dropbox日志](https://www.jianshu.com/p/eecf9aeda074)
* [Android DropboxManager介绍](https://www.jianshu.com/p/f9174a8d0a10)

## ARMv8指令

* [arm-instructionset.pdf](refers/arm-instructionset.pdf)
* [Armv8-A Instruction Set Architecture - Arm Developer](https://developer.arm.com/-/media/Arm%20Developer%20Community/PDF/Learn%20the%20Architecture/Armv8-A%20Instruction%20Set%20Architecture.pdf?revision=818c7869-3849-4e5d-bde2-710e69defb57)
  * [Armv8-A_Instruction_Set_Architecture.pdf](refers/Armv8-A_Instruction_Set_Architecture.pdf)
    * 指令集；
    * **C/C++函数调用的参数寄存器；**
    * **系统调用，ELx异常触发；**

## so异常报错

* sdcard/debuglogger/
* adb shell dumpsys dropbox -p > dropbox.txt

```
========================================
2020-09-07 03:15:51 data_app_native_crash (compressed text, 2572 bytes)
Process: imoblife.androidsensorbox
PID: 22402
UID: 10142
Flags: 0x38a8be44
Package: imoblife.androidsensorbox v27 (6.93)
Foreground: Yes
Build: QP1A.190711.020/67:user/release-keys

*** *** *** *** *** *** *** *** *** *** *** *** *** *** *** ***
Build fingerprint: 'QP1A.190711.020/67:user/release-keys'
Revision: '0'
ABI: 'arm64'
Timestamp: 2020-09-07 03:15:50+0800
pid: 22402, tid: 22402, name: ndroidsensorbox  >>> imoblife.androidsensorbox <<<
uid: 10142
signal 11 (SIGSEGV), code 1 (SEGV_MAPERR), fault addr 0x80ba002d7b
    x0  0000007fdbedabf0  x1  0000000073726563  x2  0000000000000034  x3  0000007fdbedab60
    x4  0000007c61b3ab08  x5  0000007fdbedab60  x6  0000007fdbedabd8  x7  0000000000000000
    x8  00000000de12818b  x9  0000007fdbedabf0  x10 0000007c62176c00  x11 0000000000000000
    x12 000000000000000c  x13 00000000000000ff  x14 0000000000000004  x15 0000000000000005
    x16 0000007c621956e8  x17 0000007c61cbdc18  x18 0000007c64cd8000  x19 0000007fdbedabf0
    x20 0000000000000034  x21 00000080ba002d7b  x22 0000007c643e0020  x23 0000000000000000
    x24 0000007c643e0020  x25 0000000000000000  x26 0000000000000000  x27 0000000012dceb48
    x28 0000000012dceb48  x29 0000007fdbedaa70
    sp  0000007fdbedaa50  lr  0000007c61cbdba0  pc  0000007c61cbdc38

backtrace:
      #00 pc 00000000002eac38  /system/lib64/libhwui.so (SkDescriptor::addEntry(unsigned int, unsigned long, void const*)+32) (BuildId: 0591cf420be9730a7d8df6bf18e00243)
      #01 pc 00000000002eab9c  /system/lib64/libhwui.so (_ZL19generate_descriptorRK18SkScalerContextRecRK19SkBinaryWriteBufferP12SkDescriptor.llvm.312870878177977533+52) (BuildId: 0591cf420be9730a7d8df6bf18e00243)
      #02 pc 00000000002eaa20  /system/lib64/libhwui.so (SkScalerContext::AutoDescriptorGivenRecAndEffects(SkScalerContextRec const&, SkScalerContextEffects const&, SkAutoDescriptor*)+120) (BuildId: 0591cf420be9730a7d8df6bf18e00243)
      #03 pc 00000000002ea978  /system/lib64/libhwui.so (SkScalerContext::CreateDescriptorAndEffectsUsingPaint(SkFont const&, SkPaint const&, SkSurfaceProps const&, SkScalerContextFlags, SkMatrix const&, SkAutoDescriptor*, SkScalerContextEffects*)+64) (BuildId: 0591cf420be9730a7d8df6bf18e00243)
      #04 pc 00000000002faa20  /system/lib64/libhwui.so (SkStrikeCache::FindOrCreateStrikeWithNoDeviceExclusive(SkFont const&, SkPaint const&)+144) (BuildId: 0591cf420be9730a7d8df6bf18e00243)
      #05 pc 00000000002fa7f0  /system/lib64/libhwui.so (SkStrikeCache::FindOrCreateStrikeWithNoDeviceExclusive(SkFont const&)+72) (BuildId: 0591cf420be9730a7d8df6bf18e00243)
      #06 pc 000000000042ae38  /system/lib64/libhwui.so (SkFont::getMetrics(SkFontMetrics*) const+88) (BuildId: 0591cf420be9730a7d8df6bf18e00243)
      #07 pc 00000000001672f8  /system/lib64/libandroid_runtime.so (android::PaintGlue::getMetricsInternal(long, SkFontMetrics*)+96) (BuildId: c41ac3298e350406c23b7adfd605e948)
      #08 pc 0000000000165de0  /system/lib64/libandroid_runtime.so (android::PaintGlue::getFontMetricsInt(_JNIEnv*, _jobject*, long, _jobject*)+56) (BuildId: c41ac3298e350406c23b7adfd605e948)
      #09 pc 00000000002c8ae4  /system/framework/arm64/boot-framework.oat (art_jni_trampoline+180) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #10 pc 0000000000528f18  /system/framework/arm64/boot-framework.oat (android.graphics.Paint.getFontMetricsInt+56) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #11 pc 0000000000872324  /system/framework/arm64/boot-framework.oat (android.text.TextLine.expandMetricsFromPaint+84) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #12 pc 00000000008736a0  /system/framework/arm64/boot-framework.oat (android.text.TextLine.handleText+208) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #13 pc 0000000000872a7c  /system/framework/arm64/boot-framework.oat (android.text.TextLine.handleRun+700) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #14 pc 0000000000874510  /system/framework/arm64/boot-framework.oat (android.text.TextLine.measure+624) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #15 pc 000000000087486c  /system/framework/arm64/boot-framework.oat (android.text.TextLine.metrics+60) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #16 pc 0000000000957484  /system/framework/arm64/boot-framework.oat (android.text.BoringLayout.isBoring+468) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #17 pc 0000000000bb0f38  /system/framework/arm64/boot-framework.oat (android.widget.TextView.makeSingleLayout+200) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #18 pc 0000000000bb0768  /system/framework/arm64/boot-framework.oat (android.widget.TextView.makeNewLayout+696) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #19 pc 0000000000ba6b44  /system/framework/arm64/boot-framework.oat (android.widget.TextView.checkForRelayout+436) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #20 pc 0000000000baac7c  /system/framework/arm64/boot-framework.oat (android.widget.TextView.setText+3660) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #21 pc 0000000000bba13c  /system/framework/arm64/boot-framework.oat (android.widget.TextView.setText+60) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #22 pc 0000000002003af4  /memfd:/jit-cache (deleted) (imoblife.androidsensorbox.orien.SensorOrienActivity.c+2180)
      #23 pc 0000000002005524  /memfd:/jit-cache (deleted) (imoblife.androidsensorbox.orien.SensorOrienActivity$a.onSensorChanged+180)
      #24 pc 000000000065eee8  /system/framework/arm64/boot-framework.oat (android.hardware.SystemSensorManager$SensorEventQueue.dispatchSensorEvent+696) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #25 pc 0000000000136334  /apex/com.android.runtime/lib64/libart.so (art_quick_invoke_stub+548) (BuildId: eeecc2db1acd2cf028d1094c848897b1)
      #26 pc 00000000001450ac  /apex/com.android.runtime/lib64/libart.so (art::ArtMethod::Invoke(art::Thread*, unsigned int*, unsigned int, art::JValue*, char const*)+244) (BuildId: eeecc2db1acd2cf028d1094c848897b1)
      #27 pc 00000000004b09a0  /apex/com.android.runtime/lib64/libart.so (art::(anonymous namespace)::InvokeWithArgArray(art::ScopedObjectAccessAlreadyRunnable const&, art::ArtMethod*, art::(anonymous namespace)::ArgArray*, art::JValue*, char const*)+104) (BuildId: eeecc2db1acd2cf028d1094c848897b1)
      #28 pc 00000000004b1d10  /apex/com.android.runtime/lib64/libart.so (art::InvokeVirtualOrInterfaceWithVarArgs(art::ScopedObjectAccessAlreadyRunnable const&, _jobject*, _jmethodID*, std::__va_list)+424) (BuildId: eeecc2db1acd2cf028d1094c848897b1)
      #29 pc 0000000000397ecc  /apex/com.android.runtime/lib64/libart.so (art::JNI::CallVoidMethodV(_JNIEnv*, _jobject*, _jmethodID*, std::__va_list)+628) (BuildId: eeecc2db1acd2cf028d1094c848897b1)
      #30 pc 00000000000d374c  /system/lib64/libandroid_runtime.so (_JNIEnv::CallVoidMethod(_jobject*, _jmethodID*, ...)+116) (BuildId: c41ac3298e350406c23b7adfd605e948)
      #31 pc 00000000001a18fc  /system/lib64/libandroid_runtime.so ((anonymous namespace)::Receiver::handleEvent(int, int, void*)+548) (BuildId: c41ac3298e350406c23b7adfd605e948)
      #32 pc 000000000001800c  /system/lib64/libutils.so (android::Looper::pollInner(int)+860) (BuildId: f013cbada038685234657c61db8227dc)
      #33 pc 0000000000017c10  /system/lib64/libutils.so (android::Looper::pollOnce(int, int*, int*, void**)+56) (BuildId: f013cbada038685234657c61db8227dc)
      #34 pc 00000000001392ac  /system/lib64/libandroid_runtime.so (android::android_os_MessageQueue_nativePollOnce(_JNIEnv*, _jobject*, long, int)+44) (BuildId: c41ac3298e350406c23b7adfd605e948)
      #35 pc 00000000002d7afc  /system/framework/arm64/boot-framework.oat (art_jni_trampoline+140) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #36 pc 00000000007f9bf4  /system/framework/arm64/boot-framework.oat (android.os.MessageQueue.next+228) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #37 pc 00000000007f69f8  /system/framework/arm64/boot-framework.oat (android.os.Looper.loop+680) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #38 pc 000000000057d28c  /system/framework/arm64/boot-framework.oat (android.app.ActivityThread.main+812) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #39 pc 00000000001365b8  /apex/com.android.runtime/lib64/libart.so (art_quick_invoke_static_stub+568) (BuildId: eeecc2db1acd2cf028d1094c848897b1)
      #40 pc 00000000001450cc  /apex/com.android.runtime/lib64/libart.so (art::ArtMethod::Invoke(art::Thread*, unsigned int*, unsigned int, art::JValue*, char const*)+276) (BuildId: eeecc2db1acd2cf028d1094c848897b1)
      #41 pc 00000000004b09a0  /apex/com.android.runtime/lib64/libart.so (art::(anonymous namespace)::InvokeWithArgArray(art::ScopedObjectAccessAlreadyRunnable const&, art::ArtMethod*, art::(anonymous namespace)::ArgArray*, art::JValue*, char const*)+104) (BuildId: eeecc2db1acd2cf028d1094c848897b1)
      #42 pc 00000000004b23e8  /apex/com.android.runtime/lib64/libart.so (art::InvokeMethod(art::ScopedObjectAccessAlreadyRunnable const&, _jobject*, _jobject*, _jobject*, unsigned long)+1472) (BuildId: eeecc2db1acd2cf028d1094c848897b1)
      #43 pc 000000000043e138  /apex/com.android.runtime/lib64/libart.so (art::Method_invoke(_JNIEnv*, _jobject*, _jobject*, _jobjectArray*)+48) (BuildId: eeecc2db1acd2cf028d1094c848897b1)
      #44 pc 00000000000c5c34  /system/framework/arm64/boot.oat (art_jni_trampoline+180) (BuildId: c7ebc4733c71833c7f3c65b20e5c38f098e0c0a9)
      #45 pc 0000000000a77fc8  /system/framework/arm64/boot-framework.oat (com.android.internal.os.RuntimeInit$MethodAndArgsCaller.run+136) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #46 pc 0000000000a7ff94  /system/framework/arm64/boot-framework.oat (com.android.internal.os.ZygoteInit.main+2132) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
      #47 pc 00000000001365b8  /apex/com.android.runtime/lib64/libart.so (art_quick_invoke_static_stub+568) (BuildId: eeecc2db1acd2cf028d1094c848897b1)
      #48 pc 00000000001450cc  /apex/com.android.runtime/lib64/libart.so (art::ArtMethod::Invoke(art::Thread*, unsigned int*, unsigned int, art::JValue*, char const*)+276) (BuildId: eeecc2db1acd2cf028d1094c848897b1)
      #49 pc 00000000004b09a0  /apex/com.android.runtime/lib64/libart.so (art::(anonymous namespace)::InvokeWithArgArray(art::ScopedObjectAccessAlreadyRunnable const&, art::ArtMethod*, art::(anonymous namespace)::ArgArray*, art::JValue*, char const*)+104) (BuildId: eeecc2db1acd2cf028d1094c848897b1)
      #50 pc 00000000004b0600  /apex/com.android.runtime/lib64/libart.so (art::InvokeWithVarArgs(art::ScopedObjectAccessAlreadyRunnable const&, _jobject*, _jmethodID*, std::__va_list)+408) (BuildId: eeecc2db1acd2cf028d1094c848897b1)
      #51 pc 00000000003bba30  /apex/com.android.runtime/lib64/libart.so (art::JNI::CallStaticVoidMethodV(_JNIEnv*, _jclass*, _jmethodID*, std::__va_list)+624) (BuildId: eeecc2db1acd2cf028d1094c848897b1)
      #52 pc 00000000000c058c  /system/lib64/libandroid_runtime.so (_JNIEnv::CallStaticVoidMethod(_jclass*, _jmethodID*, ...)+116) (BuildId: c41ac3298e350406c23b7adfd605e948)
      #53 pc 00000000000c34ac  /system/lib64/libandroid_runtime.so (android::AndroidRuntime::start(char const*, android::Vector<android::String8> const&, bool)+908) (BuildId: c41ac3298e350406c23b7adfd605e948)
      #54 pc 00000000000034e0  /system/bin/app_process64 (main+1168) (BuildId: c2e530ee2de0f331f5dd227dd19985ae)
      #55 pc 000000000007d86c  /apex/com.android.runtime/lib64/bionic/libc.so (__libc_init+108) (BuildId: 2a5abdc9c768b33656f7aa8d9ce5cf54)
```

## 汇编与C函数关系

* void* SkDescriptor::addEntry(uint32_t tag, size_t length, const void* data) {
  * x0: this
  * x1: tag
  * x2: length
  * x3: data
  * 如果参数大于8(x0 ~ x7)个的时候，用栈进行参数传递
* w[x]是x[x]寄存器的低32bit；

## so反汇编分析栈信息

* 确定代码位置
  * ./prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-addr2line -f -e out/target/product/\<your project\>/symbols/system/lib64/libhwui.so 00000000002eac38
    ```
    _ZN12SkDescriptor8addEntryEjmPKv
    external/skia/src/core/SkDescriptor.cpp:29
    ```
* external/skia/src/core/SkDescriptor.cpp:29
  ```CPP
  void* SkDescriptor::addEntry(uint32_t tag, size_t length, const void* data) {
      SkASSERT(tag);
      SkASSERT(SkAlign4(length) == length);
      SkASSERT(this->findEntry(tag, nullptr) == nullptr);
  
      Entry* entry = (Entry*)((char*)this + fLength);
      entry->fTag = tag;
      entry->fLen = SkToU32(length);
      if (data) {
          memcpy(entry + 1, data, length);
      }
  
      fCount += 1;
      fLength = SkToU32(fLength + sizeof(Entry) + length);
      return (entry + 1); // return its data
  }
  ```
* ./prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-objdump -d out/target/product/\<your project\>/symbols/system/lib64/libhwui.so > objdump_libhwui.so
  ```ASM
  PC        |   二进制码    |    汇编
  -------------------------------------------------------------------------------------------------
  2eac18:   |   f81d0ff5   |    str     x21, [sp,#-48]!                                       ; 入栈
  2eac1c:   |   a9014ff4   |    stp     x20, x19, [sp,#16]                                    ; 入栈
  2eac20:   |   a9027bfd   |    stp     x29, x30, [sp,#32]                                    ; 入栈
  2eac24:   |   910083fd   |    add     x29, sp, #0x20                                        ; 将 sp + 0x20 保存到 x29
  2eac28:   |   b9400408   |    ldr     w8, [x0,#4]                                           ; 将 x0(this) + 4 地址空间中的值写入 w8  --> Entry* entry = (Entry*)((char*)this + fLength);
  2eac2c:   |   aa0003f3   |    mov     x19, x0                                               ; 将 x0(this) 写入 x19(this)
  2eac30:   |   aa0203f4   |    mov     x20, x2                                               ; 将 x2(length) 写入 x20
  2eac34:   |   8b080015   |    add     x21, x0, x8                                           ; 将 x0(this) + x8 写入 x21             --> Entry* entry = (Entry*)((char*)this + fLength);
  2eac38:   |   290052a1   |    stp     w1, w20, [x21]                                        ; 将 w1，w20 写入 x21 的地址空间         --> entry->fTag = tag; entry->fLen = SkToU32(length);
  2eac3c:   |   b40000a3   |    cbz     x3, 2eac50 <_ZN12SkDescriptor8addEntryEjmPKv+0x38>    ; 将 x3 与 0 作比较，相等就 PC = 2eac50  --> if (data) {}
  2eac40:   |   910022a0   |    add     x0, x21, #0x8                                         ; 将 x21 + 0x08(entry + 1) 写入 x0      --> entry + 1
  2eac44:   |   aa0303e1   |    mov     x1, x3                                                ; 将 x3(data) 写入 x1
  2eac48:   |   aa1403e2   |    mov     x2, x20                                               ; 将 x20 写入 x2
  2eac4c:   |   941250ad   |    bl      77ef00 <memcpy@plt>                                   ; 跳转到 77ef00
  2eac50:   |   2940a269   |    ldp     w9, w8, [x19,#4]                                      ; 将 x19(this) + 4 地址空间加载到 w9，w8
  2eac54:   |   910022a0   |    add     x0, x21, #0x8                                         ; 将 x21(entry) + 0x08 写入 x0          --> (entry + 1)
  2eac58:   |   0b090289   |    add     w9, w20, w9                                           ; 将 w20(length) + w9(fLength) 写入 w9
  2eac5c:   |   11000508   |    add     w8, w8, #0x1                                          ; 将 w8（fCount) + 1 写入 w8
  2eac60:   |   11002129   |    add     w9, w9, #0x8                                          ; 将 w9 + 0x08(sizeof(Entry)) 写入 w9
  2eac64:   |   2900a269   |    stp     w9, w8, [x19,#4]                                      ; 将 w9，w8 写入 x19(this) + 4的地址空间
  2eac68:   |   a9427bfd   |    ldp     x29, x30, [sp,#32]                                    ; 出栈
  2eac6c:   |   a9414ff4   |    ldp     x20, x19, [sp,#16]                                    ; 出栈
  2eac70:   |   f84307f5   |    ldr     x21, [sp],#48                                         ; 出栈
  2eac74:   |   d65f03c0   |    ret
  ```
* stack
  ```
  signal 11 (SIGSEGV), code 1 (SEGV_MAPERR), fault addr 0x80ba002d7b
      x0  0000007fdbedabf0  x1  0000000073726563  x2  0000000000000034  x3  0000007fdbedab60
      x4  0000007c61b3ab08  x5  0000007fdbedab60  x6  0000007fdbedabd8  x7  0000000000000000
      x8  00000000de12818b  x9  0000007fdbedabf0  x10 0000007c62176c00  x11 0000000000000000
      x12 000000000000000c  x13 00000000000000ff  x14 0000000000000004  x15 0000000000000005
      x16 0000007c621956e8  x17 0000007c61cbdc18  x18 0000007c64cd8000  x19 0000007fdbedabf0
      x20 0000000000000034  x21 00000080ba002d7b  x22 0000007c643e0020  x23 0000000000000000
      x24 0000007c643e0020  x25 0000000000000000  x26 0000000000000000  x27 0000000012dceb48
      x28 0000000012dceb48  x29 0000007fdbedaa70
      sp  0000007fdbedaa50  lr  0000007c61cbdba0  pc  0000007c61cbdc38
  ```
  * fault addr: 0x80ba002d7b
  * x21: 00000080ba002d7b
  * stp     w1, w20, [x21]
    * ldr     w8, [x0,#4]
    * add     x21, x0, x8
    * x0: 0000007fdbedabf0
    * x8: 00000000de12818b
  * Entry* entry = (Entry*)((char*)this + fLength);
* x0附近内存情况，x0是this指针，也就是SkDescriptor实例对象的内存信息：
  ```
  memory near x0 ([stack]):
      0000007fdbedabd0 0000000100000000 0000000000000000  ................
      0000007fdbedabe0 0000000000000000 0000007fdbedabf0  ................
      0000007fdbedabf0 de12818b466b10f2 737265634033ea68  ..kF....h.3@cers
      0000007fdbedac00 0000007c643e0020 3f80000042100000   .>d|......B...?
      0000007fdbedac10 0000007fdbedac20 0000007c61d76b54   .......Tk.a|...
      0000007fdbedac20 0000007fdbedac70 0000007c61d76ac8  p........j.a|...
      0000007fdbedac30 0000000042a00000 0000000000000000  ...B............
      0000007fdbedac40 0000000042a00000 0000000000000000  ...B............
      0000007fdbedac50 000000123f800000 25d97ffee7defc85  ...?...........%
      0000007fdbedac60 0000000044800000 25d97ffee7defc85  ...D...........%
      0000007fdbedac70 0000000000000000 0000007fdbedad68  ........h.......
      0000007fdbedac80 0000007c643e0020 0000007c643e0020   .>d|... .>d|...
      0000007fdbedac90 0000007fdbedad10 0000007c61ccd7f4  ...........a|...
      0000007fdbedaca0 0000000000000000 0000000000000000  ................
      0000007fdbedacb0 0000000000000000 0000000000000000  ................
      0000007fdbedacc0 0000000000000000 0000000000000000  ................
  ```
  * 0000007fdbedabf0 de12818b466b10f2 737265634033ea68  ..kF....h.3@cers
    * 分析SkDescriptor(external/skia/src/core/SkDescriptor.h)类成员变量的内部偏移：
      ```CPP
      class SkDescriptor : SkNoncopyable {
      public:
          static size_t ComputeOverhead(int entryCount) {
              SkASSERT(entryCount >= 0);
              return sizeof(SkDescriptor) + entryCount * sizeof(Entry);
          }
      
          static std::unique_ptr<SkDescriptor> Alloc(size_t length);
      
          // Ensure the unsized delete is called.
          void operator delete(void* p);
          void init() {
              fLength = sizeof(SkDescriptor);
              fCount  = 0;
          }
          uint32_t getLength() const { return fLength; }
          void* addEntry(uint32_t tag, size_t length, const void* data = nullptr);
          void computeChecksum();
      
      #ifdef SK_DEBUG
          void assertChecksum() const {
              SkASSERT(SkDescriptor::ComputeChecksum(this) == fChecksum);
          }
      #endif
      
          const void* findEntry(uint32_t tag, uint32_t* length) const;
      
          std::unique_ptr<SkDescriptor> copy() const;
      
          // This assumes that all memory added has a length that is a multiple of 4. This is checked
          // by the assert in addEntry.
          bool operator==(const SkDescriptor& other) const;
          bool operator!=(const SkDescriptor& other) const { return !(*this == other); }
      
          uint32_t getChecksum() const { return fChecksum; }
      
          struct Entry {
              uint32_t fTag;
              uint32_t fLen;
          };
      
      #ifdef SK_DEBUG
          uint32_t getCount() const { return fCount; }
      #endif
      
      private:
          // private so no one can create one except our factories
          SkDescriptor() = default;
      
          static uint32_t ComputeChecksum(const SkDescriptor* desc);
      
          uint32_t fChecksum;  // must be first
          uint32_t fLength;    // must be second
          uint32_t fCount;
      };
      ```
      * uint32_t fLength;
      * 偏移为4；
    * de12818b
    * x8: de12818b

## backtrace分析思路

* `libhwui.so`是更新UI的库，这个库出现问题，大多数是因为界面卡死导致的；
* 如上一直往前推，直到跟UI界面更新无关的地方：
  ```
  backtrace:
        #00 pc 00000000002eac38  /system/lib64/libhwui.so (SkDescriptor::addEntry(unsigned int, unsigned long, void const*)+32) (BuildId: 0591cf420be9730a7d8df6bf18e00243)
        #01 pc 00000000002eab9c  /system/lib64/libhwui.so (_ZL19generate_descriptorRK18SkScalerContextRecRK19SkBinaryWriteBufferP12SkDescriptor.llvm.312870878177977533+52) (BuildId: 0591cf420be9730a7d8df6bf18e00243)
        ...省略
        #20 pc 0000000000baac7c  /system/framework/arm64/boot-framework.oat (android.widget.TextView.setText+3660) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
        #21 pc 0000000000bba13c  /system/framework/arm64/boot-framework.oat (android.widget.TextView.setText+60) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
        #22 pc 0000000002003af4  /memfd:/jit-cache (deleted) (imoblife.androidsensorbox.orien.SensorOrienActivity.c+2180)
        #23 pc 0000000002005524  /memfd:/jit-cache (deleted) (imoblife.androidsensorbox.orien.SensorOrienActivity$a.onSensorChanged+180)
        #24 pc 000000000065eee8  /system/framework/arm64/boot-framework.oat (android.hardware.SystemSensorManager$SensorEventQueue.dispatchSensorEvent+696) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
        #25 pc 0000000000136334  /apex/com.android.runtime/lib64/libart.so (art_quick_invoke_stub+548) (BuildId: eeecc2db1acd2cf028d1094c848897b1)
        #26 pc 00000000001450ac  /apex/com.android.runtime/lib64/libart.so (art::ArtMethod::Invoke(art::Thread*, unsigned int*, unsigned int, art::JValue*, char const*)+244) (BuildId: eeecc2db1acd2cf028d1094c848897b1)
        ...省略
  ```
* 重点如下这段
  ```
  #21 pc 0000000000bba13c  /system/framework/arm64/boot-framework.oat (android.widget.TextView.setText+60) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
  #22 pc 0000000002003af4  /memfd:/jit-cache (deleted) (imoblife.androidsensorbox.orien.SensorOrienActivity.c+2180)
  #23 pc 0000000002005524  /memfd:/jit-cache (deleted) (imoblife.androidsensorbox.orien.SensorOrienActivity$a.onSensorChanged+180)
  #24 pc 000000000065eee8  /system/framework/arm64/boot-framework.oat (android.hardware.SystemSensorManager$SensorEventQueue.dispatchSensorEvent+696) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
  ```
* 传感器回调出问题了：
  ```
  #24 pc 000000000065eee8  /system/framework/arm64/boot-framework.oat (android.hardware.SystemSensorManager$SensorEventQueue.dispatchSensorEvent+696) (BuildId: aa500a0a2435e72b267b4df74f02350a01dd4fc1)
  ```
* ./prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-addr2line -f -e out/target/product/\<your project\>/symbols/system/framework/arm64/boot-framework.oat 000000000065eee8
  ```
  void android.hardware.SystemSensorManager$SensorEventQueue.dispatchSensorEvent(int, float[], int, long)
  $JAVA_SRC_ROOT/android/hardware/SystemSensorManager.java:837
  ```
* find * -iname SystemSensorManager.java
  ```
  frameworks/base/core/java/android/hardware/SystemSensorManager.java
  ```
* vim frameworks/base/core/java/android/hardware/SystemSensorManager.java +837
  ```Java
  protected void dispatchSensorEvent(int handle, float[] values, int inAccuracy,
          long timestamp) {
      final Sensor sensor = mManager.mHandleToSensor.get(handle);
      if (sensor == null) {
          // sensor disconnected
          return;
      }
  
      SensorEvent t = null;
      synchronized (mSensorsEvents) {
          t = mSensorsEvents.get(handle);
      }
  
      if (t == null) {
          // This may happen if the client has unregistered and there are pending events in
          // the queue waiting to be delivered. Ignore.
          return;
      }
      // Copy from the values array.
      System.arraycopy(values, 0, t.values, 0, t.values.length);
      t.timestamp = timestamp;
      t.accuracy = inAccuracy;
      t.sensor = sensor;
  
      // call onAccuracyChanged() only if the value changes
      final int accuracy = mSensorAccuracies.get(handle);
      if ((t.accuracy >= 0) && (accuracy != t.accuracy)) {
          mSensorAccuracies.put(handle, t.accuracy);
          mListener.onAccuracyChanged(t.sensor, t.accuracy);
      }
      mListener.onSensorChanged(t);
  }
  ```
* bug问题判断为传感器数据上报太频繁了

