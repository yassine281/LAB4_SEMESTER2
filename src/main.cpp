#include <iostream>
#include "BinarySearchTree.hpp"
#include "Format.hpp"

void printMenu() {
    std::cout << "\n--- BST Menu ---\n";
    std::cout << "1. Add element\n";
    std::cout << "2. Remove element\n";
    std::cout << "3. Print in-order (LKP)\n";
    std::cout << "4. Serialize tree\n";
    std::cout << "5. Deserialize tree\n";
    std::cout << "6. Filter even numbers\n";
    std::cout << "7. Add 1 to all elements (map)\n";
    std::cout << "8. Sum of elements (reduce)\n";
    std::cout << "9. Extract subtree\n";
    std::cout << "10. Check subtree\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    BinarySearchTree<int> bst;
    std::string serialized;
    FormatSpec spec = ParseFormat("{K}(L)[P]");

    int choice = -1;
    while (choice != 0) {
        printMenu();
        std::cin >> choice;

        if (choice == 1) {
            int val;
            std::cout << "Enter value to add: ";
            std::cin >> val;
            bst.Add(val);
            std::cout << val << " added.\n";
        }
        else if (choice == 2) {
            int val;
            std::cout << "Enter value to remove: ";
            std::cin >> val;
            if (bst.Remove(val)) std::cout << val << " removed.\n";
            else std::cout << val << " not found.\n";
        }
        else if (choice == 3) {
            std::cout << "BST in-order (LKP): " << bst.to_string(Traversal::LKP) << "\n";
        }
        else if (choice == 4) {
            serialized = bst.to_string(spec);
            std::cout << "Serialized BST: " << serialized << "\n";
        }
        else if (choice == 5) {
            if (serialized.empty()) std::cout << "No serialized string available.\n";
            else {
                auto newTree = BinarySearchTree<int>::from_string(serialized, spec);
                std::cout << "Deserialized BST size: " << newTree.Size() << "\n";
            }
        }
        else if (choice == 6) {
            auto evens = bst.where([](int v){ return v % 2 == 0; });
            std::cout << "Even numbers count: " << evens.Size() << "\n";
        }
        else if (choice == 7) {
            auto plus1 = bst.map([](int v){ return v + 1; });
            std::cout << "Added 1 to all elements.\n";
        }
        else if (choice == 8) {
            int sum = bst.reduce(0, [](int v, int acc){ return acc + v; });
            std::cout << "Sum of elements: " << sum << "\n";
        }
        else if (choice == 9) {
            int key;
            std::cout << "Enter root value of subtree to extract: ";
            std::cin >> key;
            try {
                auto sub = bst.extract_subtree(key);
                std::cout << "Subtree size: " << sub.Size() << "\n";
            } catch (...) {
                std::cout << "Key not found.\n";
            }
        }
        else if (choice == 10) {
            int key;
            std::cout << "Enter root value of subtree to check: ";
            std::cin >> key;
            try {
                auto sub = bst.extract_subtree(key);
                std::cout << "BST contains subtree? " 
                          << (bst.contains_subtree(sub) ? "Yes" : "No") << "\n";
            } catch (...) {
                std::cout << "Key not found.\n";
            }
        }
        else if (choice == 0) {
            std::cout << "Exiting...\n";
        }
        else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
