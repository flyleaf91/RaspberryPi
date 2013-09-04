Android系统当中一共用wp（Weak Pointer）  sp（Strong Pointer） lightRefBase（Light Pointer）这些智能指针来回收new出来的内存，所有的代码都在RefBase.cpp RefBase.h里面。
这3种当中，轻量级的指针是最简单的，其中只有一个mCount这个计数器来计算类的引用有多少次，等于0的时候直接销毁类。
Wp 和sp 相当复杂，如果让一个类A要使用到这套机制，首先要让这个类继承RefBase这个类，然后在wp跟sp这2个类里，把这个类A赋值到这2个类里的m_ptr成员变量里面，这样，m_ptr就直接指向A。
这些类的关系可以这样描述：
RefBase这个类，里面有一个mRefs的计数变量，那个变量里面还继承了RefBase里面另外一个内嵌变量，但是里面作用就是作为调试用的可以不管，其他的有4个重要的变量：专门负责计算强引用(mStrong)，弱引用(mWeak)，存储class A（mBase）和存储class A的生命周期(mFlags)。这些变量的修改都不是在这个类里面修改的，之后会由sp，wp调用这些变量所在的操作函数，专门对这些变量进行操作。
Sp这个类和wp这个类都是一个模板类，他们调用的时候，首先一定要sp<A> spA= new A;,sp会把A加到他的成员变量m_ptr里，而wp会把A和mRefs这个计数变量也加进来。每申请一个新的sp，mRefs里面的mStrong，mWeak会增加1，每申请一个新的wp，mWeak会增加一，在销毁的时候也按照这个顺序销毁。
Wp 和sp有什么区别呢？最大的区别就是sp可以直接操作class A，因为这个类里面重载了->和*，并且实现了get成员函数，这样可以获得到class A，但是wp没有这2个重载。
Wp和sp还有个区别，在sp里面，只有一个m_ptr指向classA，但是在wp里面，除了有m_ptr指向class A，还有m_refs指向RefBase类里面专门用作计数的一个内嵌类。
引用进强，弱指针，主要是可以对class A的生命周期进行划分，并且根据生命周期的情况而酌情进行销毁类。
生命周期一共有3种情况，0， OBJECT_LIFETIME_WEAK 和OBJECT_LIFETIME_FOREVER 默认是0，这3种情况是有RefBase：：weakref_impl::mFlags进行保存的。
1，如果对象的mFlags为0，那么单纯的强引用计数为0就会delete class A，这种情况跟Light Pointer实现差不多。
2，如果对象的mFlags为OBJECT_LIFETIME_WEAK，那么强，弱计数都为0的时候，才会delete class A
3,如果对象的mFlags为OBJECT_LIFETIME_FOREVER，那么class不会delete掉，直到程序员手动delete才会消失。这种情况跟普通的指针应用就差不多了。
想要改变对象的生命周期，可以在class A的构造函数里调用extendObjectLifetime(xxx);来改变默认的mFlags值。
如何方便的调试这些代码？由于所有的类都在RefBase.cpp和RefBase.h里面，可以把这2个文件拷贝到本地目录，然后修改其中的log，textOutput和原子操作，调试仅仅需要在单线程的情况下就可以了
