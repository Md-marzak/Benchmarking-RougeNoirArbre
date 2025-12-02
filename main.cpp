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

int main()
{
    const size_t COUNT = 1000000; // nombre d'éléments à tester

    srand(static_cast<unsigned>(time(nullptr)));
    Clock monClock;

    // -----------------------
    // Lire les mots depuis le fichier
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
    // Générer une clé aléatoire par mot
    // -----------------------
    vector<int> keys;
    keys.reserve(words.size());
    for (size_t i = 0; i < words.size(); ++i)
        keys.push_back(rand() % 1000001); // clés dans [0, 1_000_000]

    size_t realCount = words.size();
    int testKey = keys[realCount / 2];
    int delKey  = keys[realCount / 3];

    // -----------------------
    // TEST 1 : RougeNoirArbre<int>
    // -----------------------
    cout << "\n==============================================";
    cout << "\n TEST 1 : RougeNoirArbre<int>";
    cout << "\n==============================================";

    RougeNoirArbre<int> monArbreRB;

    cout << "\n--------- Remplir Arbre RB ! ---------";
    monClock.chronoStart();
    for (int k : keys) monArbreRB.Inserer(k);
    monClock.chronoEnd();
    cout << monClock.display("\nRemplissage De L'Arbre RB : ");

    cout << "\n--------- Recherche RB (" << testKey << ") ---------";
    monClock.chronoStart();
    monArbreRB.Search(monArbreRB.GetRacine(), testKey);
    monClock.chronoEnd();
    cout << monClock.display("\nRecherche Dans L'Arbre RB : ");

    cout << "\n--------- Suppression RB (" << delKey << ") ---------";
    monClock.chronoStart();
    monArbreRB.Supprimer(monArbreRB.Search(monArbreRB.GetRacine(), delKey));
    monClock.chronoEnd();
    cout << monClock.display("\nSuppression Dans L'Arbre RB : ");

    // -----------------------
    // TEST 2 : std::set<int>
    // -----------------------
    cout << "\n\n==============================================";
    cout << "\n TEST 2 : std::set<int>";
    cout << "\n==============================================";

    set<int> stl_set;

    cout << "\n--------- Remplir set ! ---------";
    monClock.chronoStart();
    for (int k : keys) stl_set.insert(k);
    monClock.chronoEnd();
    cout << monClock.display("\nRemplissage Du set : ");

    cout << "\n--------- Recherche set (" << testKey << ") ---------";
    monClock.chronoStart();
    stl_set.find(testKey);
    monClock.chronoEnd();
    cout << monClock.display("\nRecherche Dans set : ");

    cout << "\n--------- Suppression set (" << delKey << ") ---------";
    monClock.chronoStart();
    stl_set.erase(delKey);
    monClock.chronoEnd();
    cout << monClock.display("\nSuppression Dans set : ");

    // -----------------------
    // TEST 3 : std::unordered_set<int>
    // -----------------------
    cout << "\n\n==============================================";
    cout << "\n TEST 3 : std::unordered_set<int>";
    cout << "\n==============================================";

    unordered_set<int> u_set;

    cout << "\n--------- Remplir unordered_set ! ---------";
    monClock.chronoStart();
    for (int k : keys) u_set.insert(k);
    monClock.chronoEnd();
    cout << monClock.display("\nRemplissage De unordered_set : ");

    cout << "\n--------- Recherche unordered_set (" << testKey << ") ---------";
    monClock.chronoStart();
    u_set.find(testKey);
    monClock.chronoEnd();
    cout << monClock.display("\nRecherche Dans unordered_set : ");

    cout << "\n--------- Suppression unordered_set (" << delKey << ") ---------";
    monClock.chronoStart();
    u_set.erase(delKey);
    monClock.chronoEnd();
    cout << monClock.display("\nSuppression Dans unordered_set : ");

    // -----------------------
    // TEST 4 : std::map<int,string>
    // -----------------------
    cout << "\n\n==============================================";
    cout << "\n TEST 4 : std::map<int,string>";
    cout << "\n==============================================";

    map<int,string> mp;

    cout << "\n--------- Remplir map (key->word) ! ---------";
    monClock.chronoStart();
    for (size_t i = 0; i < realCount; ++i)
        mp.emplace(keys[i], words[i]);
    monClock.chronoEnd();
    cout << monClock.display("\nRemplissage Du map : ");

    cout << "\n--------- Recherche map (" << testKey << ") ---------";
    monClock.chronoStart();
    mp.find(testKey);
    monClock.chronoEnd();
    cout << monClock.display("\nRecherche Dans map : ");

    cout << "\n--------- Suppression map (" << delKey << ") ---------";
    monClock.chronoStart();
    mp.erase(delKey);
    monClock.chronoEnd();
    cout << monClock.display("\nSuppression Dans map : ");

    // -----------------------
    // TEST 5 : Arbre<string>
    // -----------------------
    cout << "\n\n==============================================";
    cout << "\n TEST 5 : Arbre<string> ";
    cout << "\n==============================================";

    Arbre<string> monArbreStr;

    cout << "\n--------- Remplir Arbre<string> ! ---------";
    monClock.chronoStart();
    for (size_t i = 0; i < realCount; ++i)
        monArbreStr.inserer(keys[i], words[i]);
    monClock.chronoEnd();
    cout << monClock.display("\nRemplissage De L'Arbre<string> : ");

    cout << "\n--------- Recherche Arbre<string> (" << testKey << ") ---------";
    monClock.chronoStart();
    Node<string>* nFound = monArbreStr.rechercher(testKey);
    monClock.chronoEnd();
    cout << monClock.display("\nRecherche Dans L'Arbre<string> : ");

    cout << "\n--------- Suppression Arbre<string> (" << delKey << ") ---------";
    monClock.chronoStart();
    monArbreStr.enlever(delKey);
    monClock.chronoEnd();
    cout << monClock.display("\nSuppression Dans L'Arbre<string> : ");

    cout << "\n\n===== FIN DU TEST (" << realCount << " éléments) =====\n";
    return 0;
}
