#pragma once
#include "IEnumerable.hpp"
#include "Node.hpp"
#include <stack>
template <typename T>
class BSTInOrderEnumerator : public IEnumerator<T> {
public:
    explicit BSTInOrderEnumerator(const Node<T>* root) {
        PushLeft(root);
    }
    bool MoveNext() override {
        if (stk.empty()) return false;

        const Node<T>* node = stk.top();
        stk.pop();

        curr = node->value;
        if (node->right) PushLeft(node->right);

        return true;
    }
    const T& Current() const override {
        return curr;
    }

private:
    void PushLeft(const Node<T>* node) {
        const Node<T>* p = node;
        while (p) {
            stk.push(p);
            p = p->left;
        }
    }

    std::stack<const Node<T>*> stk; 
    T curr{};                       
};
