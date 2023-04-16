#ifndef DEMONSTRATION_HPP
#define DEMONSTRATION_HPP
#include <vector>
#include "procession.hpp"
#include <string>

////////////////////////////////////////////////////
/// since we need to simulate a step where people move forward on the grid,
/// a vector may be a better choice since we need to access elements by their position on the grid.
////////////////////////////////////////////////////

class Demonstration {
    private:
        int width;
        int length;
        std::vector<Procession *> processions;
        std::string subject;
        //Procession procession;
        int currentStep;
        //std::vector<Person *> leaders;

    public:
        Demonstration(std::string sub, int wid, int len);
        ~Demonstration();

        /// @brief  simulation of a stage ///
        void simStage();

        /// @brief test if Demo is finished //
        /// @return false when not finished yet.
        bool hasEnded() const;

        /// @brief access to a Person using its identifier
        /// @param id
        /// @return the person
        Person *getPerson(int id);

        /// @brief deletion of a Person using its identifier
        /// @param id
        void removePerson(int id);

        /// @brief access to all the leaders in the process of scrolling.
        /// @return  an array of leaders
        std::vector<Person *> getLeaders() const;

        
      
};

#endif
