
#include <unistd.h> // for usleep
#include "demonstration.hpp"

// pair<int, int> initialPosition = make_pair(p->getPosition().first, p->getID() % width);
//  pair<int,int> updatedPosition = std::make_pair(p.getPosition().first+1, p.getPosition().second);
//p.setPosition(make_pair(p.getPosition().first, temp));


#ifdef __linux__
#include <unistd.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
using namespace std;
/*
    Demonstration = Manif
*/
//Fonction sleep pour windows et linux
//@author shf301 on stackoverflow (modifiée pour ce programme)
void mySleep(int sleepMs)
{
#ifdef __linux__
    usleep(sleepMS * 1000);   // usleep(microsec)
#endif
#ifdef _WIN32
    Sleep(sleepMs);
#endif
}
/* On suppose que le cortège est déjà construit
** @param wid largeur de la grille
** @param len longueur de la grille
** @param proc cortège à faire defiler
** @return un nouvel objet Demonstration
*/
Demonstration::Demonstration(int wid, int len, Procession *proc) : width(wid), length(len), procession(proc) {
    //Initialiser la grille avec des pointeurs nuls
    grid = vector<vector<Person*> >(len, vector<Person*>(wid, nullptr));
    //Affectation du nombre de personnes au total
    numPeople = procession->getSize();
    //Correspond au nombre de simStage à effectuer pour atteindre la dernière
    //rangée contenant des personnes dans la grille
    stageCountMax = (numPeople/width) + 1;
    //Parcours de toutes les personnes a l'aide des ID (croissant 0, 1, 2...)
    for(int i = 0; i < numPeople; i++) {
        Person *p = &procession->getPerson(i);
        //Calcul et affectation de la position sur y grace à l'ID et la largeur de la grille
        //Le modulo sert alors a initialiser la meme position a deux personnes qui sont présentes
        //sur la meme colonne de la grille
       pair<int, int> initialPosition = make_pair(p->getPosition().first, p->getID() % width);   
        p->setPosition(initialPosition); 
    }
}
//***************************************************************************************************************
bool Demonstration::hasEnded() const {
    return lastRowFlag;
}
Person Demonstration::getPerson(int id) {
    return procession->getPerson(id);
}
void Demonstration::removePerson(int id) {
    
    Person p = procession->getPerson(id);

    excludedPeople.push_back({id, p.getPosition().first, p.getPosition().second});

    procession->removePerson(id);
    exclude = true;
}

