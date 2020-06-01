# README

## 测试方法

* 将dtb放入`dts/mediatek`
* 修改`Makefile`中`CONFIG_BUILD_ARM64_APPENDED_DTB_IMAGE_NAMES="mediatek/mt mediatek/m330"`
  * 空格分隔文件
* 执行：`make`

## log

```
/home/pi/zengjf/dtbo/dts/mediatek/mt.dtb /home/pi/zengjf/dtbo/dts/mediatek/mt330.dtb
make -C libufdt
make[1]: Entering directory '/home/pi/zengjf/dtbo/libufdt'
make -C libfdt
make[2]: Entering directory '/home/pi/zengjf/dtbo/libufdt/libfdt'
fdt.c
fdt.o
gcc -c fdt.c -o fdt.o
fdt_ro.c
fdt_ro.o
gcc -c fdt_ro.c -o fdt_ro.o
fdt_wip.c
fdt_wip.o
gcc -c fdt_wip.c -o fdt_wip.o
fdt_sw.c
fdt_sw.o
gcc -c fdt_sw.c -o fdt_sw.o
fdt_rw.c
fdt_rw.o
gcc -c fdt_rw.c -o fdt_rw.o
fdt_strerror.c
fdt_strerror.o
gcc -c fdt_strerror.c -o fdt_strerror.o
fdt_empty_tree.c
fdt_empty_tree.o
gcc -c fdt_empty_tree.c -o fdt_empty_tree.o
fdt_addresses.c
fdt_addresses.o
gcc -c fdt_addresses.c -o fdt_addresses.o
fdt_overlay.c
fdt_overlay.o
gcc -c fdt_overlay.c -o fdt_overlay.o
acpi.c
acpi.o
gcc -c acpi.c -o acpi.o
rm -f libfdt.a
ar cr libfdt.a fdt.o fdt_ro.o fdt_wip.o fdt_sw.o fdt_rw.o fdt_strerror.o fdt_empty_tree.o fdt_addresses.o fdt_overlay.o acpi.o
rm -f fdt.o fdt_ro.o fdt_wip.o fdt_sw.o fdt_rw.o fdt_strerror.o fdt_empty_tree.o fdt_addresses.o fdt_overlay.o acpi.o
mv libfdt.a ../
make[2]: Leaving directory '/home/pi/zengjf/dtbo/libufdt/libfdt'
make -C libufdt_sysdeps
make[2]: Entering directory '/home/pi/zengjf/dtbo/libufdt/libufdt_sysdeps'
libufdt_sysdeps_posix.c
libufdt_sysdeps_posix.o
gcc -Iinclude -c libufdt_sysdeps_posix.c -o libufdt_sysdeps_posix.o
rm -f libufdt_sysdeps.a
ar cr libufdt_sysdeps.a libufdt_sysdeps_posix.o
rm -f libufdt_sysdeps_posix.o
mv libufdt_sysdeps.a ../
make[2]: Leaving directory '/home/pi/zengjf/dtbo/libufdt/libufdt_sysdeps'
gcc -I./libfdt dt_table.c -Ilibufdt_sysdeps/include  mkdtimg.c  mkdtimg_cfg_create.c  mkdtimg_core.c  mkdtimg_create.c  mkdtimg_dump.c -o mkdtimg -L ./ -lfdt -lufdt_sysdeps
make[1]: Leaving directory '/home/pi/zengjf/dtbo/libufdt'
./libufdt/mkdtimg cfg_create dtbo.img dtboimg.cfg
create image file: dtbo.img...
Total 2 entries.
./libufdt/mkdtimg dump dtbo.img
dt_table_header:
               magic = d7b7ab1e
          total_size = 140025
         header_size = 32
       dt_entry_size = 32
      dt_entry_count = 2
   dt_entries_offset = 32
           page_size = 2048
             version = 0
dt_table_entry[0]:
             dt_size = 91879
           dt_offset = 96
                  id = 00000000
                 rev = 00000000
           custom[0] = 00000000
           custom[1] = 00000000
           custom[2] = 00000000
           custom[3] = 00000000
           (FDT)size = 91879
     (FDT)compatible = mediatek,MT330
dt_table_entry[1]:
             dt_size = 48050
           dt_offset = 91975
                  id = 00000001
                 rev = 00000000
           custom[0] = 00000000
           custom[1] = 00000000
           custom[2] = 00000000
           custom[3] = 00000000
           (FDT)size = 48050
     (FDT)compatible = (unknown)
```
