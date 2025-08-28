#include <cassert>
#include <string>
#include "BinarySearchTree.hpp"
template <typename T>
std::string inorder_str(Node<T>* n) {
    if (!n) return "";
    std::string left = inorder_str(n->left);
    std::string right = inorder_str(n->right);
    std::string val = std::to_string(n->value);
    if (!left.empty()) val = left + " " + val;
    if (!right.empty()) val = val + " " + right;
    return val;
}
void test_empty_tree() {
    BinarySearchTree<int> t;
    assert(t.Empty());
    assert(t.Size() == 0);
    assert(!t.contains(42));

    int r = t.reduce(10, [](int acc, int v){ return acc + v; });
    assert(r == 10);

    auto m = t.map([](int x){ return x*2; });
    auto w = t.where([](int){ return true; });
    assert(m.Empty() && w.Empty());

    assert(t.get_root() == nullptr);
}
void test_insert_and_contains() {
    BinarySearchTree<int> bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);

    assert(!bst.Empty());
    assert(bst.Size() == 7);

    assert(bst.contains(5));
    assert(bst.contains(2));
    assert(bst.contains(8));
    assert(!bst.contains(100));

    std::string inorder = inorder_str(bst.get_root());
    assert(inorder.find("2 3 4 5 6 7 8") != std::string::npos);
}
void test_erase() {
    BinarySearchTree<int> bst;
    bst.insert(5); bst.insert(3); bst.insert(7); 
    bst.insert(2); bst.insert(4); bst.insert(6); bst.insert(8);

    assert(bst.erase(3)); assert(!bst.contains(3));
    assert(bst.erase(5)); assert(!bst.contains(5));
    assert(!bst.erase(42));
    assert(bst.erase(2)); assert(!bst.contains(2));
    assert(bst.erase(4)); assert(!bst.contains(4));
    assert(bst.erase(6)); assert(!bst.contains(6));
    assert(bst.erase(7)); assert(!bst.contains(7));
    assert(bst.erase(8)); assert(!bst.contains(8));
    assert(bst.Empty());
}
void test_reduce_map_where() {
    BinarySearchTree<int> bst;
    bst.insert(2); bst.insert(4); bst.insert(6);

    int sum = bst.reduce(0, [](int acc, int v){ return acc + v; });
    assert(sum == 12);

    auto doubled = bst.map([](int v){ return v*2; });
    assert(doubled.Size() == bst.Size());
    assert(doubled.contains(4));
    assert(doubled.contains(8));
    assert(doubled.contains(12));

    auto evens = bst.where([](int v){ return v % 2 == 0; });
    assert(evens.Size() == 3);
    assert(evens.contains(2));
    assert(evens.contains(4));
    assert(evens.contains(6));
}
int main() {
    test_empty_tree();
    test_insert_and_contains();
    test_erase();
    test_reduce_map_where();
    return 0;
}
