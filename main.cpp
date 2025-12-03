#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Arbre.hpp"
#include "RougeNoirArbre.hpp"
#include "Clock.hpp"

using namespace std;

void printTitle(const string& title)
{
    const int width = 46;   // largeur totale
    int padding = (width - title.size()) / 2;

    cout << "\n" << string(width, '*') << "\n";
    cout << string(padding, '*') << "  " << title << "  "
         << string(width - padding - title.size() - 4, '*') << "\n";
    cout << string(width, '*') << "\n\n";
}

int main()
{
    const size_t COUNT = 1000000; // nombre d'éléments à tester

    srand(static_cast<unsigned>(time(nullptr)));
    Clock timer;

    // -----------------------
    // Lecture fichier
    // -----------------------
    ifstream inputFile("wordsFile.txt");
    if (!inputFile.is_open())
    {
        cout << "Impossible d'ouvrir le fichier wordsFile.txt !" << endl;
        return 1;
    }

    vector<string> words;
    words.reserve(COUNT);
    string word;
    while (words.size() < COUNT && (inputFile >> word))
        words.push_back(word);
    inputFile.close();

    if (words.empty())
    {
        cout << "Fichier vide ou introuvable !" << endl;
        return 1;
    }

    // -----------------------
    // Générer des clés
    // -----------------------
    vector<int> keys;
    keys.reserve(words.size());
    for (size_t i = 0; i < words.size(); ++i)
        keys.push_back(rand() % 1000001);

    size_t realCount = words.size();
    int testKey = keys[realCount / 2];
    int delKey  = keys[realCount / 3];

    // ==========================================================
    // TEST 1 : RougeNoirArbre<int>
    // ==========================================================
    printTitle("TEST 1 : RougeNoirArbre<int>");
    RougeNoirArbre<int> rbTree;

    cout << "\n--------- Remplir Arbre RB ! ---------";
    timer.chronoStart();
    for (int k : keys) rbTree.Inserer(k);
    timer.chronoEnd();
    cout << timer.display("Remplissage De L'Arbre RB : ");

    cout << "\n--------- Recherche RB (" << testKey << ") ---------";
    timer.chronoStart();
    rbTree.Search(rbTree.GetRacine(), testKey);
    timer.chronoEnd();
    cout << timer.display("Recherche Dans L'Arbre RB : ");

    cout << "\n--------- Suppression RB (" << delKey << ") ---------";
    timer.chronoStart();
    rbTree.Supprimer(rbTree.Search(rbTree.GetRacine(), delKey));
    timer.chronoEnd();
    cout << timer.display("Suppression Dans L'Arbre RB : ");
    cout<<"\n";
    // ==========================================================
    // TEST 2 : std::set<int>
    // ==========================================================
    printTitle("TEST 2 : std::set<int>");
    set<int> orderedSet;

    cout << "\n--------- Remplir set ! ---------";
    timer.chronoStart();
    for (int k : keys) orderedSet.insert(k);
    timer.chronoEnd();
    cout << timer.display("Remplissage Du set : ");

    cout << "\n--------- Recherche set (" << testKey << ") ---------";
    timer.chronoStart();
    orderedSet.find(testKey);
    timer.chronoEnd();
    cout << timer.display("Recherche Dans set : ");

    cout << "\n--------- Suppression set (" << delKey << ") ---------";
    timer.chronoStart();
    orderedSet.erase(delKey);
    timer.chronoEnd();
    cout << timer.display("Suppression Dans set : ");

    cout<<"\n";
    // ==========================================================
    // TEST 3 : std::unordered_set<int>
    // ==========================================================
    printTitle("TEST 3 : unordered_set<int>");
    unordered_set<int> hashSet;

    cout << "\n--------- Remplir unordered_set ! ---------";
    timer.chronoStart();
    for (int k : keys) hashSet.insert(k);
    timer.chronoEnd();
    cout << timer.display("Remplissage De unordered_set : ");

    cout << "\n--------- Recherche unordered_set (" << testKey << ") ---------";
    timer.chronoStart();
    hashSet.find(testKey);
    timer.chronoEnd();
    cout << timer.display("Recherche Dans unordered_set : ");

    cout << "\n--------- Suppression unordered_set (" << delKey << ") ---------";
    timer.chronoStart();
    hashSet.erase(delKey);
    timer.chronoEnd();
    cout << timer.display("Suppression Dans unordered_set : ");

    cout<<"\n";
    // ==========================================================
    // TEST 4 : std::map<int,string>
    // ==========================================================
    printTitle("TEST 4 : map<int,string>");
    map<int,string> treeMap;

    cout << "\n--------- Remplir map (key->word) ! ---------";
    timer.chronoStart();
    for (size_t i = 0; i < realCount; ++i)
        treeMap.emplace(keys[i], words[i]);
    timer.chronoEnd();
    cout << timer.display("Remplissage Du map : ");

    cout << "\n--------- Recherche map (" << testKey << ") ---------";
    timer.chronoStart();
    treeMap.find(testKey);
    timer.chronoEnd();
    cout << timer.display("Recherche Dans map : ");

    cout << "\n--------- Suppression map (" << delKey << ") ---------";
    timer.chronoStart();
    treeMap.erase(delKey);
    timer.chronoEnd();
    cout << timer.display("Suppression Dans map : ");

    cout<<"\n";
    // ==========================================================
    // TEST 5 : Arbre<string>
    // ==========================================================
    printTitle("TEST 5 : Arbre<int>");
    Arbre<int> intTree;

cout << "\n--------- Remplir Arbre<int> ! ---------";
timer.chronoStart();
for (size_t i = 0; i < realCount; ++i)
    intTree.inserer(keys[i], keys[i]);  // clé et valeur = int
timer.chronoEnd();
cout << timer.display("Remplissage De L'Arbre<int> : ");

cout << "\n--------- Recherche Arbre<int> (" << testKey << ") ---------";
timer.chronoStart();
Node<int>* foundNode = intTree.rechercher(testKey);
timer.chronoEnd();
cout << timer.display("Recherche Dans L'Arbre<int> : ");

cout << "\n--------- Suppression Arbre<int> (" << delKey << ") ---------";
timer.chronoStart();
intTree.enlever(delKey);
timer.chronoEnd();
cout << timer.display("Suppression Dans L'Arbre<int> : ");


    // ==========================================================
    // FIN
    // ==========================================================
    printTitle("FIN DU TEST");

    cout << "\nNombre d'éléments traités : " << realCount << endl;
    return 0;
}
