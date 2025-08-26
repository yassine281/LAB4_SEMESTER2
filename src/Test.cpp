#include <iostream>
#include "BinarySearchTree.hpp"
#include "Format.hpp"

int main() {
    BinarySearchTree<int> bst;
    bst.Add(5);
    bst.Add(3);
    bst.Add(7);
    bst.Add(2);
    bst.Add(4);
    bst.Add(6);
    bst.Add(8);
    std::cout << "BST in-order: " << bst.to_string(Traversal::LKP) << "\n";
    std::cout << "Contains 4? " << (bst.contains(4) ? "Yes" : "No") << "\n";
    std::cout << "Contains 10? " << (bst.contains(10) ? "Yes" : "No") << "\n";
    bst.Remove(3);
    std::cout << "After removing 3: " << bst.to_string(Traversal::LKP) << "\n";
    int sum = bst.reduce(0, [](int v, int acc) { return acc + v; });
    std::cout << "Sum of elements: " << sum << "\n";
    try {
        auto sub = bst.extract_subtree(7);
        std::cout << "Subtree (root 7) in-order: " << sub.to_string(Traversal::LKP) << "\n";
    } catch (...) {
        std::cout << "Subtree not found.\n";
    }
    auto evens = bst.where([](int v){ return v % 2 == 0; });
    std::cout << "Even numbers: " << evens.to_string(Traversal::LKP) << "\n";

    return 0;
}
