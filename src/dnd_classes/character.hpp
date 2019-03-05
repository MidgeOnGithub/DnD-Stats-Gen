/* Vocabulary:
 * PC = Player Character
*/
#ifndef DND_CHARACTER_HPP
#define DND_CHARACTER_HPP

#include <string>

#include "abilities.hpp"
#include "races.hpp"

struct CharacterBuilder;

// TODO: Consider adding basic appearance (weight, height, etc.)
// TODO: Add Level/Experience struct(s)/class(es)
class Character {
  friend struct CharacterBuilder;
public:
  virtual ~Character();

  static CharacterBuilder create();

  Abilities ab;
  // Other unimplemented aspects of a PC
  //class cls
  //inventory inv (not going to be implemented by me any time soon)
  //race r

  std::string get_name();

private:
  Character();

  std::string name = "PC";
};


struct CharacterBuilder {
  CharacterBuilder();
  explicit CharacterBuilder(std::string name);

  virtual ~CharacterBuilder();

  CharacterBuilder& give_generated_scores(std::array<int, 6>& scores);
  CharacterBuilder& give_name(std::string name);

  operator Character() const;

  Character pc;
};

#endif //DND_CHARACTER_HPP
