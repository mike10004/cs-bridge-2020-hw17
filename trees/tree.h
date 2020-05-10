#ifndef HW17_TREE_H
#define HW17_TREE_H

template <class T>
class Tree {
public:
    Tree() = default;
    virtual ~Tree() = default;
    virtual bool isEmpty() const = 0;
    virtual int getSize() const = 0;
    virtual void insert(const T&) = 0;
    virtual bool isInTree(const T& toFind) const = 0;
    virtual bool check() const = 0;
};


//template class Tree<int>;
//template class Tree<char>;
//template class Tree<std::string>;


#endif //HW17_TREE_H
