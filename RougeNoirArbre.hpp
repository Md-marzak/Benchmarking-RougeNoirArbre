#ifndef ROUGENOIRARBRE_HPP_INCLUDED
#define ROUGENOIRARBRE_HPP_INCLUDED

#include "RougeNoirNode.hpp"
#include <iostream>

template <typename Type>
class RougeNoirArbre
{
    using Node = RougeNoirNode<Type>;

private:
    Node* Racine;

    void RotateLeft(Node* x);
    void RotateRight(Node* x);
    void FixInsert(Node* z);
    Node* Minimum(Node* x) const;
    void Transplant(Node* u, Node* v);
    void FixDelete(Node* x);
    void InOrderHelper(Node* root) const;

public:
    RougeNoirArbre();
    typename RougeNoirArbre<Type>::Node* GetRacine() const;
    void Inserer(Node* z);
    void Inserer(Type val);
    typename RougeNoirArbre<Type>::Node* Search(Node* x, const Type& k) const;
    void Supprimer(Node* z);
    void PrintTree() const;
};

// ==========================================
// Implémentation
// ==========================================

template <typename Type>
RougeNoirArbre<Type>::RougeNoirArbre() : Racine(nullptr) {}

template <typename Type>
typename RougeNoirArbre<Type>::Node* RougeNoirArbre<Type>::GetRacine() const {
    return Racine;
}

template <typename Type>
void RougeNoirArbre<Type>::RotateLeft(Node* x) {
    Node* y = x->getDroite();
    x->setDroite(y->getGauche());

    if (y->getGauche())
        y->getGauche()->setParent(x);

    y->setParent(x->getParent());

    if (!x->getParent())
        Racine = y;
    else if (x == x->getParent()->getGauche())
        x->getParent()->setGauche(y);
    else
        x->getParent()->setDroite(y);

    y->setGauche(x);
    x->setParent(y);
}

template <typename Type>
void RougeNoirArbre<Type>::RotateRight(Node* x) {
    Node* y = x->getGauche();
    x->setGauche(y->getDroite());

    if (y->getDroite())
        y->getDroite()->setParent(x);

    y->setParent(x->getParent());

    if (!x->getParent())
        Racine = y;
    else if (x == x->getParent()->getDroite())
        x->getParent()->setDroite(y);
    else
        x->getParent()->setGauche(y);

    y->setDroite(x);
    x->setParent(y);
}

template <typename Type>
void RougeNoirArbre<Type>::FixInsert(Node* z) {
    while (z->getParent() && z->getParent()->getCouleur() == Rouge) {
        if (z->getParent() == z->getParent()->getParent()->getGauche()) {
            Node* y = z->getParent()->getParent()->getDroite();
            if (y && y->getCouleur() == Rouge) {
                z->getParent()->setCouleur(Noire);
                y->setCouleur(Noire);
                z->getParent()->getParent()->setCouleur(Rouge);
                z = z->getParent()->getParent();
            } else {
                if (z == z->getParent()->getDroite()) {
                    z = z->getParent();
                    RotateLeft(z);
                }
                z->getParent()->setCouleur(Noire);
                z->getParent()->getParent()->setCouleur(Rouge);
                RotateRight(z->getParent()->getParent());
            }
        } else {
            Node* y = z->getParent()->getParent()->getGauche();
            if (y && y->getCouleur() == Rouge) {
                z->getParent()->setCouleur(Noire);
                y->setCouleur(Noire);
                z->getParent()->getParent()->setCouleur(Rouge);
                z = z->getParent()->getParent();
            } else {
                if (z == z->getParent()->getGauche()) {
                    z = z->getParent();
                    RotateRight(z);
                }
                z->getParent()->setCouleur(Noire);
                z->getParent()->getParent()->setCouleur(Rouge);
                RotateLeft(z->getParent()->getParent());
            }
        }
    }
    if (Racine) Racine->setCouleur(Noire);
}

template <typename Type>
typename RougeNoirArbre<Type>::Node* RougeNoirArbre<Type>::Minimum(Node* x) const {
    while (x->getGauche())
        x = x->getGauche();
    return x;
}

template <typename Type>
void RougeNoirArbre<Type>::Transplant(Node* u, Node* v) {
    if (!u->getParent())
        Racine = v;
    else if (u == u->getParent()->getGauche())
        u->getParent()->setGauche(v);
    else
        u->getParent()->setDroite(v);
    if (v) v->setParent(u->getParent());
}

