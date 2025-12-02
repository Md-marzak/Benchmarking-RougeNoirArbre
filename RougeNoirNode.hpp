#ifndef ROUGENOIRNODE_HPP_INCLUDED
#define ROUGENOIRNODE_HPP_INCLUDED

#include <iostream>

// ----------------------------
// Définition des couleurs
// ----------------------------
enum CouleurRN {
    Noire = 0,
    Rouge = 1
};

template <typename Type>
class RougeNoirNode
{
private:
    Type valeur;
    CouleurRN couleur;

    RougeNoirNode* gauche;
    RougeNoirNode* droite;
    RougeNoirNode* parent;

public:

    // -------------------------------------------------------
    // Constructeur
    // -------------------------------------------------------
    explicit RougeNoirNode(const Type& val)
        : valeur(val), couleur(Rouge),
          gauche(nullptr), droite(nullptr), parent(nullptr)
    {}

    // -------------------------------------------------------
    // Getters
    // -------------------------------------------------------
    Type getValeur() const { return valeur; }
    CouleurRN getCouleur() const { return couleur; }

    RougeNoirNode* getGauche() const { return gauche; }
    RougeNoirNode* getDroite() const { return droite; }
    RougeNoirNode* getParent() const { return parent; }

    // -------------------------------------------------------
    // Setters
    // -------------------------------------------------------
    void setValeur(const Type& v) { valeur = v; }
    void setCouleur(CouleurRN c) { couleur = c; }

    void setGauche(RougeNoirNode* g) { gauche = g; }
    void setDroite(RougeNoirNode* d) { droite = d; }
    void setParent(RougeNoirNode* p) { parent = p; }

    // -------------------------------------------------------
    // Affichage
    // -------------------------------------------------------
    void print() const {
        std::cout << valeur << "(" << (couleur == Rouge ? "R" : "N") << ") ";
    }
};





#endif // ROUGENOIRNODE_HPP_INCLUDED
