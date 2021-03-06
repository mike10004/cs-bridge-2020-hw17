#ifndef HW17_TREE_H
#define HW17_TREE_H

#include <iostream>
#include <queue>

using ostream = std::ostream;

template <class T>
T max(const T& left, const T& right){
    if (left < right)
        return right;
    else
        return left;

}

template<class T>
class TreeNode {
public:
    T data;
    TreeNode<T>* parent, *left, *right;
    TreeNode(const T& data, TreeNode<T>* parent, TreeNode<T>* left, TreeNode<T>* right)
            : data(data), parent(parent), left(left), right(right) {}
    virtual ~TreeNode() = default;
    void printInOrder(ostream& out)const{
        if (left != nullptr)
            left->printInOrder(out);
        out << data << std::endl;
        if (right != nullptr)
            right->printInOrder(out);
    }
    void printPostOrder(ostream& out)const;
    int size()const{
        int leftSize = 0;
        int rightSize = 0;
        if (left != nullptr)
            leftSize = left->size();
        if (right != nullptr)
            rightSize = right->size();
        return 1 + leftSize + rightSize;
    }
    virtual int getHeight() const {
        return recalcHeight();
    }
    int recalcHeight()const{
        int leftSize = -1;
        int rightSize = -1;
        if (left != nullptr)
            leftSize = left->recalcHeight();
        if (right != nullptr)
            rightSize = right->recalcHeight();
        return 1 + max(leftSize, rightSize);
    }
    int depth() const{
        int parentDepth = -1;
        if (parent != nullptr)
            parentDepth = parent->depth();
        return 1 + parentDepth;
    }
};

class Listener {
public:
    Listener() = default;
    virtual ~Listener() = default;
    virtual void Message(const std::string& message) = 0;
};

class InactiveListener : public Listener {
    void Message(const std::string& message) override {}
};

class PrintingListener : public Listener {
public:
    PrintingListener(std::ostream& out) : out(out) {}
    void Message(const std::string& message) override {
        out << message << std::endl;
    }
private:
    std::ostream& out;
};

template <class T>
class Tree {
public:
    Tree() : root(nullptr) {};
    virtual ~Tree() = default;
    virtual bool isEmpty() const;
    virtual int getSize() const = 0;
    virtual void insert(const T&) = 0;
    virtual bool isInTree(const T& toFind) const = 0;
    virtual bool check() const {
        InactiveListener il;
        return check(il);
    }
    virtual bool check(Listener& listener) const;
    virtual void clear() = 0;
    virtual void singleCCR(TreeNode<T>*& point);
    virtual void doubleCR(TreeNode<T>*& point);
    virtual void singleCR(TreeNode<T>*& point);
    virtual void doubleCCR(TreeNode<T>*& point);
    virtual void printInOrder(ostream& out)const{ root->printInOrder(out); }
    virtual void printPostOrder(ostream& out)const{ root->printPostOrder(out); }
    virtual void printLevelOrder(ostream& out)const;
protected:
    TreeNode<T>* root;
    virtual bool checkOrder(TreeNode<T>* node, Listener& listener) const;
    virtual bool checkRelationships(TreeNode<T>* node, Listener& listener) const;
};

template <class T>
bool Tree<T>::isEmpty() const {
    return root == nullptr;
}

template <class T>
void Tree<T>::printLevelOrder(ostream& out) const{
    std::queue<TreeNode<T>*> q;
    q.push(root);
    while (!q.empty()){
        TreeNode<T>* front = q.front();
        out << front->data << "\t" << front->getHeight() << std::endl;
        if (front->left!=nullptr)
            q.push(front->left);
        if (front->right)
            q.push(front->right);
        q.pop();
    }
}
template <class T>
void Tree<T>::doubleCCR(TreeNode<T>*& point){
    singleCR(point->right);
    singleCCR(point);
}

template <class T>
void Tree<T>::doubleCR(TreeNode<T>*& point){
    singleCCR(point->left);
    singleCR(point);
}

template <class T>
void Tree<T>::singleCR(TreeNode<T>*& point){
    TreeNode<T>* grandparent = point;
    TreeNode<T>* parent = point->left;
    parent->parent = grandparent->parent;
    grandparent->parent = parent;
    grandparent->left = parent->right;
    parent->right = grandparent;
    if (grandparent->left != nullptr) //if we now have a left child, update its parent pointer
        grandparent->left->parent = grandparent;
    if (parent->parent == nullptr)//if we were the root, update the root!
        root = parent;
    else if (parent->parent->left == grandparent)
        parent->parent->left = parent;
    else
        parent->parent->right = parent;
}

template <class T>
void Tree<T>::singleCCR(TreeNode<T>*& point){
    TreeNode<T>* grandparent = point;
    TreeNode<T>* parent = point->right;
    parent->parent = grandparent->parent;
    grandparent->parent = parent;
    grandparent->right = parent->left;
    parent->left = grandparent;
    if (grandparent->right != nullptr) //if we now have a right child, update its parent pointer
        grandparent->right->parent = grandparent;
    if (parent->parent == nullptr)//if we were the root, update the root!
        root = parent;
    else if (parent->parent->right == grandparent)
        parent->parent->right = parent;
    else
        parent->parent->left = parent;
}

template<class T>
bool Tree<T>::checkOrder(TreeNode<T> *node, Listener& listener) const {
    if (node == nullptr) {
        return true;
    }
    if (node->left != nullptr) {
        if (node->data < node->left->data) {
            listener.Message("node's left child has key lesser than node");
            return false;
        }
        if (!checkOrder(node->left, listener)) {
            return false;
        }
    }
    if (node->right != nullptr) {
        if (node->right->data < node->data) {
            listener.Message("node's right child has key greater than node");
            return false;
        }
        if (!checkOrder(node->right, listener)) {
            return false;
        }
    }
    return true;
}

template<class T>
bool Tree<T>::check(Listener& listener) const {
    return checkOrder(root, listener) && checkRelationships(root, listener);
}

template<class T>
bool Tree<T>::checkRelationships(TreeNode<T>* node, Listener& listener) const {
    if (node == nullptr) {
        return true;
    }
    TreeNode<T>* parent = node->parent;
    if (parent == nullptr) {
        if (root != node) {
            listener.Message("node has no parent but is not root");
            return false;
        }
        return true;
    }
    if (parent->left == parent->right) {
        listener.Message("duplicate children");
        return false;
    }
    if (parent->left != node && parent->right != node) {
        listener.Message("node is not among node's parent's children");
        return false;
    }
    return checkRelationships(node->left, listener) && checkRelationships(node->right, listener);
}

template <class T>
void TreeNode<T>::printPostOrder(ostream& out)const{
    if (left != nullptr)
        left->printInOrder(out);
    if (right != nullptr)
        right->printInOrder(out);
    out << data << std::endl;
}



template class Tree<int>;
template class Tree<char>;
template class Tree<std::string>;


#endif //HW17_TREE_H
