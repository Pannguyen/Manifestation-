#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <time.h>
#include "demonstration.hpp"
#include <memory>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// choix aléatoire d'un élément dans l'ensemble passé en paramètre
std::string choisir_prenom(const set<std::string> &s)
{
    int n = s.size(),
        k = rand() % n;

    auto it = s.begin();
    std::advance(it, k);
    return *it;
}

////////////////////////////////////////////////////////////////////////////////
// lecture du fichier des prénoms
void lecture_fichier_prenoms(set<std::string> &ens)
{
    ifstream fin;
    fin.open("nat2021.csv", ios::in);
    string line, mot;

    while (fin >> line)
    {
        istringstream is(line);
        getline(is, mot, ';');
        getline(is, mot, ';');
        ens.insert(mot);
    }
    fin.close();
}

////////////////////////////////////////////////////////////////////////////////
int main()
{

    // initialisation du générateur de nombres aléatoires
    srand(time(0));

    // lecture du fichier des prénoms
    set<string> ens_prenom;
    lecture_fichier_prenoms(ens_prenom);

    // lecture du fichier des corteges
    ifstream fcor;
    fcor.open("declaration.csv", ios::in);
    string line, nom, couleur, str, sujet;
    int taille;

    getline(fcor, sujet);

    // création d'un cortège
    Procession p = Procession(sujet);

    while (fcor >> line)
    {
        istringstream is(line);
        getline(is, nom, ';');
        getline(is, couleur, ';');
        getline(is, str, ';');
        taille = stoi(str);

        //cout << nom << ';' << couleur << ';' << taille << endl;
        Group *g = new Group(nom, couleur, taille);
        p.addGroup(g);
        string prenom = choisir_prenom(ens_prenom);   // appel de la fonction choisir_prenom
       // cout << "Prenom choisi : " << prenom << endl; // affichage du prénom choisi
       int i = 0;
        while (i < taille)
        {
            Person *pers = new Person(choisir_prenom(ens_prenom));
            std::pair<int, int> position = std::make_pair(0, 0);
            pers->setPosition(position);
            
            g->insertPerson(pers);
            //int id = pers->getID(); // récupérer l'ID de la personne créée

            g->insertPerson(pers);
            i++; 
         
        }
    }
    fcor.close();

    // Affichage des groupes dans le cortège
     cout << "Groupes dans le cortège : " << endl;
    for (auto group : p.getGroups())
    {
        cout << "Nom : " << group->getName() << endl;
        cout << "Couleur : " << group->getColor() << endl;
        cout << "Taille : " << group->getSize() << endl;
    } 
// Simulation de la manifestation
cout << "Début de la manifestation" << endl;
auto groupIterator = p.getGroups().begin();
auto personIterator = (*groupIterator)->getGroupMap().begin();
while (groupIterator != p.getGroups().end()){
      // Affichage du nom du groupe qui défile
    cout << "Le groupe " << (*groupIterator)->getName() << " défile :" << endl;
    while (personIterator != (*groupIterator)->getGroupMap().end()){
        Person &p = *(personIterator->second->p);
        cout << "- Nom : " << personIterator->second->p->getName() << endl;
        cout << "  - ID : " << personIterator->second->p->getID() << endl; 
        cout << "  - Position : (" << personIterator->second->p->getPosition().first << ", " << personIterator->second->p->getPosition().second << ")" << endl;

        // Déplacement de la personne suivante
        ++personIterator;

        // Si on a parcouru toutes les personnes du groupe actuel, on passe au groupe suivant
        if (personIterator == (*groupIterator)->getGroupMap().end()){
            ++groupIterator;

            // Si on a parcouru tous les groupes, on a fini la manifestation
           //??? 

            // Sinon, on passe à la première personne du nouveau groupe
            personIterator = (*groupIterator)->getGroupMap().begin();
        }
    }
       cout << endl;
}
/* // Parcours de chaque groupe dans la procession
for (auto group : p.getGroups())
{
    // Affichage du nom du groupe qui défile
    cout << "Le groupe " << group->getName() << " défile :" << endl;

    // Parcours de chaque personne dans le groupe
    for (auto it = group->getGroupMap().begin(); it != group->getGroupMap().end(); ++it)
    {
        Person &p = *(it->second->p);
        cout << "- Nom : " << it->second->p->getName() << endl;
        cout << "  - ID : " << it->second->p->getID() << endl; 
       // cout << "  - Position : " << std::to_string(it->second->p->getPosition()) << endl;


        
    }

    // Affichage d'un message de séparation entre chaque groupe
    cout << endl;
}

// Affichage de la fin de la manifestation
cout << "Fin de la manifestation" << endl;
 */


    // Libération de la mémoire allouée pour les objets Person et Group
     for (auto group : p.getGroups())
{
    for (auto it = group->getGroupMap().begin(); it != group->getGroupMap().end(); ++it)
    {
        delete it->second->p; // libération de la mémoire allouée pour chaque Person
        delete it->second;    // libération de la mémoire allouée pour chaque objet GroupPerson
    }
    group->getGroupMap().clear(); // suppression des pointeurs de GroupPerson de la map
    delete group; // libération de la mémoire allouée pour chaque objet Group
}
p.getGroups().clear(); // suppression des pointeurs de Group de la procession

 
    cout << "Fin" << endl;

    return 0;
}
