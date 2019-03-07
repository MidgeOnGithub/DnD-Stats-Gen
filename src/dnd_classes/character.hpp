/* Vocabulary:
 * PC = Player Character
*/
#ifndef DND_CHARACTER_HPP
#define DND_CHARACTER_HPP

#include <array>
#include <string>

#include "abilities.hpp"
#include "races.hpp"

struct CharacterBuilder;
struct CharacterLeveler;

// TODO: Consider adding basic appearance (weight, height, etc.)
// TODO: Add Level/Experience struct(s)/class(es)
class Character {
  friend struct CharacterBuilder;
  friend struct CharacterLeveler;
public:
  virtual ~Character();

  static CharacterBuilder create();
  CharacterLeveler advance();

  Abilities ab;
  // Other unimplemented aspects of a PC
  //class cls
  //inventory inv (not going to be implemented by me any time soon)
  //race r

  std::string get_name() const;
  unsigned int get_level() const;
  unsigned int get_experience() const;

private:
  Character();

  std::string name = "PC";
  unsigned int level = 1;
  unsigned int experience = 0;

};


struct CharacterBuilder {
  CharacterBuilder();
  explicit CharacterBuilder(std::string name);
  virtual ~CharacterBuilder();

  operator Character() const;

  CharacterBuilder& give_name(std::string name);
  CharacterBuilder& give_generated_scores(std::array<int, 6>& scores);
  CharacterBuilder& give_score_modifiers(std::array<int, 6>& modifiers);

  Character pc;
};


struct CharacterLeveler {
  explicit CharacterLeveler(Character& pc);
  virtual ~CharacterLeveler();

  // TODO: If reasonably possible, allow a totally new character
  //  to obtain the results of a Character after it has been edited
  //  by a CharacterLeveler instance
  operator Character() const;

  CharacterLeveler& give_experience(unsigned int experience);
  CharacterLeveler& increase_level(unsigned int how_many = 1);

  const static std::array<unsigned int, 19> level_up_thresholds;
  Character& pc;
};

#endif //DND_CHARACTER_HPP
