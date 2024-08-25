#include <stdio.h>

int g[5]; // 全局变量声明数组， 数组元素会被初始化为0

int main(int argc, char *argv[]) {

    // -------------- 数组初始化的方式 ----------------

    int a[5]; // 本地变量声明的数组，不会进行初始化，数组元素都是随机值
    for (int i = 0; i < 5; i++) {
        printf("a[%d] = %d\n", i, a[i]);
    }


    static int b[5]; // 静态变量，数组元素会被初始化为0
    for (int i = 0; i < 5; i++) {
        printf("b[%d] = %d\n", i, b[i]);
    }

    // 全局变量声明数组，数组元素会被初始化为0
    for (int i = 0; i < 5; i++) {
        printf("g[%d] = %d\n", i, g[i]);
    }


    /*
    * 字符串通过字面量创建数组
    * 1.字符串的值存储在 text-segment 只读，不能修改
    * 2.指针变量s存储在栈上，值是指向数据区的指针
    */
    char *s = "hello world";
    for (char c = *s; c != '\0'; c = *(++s)) {
        printf("%c", c);
    }

    // 指向数组的指针
    char *arrayptr[] = {"hello", "world", "welcome", "backbone"};

    // 常用计算数组长度的方法
    size_t len = sizeof(arrayptr) / sizeof(arrayptr[0]);
    printf("pointer array length %ld\n", len);
    
    for (int i = 0; i < len; i++) {
        printf("%s\n", arrayptr[i]);
    }




}