#include "group.hpp"

#include <iostream>
using namespace std;

Group::Group(string name, string color, int size){
    this->name = name;
    this->color = color;
    this->size = size;
    this->leader = nullptr;
    this->last = nullptr;
}


int Group::getSize() const
{
  return groupMap.size();
}


string Group::getName() const{
  return this->name;
}

string Group::getColor() const{
  return this->color;
}

Person Group::getPerson(int id) const{
  auto it = this->groupMap.find(id);
  if (it != groupMap.end())
  {
    cout << "Found person " << it->second->p.getName() << endl;
    return it->second->p;
  }
  else{
    return Person("INEXISTANT", -1);
  }
  
}

Person Group::getLeader() const {
  if (leader != nullptr) {
    cout << "Leader of group is " << leader->p.getName() << endl;
    return leader->p;
  } else {
    throw runtime_error("Group is empty");
  }
}
 

void Group::insertPerson(Person *person){
  
  // Check if the person is already in the group
  if (groupMap.find(person->getID()) != groupMap.end())
  {
    std::cout << "Person with id " << person->getID() << " already in the group" << std::endl;
    return;
  }
  // Create a new node for the person
  Node *newNode = new Node;
  newNode->p = *person;
  newNode->next = nullptr;
  newNode->prev = nullptr;
    // If the linked list is empty, set the new node as both the leader and the last node
    if (leader == nullptr)
    {
      leader = newNode;
      last = newNode;
    }
    // insert new node to the end of linked list
    else
    {
      last->next = newNode;
      newNode->prev = last;
      last = newNode;
    }
  // then, add this person in map
groupMap.insert(std::make_pair(person->getID(), newNode));


  size++; 
}

void Group::removePerson(int id){
  auto it = groupMap.find(id);
  /* if id is found in map, remove it*/
  if (it != groupMap.end())
  {
    Node *nodeToRemove = it->second;
    if (nodeToRemove == leader)
    {
      leader = leader->next;
      leader->prev = nullptr;
    }
    if (nodeToRemove == last)
    {
      last = last->prev;
      last->next = nullptr;
    }
    if (nodeToRemove->prev != nullptr)
    {
      nodeToRemove->prev->next = nodeToRemove->next;
    }
    if (nodeToRemove->next != nullptr)
    {
      nodeToRemove->next->prev = nodeToRemove->prev;
    }
    delete nodeToRemove;
    groupMap.erase(it);
    size--; 
  }
  else
  {
    cout << "Person with id " << id << " not found" << endl;
  }
}

void Group::removeLeader() {
  if (leader != nullptr) {
    Node *oldLeader = leader;
    leader = leader->next;
    if (leader != nullptr) {
      leader->prev = nullptr;
    } else {
      last = nullptr;
    }
    delete oldLeader;
    std::cout << "Leader removed from the group" << std::endl;
  } else {
    throw std::runtime_error("Group is empty");
  }
}


//FIX
Group::GroupIterator Group::begin() const {
    return GroupIterator(leader);
}

Group::GroupIterator Group::end() const {
    return GroupIterator(nullptr);
}


Group::~Group() {
  Node* current = leader;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    groupMap.clear();
}

