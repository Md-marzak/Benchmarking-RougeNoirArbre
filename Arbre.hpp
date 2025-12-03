#ifndef ARBRE_HPP_INCLUDED
#define ARBRE_HPP_INCLUDED

#include "Node.hpp"

template<typename T>
class Arbre
{
private:
    Node<T>* root;

public:
    Arbre() : root(nullptr) {}
    ~Arbre() { delete root; }

    int inserer(int key, const T& val) {
        if (!root) { root = new Node<T>(key, val); return 1; }

        Node<T>* cur = root;
        Node<T>* prec = nullptr;
        while (cur) {
            prec = cur;
            if (key < cur->getKey()) cur = cur->getLeft();
            else cur = cur->getRight();
        }

        if (key < prec->getKey())
            prec->attachLeft(new Node<T>(key, val));
        else
            prec->attachRight(new Node<T>(key, val));

        return 1;
    }

    Node<T>* rechercher(int key) const {
        return root ? root->search(key) : nullptr;
    }

    void enlever(int key) {
        if (root) root = root->deleteNode(key);
    }
};

#endif // ARBRE_HPP_INCLUDED
