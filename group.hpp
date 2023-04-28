#include "person.hpp"

#ifndef GROUP_HPP
#define GROUP_HPP

#include <string>
#include <unordered_map>



/*
Group = Groupe s'agit de plusieurs personnes rangées dans leur ordre d’arrivée, le plus ancien est le leader.
Les opérations de Group sont de complexité constante Θ(1)
*/


/* Node est un maillon composé de trois pointeurs, le premier vers une Person
** Les autres pointeurs, vers le suivant et le précedent de cette Person 
*/
struct Node {
    Person *p;
    Node* next;
    Node* prev; 
    Node() : p(), next(nullptr), prev(nullptr) {}
};

class Group {
    private:
        
        std::string name;
        std::string color;
        int size;
        Node* leader;
        Node* last;

        std::unordered_map<int, Node* > groupMap;

    public:
        Group(std::string name, std::string color);
        ~Group();

        int getSize() const;
        std::string getName() const;
        std::string getColor() const;
        std::unordered_map<int, Node* > getGroupMap() const;
        Person& getPerson(int id) const;
        Person& getLeader() const;

        void insertPerson(Person* person);
        void removePerson(int id);
        void removeLeader();

        //Voir si ajouter d'autres operateurs
        class GroupIterator {
            private:
                Node* current;

            public:
                GroupIterator(Node *node) : current(node) {}

                Node& operator*() const {
                    return *current;
                }

                GroupIterator& operator++() {
                    current++;
                    return *this;
                }

                bool operator==(const GroupIterator& other) const {
                    return this->current == other.current;
                }
                bool operator!=(const GroupIterator& other) const {
                    return this->current != other.current;
                }
        };

        GroupIterator begin() const {
            return GroupIterator(leader);
        }
        GroupIterator end() const {
            return GroupIterator(last);
        }
}; 


#endif
