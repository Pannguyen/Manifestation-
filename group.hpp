#include <string>
#include <unordered_map>
#include <list>
#ifndef GROUP_HPP
#define GROUP_HPP

#include "person.hpp"

/////////////////////////////////////////////////////////////////////////////////
// We are interested in the access to a person from the identifier in the group//
// The time complexity must be a Θ(1). So I use Hashtable here                 //
//because Group is a collection of people ordered from oldest (first) to newest (last)
// So I decided 

class Group {
    private:
     
     struct Node {
        Person p;
        Node* next;
        Node* prev; 
        Node() : p(p.getName(), p.getID()), next(nullptr), prev(nullptr) {}
    };
        std::string name;
        std::string color;
        Node* leader;
        Node* last;
      
        //std::list<Person> peopleQ;
        std::unordered_map<int, Node* > groupMap;

    public:
        Group(std::string name, std::string color);
        ~Group();

        int getSize() const;
        std::string getName() const;
        std::string getColor() const;
        Person getPerson(int id) const;
        Person getLeader() const;

        void insertPerson(Person* person);
        void removePerson(int id);
        void removeLeader();


        class Iterator {
            private:
                Person* current;

            public:
                Iterator(Person* person);
                Person* operator*() const;
                Iterator& operator++();
                bool operator==(const Iterator& other) const;
                bool operator!=(const Iterator& other) const;
        };

        Iterator begin() const;
        Iterator end() const; 
}; 


#endif