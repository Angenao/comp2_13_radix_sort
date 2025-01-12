#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義

#include "../include/lib_func.h"
#include <stdio.h>
#include <stdlib.h>

// 基数ソート(引数が不適切であればfalseを返す)
// begin: ソートする配列の先頭要素へのポインタ
// end: ソートする配列の末尾要素の次の要素へのポインタ
// radix: 基数
bool radix_sort(item* begin, const item* end, int radix)
{
	// ToDo: 基数ソートを実装する
    if (!begin || !end || end <= begin || radix < 2)
        return false;

    size_t size = end - begin;

    int* count = (int*)malloc(radix * sizeof(int));
    if (!count)
        return false;

    item* buffer = (item*)malloc(size * sizeof(item));
    if (!buffer)
    {
        free(count);
        return false;
    }

    unsigned int max_key = 0;
    for (item* it = begin; it < end; ++it)
        if (it->key > max_key)
            max_key = it->key;

    item* src = begin;
    item* dest = buffer;

    for (unsigned int place = 1; max_key / place > 0; place *= radix)
    {
        memset(count, 0, radix * sizeof(int));

        for (item* it = src; it < src + size; ++it)
            count[(it->key / place) % radix]++;

        for (int i = 1; i < radix; ++i)
            count[i] += count[i - 1];

        for (item* it = src + size - 1; it >= src; --it)
        {
            int idx = (it->key / place) % radix;
            dest[--count[idx]] = *it;
        }

        item* temp = src;
        src = dest;
        dest = temp;
    }

    if (src != begin)
        memcpy(begin, src, size * sizeof(item));

    free(count);
    free(buffer);
    return true;
}
