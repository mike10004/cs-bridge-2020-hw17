#ifndef HW17_AVL_H
#define HW17_AVL_H

#include <string>
#include <iostream>
#include <ctime>
#include <queue>
#include "tree.h"

using ostream = std::ostream;

template <class T>
class AVL;


template <class T>
class AVLNode : public TreeNode<T> {
    int height;
public:
    friend class AVL < T > ;
    explicit AVLNode(const T& newdata, AVLNode<T>* newparent, AVLNode<T>* newleft, AVLNode<T>* newright)
    :TreeNode<T>(newdata, newparent, newleft, newright), height(-2) {
        calcHeight();
    }
    void calcHeight(){
        int leftHeight = -1;
        int rightHeight = -1;
        if (this->left != nullptr)
            leftHeight = this->left->height;
        if (this->right != nullptr)
            rightHeight = this->right->height;
        height = max(leftHeight, rightHeight) + 1;
        if (this->parent) //Update all parent heights also
            this->parent->calcHeight();
    }
    int getHeight() const override {
        return height;
    }
};

template <class T>
class AVL : public Tree<T> {
    int heightDiff(AVLNode<T>* point);
    void doRotation(AVLNode<T>* point);
    bool check(AVLNode<T>* point) const;
public:
    AVL() : Tree<T>() {}

    //memory on the heap so.... here comes the big 3!
    AVL(const AVL<T>& rhs) : Tree<T>() { *this = rhs; }
    ~AVL() override { clear(); }
    AVL& operator=(const AVL<T>& rhs);

    AVLNode<T>* recursiveCopy(AVLNode<T>* toCopy);
    bool isInTree(const T& toFind) const override { return find(toFind) != nullptr; }
    bool isEmpty() const override { return this->root == nullptr; }
    int getSize() const override;
    void remove(const T& toRemove){
        AVLNode<T>* item = find(toRemove);
        if (item != nullptr)
            remove(item);
    }
    void insert(const T&) override;
    void remove(TreeNode<T>*);
private:
    void insert(const T&, TreeNode<T>*& point);
    AVLNode<T>* find(const T& toFind) const;
    void clear() override { while (!isEmpty()) remove(this->root); }
    bool check() const override;

    void singleCR(TreeNode<T>*& point) override;
    void singleCCR(TreeNode<T>*& point) override;
};

template class AVL<int>;
template class AVL<char>;
template class AVL<std::string>;

#endif //HW17_AVL_H
