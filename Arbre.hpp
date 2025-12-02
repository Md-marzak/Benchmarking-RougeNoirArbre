#ifndef ARBRE_HPP_INCLUDED
#define ARBRE_HPP_INCLUDED

#include <queue>
#include "Node.hpp"

template<typename T>
class Arbre
{
private:
    Node<T>* root;

public:

    Arbre() : root(nullptr) {}

    ~Arbre() {
        delete root;
        root = nullptr;
    }

    /* ======================================================
       Parcours en largeur (BFS) réécrit
    ====================================================== */
    void parcourirLargeur() const
    {
        if (!root)
            return;

        std::queue<Node<T>*> q;
        q.push(root);

        while (!q.empty())
        {
            Node<T>* cur = q.front();
            q.pop();

            // Exemple d'utilisation :
            // std::cout << cur->getKey() << " ";

            if (cur->hasLeft())
                q.push(cur->getLeft());

            if (cur->hasRight())
                q.push(cur->getRight());
        }
    }

    /* ======================================================
       Insertion dans un ABR ( totalement réécrit )
    ====================================================== */
    int inserer(int cle, const T& val)
    {
        Node<T>* existant = rechercher(cle);

        if (existant)
        {
            existant->setData(val);
            return 1;
        }

        Node<T>* nouveau = new Node<T>(cle, val);

        if (!root)
        {
            root = nouveau;
            return 1;
        }

        Node<T>* courant = root;
        Node<T>* prec = nullptr;

        while (courant)
        {
            prec = courant;

            if (cle < courant->getKey())
                courant = courant->getLeft();
            else
                courant = courant->getRight();
        }

        if (cle < prec->getKey())
            prec->attachLeft(nouveau);
        else
            prec->attachRight(nouveau);

        return 1;
    }

    /* ======================================================
       Recherche réécrite (utilise Node::search)
    ====================================================== */
    Node<T>* rechercher(int cle) const
    {
        if (!root)
            return nullptr;

        return root->search(cle);
    }

    /* ======================================================
       Retourner le maximum
    ====================================================== */
    Node<T>* max() const
    {
        if (!root)
            return nullptr;

        return root->findMax();
    }

    /* ======================================================
       Suppression réécrite
    ====================================================== */
    int enlever(int cle)
    {
        if (!root)
            return 0;

        if (!rechercher(cle))
            return 0;

        root = root->deleteNode(cle);
        return 1;
    }
};




#endif // ARBRE_HPP_INCLUDED
