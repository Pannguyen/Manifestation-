#include "procession.hpp"

#include <iostream>
using namespace std;

Procession::Procession(const std::string &name){
    this->name = name; 
}
string Procession::getName() const{
    return this->name;
}




void Procession::addGroup(Group *group){
    
    if (groups.empty() ) {
        groups.push_front(group); 
    }
    else {
        auto it = groups.begin();
        while (it != groups.end() && (*it)->getColor() <= group->getColor()) {
            ++it;
        }
    }
}


void Procession::removeGroup(const std::string &name) {
    for (auto it = groups.begin(); it != groups.end(); ++it) {
        if ((*it)->getName() == name) {
            delete *it; // free memory of the group being removed
            groups.erase(it);
        }
    }
}

Person Procession::getPerson(int id) {
    for (Group *group : groups) {
        Person person = group->getPerson(id);
        if (person.getID() == id) {
            return person;
        }
    }
    return ;
}

void Procession::removePerson(int id){
     for (Group *group : groups) {
        Person person = group->getPerson(id);
        if (person.getID() == id) {
            group->removePerson(id);
            return;
        }
    }
}




void Procession::sortColor() {
    quickSortColor(groups.begin(), groups.end());
}

void Procession::quickSortColor(std::list<Group*>::iterator begin, std::list<Group*>::iterator end) {
    if (std::distance(begin, end) < 2) {  // base case: list is already sorted
        return;
    }
    // choose pivot element
    std::list<Group*>::iterator pivot = std::next(begin, std::distance(begin, end) / 2);
    // partition the list around the pivot
    std::list<Group*>::iterator middle = std::partition(begin, end, [pivot](const Group* group) { return group->getColor() < (*pivot)->getColor(); });
    // recursively sort the two partitions
    quickSortColor(begin, middle);
    quickSortColor(middle, end);
}


void Procession::sortSize() {
    for (auto it1 = groups.begin(); it1 != groups.end(); ++it1) {
        for (auto it2 = it1; it2 != groups.begin(); --it2) {
            if ((*it2)->getSize() > (*(std::prev(it2)))->getSize()) {
                std::iter_swap(it2, std::prev(it2));
            }
        }
    }
}

Procession::~Procession() {
        for (auto it = groups.begin(); it != groups.end(); ++it) {
            delete *it;
        }
    }
   