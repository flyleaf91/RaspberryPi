# Android RefBase sp wp

理解Android强指针、弱指针

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
