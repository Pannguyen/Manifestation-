#include "person.hpp"
#include <iostream>

using namespace std;

/*
    Person = Personne
*/

/* nextID permet d'affecter au préalable un identifiant unique a chaque personne
** et a chaque construction d'un objet Person il est incrémenté
*/
int Person::nextID = 0;
Person::Person(const string& name) : name(name), id(nextID), position(make_pair(-1, -1)) {nextID++;}

Person::~Person() {}

string Person::getName() const{
    return name;
}

int Person::getID() const{
    return id;
}

pair<int, int> Person::getPosition() const{
    return position;
}

void Person::setPosition(const pair<int, int> & newPosition){
    position = newPosition;
}



//Person::Person(const string& name) : name(name), id(nextID), position(make_pair(-1, -1)) {nextID++;}
