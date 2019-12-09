# wav Sound Generator

## 参考文档

* [Generate wavfile](https://github.com/ZengjfOS/ASoC/blob/master/docs/0019_Generate_wavfile/README.md)

## steps

* `raspi-config`
  * Advanced Options
    * Audio
      * Force 3.5mm ('headphone') jack
* `ls /dev/snd/`
  ```
  by-path  controlC0  pcmC0D0p  pcmC0D1p  pcmC0D2p  seq  timer
  ```
* https://github.com/ZengjfOS/RaspberryPi/tree/wavfile
  * make
  * wavfile
    * sound.wav
* `aplay sound.wav`