# RPI4 USB Camera

还以为摄像头坏了，结果是这个版本的内核不支持YUYV获取图像，要用MJPEG的方式获取，这样的获取的图像数据就不需要进行转换了，直接保存数据就可以看图像；

## 参考文档

* [[Buster] USB camera, Internal data stream error](https://www.raspberrypi.org/forums/viewtopic.php?t=250379)
* [sample](https://github.com/ZengjfOS/V4L2/tree/master/docs/0002_v4l2_capture/sample)
* https://gist.github.com/jayrambhia/5866483

## v4l2-compliance

* khadas
  ```
  khadas@Khadas:sample$ v4l2-compliance | grep FAIL
                  test VIDIOC_QUERY_EXT_CTRL/QUERYMENU: FAIL
                  test VIDIOC_G/S_PARM: FAIL
                  test VIDIOC_G_FMT: FAIL
  ```
* rpi4
  ```
  root@raspberrypi:/home/pi# v4l2-compliance | grep FAIL
          test VIDIOC_QUERY_EXT_CTRL/QUERYMENU: FAIL
          test VIDIOC_G/S_CTRL: FAIL
          test VIDIOC_G/S/TRY_EXT_CTRLS: FAIL
          test VIDIOC_G/S_PARM: FAIL
          test VIDIOC_REQBUFS/CREATE_BUFS/QUERYBUF: FAIL
  
  ```

## fswebcam

```
root@raspberrypi:/home/pi# fswebcam -r 640x480 –no-banner test_4k.jpg
--- Opening /dev/video0...
Trying source module v4l2...
/dev/video0 opened.
No input was specified, using the first.
--- Capturing frame...
Captured frame in 0.00 seconds.
--- Processing captured image...
Writing JPEG image to '–no-banner'.
Writing JPEG image to 'test_4k.jpg'.
```

## sample code patch

* [sample](https://github.com/ZengjfOS/V4L2/tree/master/docs/0002_v4l2_capture/sample)
  ```diff
  index 1895a6c..dbcc739 100644
  --- a/docs/0002_v4l2_capture/sample/getyuyv.c
  +++ b/docs/0002_v4l2_capture/sample/getyuyv.c
  @@ -12,8 +12,8 @@
  
   #define WIDTH 640                      // 图片的宽度
   #define HEIGHT 480                     // 图片的高度
  -#define FMT V4L2_PIX_FMT_YUYV          // 图片格式
  -#define COUNT 5                        // 缓冲区个数
  +#define FMT V4L2_PIX_FMT_MJPEG         // 图片格式
  +#define COUNT 2                        // 缓冲区个数
  
   // int main(int argc, char **argv) {
   int main() {
  @@ -112,7 +112,7 @@ int main() {
          }
  
          /* 第八步：从退出队列的缓冲区中获取数据并保存到文件中 */
  -       FILE *fl; fl = fopen("./my.yuyv", "w");
  +       FILE *fl; fl = fopen("./my.jpg", "w");
          if (NULL == fl) {
                  fprintf(stderr, "open write file failed.");
          }
  ```
