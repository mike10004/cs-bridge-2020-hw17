#ifndef HW17_REDBLACK_H
#define HW17_REDBLACK_H

#include <stack>
#include "tree.h"

typedef bool Color;

const bool RED = false;
const bool BLACK = true;

template <class T>
class RBNode : public TreeNode<T> {
private:
    Color color;
public:
    RBNode(const T& data, RBNode<T>* parent, RBNode<T>* left, RBNode<T>* right)
        : RBNode(data, parent, left, right, RED) {}
    RBNode(const T& data)
        : RBNode(data, nullptr, nullptr, nullptr, RED) {}
    RBNode(const T& data, RBNode<T>* parent)
        : RBNode(data, parent, nullptr, nullptr, RED) {}
    bool isRed() const;
    bool isBlack() const;
    RBNode<T>* GetParent() const;
    RBNode<T>* GetLeft() const;
    RBNode<T>* GetRight() const;
    RBNode<T>* GetSibling();
    void SetColor(Color color);
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
    RBNode(const T& data, RBNode<T>* parent, RBNode<T>* left, RBNode<T>* right, Color color)
            : TreeNode<T>(data, parent, left, right), color(color) {}

};

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
    void clear(TreeNode<T>*& node);
    bool check(RBNode<T>* node) const;
    void GetDescendants(RBNode<T>* node, std::vector<RBNode<T>*>& nodes) const;
    /**
     * Inserts a value into the tree. Returns the new or existing node containing the given value.
     * @param value
     * @param parent
     * @return
     */
    RBNode<T>* insert(const T& value, RBNode<T>* parent);
    void repair(RBNode<T>* node);
};


template class RBNode<int>;
template class RBNode<char>;
template class RBNode<std::string>;
template class RedBlackTree<int>;
template class RedBlackTree<char>;
template class RedBlackTree<std::string>;

#endif //HW17_REDBLACK_H
