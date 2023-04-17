/*Procession <=> Cortege*/

#ifndef PROCESSION_HPP
#define PROCESSION_HPP

#include <vector>
#include <list>
#include "group.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// because We are also interested in the identification and extraction of a person knowing the identifier//
/// in case of emergency,                                                                                 //
/// This is the operations involve inserting or deleting elements in the middle of the structure.         //
/// So I dicided using LINKED LIST as std::list                                                                         //
////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Procession
{
private:
    std::string name;
    std::list<Group *> groups;

public:
    Procession(const std::string &name);
    ~Procession();

        std::string getName() const;
        std::list<Group*> getGroups() const;


    /// @brief insertion of a Group into Procession
    /// @param group
    void addGroup(Group *group);

    //// @brief deletion of a Group ////
    //// @param name of the Group ////
    void removeGroup(const std::string &name);

    /// @brief acces a person in Procession ////
    /// @param id identifier of the Person ///
    /// @return return person
    Person getPerson(int id) const;

    /// @brief deletion person in Procession ////
    /// @param id identifier of the Person
    void removePerson(int id);




    /// @brief sorting by color of the groups ///
    void sortColor();
   void quickSortColor(std::list<Group*>::iterator begin, std::list<Group*>::iterator end);
  
    /// @brief sorting by Size of the groups ///
    void sortSize();

    // Iterators: a nested class that represents an iterator for the Procession class
    class iterator
    {
    private:
        std::list<Group *>::iterator group_it;

    public:
        iterator(std::list<Group *>::iterator it) : group_it(it) {}

        // Opérateur de comparaison pour tester l'égalité de deux itérateurs
        bool operator==(const iterator &other) const
        {
            return group_it == other.group_it;
        }

        bool operator!=(const iterator &other) const
        {
            return group_it != other.group_it;
        }

        iterator operator++()
        {
            ++group_it;
            return *this;
        }

        Group &operator*() const
        {
            return *(*group_it);
        }
    };
    // Méthode begin() pour obtenir un itérateur pointant sur le premier groupe du cortège
    iterator begin()
    {
        return iterator(groups.begin());
    }
    // Méthode end() pour obtenir un itérateur pointant après le dernier groupe du cortège
    iterator end()
    {
        return iterator(groups.end());
    }
};
#endif
