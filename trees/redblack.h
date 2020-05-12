#ifndef HW17_REDBLACK_H
#define HW17_REDBLACK_H

#include <stack>
#include "tree.h"

typedef bool Color;

const bool RED = false;
const bool BLACK = true;

template <class T>
class RBNode : public TreeNode<T> {
public:
    RBNode(const T& data, RBNode<T>* parent, RBNode<T>* left, RBNode<T>* right)
    : TreeNode<T>(data, parent, left, right), color(RED) {}
    bool isRed() const;
    bool isBlack() const;
    RBNode<T>* GetParent();
    RBNode<T>* GetLeft();
    RBNode<T>* GetRight();

    /**
     * Gets the path from the given node to this node.
     * The result is empty if the given node is not an ancestor of this node.
     * Otherwise, the result contains both the given node and this node.
     * If the given node is this node, then the path contains this node exactly once.
     * If the given node is null, then the result contains the path from the root.
     * @param node
     * @return
     */
    std::vector<RBNode<T>*> GetPathFrom(RBNode<T>* node) const;
private:
    Color color;

};

template<class T>
std::vector<RBNode<T> *> RBNode<T>::GetPathFrom(RBNode<T>* node) const {
    std::stack<RBNode<T>*> path;
    RBNode<T>* current = this;
    bool found = false;
    while (current != nullptr) {
        path.push(current);
        if (current == node) {
            found = true;
            break;
        }
        current = current->GetParent();
    }
    if (found || node == nullptr) {
        return std::vector<RBNode<T>*>(path.begin(), path.end());
    } else {
        return std::vector<RBNode<T>*>();
    }
}

template<class T>
bool RBNode<T>::isRed() const {
    return color == RED;
}

template<class T>
bool RBNode<T>::isBlack() const {
    return color == BLACK;
}

template<class T>
RBNode<T> *RBNode<T>::GetParent() {
    return (RBNode<T>*) (this->parent);
}

template<class T>
RBNode<T> *RBNode<T>::GetLeft() {
    return (RBNode<T>*) (this->left);
}

template<class T>
RBNode<T> *RBNode<T>::GetRight() {
    return (RBNode<T>*) (this->right);
}

template <class T>
class RedBlackTree : public Tree<T> {
public:
    RedBlackTree() : Tree<T>() {}
    ~RedBlackTree() override;
    bool isEmpty() const override;
    int getSize() const override;
    void clear() override;
    bool check() const override;
    bool isInTree(const T& element) const override;
    void insert(const T& value) override;
private:
    void clear(TreeNode<T>* node);
    bool check(RBNode<T>* node) const;
    void GetDescendants(RBNode<T>* node, std::vector<RBNode<T>*>& nodes) const;
};

template class RedBlackTree<int>;
template class RedBlackTree<char>;
template class RedBlackTree<std::string>;

#endif //HW17_REDBLACK_H