template <typename Type>
void RougeNoirArbre<Type>::FixDelete(Node* x) {
    while (x != Racine && (!x || x->getCouleur() == Noire)) {
        if (!x) break;
        if (x == x->getParent()->getGauche()) {
            Node* w = x->getParent()->getDroite();
            if (w->getCouleur() == Rouge) {
                w->setCouleur(Noire);
                x->getParent()->setCouleur(Rouge);
                RotateLeft(x->getParent());
                w = x->getParent()->getDroite();
            }
            if ((!w->getGauche() || w->getGauche()->getCouleur() == Noire) &&
                (!w->getDroite() || w->getDroite()->getCouleur() == Noire)) {
                w->setCouleur(Rouge);
                x = x->getParent();
            } else {
                if (!w->getDroite() || w->getDroite()->getCouleur() == Noire) {
                    if (w->getGauche()) w->getGauche()->setCouleur(Noire);
                    w->setCouleur(Rouge);
                    RotateRight(w);
                    w = x->getParent()->getDroite();
                }
                w->setCouleur(x->getParent()->getCouleur());
                x->getParent()->setCouleur(Noire);
                if (w->getDroite()) w->getDroite()->setCouleur(Noire);
                RotateLeft(x->getParent());
                x = Racine;
            }
        } else {
            Node* w = x->getParent()->getGauche();
            if (w->getCouleur() == Rouge) {
                w->setCouleur(Noire);
                x->getParent()->setCouleur(Rouge);
                RotateRight(x->getParent());
                w = x->getParent()->getGauche();
            }
            if ((!w->getGauche() || w->getGauche()->getCouleur() == Noire) &&
                (!w->getDroite() || w->getDroite()->getCouleur() == Noire)) {
                w->setCouleur(Rouge);
                x = x->getParent();
            } else {
                if (!w->getGauche() || w->getGauche()->getCouleur() == Noire) {
                    if (w->getDroite()) w->getDroite()->setCouleur(Noire);
                    w->setCouleur(Rouge);
                    RotateLeft(w);
                    w = x->getParent()->getGauche();
                }
                w->setCouleur(x->getParent()->getCouleur());
                x->getParent()->setCouleur(Noire);
                if (w->getGauche()) w->getGauche()->setCouleur(Noire);
                RotateRight(x->getParent());
                x = Racine;
            }
        }
    }
    if (x) x->setCouleur(Noire);
}

template <typename Type>
void RougeNoirArbre<Type>::InOrderHelper(Node* root) const {
    if (!root) return;
    InOrderHelper(root->getGauche());
    root->print();
    InOrderHelper(root->getDroite());
}

template <typename Type>
void RougeNoirArbre<Type>::Inserer(Node* z) {
    Node* y = nullptr;
    Node* x = Racine;
    while (x) {
        y = x;
        if (z->getValeur() < x->getValeur())
            x = x->getGauche();
        else
            x = x->getDroite();
    }
    z->setParent(y);
    if (!y)
        Racine = z;
    else if (z->getValeur() < y->getValeur())
        y->setGauche(z);
    else
        y->setDroite(z);
    FixInsert(z);
}

template <typename Type>
void RougeNoirArbre<Type>::Inserer(Type val) {
    Inserer(new typename RougeNoirArbre<Type>::Node(val));
}

template <typename Type>
typename RougeNoirArbre<Type>::Node* RougeNoirArbre<Type>::Search(Node* x, const Type& k) const {
    if (!x || k == x->getValeur()) return x;
    if (k < x->getValeur()) return Search(x->getGauche(), k);
    else return Search(x->getDroite(), k);
}

template <typename Type>
void RougeNoirArbre<Type>::Supprimer(Node* z) {
    if (!z) return;

    Node* y = z;
    Node* x = nullptr;
    CouleurRN originalColor = y->getCouleur();

    if (!z->getGauche()) {
        x = z->getDroite();
        Transplant(z, z->getDroite());
    } else if (!z->getDroite()) {
        x = z->getGauche();
        Transplant(z, z->getGauche());
    } else {
        y = Minimum(z->getDroite());
        originalColor = y->getCouleur();
        x = y->getDroite();
        if (y->getParent() == z) {
            if (x) x->setParent(y);
        } else {
            Transplant(y, y->getDroite());
            y->setDroite(z->getDroite());
            y->getDroite()->setParent(y);
        }
        Transplant(z, y);
        y->setGauche(z->getGauche());
        y->getGauche()->setParent(y);
        y->setCouleur(z->getCouleur());
    }

    if (originalColor == Noire && x)
        FixDelete(x);

    delete z;
}

template <typename Type>
void RougeNoirArbre<Type>::PrintTree() const {
    InOrderHelper(Racine);
    std::cout << std::endl;
}

#endif // ROUGENOIRARBRE_HPP_INCLUDED
