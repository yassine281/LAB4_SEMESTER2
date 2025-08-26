#pragma once
#include "BinarySearchTree.hpp"
template <typename T, typename Compare>
void BinarySearchTree<T,Compare>::insert(const T& value) {
    if (!root) { root = new Node<T>(value); _size = 1; return; }
    Node<T>* cur = root;
    while (true) {
        if (cmp(value, cur->value)) {
            if (!cur->left) { cur->left = new Node<T>(value); ++_size; break; }
            cur = cur->left;
        } else if (cmp(cur->value, value)) {
            if (!cur->right) { cur->right = new Node<T>(value); ++_size; break; }
            cur = cur->right;
        } else {
            cur->value = value; 
            break;
        }
    }
}
template <typename T, typename Compare>
bool BinarySearchTree<T,Compare>::contains(const T& value) const {
    Node<T>* cur = root;
    while (cur) {
        if (cmp(value, cur->value)) cur = cur->left;
        else if (cmp(cur->value, value)) cur = cur->right;
        else return true;
    }
    return false;
}
template <typename T, typename Compare>
bool BinarySearchTree<T,Compare>::erase(const T& value) {
    Node<T>* parent = nullptr;
    Node<T>* cur = root;
    while (cur) {
        if (cmp(value, cur->value)) { parent = cur; cur = cur->left; }
        else if (cmp(cur->value, value)) { parent = cur; cur = cur->right; }
        else break;
    }
    if (!cur) return false;

    auto replace_child = [&](Node<T>* p, Node<T>* oldc, Node<T>* newc) {
        if (!p) root = newc;
        else if (p->left == oldc) p->left = newc;
        else p->right = newc;
    };

    if (!cur->left) { replace_child(parent, cur, cur->right); delete cur; }
    else if (!cur->right) { replace_child(parent, cur, cur->left); delete cur; }
    else {
        Node<T>* succParent = cur;
        Node<T>* succ = cur->right;
        while (succ->left) { succParent = succ; succ = succ->left; }
        cur->value = succ->value;
        if (succParent->left == succ) succParent->left = succ->right;
        else succParent->right = succ->right;
        delete succ;
    }
    --_size;
    return true;
}
template <typename T, typename Compare>
template <typename F>
BinarySearchTree<T,Compare> BinarySearchTree<T,Compare>::map(F f) const {
    BinarySearchTree<T,Compare> out;
    auto map_rec = [&](Node<T>* n, auto&& map_rec_ref) -> void {
        if (!n) return;
        out.insert(f(n->value));
        map_rec_ref(n->left, map_rec_ref);
        map_rec_ref(n->right, map_rec_ref);
    };
    map_rec(root, map_rec);
    return out;
}
template <typename T, typename Compare>
template <typename Pred>
BinarySearchTree<T,Compare> BinarySearchTree<T,Compare>::where(Pred p) const {
    BinarySearchTree<T,Compare> out;
    auto where_rec = [&](Node<T>* n, auto&& where_rec_ref) -> void {
        if (!n) return;
        if (p(n->value)) out.insert(n->value);
        where_rec_ref(n->left, where_rec_ref);
        where_rec_ref(n->right, where_rec_ref);
    };
    where_rec(root, where_rec);
    return out;
}
template <typename T, typename Compare>
template <typename Op>
T BinarySearchTree<T,Compare>::reduce(const T& init, Op op) const {
    T acc = init;
    auto reduce_rec = [&](Node<T>* n, auto&& reduce_rec_ref) -> void {
        if (!n) return;
        reduce_rec_ref(n->left, reduce_rec_ref);
        acc = op(n->value, acc);
        reduce_rec_ref(n->right, reduce_rec_ref);
    };
    reduce_rec(root, reduce_rec);
    return acc;
}
template <typename T, typename Compare>
BinarySearchTree<T,Compare> BinarySearchTree<T,Compare>::extract_subtree(const T& key) const {
    Node<T>* cur = root;
    while (cur) {
        if (cmp(key, cur->value)) cur = cur->left;
        else if (cmp(cur->value, key)) cur = cur->right;
        else break;
    }
    if (!cur) throw TreeException("Key not found for extract_subtree");
    BinarySearchTree<T,Compare> out;
    auto clone_rec = [&](Node<T>* n, auto&& clone_rec_ref) -> Node<T>* {
        if (!n) return nullptr;
        Node<T>* nn = new Node<T>(n->value);
        nn->left = clone_rec_ref(n->left, clone_rec_ref);
        nn->right = clone_rec_ref(n->right, clone_rec_ref);
        return nn;
    };
    out.root = clone_rec(cur, clone_rec);
    auto count_rec = [&](Node<T>* n, auto&& count_rec_ref) -> std::size_t {
        if (!n) return 0;
        return 1 + count_rec_ref(n->left, count_rec_ref) + count_rec_ref(n->right, count_rec_ref);
    };
    out._size = count_rec(out.root, count_rec);
    return out;
}
template <typename T, typename Compare>
bool BinarySearchTree<T,Compare>::contains_subtree(const BinarySearchTree& small) const {
    auto equals_rec = [](Node<T>* a, Node<T>* b, auto&& equals_rec_ref) -> bool {
        if (!a && !b) return true;
        if (!a || !b) return false;
        return a->value == b->value &&
               equals_rec_ref(a->left, b->left, equals_rec_ref) &&
               equals_rec_ref(a->right, b->right, equals_rec_ref);
    };
    auto contains_rec = [&](Node<T>* big, Node<T>* small, auto&& contains_rec_ref) -> bool {
        if (!small) return true;
        if (!big) return false;
        if (equals_rec(big, small, equals_rec)) return true;
        return contains_rec_ref(big->left, small, contains_rec_ref) ||
               contains_rec_ref(big->right, small, contains_rec_ref);
    };
    return contains_rec(root, small.root, contains_rec);
}
