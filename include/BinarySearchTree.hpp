#pragma once
#include <functional>
#include <string>
#include <sstream>
#include <queue>
#include "Node.hpp"
template <typename T>
struct Node {
    T value;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(const T& v) : value(v) {}
};

template <typename T, typename Compare = std::less<T>>
class BinarySearchTree {
public:
    BinarySearchTree() = default;
    ~BinarySearchTree() { clear(root); }

    void insert(const T& value) {
        root = insert_rec(root, value);
        ++_size;
    }

    bool contains(const T& value) const {
        Node<T>* curr = root;
        while (curr) {
            if (cmp(value, curr->value)) curr = curr->left;
            else if (cmp(curr->value, value)) curr = curr->right;
            else return true;
        }
        return false;
    }

    bool erase(const T& value) {
        bool removed = false;
        root = erase_rec(root, value, removed);
        if (removed) --_size;
        return removed;
    }

    std::size_t Size() const { return _size; }
    bool Empty() const { return _size == 0; }
    template <typename F>
    BinarySearchTree map(F f) const {
        BinarySearchTree<T, Compare> newTree;
        map_rec(root, newTree, f);
        return newTree;
    }
    template <typename Pred>
    BinarySearchTree where(Pred p) const {
        BinarySearchTree<T, Compare> newTree;
        where_rec(root, newTree, p);
        return newTree;
    }
    template <typename Op>
    T reduce(T init, Op op) const {
        return reduce_rec(root, init, op);
    }

    Node<T>* get_root() const { return root; }

private:
    Node<T>* root = nullptr;
    std::size_t _size = 0;
    Compare cmp{};
    Node<T>* insert_rec(Node<T>* n, const T& value) {
        if (!n) return new Node<T>(value);
        if (cmp(value, n->value)) n->left = insert_rec(n->left, value);
        else if (cmp(n->value, value)) n->right = insert_rec(n->right, value);
        return n;
    }

    Node<T>* erase_rec(Node<T>* n, const T& value, bool& removed) {
        if (!n) return nullptr;
        if (cmp(value, n->value)) n->left = erase_rec(n->left, value, removed);
        else if (cmp(n->value, value)) n->right = erase_rec(n->right, value, removed);
        else {
            removed = true;
            if (!n->left) { Node<T>* r = n->right; delete n; return r; }
            if (!n->right) { Node<T>* r = n->left; delete n; return r; }
            Node<T>* succ = n->right;
            while (succ->left) succ = succ->left;
            n->value = succ->value;
            n->right = erase_rec(n->right, succ->value, removed);
        }
        return n;
    }

    void clear(Node<T>* n) {
        if (!n) return;
        clear(n->left);
        clear(n->right);
        delete n;
    }

    template <typename F>
    void map_rec(Node<T>* n, BinarySearchTree<T, Compare>& tree, F f) const {
        if (!n) return;
        tree.insert(f(n->value));
        map_rec(n->left, tree, f);
        map_rec(n->right, tree, f);
    }

    template <typename Pred>
    void where_rec(Node<T>* n, BinarySearchTree<T, Compare>& tree, Pred p) const {
        if (!n) return;
        if (p(n->value)) tree.insert(n->value);
        where_rec(n->left, tree, p);
        where_rec(n->right, tree, p);
    }

    template <typename Op>
    T reduce_rec(Node<T>* n, T acc, Op op) const {
        if (!n) return acc;
        acc = reduce_rec(n->left, acc, op);
        acc = op(acc, n->value);
        acc = reduce_rec(n->right, acc, op);
        return acc;
    }
};
