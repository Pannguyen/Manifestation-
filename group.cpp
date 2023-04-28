#include "group.hpp"

#include <stdexcept>
#include <iostream>
using namespace std;

Group::Group(string name, string color){
    this->name = name;
    this->color = color;
    this->size = 0;
    this->leader = nullptr;
    this->last = nullptr;
}



int Group::getSize() const{
    return this->size;
}

string Group::getName() const{
    return this->name;
}

string Group::getColor() const{
    return this->color;
}

Person& Group::getPerson(int id) const{
    auto it = this->groupMap.find(id);

    if (it != groupMap.end()){
        //Affichage pour aider
        return *(it->second->p);
    }

    throw invalid_argument("Non existent id");
}

Person& Group::getLeader() const{
    if(this->leader != nullptr){
        return *(this->leader->p);
    }

    throw invalid_argument("Empty group");
}
unordered_map<int, Node* > Group::getGroupMap() const{
    return this->groupMap;
}


void Group::insertPerson(Person *person){

    // Si la personne est déjà dans le groupe on ne le rajoute pas
    if (groupMap.find(person->getID()) != groupMap.end()){
        cout << "Person with id " << person->getID() << " is already in the group" << endl;
        return;
    }

    // Sinon on crée un nouveau maillon
    Node *newNode = new Node();
    newNode->p = person;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    // La personne est leader + dernier si la liste est vide
    if (leader == nullptr){
        leader = newNode;
        last = newNode;
    // Sinon, la personne est insérée à la fin de la liste
    }else{
        last->next = newNode;
        newNode->prev = last;
        last = newNode;
    }
    // Insertion de la personne dans la map
    groupMap.insert(std::make_pair(person->getID(), newNode));
    size++;   
}

void Group::removePerson(int id){

    auto it = groupMap.find(id);

    // Maillon trouvé dans la map
    if (it != groupMap.end()){

        Node *nodeToRemove = it->second;

        //Si on fait un retrait de la 1e personne donc le leader
        // removeLeader() s'occupe des destructions et maj de taille
        if (nodeToRemove->prev == nullptr){
            this->removeLeader();
            return;
        }

        //Retrait de la map en premier lieu
        //Pas de retrait avant car removeLeader() le fait déjà
        groupMap.erase(it);

        //On arrive ici dans le cas où la personne B à retirer
        //est au milieu, entre deux autres personnes A<->B<->C
        if (nodeToRemove->next != nullptr && nodeToRemove->prev != nullptr){

            nodeToRemove->prev->next = nodeToRemove->next;//A.suivant = C
            nodeToRemove->next->prev = nodeToRemove->prev;//C.precedent = A
        
        //Sinon on est dans le cas du retrait du dernier
        }else{
            last = last->prev;
            last->next = nullptr;
        }

        //Destruction des objets
        delete nodeToRemove->p;
        delete nodeToRemove;

        nodeToRemove = nullptr;

        size--;
    }else{
        cout << "Person with id " << id << " not found" << endl;
    }
}

void Group::removeLeader(){

    //0 personne dans le groupe
    if (groupMap.empty()){
        cout << " This group is empty " << endl;
        return;
    }

    groupMap.erase(groupMap.find(getLeader().getID()));

    leader = leader->next;

    //Dans le cas ou il y a + qu'une personne
    if (leader != nullptr){
        delete leader->prev->p;

        delete leader->prev;
        leader->prev = nullptr;
    }else{
        delete last->p;

        delete last;
        last = nullptr;
    }
    size--;
    cout << "Leader removed from the group" << endl;
}


Group::~Group() {
    
    Node* current = leader;

    //A la destruction d'un objet Group, on parcours en faisant des removeLeader()
    //removeLeader s'occupe de la suppression et du changement de leader ainsi
    //que la destruction de l'objet Person leader lui meme
    while(current != nullptr) {
        removeLeader();
        current = leader;
    }
}












// groupMap.insert(std::make_pair(person->getID(), newNode));