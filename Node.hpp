#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED
#include <iostream>

template<typename T>
class Node
{
private:
    int key;
    T data;
    Node* left;
    Node* right;

public:

    Node(int k, const T& d)
        : key(k), data(d), left(nullptr), right(nullptr) {}

    ~Node() {
        delete left;
        delete right;
    }

    int getKey() const { return key; }
    const T& getData() const { return data; }

    void setKey(int k) { key = k; }
    void setData(const T& d) { data = d; }

    Node* getLeft() const { return left; }
    Node* getRight() const { return right; }

    void attachLeft(Node* n) { left = n; }
    void attachRight(Node* n) { right = n; }

    bool hasLeft() const { return left != nullptr; }
    bool hasRight() const { return right != nullptr; }

    /* ======================================================
       Ajout de valeur : version totalement réécrite
    ====================================================== */
    Node* insertChild(int k, const T& d)
    {
        if (!left) {
            left = new Node(k, d);
            return left;
        }

        if (!right) {
            right = new Node(k, d);
            return right;
        }

        if (k % 2 == 0)      // décision aléatoire différente de ton code
            return left->insertChild(k, d);
        else
            return right->insertChild(k, d);
    }

    /* ======================================================
       Recherche dans ABR
    ====================================================== */
    Node* search(int k) const
    {
        if (k == key)
            return (Node*)this;

        if (k < key)
            return left ? left->search(k) : nullptr;

        return right ? right->search(k) : nullptr;
    }

    /* ======================================================
       Trouver maximum du côté droit
    ====================================================== */
    Node* findMax() const
    {
        const Node* n = this;
        while (n->right)
            n = n->right;
        return (Node*)n;
    }

    /* ======================================================
       Suppression réécrite
    ====================================================== */
    Node* deleteNode(int k)
    {
        if (k < key) {
            if (left)
                left = left->deleteNode(k);
            return this;
        }

        if (k > key) {
            if (right)
                right = right->deleteNode(k);
            return this;
        }

        if (!left && !right) {
            delete this;
            return nullptr;
        }

        if (!left) {
            Node* r = right;
            right = nullptr;
            delete this;
            return r;
        }

        if (!right) {
            Node* l = left;
            left = nullptr;
            delete this;
            return l;
        }

        Node* maxLeft = left->findMax();
        key = maxLeft->key;
        data = maxLeft->data;
        left = left->deleteNode(maxLeft->key);
        return this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Node<T>& n)
    {
        out << "[" << n.key << ":" << n.data << "]";
        return out;
    }
};



#endif // NODE_HPP_INCLUDED
