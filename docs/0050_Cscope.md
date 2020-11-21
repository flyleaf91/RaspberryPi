# cscope

和ctags一样好用的代码跟踪工具

http://cscope.sourceforge.net/


## Install

* `sudo apt-get install cscope`


## Vim Cscope默认按键映射文件

* http://cscope.sourceforge.net/cscope_maps.vim

`~/.vimrc`

```vimrc
set hlsearch
hi Search ctermbg=white
hi Search ctermfg=black

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" cscope setting

if has("cscope")
    set csprg=/usr/bin/cscope
    set csto=1
    set cst
    set nocsverb
    " add any database in current directory
    " if filereadable("cscope.out")
    "     cs add cscope.out
    " endif
    cs add /home/pi/zengjf/helloworld/cscope.out /home/pi/zengjf/helloworld
    set csverb
endif

nmap <C-\>s :cs find s <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>g :cs find g <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>c :cs find c <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>t :cs find t <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>e :cs find e <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>f :cs find f <C-R>=expand("<cfile>")<CR><CR>
nmap <C-\>i :cs find i ^<C-R>=expand("<cfile>")<CR>$<CR>
nmap <C-\>d :cs find d <C-R>=expand("<cword>")<CR><CR>
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
```

## 生成索引文件

### 根据文件生成索引

Cscope在产生索引文件时，只搜索类型为C、lex和yacc的文件(后缀名为.c, .h, .l, .y)，C++的文件根本没有生成索引。不过按照手册上的说明，Cscope支持C++和Java语言的文件。按照Cscope手册上提供的方法，先产生一个文件列表，然后让Cscope为这个列表中的每个文件都生成索引。

```shell
#!/bin/bash

find . -name "*.h" -o -name "*.c" -o -name "*.cc" -o -name "*.S" > cscope.files
cscope -bkq -i cscope.files                     # 生成Cscope索引文件
ctags -R                                        # 生成Ctags索引文件，这个不是必须的
```

### 项目目录生成索引

`cscope -Rb`

* 默认cscope输出文件不像ctags输出文件可以在.vimrc中添加很多，vim开启的地方要有cscope.out才能索引
* [How to let cscope use absolute path in cscope.out file?](https://stackoverrun.com/cn/q/450057)
  * :cscope add /path/to/cscope.out /path/to/src/code
  * ~/.vimrc
    * cs add /home/pi/zengjf/helloworld/cscope.out /home/pi/zengjf/helloworld
* 这种用的比较多

## 快捷键说明

* s: 查找C语言符号，即查找函数名、宏、枚举值等出现的地方
* g: 查找函数、宏、枚举等定义的位置，类似ctags所提供的功能
* d: 查找本函数调用的函数
* c: 查找调用本函数的函数
* t: 查找指定的字符串
* e: 查找egrep模式，相当于egrep功能，但查找速度快多了
* f: 查找并打开文件，类似vim的find功能
* i: 查找包含本文件的文
