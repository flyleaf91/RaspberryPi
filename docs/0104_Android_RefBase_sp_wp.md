# Android RefBase sp wp

本来想把Android RefBase sp wp移到RPI上使用，暂时不行

## 一、参考文档

* [Android中sp和wp的使用](https://www.cnblogs.com/chen-cai/p/9947906.html)
* [Android智能指针SP WP使用方法介绍](https://www.cnblogs.com/polo/p/5672856.html)

## 二、简述

* sp（强指针）是通过引用计数来记录有多少使用者在使用一个对象，如果所有使用者都放弃了对该对象的引用，则该对象将被自动销毁；
* wp（弱指针）在指向一个对象时，仅仅记录该对象的地址，不能通过弱指针来访问该对象（即：不能通过弱指针来调用该对象的成员）；
* 假设有一个类MyClass，我们要用智能指针来引用这个类的对象，那么这个类需要满足下面两个条件：
  * `::Android::sp<MyClass> myClass = new MyClass();`
    * 此时定义好的myClass就可以像普通指针一样去使用了。在我们不需要再使用该智能指针时，只需将myClass = NULL;即可。（普通指针的定义方法：MyClass *myClass）
  * `::Android::wp<MyClass> myClass = new MyClass();`
    * 此时不能用myClass去调用该对象的成员，需要先升级为强指针，`::Android::sp<MyClass> pMyClass = myClass.promote();`
* Android智能指针用起来是很方便，在一般情况下最好使用智能指针来代替普通指针，但是智能指针是一个对象，并不是一个真正的指针，因此运行效率是远远比不上普通指针的，所以在运行效率敏感的地方，最好还是不要使用智能指针。
