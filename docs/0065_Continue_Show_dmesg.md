# Continue Show dmesg

在终端持续显示dmesg信息

## 参考文档

* [How can I see dmesg output as it changes?](https://unix.stackexchange.com/questions/95842/how-can-i-see-dmesg-output-as-it-changes)


## dmesg

* dmesg --help
  ```
  -w, --follow                wait for new messages
  ```


## tail

* tail --help
  ```
  -f, --follow[={name|descriptor}]
  ```
* tail -f /var/log/kern.log