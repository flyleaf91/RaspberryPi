# Cscope

和ctags一样好用的代码跟踪工具

http://cscope.sourceforge.net/


## Install

* `sudo apt-get install cscope`


## Vim Cscope默认按键映射文件

* http://cscope.sourceforge.net/cscope_maps.vim


## 生成索引文件

Cscope在产生索引文件时，只搜索类型为C、lex和yacc的文件(后缀名为.c, .h, .l, .y)，C++的文件根本没有生成索引。不过按照手册上的说明，Cscope支持C++和Java语言的文件。按照Cscope手册上提供的方法，先产生一个文件列表，然后让Cscope为这个列表中的每个文件都生成索引。

```shell
#!/bin/bash

find . -name "*.h" -o -name "*.c" -o -name "*.cc" -o -name "*.S" > cscope.files
cscope -bkq -i cscope.files                     # 生成Cscope索引文件
ctags -R                                        # 生成Ctags索引文件，这个不是必须的
```


## steps

* `wget http://cscope.sourceforge.net/cscope_maps.vim`
  ```
  [...省略]
  " add any cscope database in current directory
  if filereadable("cscope.out")
      cs add cscope.out
  " else add the database pointed to by environment variable
  elseif $CSCOPE_DB != ""                       " 注意这个宏
      cs add $CSCOPE_DB
  endif
  [...省略]
  ```
* `cat cscope_maps.vim >> ~/.vimrc`
* 如上可知`CSCOPE_DB`环境变量可以加载多个Cscope配置索引文件，如果当前目录有索引文件，只加载当前目录下的索引文件；
  * `~/.bashrc`
    ```
    [...省略]
    export CSCOPE_DB=/home/pi/zengjf/rpi-sense/cscope.out
    ```
* 基本使用方法：
  ```
  [...省略]
  nmap <C-\>s :cs find s <C-R>=expand("<cword>")<CR><CR>
  nmap <C-\>g :cs find g <C-R>=expand("<cword>")<CR><CR>
  nmap <C-\>c :cs find c <C-R>=expand("<cword>")<CR><CR>
  nmap <C-\>t :cs find t <C-R>=expand("<cword>")<CR><CR>
  nmap <C-\>e :cs find e <C-R>=expand("<cword>")<CR><CR>
  nmap <C-\>f :cs find f <C-R>=expand("<cfile>")<CR><CR>
  nmap <C-\>i :cs find i ^<C-R>=expand("<cfile>")<CR>$<CR>
  nmap <C-\>d :cs find d <C-R>=expand("<cword>")<CR><CR>
  [...省略]
  ```
  * 常用：
    * `ctrl - \` + `s`：查找原型
    * `ctrl - \` + `c`：查找调用