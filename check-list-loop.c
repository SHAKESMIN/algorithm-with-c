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

typedef struct node* link;
struct node 
{
    int item;
    link next;
};

int main(int argc, char **argv)
{
    /* 构造存在部分回环的链表 
     * list:  1 - 2  - 3  - 4  - 5
     *                      |    |
     *                      7  - 6
     * */
    link list, p, t;
    int i = 1;
    list = malloc(sizeof *p);
    list->item = 1;
    t = list;
    for (i = 2; i <= 7; i++)
    {
        p = malloc(sizeof *p);
        p->item = i;
        t->next = p;
        t = p;
    }
    /* 设置有循环 */
     p -> next = list->next->next->next;

    /* 设置无循环 */
    /* p -> next = NULL; */

    /* 检查链表是否存在回环: 可能是中间某部分的回环
     * 原理：  用两个指针，步长分别1， 2， 步长2的指针能追上步长为1的指针则存在回环
     *
     * */
    link fast = list, slow = list;
    while (1)
    {
        if (NULL != fast && NULL != fast->next) 
            fast = fast->next->next;
        else 
            fast = NULL;
        if (NULL != slow)
            slow = slow->next;
        else 
            slow = NULL;
        if (fast == slow && fast != NULL) 
        {
            printf("exist loop in the list.\n");
            break;
        }
        else if (NULL == fast && NULL == slow)
        {
            printf("not exist loop in the list.\n");
            break;
        }
    }


    return 0;
}
