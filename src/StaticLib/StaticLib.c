#define WIN32_LEAN_AND_MEAN
#include "Windows.h"
#include "../include/lib_func.h"
#include <stdlib.h>
#include <string.h>


// 基数ソート(引数が不適切であればfalseを返す)
// begin: ソートする配列の先頭要素へのポインタ
// end: ソートする配列の末尾要素の次の要素へのポインタ
// radix: 基数
bool radix_sort(item* begin, const item* end, int radix) {
    // ToDo: 基数ソートを実装する

    if (begin == NULL || end == NULL || begin >= end || radix <= 1) {
        return false;
    }

    int size = end - begin;

    unsigned int max_value = 0;
    for (int i = 0; i < size; i++) {
        if (begin[i].key > max_value) {
            max_value = begin[i].key;
        }
    }

    int max_digits = 0;
    while (max_value > 0) {
        max_value /= radix;
        max_digits++;
    }

    item* temp = (item*)malloc(sizeof(item) * size);
    if (!temp) return false;

    int* count = (int*)malloc(sizeof(int) * radix);
    if (!count) {
        free(temp);
        return false;
    }

    unsigned int exp = 1;
    for (int d = 0; d < max_digits; d++) {
        for (int i = 0; i < radix; i++) {
            count[i] = 0;
        }

        for (int i = 0; i < size; i++) {
            int bucket_index = (begin[i].key / exp) % radix;
            count[bucket_index]++;
        }

        for (int i = 1; i < radix; i++) {
            count[i] += count[i - 1];
        }

        // 配列の再配置
        for (int i = size - 1; i >= 0; i--) {
            int bucket_index = (begin[i].key / exp) % radix;
            temp[--count[bucket_index]] = begin[i];
        }

        memcpy(begin, temp, sizeof(item) * size);

        exp *= radix;
    }

    //解放
    free(temp);
    free(count);

    return true;
}