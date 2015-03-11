#include <stdio.h>
#include <stdlib.h>


/* 异或运算
 *
 *
 * 布尔环
eg:
 x  00000010  2
 y  00000011  3
 x'=x^y 00000001

 x' 00000001  1
 y  00000011  3
 y'=x^y 00000010  2

 x' 00000001  1
 y' 00000010  2
 x''=x^y    00000011  3
*/


void  swap(int *x, int *y)
{
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
} 

int main(int argc, char **argv)
{
    int a = 2, b = 3;
    swap(&a, &b);
    printf("%d, %d\n", a, b);
    return 0;
}
