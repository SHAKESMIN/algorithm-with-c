/*
 * Copyright (c) 2015, SHAKESMIN <chengminxie at yahoo dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* 复杂度：指数级 */
long long fib1(int n)
{
    if (0 == n) return 0;
    if (1 == n) return 1;
    return fib1(n - 1) + fib1(n - 2);
}

/* 复杂度: O(N) */
long long fib2(int n)
{
    if (0 == n) return 0;
    if (1 == n) return 1;

    long long a = 0, b = 1;
    int i;
    for (i = 2; i <= n; i+=2)
    {
        a = a + b;
        b = a + b;
    }
    return n % 2 == 0 ? a : b;
}


/* 复杂度: O(lgN) 
先介绍一个数学公式：
{f(n), f(n-1), f(n-1), f(n-2)} ={1, 1, 1,0}n-1
(注：{f(n+1), f(n), f(n), f(n-1)}表示一个矩阵。在矩阵中第一行第一列是f(n+1)，第一行第二列是f(n)，第二行第一列是f(n)，第二行第二列是f(n-1)。) 有了这个公式，要求得f(n)，我们只需要求得矩阵{1, 1, 1,0}的n-1次方，因为矩阵{1, 1, 1,0}的n-1次方的结果的第一行第一列就是f(n)。这个数学公式用数学归纳法不难证明。感兴趣的朋友不妨自己证明一下。 现在的问题转换为求矩阵{1, 1, 1, 0}的乘方。如果简单第从0开始循环，n次方将需要n次运算，并不比前面的方法要快。但我们可以考虑乘方的如下性质：

    /  an/2*an/2                      n为偶数时
    an=
    \  a(n-1)/2*a(n-1)/2            n为奇数时

    要求得n次方，我们先求得n/2次方，再把n/2的结果平方一下。如果把求n次方的问题看成一个大问题，把求n/2看成一个较小的问题。这种把大问题分解成一个或多个小问题的思路我们称之为分治法。这样求n次方就只需要logn次运算了。

    实现这种方式时，首先需要定义一个2×2的矩阵，并且定义好矩阵的乘法以及乘方运算。当这些运算定义好了之后，剩下的事情就变得非常简单。
*/
typedef struct {
    long long m00;
    long long m01;
    long long m10;
    long long m11;
} Matrix2_2;

Matrix2_2 matrix_mul(const Matrix2_2 m, const Matrix2_2 n)
{
    Matrix2_2  matrix = { 0 };
    matrix.m00 = m.m00 * n.m00 + m.m01 * n.m10;
    matrix.m01 = m.m00 * n.m01 + m.m01 * n.m11;
    matrix.m10 = m.m10 * n.m00 + m.m11 * n.m10;
    matrix.m11 = m.m10 * n.m01 + m.m11 * n.m11;
    return matrix;
}

Matrix2_2 matrix_power(int n)
{
    assert(n > 0);
    Matrix2_2 matrix;
    if (1 == n) 
        matrix = (Matrix2_2){1, 1, 1, 0};
    else if (n % 2 == 0)
    {
        matrix = matrix_power(n / 2);
        matrix = matrix_mul(matrix, matrix);
    } 
    else if (n % 2 == 1)
    {
        matrix = matrix_power( (n - 1) / 2);
        matrix = matrix_mul(matrix, matrix);
        matrix = matrix_mul(matrix, (Matrix2_2){1, 1, 1, 0});
    }
    return matrix;
}

long long  fib3(int n)
{
    if (0 == n) return 0;
    if (1 == n) return 1;
    
    Matrix2_2  res = matrix_power(n - 1);
    return res.m00; 
}


int main(int argc, char **argv)
{
    int n = atoi(argv[1]);
    printf("fibonacci1(%d) = %ld\n", n, fib3(n));
    printf("fibonacci2(%d) = %ld\n", n, fib2(n));
    printf("fibonacci1(%d) = %ld\n", n, fib1(n));
    return 0;
}
