#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include "backtrace.h"


/* 测试函数 2 */
void test_meloner() {
    dump_trace();
    return;
}

/* 测试函数 1 */
void test_hutaow() {
    test_meloner();
    return;
}

/* 主函数 */
int main(int argc, char *argv[]) {
    test_hutaow();
    return 0;
}
