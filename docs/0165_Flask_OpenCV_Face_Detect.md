# Flask OpenCV Face Detect

Flask作为HTTP视频流，OpenCV识别摄像头采集的人脸

## 参考文档

* [利用flask将opencv实时视频流输出到浏览器](https://www.cnblogs.com/arkenstone/p/7159615.html)
* [流内容](https://dormousehole.readthedocs.io/en/latest/patterns/streaming.html)
* [0163_esp-who.md](0163_esp-who.md)
* [0164_Led_Button.md](0164_Led_Button.md)

## steps

* sudo pip3 install flask
* sudo pip3 install opencv-python
* 下载OpenCV人脸识别模型haarcascade_frontalface_alt.xml，模型可在链接中下载：https://github.com/TimeIvyace/OpenCV-PCA-KNN-SVM_face_recognition.git。
* 参考代码：https://github.com/ZengjfOS/RaspberryPi/tree/FaceDetect
  * face.py