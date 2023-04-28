#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <utility>

class Person {
    private:
        std::string name;
        int id;
        static int nextID;
        std::pair<int, int> position;

    public:
        Person(const std::string & name);
        ~Person();

        std::string getName() const;
        int getID() const;
        std::pair<int, int> getPosition() const;
        void setPosition(const std::pair<int, int> & newPosition);
};

#endif
