#ifndef HW17_AVL_H
#define HW17_AVL_H

#include <string>
#include <iostream>
#include <ctime>
#include <queue>

using ostream = std::ostream;

template <class T>
class AVL;

template <class T>
T& max(T& left, T& right){
    if (left > right)
        return left;
    else
        return right;

}
template <class T>
T max(const T& left, const T& right){
    if (left > right)
        return left;
    else
        return right;

}

template <class T>
class AVLNode{
    AVLNode<T>* parent, *left, *right;
    int height;
    T data;
public:
    friend class AVL < T > ;
    explicit AVLNode(const T& newdata = T(), AVLNode<T>* newparent = nullptr, AVLNode<T>* newleft = nullptr, AVLNode<T>* newright = nullptr) :
            parent(newparent), left(newleft), right(newright), height(-2), data(newdata) {
        calcHeight();
    }
    void calcHeight(){
        int leftHeight = -1;
        int rightHeight = -1;
        if (left != nullptr)
            leftHeight = left->height;
        if (right != nullptr)
            rightHeight = right->height;
        height = max(leftHeight, rightHeight) + 1;
        if (parent) //Update all parent heights also
            parent->calcHeight();
    }
    void printInOrder(ostream& out)const{
        if (left != nullptr)
            left->printInOrder(out);
        out << data <<"\t"<<height<< std::endl;
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
    /*	int height()const{
            int leftSize = -1;
            int rightSize = -1;
            if (left != nullptr)
            leftSize = left->height();
            if (right != nullptr)
            rightSize = right->height();
            return 1 + max(leftSize, rightSize);
            }*/
    int depth() const{
        int parentDepth = -1;
        if (parent != nullptr)
            parentDepth = parent->depth();
        return 1 + parentDepth;
    }
};

template <class T>
void AVLNode<T>::printPostOrder(ostream& out)const{
    if (left != nullptr)
        left->printInOrder(out);
    if (right != nullptr)
        right->printInOrder(out);
    out << data << std::endl;
}


template <class T>
class AVL{
    AVLNode<T>* root;
    AVLNode<T>* recursiveCopy(AVLNode<T>* toCopy);
    void singleCCR(AVLNode<T>*& point);
    void doubleCR(AVLNode<T>*& point);
    void singleCR(AVLNode<T>*& point);
    void doubleCCR(AVLNode<T>*& point);
    int heightDiff(AVLNode<T>* point);
    void doRotation(AVLNode<T>* point);
public:
    AVL() { root = nullptr; }

    //memory on the heap so.... here comes the big 3!
    AVL(const AVL<T>& rhs) : root(nullptr) { *this = rhs; }
    virtual ~AVL(){ clear(); }
    AVL& operator=(const AVL<T>& rhs);

    bool isInTree(const T& toFind) const{ return find(toFind) != nullptr; }
    bool isEmpty()const{ return root == nullptr; }
    int getSize()const;
    void remove(const T& toRemove){
        AVLNode<T>* item = find(toRemove);
        if (item != nullptr)
            remove(item);
    }
    void insert(const T&);
    void insert(const T&, AVLNode<T>*& point);
    void remove(AVLNode<T>*);
    AVLNode<T>* find(const T& toFind) const;
    void clear(){ while (!isEmpty()) remove(root); }
    void printInOrder(ostream& out)const{ root->printInOrder(out); }
    void printPostOrder(ostream& out)const{ root->printPostOrder(out); }
    void printLevelOrder(ostream& out)const;
};

template class AVL<int>;
template class AVL<char>;
template class AVL<std::string>;

#endif //HW17_AVL_H
