# Local Socket

## 参考文档

* [unix_server.c](https://gist.github.com/tscho/397539)
* [unix_client.c](https://gist.github.com/tscho/397591)

## Code

* https://github.com/ZengjfOS/RaspberryPi/tree/LocalSocket
* 分析本地socket的工作原理，实现server、client通信；
* 利用SIGCHLD，实现父进程监听子进程退出，Android的内部init进程使用这个机制；
* 通常exec会放在fork() 函数的子进程部分, 来替代子进程执行啦, 执行成功后子程序就会消失,  但是执行失败的话, 必须用exit()函数来让子进程退出!