vector<Person*> Demonstration::getLeaders() const {
    vector<Person*> leaders;
    // On parcourt chaque groupe
    for (Group* g : procession->getGroups()) {
        // On ajoute le leader de chaque groupe à la liste des leaders si le groupe n'est pas vide
        try{
            leaders.push_back(&g->getLeader());
        //Si le groupe est vide on continue vers le suivant
        }catch(invalid_argument e){
            continue;
        }
    }
    return leaders;
}
//***************************************************************************************************************
/* Incrementer l' de la personne portant cet id
** @param id l'identifiant de la personne a faire avancer
*/
void Demonstration::updatePosition(int id) {
    //Une reference vers notre personne 
    Person &p = procession->getPerson(id);
    //Actualisation du la position de la personne actuelle
     pair<int,int> updatedPosition = std::make_pair(p.getPosition().first+1, p.getPosition().second);
    p.setPosition(updatedPosition);
}
void Demonstration::shiftPositions(int id) {
    for(int i = id + 1; i < numPeople; i++) {
        
        Person &p = procession->getPerson(i);
        
        int temp = ((p.getPosition().second - 1)%width + width)%width;
        if(temp == width - 1) {
            //cout<<p.getPosition().first + 1<<temp<<" ";
            p.setPosition(make_pair(p.getPosition().first, temp));

        }else{
            //cout<<p.getPosition().first + 1<<temp<<" ";
            p.setPosition({p.getPosition().first, temp});
        }
    }
}
/* Simuler une seule étape de la manifestation, donc un pas en avant
*/
void Demonstration::simStage() {
    //a mimir
    mySleep(500);
    sig = false;
    //Parcours des personnes concernées par le changement de position
    //Au début uniquement la première rangée (en bas)
    //Ensuite c'est la première et la deuxième etc...
    for(int i = 0; i < width*stageCount; i++) {
        //Dans ce cas on a dépassé les cases 
        //ou il devrait y avoir de personnes
        if(i >= numPeople) {
            sig = true;
            break;
        }
        //La personne avance d'un pas
        try{
            updatePosition(i);
        }catch(invalid_argument e){
            if(exclude){
                shiftPositions(i);
            }
            continue;
        }
        Person *p = &procession->getPerson(i);
        int x = p->getPosition().first;
        int y = p->getPosition().second;
        //Condition pour ne pas remplir la grille hors de ses limites par le haut
        //Les positions des personnes changent meme apres avoir quitté la grille
        if(x < (int)grid.size()) {
            grid[x][y] = p;
        }
    }
    if(sig) {
        //Dans le cas ou il n'y a que la rangée la 
        //plus en haut ou il y a des personnes présentes
        if(stageCount - stageCountMax >= (int)grid.size()) {
            //On remplace alors toute la rangée par des pointeurs nuls
            for(int i = 0; i < width; i++) {
                grid[length-1][i] = nullptr;
                lastRowFlag = true;
            }
            displayGrid();
            return;
        }
        //Boucler uniquement pour la rangée 
        //contenant les dernières personnes du cortège
        for(int i = (numPeople)%width - excludedPeople.size(); i < width; i++) {
            grid[stageCount - stageCountMax][i] = nullptr;
        }
        //Boucler pour le reste des rangées (donc à vider)
        for(int i = 0; i < width; i++) {
            
            for(int j = stageCount - stageCountMax - 1; j >= 0; j--) {
                grid[j][i] = nullptr;
            }
        }
    }
    exclude = false;
    //Appel à l'affichage de grid
    //grid étant mise à jour à cet instant
    displayGrid();
    stageCount++;
}
/* Afficher la grille sur laquelle se déplacent les personnes de la manifestation
*/
void Demonstration::displayGrid() {
    //Pour chaque rangée (ligne)
    for(int i = length-1; i >= 0; i--) {
        //Numero de ligne à afficher
        cout<<i+1<<" ";
        //pour chaque colonne de la grille
        for(int j = 0; j < width; j++) {
            //Permet de définir si une personne est 
            //présente a cette position de la grille
            Person *p = grid[i][j];
            //S'il n'y a personne à cette case
            if(p == nullptr) {
                cout<<"_ ";
            }else{
                string color;
                int id = p->getID();
                //Parcours des groupes pour retrouver la couleur (a ameliorer parcours inutile)
                for(Group *g : procession->getGroups()) {
                    try{
                        g->getPerson(id);
                        //Au succès l'exception n'est pas levée et on casse la boucle
                        //On retrouve donc la couleur a utiliser pour l'affichage
                        color = g->getColor();
                        break;
                    //Exception levée si la personne n'est pas dans le groupe actuel
                    //On continue le parcours vu que la personne est forcément présente
                    }catch(invalid_argument e) {
                        continue;
                    }
                }
                //Couleur trouvée et créée
                Couleur col = Couleur::creer(color);
                //Affichage de l'initial de la personne sur la grille
                col.afficher(cout, p->getName().substr(0,1));
                cout<<" ";
            }
        }
        cout<<endl;
    }
    //Affichage de la dernière partie de la grille
    //contenant les numéros de colonnes
    cout<<"  ";
    for(int j = 0; j < width; j++) {
        cout<<j+1<<" ";
    }
    cout<<endl;
}
//***************************************************************************************************************
Demonstration::~Demonstration() {
    delete procession;
}