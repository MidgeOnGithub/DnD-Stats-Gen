/* Vocabulary:
 * PC = Player Character
*/
#ifndef DND_CHARACTER_HPP
#define DND_CHARACTER_HPP

#include <string>

#include "abilities.hpp"

class Character
{

public:

    Character();
    Character(std::string name);
    
    Abilities ab;
    // Other unimplemented aspects of a PC
    //class cls
    //inventory inv
    //race r

    std::string get_name();
    void set_name(std::string new_name);

    ~Character();

private:

    std::string name;

};

#endif //DND_CHARACTER_HPP
