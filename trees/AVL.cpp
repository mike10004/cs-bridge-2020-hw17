#include <iostream>
#include "avl.h"

template <class T>
using queue = std::queue<T>;


template <class T>
AVLNode<T>* AVL<T>::recursiveCopy(AVLNode<T>* toCopy){
	if (toCopy == nullptr)
		return nullptr;
	AVLNode<T>* temp = new AVLNode<T>(toCopy->data, nullptr, recursiveCopy(toCopy->left), recursiveCopy(toCopy->right));
	if (temp->left != nullptr)
		temp->left->parent = temp;
	if (temp->right != nullptr)
		temp->right->parent = temp;
	return temp;
}

template <class T>
AVL<T>& AVL<T>::operator=(const AVL<T>& rhs){
	if (this == &rhs)
		return *this;
	clear();
    this->root = recursiveCopy(rhs.root);
	return *this;
}

template <class T>
void AVL<T>::remove(TreeNode<T>* toRemove){
	if (this->root == nullptr)
		return; //Remove from an empty tree????
	if (toRemove->left == nullptr && toRemove->right == nullptr){ //leaf node case
		if (toRemove->parent == nullptr){
            this->root = nullptr;
		}
		else if (toRemove == toRemove->parent->left) //left child!
			toRemove->parent->left = nullptr; //fix the parent's pointer!
		else
			toRemove->parent->right = nullptr;
		delete toRemove;
	}
	else if (toRemove->right == nullptr){ //has one (left) child
		if (toRemove->parent == nullptr){
            this->root = toRemove->left;
            this->root->parent = nullptr;
		}
		else if (toRemove == toRemove->parent->left){ //we're the left child of our parent
			toRemove->parent->left = toRemove->left;
			toRemove->left->parent = toRemove->parent;
		}
		else{
			toRemove->parent->right = toRemove->left;
			toRemove->left->parent = toRemove->parent;
		}
		delete toRemove;
	}
	else if (toRemove->left == nullptr){ //has one right child, almost same solution as left child only
		if (toRemove->parent == nullptr){
            this->root = toRemove->right;
            this->root->parent = nullptr;
		}
		else if (toRemove == toRemove->parent->left){ //we're the left child of our parent
			toRemove->parent->left = toRemove->right;
			toRemove->right->parent = toRemove->parent;
		}
		else{
			toRemove->parent->right = toRemove->right;
			toRemove->right->parent = toRemove->parent;
		}
		delete toRemove;
	}
	else{ //sigh... two children!
		AVLNode<T>* temp = toRemove->right;
		while (temp->left != nullptr)
			temp = temp->left;
		toRemove->data = temp->data;
		remove(temp);
	}

}

template <class T>
AVLNode<T>* AVL<T>::find(const T& toFind) const{
	AVLNode<T>* temp = this->root;
	while (temp != nullptr && temp->data != toFind){
		if (toFind < temp->data)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return temp;
}

template <class T>
void AVL<T>::insert(const T& toInsert, TreeNode<T>*& point_){
	if (point_==nullptr) {
        point_ = new AVLNode<T>(toInsert, nullptr, nullptr, nullptr);
        return;
    }
	AVLNode<T>* point = (AVLNode<T>*) point_;
	if (toInsert < point->data){
		insert(toInsert, point->left);
		point->left->parent = point; //update parent pointer
		point->calcHeight();
		if (heightDiff(point) > 1){
			doRotation(point);
		}
	}
	else{
		insert(toInsert, point->right);
		point->right->parent = point;
		point->calcHeight();
		if (heightDiff(point) > 1){
			doRotation(point);
		}
	}
}

template <class T>
void AVL<T>::insert(const T& toInsert){
	AVL<T>::insert(toInsert, this->root);
}
template <class T>
void AVL<T>::doRotation(AVLNode<T>* point){
	int leftChild = -1;
	int rightChild = -1;
	if (point->left != nullptr)
		leftChild = point->left->getHeight();
	if (point->right != nullptr)
		rightChild = point->right->getHeight();

	if (leftChild > rightChild){//CR, but is it single or double?
		int leftGC = -1;
		int rightGC = -1;
		if (point->left->left != nullptr)
			leftGC = point->left->left->getHeight();
		if (point->left->right != nullptr)
			rightGC = point->left->right->getHeight();
		if (leftGC > rightGC) // single rotation
			singleCR(point);
		else
			doubleCR(point);
	}
	else{//definitely a CCR, but which one?
		int leftGC = -1;
		int rightGC = -1;
		if (point->right->left != nullptr)
			leftGC = point->right->left->height;
		if (point->right->right != nullptr)
			rightGC = point->right->right->height;
		if (leftGC > rightGC) // double rotation
			doubleCCR(point);
		else
			singleCCR(point);
	}
}


template<class T>
int AVL<T>::heightDiff(AVLNode<T>* point){
	int leftHeight = -1;
	int rightHeight = -1;
	if (point->left != nullptr)
		leftHeight = point->left->height;
	if (point->right != nullptr)
		rightHeight = point->right->height;
	return (abs(leftHeight - rightHeight));
}

template <class T>
int AVL<T>::getSize() const {
    if (root == nullptr) {
        return 0;
    }
    return root->size();
}

template <class T>
bool AVL<T>::check() const {
    if (!check(root)) {
        return false;
    }
    if (root != nullptr) {
        if (!check(root->left)) {
            return false;
        }
        if (!check(root->right)) {
            return false;
        }
    }
    return true;
}

template<class T>
bool AVL<T>::check(AVLNode<T>* node) const {
    if (node == nullptr) {
        return true;
    }
    int leftHeight = -1, rightHeight = -1;
    if (node->left != nullptr) {
        if (node->data < node->left->data) {
            return false;
        }
        leftHeight = node->left->recalcHeight();
    }
    if (node->right != nullptr) {
        if (node->right->data < node->data) {
            return false;
        }
        rightHeight = node->right->recalcHeight();
    }
    if (std::abs(leftHeight - rightHeight) > 1) {
        return false;
    }
    return true;
}

template <class T>
void AVL<T>::singleCR(TreeNode<T>*& point){
    AVLNode<T>* grandparent = (AVLNode<T>*) point;
    AVLNode<T>* parent = (AVLNode<T>*) point->left;
    Tree<T>::singleCR(point);
    grandparent->calcHeight();
    parent->calcHeight();
}

template <class T>
void AVL<T>::singleCCR(TreeNode<T>*& point){
    AVLNode<T>* grandparent = (AVLNode<T>*) point;
    AVLNode<T>* parent = (AVLNode<T>*) point->right;
    Tree<T>::singleCCR(point);
    grandparent->calcHeight();
    parent->calcHeight();
}

