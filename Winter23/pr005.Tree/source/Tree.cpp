#include "Tree.h"


Tree::Node::Node(Node* parent, int value) : value(value), parent(parent), l(nullptr), r(nullptr) {}

void Tree::Node::addL(int value) {
    // if (this->l) std::cout << "addL по живому" << endl;
    this->l = new Node(this, value);
}

void Tree::Node::addR(int value) {
    // if (this->r) std::cout << "addR по живому" << endl;
    this->r = new Node(this, value);
}

int Tree::Node::getValue() {
    return this->value;
}

Tree::Node* Tree::Node::getParent() {
    return this->parent;
}

Tree::Node* Tree::Node::getL() {
    return this->l;
}

Tree::Node* Tree::Node::getR() {
    return this->r;
}

void Tree::Node::setL(Tree::Node* newL) {
    this->l = newL;
    if (!newL) return;
    newL->parent = this;
}

void Tree::Node::setR(Tree::Node* newR) {
    this->r = newR;
    if (!newR) return;
    newR->parent = this;
}

void Tree::Node::setParent(Node* newParent) {
    this->parent = newParent;
}

void Tree::Node::swap(Node* b) {
    int temp = this->value;
    this->value = b->value;
    b->value = temp;
}


Tree::Tree() : root(nullptr) {}

void Tree::add(int value) {
    if (root) add(root, value);
    else root = new Node(nullptr, value);
}

Tree::Node* Tree::search(int value) {
    if (root) return search(root, value);
    else return nullptr;
}

bool Tree::remove(int value) {
    if (root) return remove(root, value);
    else return false;
}

void Tree::add(Node* node, int value) {
    if (value < node->getValue()) {
        if (node->getL()) add(node->getL(), value);
        else node->addL(value);
    }
    if (value > node->getValue()) {
        if (node->getR()) add(node->getR(), value);
        else node->addR(value);
    }
}

Tree::Node* Tree::search(Tree::Node* node, int value) {
    if (value < node->getValue()) {
        if (node->getL()) return search(node->getL(), value);
        else return nullptr;
    }
    if (value > node->getValue()) {
        if (node->getR()) return search(node->getR(), value);
        else return nullptr;
    }

    return node;
}

Tree::Node* Tree::next(Node* node) {
    Node* ptr = node->getR();

    while (ptr->getL()) {
        ptr = ptr->getL();
    }

    return ptr;
}

bool Tree::remove(Node* node, int value) {
    Node* ptr = search(value);

    if (!ptr) return false;

    remove(ptr);

    return true;
}

void Tree::remove(Node* ptr) {
    if (ptr->getL()) {
        if (ptr->getR()) {
            Node* ptrNext = this->next(ptr);
            ptr->swap(ptrNext);

            remove(ptrNext);

        } else {
            if (!ptr->getParent()) return;
            if (ptr->getParent()->getL() == ptr) ptr->getParent()->setL(ptr->getL());
            if (ptr->getParent()->getR() == ptr) ptr->getParent()->setR(ptr->getL());
        }
    } else {
        if (!ptr->getParent()) return;
        if (ptr->getR()) {
            if (ptr->getParent()->getL() == ptr) ptr->getParent()->setL(ptr->getR());
            if (ptr->getParent()->getR() == ptr) ptr->getParent()->setR(ptr->getR());
        } else {
            if (ptr->getParent()->getL() == ptr) ptr->getParent()->setL(nullptr);
            if (ptr->getParent()->getR() == ptr) ptr->getParent()->setR(nullptr);
        }
    }
}

