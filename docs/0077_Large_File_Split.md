# Large File Splite

splite分割大文件

## 参考文档

* [Linux大文件分割splite](https://www.cnblogs.com/zengjfgit/p/9002193.html)
* [How to Split Large Text File into Smaller Files in Linux](https://linoxide.com/linux-how-to/split-large-text-file-smaller-files-linux/)

## Steps

* `split -b <size> <input file name> <output file prefix name>`
  ```Shell
  pi@raspberrypi:~/zengjf/split_dir $ ls -al
  total 12
  drwxr-xr-x  2 pi pi 4096 Feb 10 06:41 .
  drwxr-xr-x 51 pi pi 4096 Feb 10 06:41 ..
  -rw-r--r--  1 pi pi 2006 Feb 10 06:41 mxc_mmc_test.tar.bz2
  pi@raspberrypi:~/zengjf/split_dir $ split -b 1k mxc_mmc_test.tar.bz2 mxc_mmc_test.tar.bz2
  pi@raspberrypi:~/zengjf/split_dir $ ls
  mxc_mmc_test.tar.bz2  mxc_mmc_test.tar.bz2aa  mxc_mmc_test.tar.bz2ab
  pi@raspberrypi:~/zengjf/split_dir $ ls -al
  total 20
  drwxr-xr-x  2 pi pi 4096 Feb 10 06:42 .
  drwxr-xr-x 51 pi pi 4096 Feb 10 06:41 ..
  -rw-r--r--  1 pi pi 2006 Feb 10 06:41 mxc_mmc_test.tar.bz2
  -rw-r--r--  1 pi pi 1024 Feb 10 06:42 mxc_mmc_test.tar.bz2aa
  -rw-r--r--  1 pi pi  982 Feb 10 06:42 mxc_mmc_test.tar.bz2ab
  ```
* cat mxc_mmc_test.tar.bz2a* > mxc_mmc_test.tar.bz2c
* tar xvf mxc_mmc_test.tar.bz2c
* **The SIZE argument is an integer and optional unit (example: 10K is 10*1024). Units are K,M,G,T,P,E,Z,Y (powers of 1024) or KB,MB,... (powers of 1000).**