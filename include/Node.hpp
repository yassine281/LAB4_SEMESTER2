#pragma once
#include <memory>

template <typename T>
struct Node {
    T value;
    Node* left = nullptr;
    Node* right = nullptr;

    explicit Node(const T& v) : value(v) {}
};
