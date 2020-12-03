# Android RefBase sp wp

理解Android强指针、弱指针，将sp、wp理解为RefBase的容器更好理解

## 参考文档

* [0168_gtest.md](0168_gtest.md)
* [android-refbase-sample](https://github.com/leelwh/android-refbase-sample)
  ```diff
  diff --git a/Makefile b/Makefile
  old mode 100755
  new mode 100644
  index cfc46b5..10160e1
  --- a/Makefile
  +++ b/Makefile
  @@ -2,7 +2,7 @@ all:RefBase.o test.o
          g++ RefBase.o test.o -o all
   RefBase.o:RefBase.cpp RefBase.h
  -       g++ -g -c RefBase.cpp -o RefBase.o
  +       g++ -g -c RefBase.cpp -o RefBase.o -fpermissive
   test.o:test.cpp
          g++ -g -c -fpermissive test.cpp -o test.o
  ```

## install

* sudo apt-get install libgtest-dev

## 示例编译运行

* https://github.com/ZengjfOS/RaspberryPi/tree/Android_RefBase
  * 修改自：https://android.googlesource.com/platform/system/core/+/master/libutils/
* cmake CMakeLists.txt
* make
* ./runTests

```
[==========] Running 6 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 6 tests from RefBase
[ RUN      ] RefBase.StrongMoves
[       OK ] RefBase.StrongMoves (0 ms)
[ RUN      ] RefBase.WeakCopies
[       OK ] RefBase.WeakCopies (0 ms)
[ RUN      ] RefBase.Comparisons
[       OK ] RefBase.Comparisons (0 ms)
[ RUN      ] RefBase.ReplacedComparison
[       OK ] RefBase.ReplacedComparison (0 ms)
[ RUN      ] RefBase.RacingDestructors
[       OK ] RefBase.RacingDestructors (1620 ms)
[ RUN      ] RefBase.RacingPromotions
[       OK ] RefBase.RacingPromotions (2542 ms)
[----------] 6 tests from RefBase (4165 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 1 test case ran. (4167 ms total)
[  PASSED  ] 6 tests.
```

## RefBase StrongMoves示例分析

### Foo类

```CPP
class Foo : public RefBase {
public:
    Foo(bool* deleted_check) : mDeleted(deleted_check) {
        *mDeleted = false;
    }

    ~Foo() {
        *mDeleted = true;
    }
private:
    bool* mDeleted;
};
```

### Foo TEST

```CPP
TEST(RefBase, StrongMoves) {
    bool isDeleted;
    Foo* foo = new Foo(&isDeleted);
    ASSERT_EQ(INITIAL_STRONG_VALUE, foo->getStrongCount());
    ASSERT_FALSE(isDeleted) << "Already deleted...?";
    sp<Foo> sp1(foo);
    wp<Foo> wp1(sp1);
    ASSERT_EQ(1, foo->getStrongCount());
    // Weak count includes both strong and weak references.
    ASSERT_EQ(2, foo->getWeakRefs()->getWeakCount());
    {
        sp<Foo> sp2 = std::move(sp1);
        ASSERT_EQ(1, foo->getStrongCount())
                << "std::move failed, incremented refcnt";
        ASSERT_EQ(nullptr, sp1.get()) << "std::move failed, sp1 is still valid";
        // The strong count isn't increasing, let's double check the old object
        // is properly reset and doesn't early delete
        sp1 = std::move(sp2);
    }
    ASSERT_FALSE(isDeleted) << "deleted too early! still has a reference!";
    {
        // Now let's double check it deletes on time
        sp<Foo> sp2 = std::move(sp1);
    }
    ASSERT_TRUE(isDeleted) << "foo was leaked!";
    ASSERT_TRUE(wp1.promote().get() == nullptr);
}
```

## 理解sp、wp容器

1. 添加构造、析构打印；
2. 修改访问局部变量权限；
3. 添加测试代码；

```diff
diff --git a/RefBase_test.cpp b/RefBase_test.cpp
index c9b4894..f090512 100755
--- a/RefBase_test.cpp
+++ b/RefBase_test.cpp
@@ -35,13 +35,15 @@ static constexpr int INITIAL_STRONG_VALUE = 1 << 28;  // Mirroring RefBase defin
 class Foo : public RefBase {
 public:
     Foo(bool* deleted_check) : mDeleted(deleted_check) {
+        printf("Foo\n");
         *mDeleted = false;
     }

     ~Foo() {
+        printf("~Foo\n");
         *mDeleted = true;
     }
-private:
+public:
     bool* mDeleted;
 };

@@ -83,6 +85,23 @@ private:
 int FooFixedAlloc::mAllocCount(0);
 void* FooFixedAlloc::theMemory(nullptr);

+TEST(RefBase, CheckSP) {
+    bool isDeleted;
+    Foo* foo = new Foo(&isDeleted);
+    sp<Foo> sp1(foo);
+    {
+        sp<Foo> sp2 = std::move(sp1);
+        printf("foo->mDeleted: %d\n", *(foo->mDeleted));
+        printf("sp1->mDeleted: %d\n", *(sp2->mDeleted));
+    }
+    printf("foo->mDeleted: %d\n", *(foo->mDeleted));
+    printf("sp1->mDeleted: %d\n", *(sp1->mDeleted));
+    ASSERT_FALSE(isDeleted) << "deleted too early! still has a reference!";
+}
+
+#if 0
+
 TEST(RefBase, StrongMoves) {
     bool isDeleted;
     Foo* foo = new Foo(&isDeleted);
@@ -406,3 +425,4 @@ TEST(RefBase, RacingPromotions) {
         ASSERT_EQ(NITERS, deleteCount) << "Deletions missed!";
     }  // Otherwise this is slow and probably pointless on a uniprocessor.
 }
+#endif
```

测试log如下：

```shell
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from RefBase
[ RUN      ] RefBase.CheckSP
Foo
foo->mDeleted: 0
sp1->mDeleted: 0
~Foo
foo->mDeleted: 1
Segmentation fault
```

1. 创建foo，调用构造函数；
2. 将foo放入容器sp1；
3. {}创建新的栈空间；
4. sp1容器转移到sp2容器，sp1相当于释放了foo；
5. 输出foo、sp2指向的内部变量值；
6. 跳出前面创建的栈空间，此时foo释放，调用析构函数；
7. 输出foo内部变量值；
8. sp1前面已经释放了，这里段错误；

## sp强指针分析

### sp构造函数

通过sp构造函数将对象方入容器，可以是对象，也可以本身也是sp，或者其他的；

```cpp
template<typename T>
sp<T>::sp(T* other)
        : m_ptr(other) {
    if (other)
        other->incStrong(this);
}

template<typename T>
sp<T>::sp(const sp<T>& other)
        : m_ptr(other.m_ptr) {
    if (m_ptr)
        m_ptr->incStrong(this);
}

template <typename T>
sp<T>::sp(sp<T>&& other) noexcept : m_ptr(other.m_ptr) {
    other.m_ptr = nullptr;
}

template<typename T> template<typename U>
sp<T>::sp(U* other)
        : m_ptr(other) {
    if (other)
        (static_cast<T*>(other))->incStrong(this);
}

template<typename T> template<typename U>
sp<T>::sp(const sp<U>& other)
        : m_ptr(other.m_ptr) {
    if (m_ptr)
        m_ptr->incStrong(this);
}

template<typename T> template<typename U>
sp<T>::sp(sp<U>&& other)
        : m_ptr(other.m_ptr) {
    other.m_ptr = nullptr;
}
```

### sp赋值

赋值也是函数，通过sp赋值函数将对象方入容器，可以是对象，也可以本身也是sp，或者其他的；

```cpp
template<typename T>
sp<T>& sp<T>::operator =(const sp<T>& other) {
    // Force m_ptr to be read twice, to heuristically check for data races.
    T* oldPtr(*const_cast<T* volatile*>(&m_ptr));
    T* otherPtr(other.m_ptr);
    if (otherPtr) otherPtr->incStrong(this);
    if (oldPtr) oldPtr->decStrong(this);
    if (oldPtr != *const_cast<T* volatile*>(&m_ptr)) sp_report_race();
    m_ptr = otherPtr;
    return *this;
}

template <typename T>
sp<T>& sp<T>::operator=(sp<T>&& other) noexcept {
    T* oldPtr(*const_cast<T* volatile*>(&m_ptr));
    if (oldPtr) oldPtr->decStrong(this);
    if (oldPtr != *const_cast<T* volatile*>(&m_ptr)) sp_report_race();
    m_ptr = other.m_ptr;
    other.m_ptr = nullptr;
    return *this;
}

template<typename T>
sp<T>& sp<T>::operator =(T* other) {
    T* oldPtr(*const_cast<T* volatile*>(&m_ptr));
    if (other) other->incStrong(this);
    if (oldPtr) oldPtr->decStrong(this);
    if (oldPtr != *const_cast<T* volatile*>(&m_ptr)) sp_report_race();
    m_ptr = other;
    return *this;
}

template<typename T> template<typename U>
sp<T>& sp<T>::operator =(const sp<U>& other) {
    T* oldPtr(*const_cast<T* volatile*>(&m_ptr));
    T* otherPtr(other.m_ptr);
    if (otherPtr) otherPtr->incStrong(this);
    if (oldPtr) oldPtr->decStrong(this);
    if (oldPtr != *const_cast<T* volatile*>(&m_ptr)) sp_report_race();
    m_ptr = otherPtr;
    return *this;
}

template<typename T> template<typename U>
sp<T>& sp<T>::operator =(sp<U>&& other) {
    T* oldPtr(*const_cast<T* volatile*>(&m_ptr));
    if (m_ptr) m_ptr->decStrong(this);
    if (oldPtr != *const_cast<T* volatile*>(&m_ptr)) sp_report_race();
    m_ptr = other.m_ptr;
    other.m_ptr = nullptr;
    return *this;
}

template<typename T> template<typename U>
sp<T>& sp<T>::operator =(U* other) {
    T* oldPtr(*const_cast<T* volatile*>(&m_ptr));
    if (other) (static_cast<T*>(other))->incStrong(this);
    if (oldPtr) oldPtr->decStrong(this);
    if (oldPtr != *const_cast<T* volatile*>(&m_ptr)) sp_report_race();
    m_ptr = other;
    return *this;
}
```

### sp指针操作

指针操作也是函数，通过返回`m_ptr`，从而相当于操作对象；

```cpp
inline T&       operator* () const     { return *m_ptr; }
inline T*       operator-> () const    { return m_ptr;  }
```

### sp析构

主要就是计数减一，那问题来了，到底是谁最终调用了对象的析构函数？那就再看一下`decStrong()`是怎么处理的

```cpp
template<typename T>
sp<T>::~sp() {
    if (m_ptr)
        m_ptr->decStrong(this);
}
```

如下所示，当调用`decStrong()`，发现`count == 1`的时候，就会调用`delete this`；

```cpp
void RefBase::decStrong(const void* id) const
{
    weakref_impl* const refs = mRefs;
    refs->removeStrongRef(id);
    const int32_t c = refs->mStrong.fetch_sub(1, std::memory_order_release);
#if PRINT_REFS
    ALOGD("decStrong of %p from %p: cnt=%d\n", this, id, c);
#endif
    LOG_ALWAYS_FATAL_IF(BAD_STRONG(c), "decStrong() called on %p too many times",
            refs);
    if (c == 1) {
        std::atomic_thread_fence(std::memory_order_acquire);
        refs->mBase->onLastStrongRef(id);
        int32_t flags = refs->mFlags.load(std::memory_order_relaxed);
        if ((flags&OBJECT_LIFETIME_MASK) == OBJECT_LIFETIME_STRONG) {
            delete this;
            // The destructor does not delete refs in this case.
        }
    }
    // Note that even with only strong reference operations, the thread
    // deallocating this may not be the same as the thread deallocating refs.
    // That's OK: all accesses to this happen before its deletion here,
    // and all accesses to refs happen before its deletion in the final decWeak.
    // The destructor can safely access mRefs because either it's deleting
    // mRefs itself, or it's running entirely before the final mWeak decrement.
    //
    // Since we're doing atomic loads of `flags`, the static analyzer assumes
    // they can change between `delete this;` and `refs->decWeak(id);`. This is
    // not the case. The analyzer may become more okay with this patten when
    // https://bugs.llvm.org/show_bug.cgi?id=34365 gets resolved. NOLINTNEXTLINE
    refs->decWeak(id);
}
```
