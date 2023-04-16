#include "person.hpp"

using namespace std;

Person::Person(const std::string &name, int id) : name(name), id(id), position(position) {}

Person::~Person() {}

std::string Person::getName() const
{
    return name;
}

int Person::getID() const
{
    return id;
}

std::pair<int, int> Person::getPosition() const
{
    return position;
}

void Person::setPosition(const std::pair<int, int> &newPosition)
{
    position = newPosition;
}
