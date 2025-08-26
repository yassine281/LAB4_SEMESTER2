#pragma once 
#include <cstddef>
#include <iterator>
template <typename Func>
void map_pos(size_t n, Func f) {
    for (size_t i = 0; i < n; i++) {
        f(i);
    }
}
template <typename Pred, typename Func>
void where_pos(size_t n, Pred pred, Func f) {
    for (size_t i = 0; i < n; i++) {
        if (pred(i)) f(i);
    }
}
template <typename T, typename Op>
T reduce_pos(size_t n, T init, Op op) {
    T acc = init;
    for (size_t i = 0; i < n; i++) {
        acc = op(acc, i);
    }
    return acc;
}
