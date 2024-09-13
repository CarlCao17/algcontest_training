//
// Created by 曹正盛 on 24-8-10.
//
#include<cstdio>
#include"../utility.h"
#define N 1000

template <typename T>
int partition(T arr[], int l, int r) { // [l, r]
    int idx = (int)getRandomNumber(l, r);
    swap(arr, l, idx);
    int i = l; // <= pivot: [l, i]
    // > pivot [i+1, j)
    // to process: [j, r]
    for (int j = l+1; j <= r; j++) {
        if (arr[j] < arr[l]) {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[l], arr[i]);
    return i;
}

template <typename T>
void sort_in_place(T arr[], int l, int r) {
    if (r - l < 1) {
        return ;
    }
    int pivot = partition(arr, l, r);
    sort_in_place(arr, l, pivot-1);
    sort_in_place(arr, pivot+1, r);
}

template <typename T>
int array_should_equal(T dst[], T src[], int n) {
    for (int i = 0; i < n; i++) {
        if (dst[i] != src[i]) return i;
    }
    return -1;
}


template <typename T>
void copy_array(T dst[], T src[], int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
    }
}

template <typename T>
void print_array(T dst[], int n) {
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", dst[i]);
    }
    printf("\n");
}

int main() {
    int n = 0;
    long num[N];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%ld", &num[i]);
    }
    sort_in_place(num, 0, n-1);
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%ld", num[i]);
    }
    printf("\n");
}
