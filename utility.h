//
// Created by 曹正盛 on 24-8-10.
//

#ifndef CPP_UTILITY_H
#define CPP_UTILITY_H
#include<random>
#define MAX_N 10000

extern std::mt19937_64 rnd;

template <typename T>
void swap(T& a, T& b) {
    T t = a;
    a = b;
    b = t;
}

template<typename T>
void swap(T arr[], int i, int j) {
    swap(arr[i], arr[j]);
}

template<typename T>
long get_random_number(T l, T r) {
    std::uniform_int_distribution<long> dis(l, r);
    return dis(rnd);
}

template<typename T>
long get_random_number(T n) {
    return get_random_number(0, n);
}

template<typename T>
long get_random_number() {
    return get_random_number(0, MAX_N);
}

template<typename T>
void fill_random_int(T a[], int n, T min, T max) {
    for (int i = 0; i < n; i++) {
        a[i] = get_random_number(min, max);
    }
}

template<typename T>
void fill_random_int(T a[], int n) {
    const T MAX_RANDOM_NUM_DEFAULT = MAX_N + 1;
    fill_random_int(a, n, 0, MAX_RANDOM_NUM_DEFAULT);
}

template<typename T>
void fill_random_int(std::vector<T>& vec, int cnt, T min, T max) {
    for (int i = 0; i < cnt; i++) {
        vec[i] = get_random_number(min, max);
    }
}

template<typename T>
void fill_random_int(std::vector<T>& vec, int cnt) {
    const T MAX_RANDOM_NUM_DEFAULT = MAX_N + 1;
    fill_random_int(vec, cnt, 0, MAX_RANDOM_NUM_DEFAULT);
}


#endif //CPP_UTILITY_H
