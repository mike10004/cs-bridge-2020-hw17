#include "redblack.h"
#include <set>
#include <cassert>

template<class T>
std::vector<RBNode<T> *> RBNode<T>::GetPathFrom(RBNode<T>* node) const {
    std::stack<RBNode<T>*> path_from_here;
    RBNode<T>* current = GetParent();
    bool found = false;
    while (current != nullptr) {
        path_from_here.push(current);
        if (current == node) {
            found = true;
            break;
        }
        current = current->GetParent();
    }
    if (found || node == nullptr) {
        std::vector<RBNode<T>*> path_from_node;
        while (!path_from_here.empty()) {
            path_from_node.push_back(path_from_here.top());
            path_from_here.pop();
        }
        return path_from_node;
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
RBNode<T> *RBNode<T>::GetParent() const {
    return (RBNode<T>*) (this->parent);
}

template<class T>
RBNode<T> *RBNode<T>::GetLeft() const {
    return (RBNode<T>*) (this->left);
}

template<class T>
RBNode<T> *RBNode<T>::GetRight() const {
    return (RBNode<T>*) (this->right);
}

template<class T>
void RBNode<T>::SetColor(Color color_) {
    color = color_;
}

template<class T>
RBNode<T>* RBNode<T>::GetSibling() {
    RBNode<T>* parent = GetParent();
    if (parent == nullptr) {
        return nullptr;
    }
    RBNode<T>* parent_left = parent->GetLeft();
    RBNode<T>* parent_right = parent->GetRight();
    return parent_left == this ? parent_right : parent_left;
}

template<class T>
RedBlackTree<T>::~RedBlackTree() {
    clear();
}

template<class T>
bool RedBlackTree<T>::isEmpty() const {
    return Tree<T>::isEmpty();
}

template<class T>
void RedBlackTree<T>::clear(TreeNode<T>*& node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
        node = nullptr;
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
            path_from_root.push_back(node);
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

template<class T>
void RedBlackTree<T>::insert(const T &value) {
    // case 1: insert root
    if (this->root == nullptr) {
        RBNode<T>* node = new RBNode<T>(value);
        node->SetColor(BLACK);
        this->root = node;
    } else {
        RBNode<T>* inserted_node = insert(value, (RBNode<T>*) this->root);
        this->root = repair(inserted_node);
    }
}

template <class T>
RBNode<T>* RedBlackTree<T>::insert(const T& value, RBNode<T>* point) {
    assert(point != nullptr);
    if (value < point->data) {
        if (point->left == nullptr) {
            RBNode<T>* node = new RBNode<T>(value, point);
            point->left = node;
            return node;
        } else {
            return insert(value, (RBNode<T>*) point->left);
        }
    } else if (value > point->data) {
        if (point->right == nullptr) {
            RBNode<T>* node = new RBNode<T>(value, point);
            point->right = node;
            return node;
        } else {
            return insert(value, (RBNode<T>*) point->right);
        }
    } else { // value equals point->data
        return point;
    }
}

template<class T>
RBNode<T>* RedBlackTree<T>::repair(RBNode<T> *node) {
    assert(node != nullptr);
    RBNode<T>* parent = node->GetParent();
    if (parent == nullptr) {
        // case 1: inserted root
        node->SetColor(BLACK);
        return node;
    } else {
        // case 2: if parent of inserted node is black, then do nothing; otherwise...
        if (parent->isBlack()) {
            return (RBNode<T>*) this->root;
        } else {
            RBNode<T>* parent_sibling = parent->GetSibling();
            if (parent_sibling != nullptr && parent_sibling->isRed()) {
                // case 3
                parent->SetColor(BLACK);
                parent_sibling->SetColor(BLACK);
                return repair(parent->GetParent()); // we know it's non-null because parent_sibling is non-null
            } else {
                // case 4
                TreeNode<T>* p = node->parent;
                TreeNode<T>* g = p == nullptr ? nullptr : p->parent;
                if (node == p->right && p == g->left) {
                    rotateLeft(p);
                    repairCase4Step2((RBNode<T>*) (node->left));
                } else if (node == p->left && p == g->right) {
                    rotateRight(p);
                    repairCase4Step2((RBNode<T>*) (node->right));
                }
                TreeNode<T>* new_root = node;
                while (new_root->parent != nullptr) {
                    new_root = new_root->parent;
                }
                return (RBNode<T>*) new_root;
            }
        }
    }
}

template <class T>
void RedBlackTree<T>::rotateLeft(TreeNode<T>* n) {
    TreeNode<T>* nnew = n->right;
    TreeNode<T>* p = n->parent;
    assert(nnew != nullptr);

    n->right = nnew->left;
    nnew->left = n;
    n->parent = nnew;

    if (n->right != nullptr) {
        n->right->parent = n;
    }

    if (p != nullptr) {
        if (n == p->left) {
            p->left = nnew;
        } else if (n == p->right) {
            p->right = nnew;
        }
    }
    nnew->parent = p;
}

template <class T>
void RedBlackTree<T>::rotateRight(TreeNode<T>* n) {
    TreeNode<T>* nnew = n->left;
    TreeNode<T>* p = n->parent;
    assert(nnew != nullptr);

    n->left = nnew->right;
    nnew->right = n;
    n->parent = nnew;

    if (n->left != nullptr) {
        n->left->parent = n;
    }

    if (p != nullptr) {
        if (n == p->left) {
            p->left = nnew;
        } else if (n == p->right) {
            p->right = nnew;
        }
    }
    nnew->parent = p;
}

template <class T>
void RedBlackTree<T>::repairCase4Step2(RBNode<T>* node) {
    RBNode<T>* p = node->GetParent();
    RBNode<T>* g = p == nullptr ? nullptr : p->GetParent();
    if (node == p->left) {
        rotateRight(g);
    } else {
        rotateLeft(g);
    }
    p->SetColor(BLACK);
    g->SetColor(RED);
}


