#include "procession.hpp"

#include <iostream>
using namespace std;


/*
    Procession <=> Cortège
*/

/* 
** @param name le sujet qui rassemble les groupes
** @return un nouvel objet Procession c.f
*/
Procession::Procession(const string &name){
    this->name = name;
    this->size = 0;
}


//******************************************************************************************


/* La taille du cortège correspond au nombre total de personnes
** Le calcul est refait car on peut avoir l'addition de groupe vide
** Donc l'attribut size reste a 0 alors qu'il y a des personnes dedans
** @return taille du cortège
*/
int Procession::getSize() const {
    int numPeople = 0;
    for(Group *g : getGroups()) {
        numPeople += g->getSize();
    }

    return numPeople;
}

/* Retourner le sujet qui rassemble les groupes
** @return le nom du cortège
*/
string Procession::getName() const{
    return this->name;
}

/* Rechercher la personne dans tous les groupes du cortège;
** L'exception est levée pour chaque groupe dans lequel la personne
** n'est pas présente. On vérifie alors qu'on a parcouru tous les
** groupes du cortège avant de lancer une exception 'finale'
** @param id identifiant d'une Personne
** @return reference à la Personne recherchée
*/
Person& Procession::getPerson(int id) const{

    //Sert de compteur pour savoir si tout les groupe du cortege on été
    //parcouru dans la liste groups
    uint64_t count = 0;

    //Parcours des groupes du cortège
    for(Group *g : groups) {
        count++;

        try{
            return g->getPerson(id);//recherche de la personne dans le groupe actuel

        //L'exception est levée quand on ne trouve 
        //pas la personne dans le groupe actuel
        }catch(invalid_argument e) {

            //Si on a parcouru tout les groupes du cortège
            if(count >= groups.size()) {
                break;
            }
        }
    }

    //Ligne atteinte seulement si la personne n'est pas trouvée dans tous les groupes
    throw invalid_argument("Personne non présente dans le cortège");
}

/* Accèder à tout les groupes du cortège
** @return liste chainée de pointeurs vers Groups
*/
Group Procession::getGroup(string name) const {

    if(groups.size() == 0){
        throw logic_error("Cortège vide");
    }

    for(Group *g : groups) {
        if(g->getName() == name) {
            return *g;
        }
    }

    //On atteint cette ligne uniquement quand le groupe n'est pas trouvé
    throw invalid_argument("Groupe non présent dans le cortège");
}





//******************************************************************************************


/* Ajouter un groupe au cortège
** @param group pointeur vers un objet groupe
*/
void Procession::addGroup(Group *group){
    groups.push_back(group);
    size += group->getSize();
}


/* Retirer et détruire un groupe du cortège
** @param name nom du groupe à retirer
*/
void Procession::removeGroup(const string &name) {

    if(groups.size() == 0){
        throw logic_error("Cortège vide");
    }

    //Recherche du groupe dans le cortege par nom
    for (auto it = groups.begin(); it != groups.end(); ++it) {

        if ((*it)->getName() == name) {

            //Destruction puis retrait du groupe
            delete *it;
            groups.erase(it);
            size -= (*it)->getSize();
            return;
        }
    }

    //Ligne atteinte dans le cas ou le nom du groupe a retirer
    //ne correspond pas à un groupe présent dans le cortège
    throw logic_error("Groupe non présent dans le cortège");
}

/* Retirer et détruire une personne du cortège
** @param id l'identifiant de la personne
*/
void Procession::removePerson(int id){

    for(Group* g : groups) {
        Person p = g->getPerson(id);

        if(p.getID() != -1){
            g->removePerson(id);
            cout<<"Person removed"<<endl;
            size--;
            return;
        }
    }
}


//******************************************************************************************




/* Tri rapide implémenté pour la SDC du cortège utilisée
** @param begin iterateur vers le début
** @param end itérateur vers la fin
*/

void Procession::sortColor() {

    try {
        //Cas de cortège vide
        if (groups.empty()) {
            throw runtime_error("Le Cortège est vide");
        }

        //Lambda expression : la fonction prend deux pointeurs de groupes 
        //(gA et gB), récupère leurs couleurs respectives, et les compare.
        groups.sort([](const Group* gA, const Group* gB) {
            string colA = gA->getColor();
            string colB = gB->getColor();
          
            //Renvoyer true si la couleur de gA précède alphabétiquement la couleur de gB
            return colA < colB;
        });

    }catch(const runtime_error e) {
        cout<<"erreur sortColor - "<<e.what()<<endl;
    }
}

///////////////////////////////////////Mis en commentaire pour compilation
void Procession::sortSize(){
    for (auto it1 = groups.begin(); it1 != groups.end(); it1++)
    {
        for (auto it2 = it1; it2 != groups.begin(); it2--)
        {
            if ((*it2)->getSize() > (*(prev(it2)))->getSize())
            {
                std::swap(*it2, *(std::prev(it2)));
            }
        }
    }
}
Procession::~Procession()
{
    for (auto it = groups.begin(); it != groups.end(); ++it)
    {
        delete *it;
    }
}
