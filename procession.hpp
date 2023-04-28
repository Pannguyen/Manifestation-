#include "group.hpp"

#ifndef PROCESSION_HPP
#define PROCESSION_HPP

#include <list>

/*
Procession = Cortège, son nom est le sujet de la manifestation
Un cortège regroupe des groupes autour d'un unique sujet
*/

class Procession {
    private:
        std::string name;
        std::list<Group*> groups;

        //Indique le nombre de personnes 
        //au total dans le cortège
        int size;

    public:
        Procession(const std::string & name);
        ~Procession();

        int getSize() const;
        std::string getName() const;
        Person& getPerson(int id) const;
        std::list<Group*> getGroups() const;
        Group getGroup(std::string name) const;

        void addGroup(Group *group);
        void removeGroup(const std::string &name);
        void removePerson(int id);

        void sortColor();
        void sortSize();

        class ProcessIterator {
            private:
                std::list<Group*>::iterator group_it;

            public:
                ProcessIterator(std::list<Group*>::iterator it) : group_it(it) {}

                
                //Opérateur de comparaison pour tester l'égalité de deux itérateurs
                bool operator==(const ProcessIterator& other) const {
                    return group_it == other.group_it;
                }

                bool operator!=(const ProcessIterator& other) const {
                    return group_it != other.group_it;
                }

                bool operator<(const ProcessIterator& other) const {
                    return (*(*group_it)).getSize() < (*(*other.group_it)).getSize();
                }

                ProcessIterator operator++() {
                    ++group_it;
                    return *this;
                }

                Group& operator*() const {
                    return *(*group_it);
                }
        };
        // Méthode begin() pour obtenir un itérateur pointant sur le premier groupe du cortège
        ProcessIterator begin() {
            return ProcessIterator(groups.begin());
        }
        // Méthode end() pour obtenir un itérateur pointant après le dernier groupe du cortège
        ProcessIterator end() {
            return ProcessIterator(groups.end());
        }
}; 
#endif
