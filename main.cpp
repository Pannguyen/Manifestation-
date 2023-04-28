#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <time.h>
#include "demonstration.hpp"
#include "couleur.hpp"
#include <ctime>

using namespace std;

void displayGroupMembers(Group *g)
{

    if (g->getSize() == 0)
    {
        cout << endl
             << g->getName() << " : vide" << endl;
        return;
    }

    auto it = g->getGroupMap().find(g->getLeader().getID());
    Node *temp = it->second;

    cout << endl
         << g->getName() << " : ";

    while (temp != nullptr)
    {
        cout << temp->p->getName().substr(0, 1) << "-";
        temp = temp->next;
    }
}

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
    clock_t start, end;
    double cpu_time_used;

    // initialisation du générateur de nombres aléatoires
    srand(time(0));

    // lecture du fichier des prénoms
    set<std::string> ens_prenom;
    lecture_fichier_prenoms(ens_prenom);

    // lecture du fichier des corteges
    ifstream fcor;
    fcor.open("declaration.csv", ios::in);
    std::string line, nom, couleur, str, sujet;
    int taille;

    getline(fcor, sujet);

    /*Cortege créé*/
    Procession *pr = new Procession(sujet); // Mu zik !

    // Iteration sur les groupes dans declaration.csv
    while (fcor >> line)
    {
        istringstream is(line);
        getline(is, nom, ';');
        getline(is, couleur, ';');
        getline(is, str, ';');
        taille = stoi(str);

        /*Ajout du groupe actuel au cortege*/
        Group *g = new Group(nom, couleur); // it 1 : Group(electro, vert, 8)
        pr->addGroup(g);

        /*Insertion de personne dans le groupe actuel dans le groupe*/
        for (int i = 0; i < taille; i++)
        {
            Person *p = new Person(choisir_prenom(ens_prenom));
            g->insertPerson(p);
        }
    }
    fcor.close();
    Demonstration *d = new Demonstration(5, 7, pr);
    pr->sortColor();

    pr->sortSize();

    // Affichage des groupes dans le cortège
    start = clock();
    cout << "Les groupes est triés par ordre décroissant des tailles." << endl;
    cout << "Groupes dans le cortège : " << endl;
    for (auto group : pr->getGroups())
    {
        cout << "Nom : " << group->getName() << endl;
        cout << "Couleur : " << group->getColor() << endl;
        cout << "Taille : " << group->getSize() << endl;
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Temps pris par le tri de group par taille : " << cpu_time_used << " secondes." << endl;
    cout << endl
         << endl;

    for (Group *g : pr->getGroups())
    {
        displayGroupMembers(g);
    }

    cout << endl
         << endl;
    start = clock();
    while (!d->hasEnded())
    {
        d->simStage();
    }
    end = clock();
    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Durée de la simulation : " << duration << " secondes" << endl;

    cout << endl
         << "Fin";

    return 0;
}
