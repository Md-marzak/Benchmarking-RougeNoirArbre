# Benchmarking-RougeNoirArbre

Ce projet compare les performances de différentes structures de données en C++ :  

- `RougeNoirArbre<int>`  
- `std::set<int>`  
- `std::unordered_set<int>`  
- `std::map<int,string>`  
- `Arbre<string>`  

Les opérations testées sont : **insertion, recherche et suppression** sur **1 000 000 éléments**.

---

## Table des Matières

1. [Prérequis](#prérequis)  
2. [Installation](#installation)  
3. [Compilation et Exécution](#compilation-et-exécution)  
4. [Structure du Projet](#structure-du-projet)  
5. [Compte Rendu (PDF)](./Compte_Rendu_RedBlackTree.pdf)  

---

## Prérequis

- Compilateur C++ compatible C++17 ou supérieur (`g++`, `clang++`)  
- Git pour cloner le projet  

---

## Installation

Cloner le dépôt sur votre ordinateur :

```bash
git clone https://github.com/Md-marzak/Benchmarking-RougeNoirArbre.git
cd Benchmarking-RougeNoirArbre

## Structure du Projet

- `main.cpp` : Programme principal  
- `RougeNoirArbre.h` : Implémentation de l'arbre rouge-noir
- `RougeNoirNode.h` : Implémentation de l'arbre rouge-noir   
- `Arbre.h` : Implémentation de l'arbre générique
- `Node.h` : Implémentation de l'arbre générique
- `README.md` : Ce fichier  
- `Compte_Rendu_RedBlackTree.pdf` : Rapport détaillé
