#include <iostream>
#include <queue>
#include "avl.h"

template <class T>
using queue = std::queue<T>;

template <class T>
void AVL<T>::printLevelOrder(ostream& out) const{
	queue<AVLNode<T>*> q;
	q.push(root);
	while (!q.empty()){
		AVLNode<T>* front = q.front();
		out << front->data << "\t" << front->height << std::endl;
		if (front->left!=nullptr)
			q.push(front->left);
		if (front->right)
			q.push(front->right);
		q.pop();
	}
}
template <class T>
void AVL<T>::doubleCCR(AVLNode<T>*& point){
	singleCR(point->right);
	singleCCR(point);
}

template <class T>
void AVL<T>::doubleCR(AVLNode<T>*& point){
	singleCCR(point->left);
	singleCR(point);
}

template <class T>
void AVL<T>::singleCR(AVLNode<T>*& point){
	AVLNode<T>* grandparent = point;
	AVLNode<T>* parent = point->left;
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
	grandparent->calcHeight();
	parent->calcHeight();
}

template <class T>
void AVL<T>::singleCCR(AVLNode<T>*& point){
	AVLNode<T>* grandparent = point;
	AVLNode<T>* parent = point->right;
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
	grandparent->calcHeight();
	parent->calcHeight();
}


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
	root = recursiveCopy(rhs.root);
	return *this;
}

template <class T>
void AVL<T>::remove(AVLNode<T>* toRemove){
	if (root == nullptr)
		return; //Remove from an empty tree????
	if (toRemove->left == nullptr && toRemove->right == nullptr){ //leaf node case
		if (toRemove->parent == nullptr){
			root = nullptr;
		}
		else if (toRemove == toRemove->parent->left) //left child!
			toRemove->parent->left = nullptr; //fix the parent's pointer!
		else
			toRemove->parent->right = nullptr;
		delete toRemove;
	}
	else if (toRemove->right == nullptr){ //has one (left) child
		if (toRemove->parent == nullptr){
			root = toRemove->left;
			root->parent = nullptr;
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
			root = toRemove->right;
			root->parent = nullptr;
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
	AVLNode<T>* temp = root;
	while (temp != nullptr && temp->data != toFind){
		if (toFind < temp->data)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return temp;
}

template <class T>
void AVL<T>::insert(const T& toInsert, AVLNode<T>*& point){
	if (point==nullptr)
		point = new AVLNode<T>(toInsert);
	else if (toInsert < point->data){
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
	insert(toInsert, root);
}
template <class T>
void AVL<T>::doRotation(AVLNode<T>* point){
	int leftChild = -1;
	int rightChild = -1;
	if (point->left != nullptr)
		leftChild = point->left->height;
	if (point->right != nullptr)
		rightChild = point->right->height;

	if (leftChild > rightChild){//CR, but is it single or double?
		int leftGC = -1;
		int rightGC = -1;
		if (point->left->left != nullptr)
			leftGC = point->left->left->height;
		if (point->left->right != nullptr)
			rightGC = point->left->right->height;
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