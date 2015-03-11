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

/*
 最大公约数： 欧几里德算法又称辗转相除法，用于计算两个整数a,b的最大公约数。

 基本算法：设a=qb+r，其中a，b，q，r都是整数，则gcd(a,b)=gcd(b,r)，即gcd(a,b)=gcd(b,a%b)

证明：
要证欧几里德算法成立，即证: gcd(a,b)=gcd(b,r),其中 gcd是取最大公约数的意思，r=a mod b
下面证 gcd（a，b）=gcd（b，r）
设  c是a，b的最大公约数，即c=gcd（a，b），则有 a=mc，b=nc，其中m，n为正整数，且m，n互为质数
由 r= a mod b可知，r= a- qb 其中，q是正整数，
则 r=a-qb=mc-qnc=（m-qn）c
b=nc,r=(m-qn)c，且n，（m-qn）互质（假设n，m-qn不互质，则n=xd, m-qn=yd 其中x,y,d都是正整数，且d>1
则a=mc=(qx+y)dc, b=xdc,这时a,b 的最大公约数变成dc，与前提矛盾， 所以n ，m-qn一定互质）
则gcd（b,r）=c=gcd（a,b）
得证
*/

int gcd(int m, int n)
{
    return n == 0 ? m : gcd(n, m % n);
}

int main(int argc, char **argv)
{

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    printf("gcd(%d, %d) = %d\n", m, n, gcd(m, n));
    return 0;
}
