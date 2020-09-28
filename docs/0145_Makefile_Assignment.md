# Makefile Assignment

Makefile赋值`=`/`:=`/`?=`/`+=`区别

## 参考文档

* [Makefile 中:= ?= += =的区别](https://www.cnblogs.com/wanqieddy/archive/2011/09/21/2184257.html)

## 简述

* `=`: 是最基本的赋值
* `:=`: 是覆盖之前的值
* `?=`: 是如果没有被赋值过就赋予等号后面的值
* `+=`: 是添加等号后面的值

其中`=`，`make`会将整个`Makefile`展开后，再决定变量的值。也就是说，变量的值将会是整个`Makefile`中最后被指定的值。如示例：

```Makefile
x = foo
y = $(x) bar
x = xyz
```

在上例中，`y`的值将会是`xyz bar`，而不是`foo bar`。

而`:=`，表示变量的值决定于它在`Makefile`中的位置，而不是整个`Makefile`展开后的最终值：

```Makefile
x := foo
y := $(x) bar
x := xyz
```

在上例中，`y`的值将会是`foo bar`，而不是`xyz bar`了。
