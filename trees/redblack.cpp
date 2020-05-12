#include "redblack.h"
#include <set>

template<class T>
RedBlackTree<T>::~RedBlackTree() {
    clear();
}

template<class T>
bool RedBlackTree<T>::isEmpty() const {
    return Tree<T>::isEmpty();
}

template<class T>
void RedBlackTree<T>::clear(TreeNode<T>* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template<class T>
void RedBlackTree<T>::clear() {
    clear(this->root);
}

template<class T>
int RedBlackTree<T>::getSize() const {
    if (this->root == nullptr) {
        return 0;
    }
    return this->root->size();
}

template <class T>
bool RedBlackTree<T>::check() const {
    if (!Tree<T>::check()) {
        return false;
    }
    RBNode<T>* root = (RBNode<T>*) (this->root);
    return check(root);
}


template <class T>
bool RedBlackTree<T>::check(RBNode<T>* node) const {
    if (node == nullptr) {
        return true;
    }
    // rule 1 is stipulated by data structure
    // rule 2: root must be black
    if (node->parent == nullptr && !node->isBlack()) {
        return false;
    }
    RBNode<T>* left = node->GetLeft();
    RBNode<T>* right = node->GetRight();
    // rule 3: if a node is red, its children must be black
    if (node->isRed()) {
        if (left != nullptr && left->isRed()) {
            return false;
        }
        if (right != nullptr && right->isRed()) {
            return false;
        }
    }
    // rule 4: every path from a node to null must traverse same number of black nodes
    using namespace std;
    vector<RBNode<T>*> descendants;
    GetDescendants(node, descendants);
    vector<vector<RBNode<T>*>> paths_with_nulls;
    for (RBNode<T>* d : descendants) {
        if (d->left == nullptr || d->right == nullptr) {
            vector<RBNode<T>*> path_from_root = d->GetPathFrom(node);
            paths_with_nulls.push_back(path_from_root);
        }
    }
    set<size_t> black_node_counts;
    for (const vector<RBNode<T>*> path : paths_with_nulls) {
        size_t num_black_nodes = 0;
        for (RBNode<T>* n : path) {
            if (n->isBlack()) {
                num_black_nodes++;
            }
        }
        black_node_counts.insert(num_black_nodes);
    }
    if (black_node_counts.size() > 1) {
        return false;
    }
    return check(left) && check(right);
}

template<class T>
bool RedBlackTree<T>::isInTree(const T &element) const {
    TreeNode<T>* current = this->root;
    while (current != nullptr && current->data != element) {
        if (element < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return current != nullptr;
}

template<class T>
void RedBlackTree<T>::GetDescendants(RBNode<T>* node, std::vector<RBNode<T>*> &nodes) const {
    if (node != nullptr) {
        nodes.push_back(node);
        GetDescendants(node->GetLeft(), nodes);
        GetDescendants(node->GetRight(), nodes);
    }
}


