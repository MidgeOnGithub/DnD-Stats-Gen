#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "abilities_script.hpp"


namespace AbilityScripts {

  static std::string write_prompt() {
    // Use ostringstream to format as if using std::cout
    std::ostringstream write_prompt;
    write_prompt << "\nHow should we generate ability scores?\n"
                 << "------------------\n"
                 << "|| 1: " << std::setw(13) << "4d6 ||\n"
                 << "|| 2: " << std::setw(13) << "3d6 ||\n"
                 << "|| 3: " << std::setw(12) << "Point-Buy ||"
                 << "  <--  Unimplemented!!!\n"
                 << "------------------\n"
                 << "Choice: ";
    return write_prompt.str();
  }

  int method_choice() {
    int choice;
    std::string prompt = write_prompt();
    bool good_input = false;
    int countdown = 3;
    while (!good_input) {
      // Prevent infinite looping possibility
      if (--countdown == 0) {
        std::cout << "Failed to get input after three tries.\n"
                     "Terminating program." << std::endl;
        exit(2);
      }
      // Prompt the user and check their response
      choice = dice_roller::int_input(prompt);
      if (choice == 3) {
        // Temporary message while point-buy system is built
        std::cout << "This doesn't work yet"
                  << " -- choose another option!" << std::endl;
      } else {
        good_input = (choice > 0 && choice < 3);
      }
    }
    return choice;
  }


  static void print_rolled_score(int index, int score) {
    // Describe the score value (index + 1 for natural counting)
    int display = index + 1;
    std::cout << "Roll " << display << " = "
              << std::setw(2) << score << std::endl;
  }

  std::array<int, 6> generate_3d6(dice_roller::Options& options) {
    std::array<int, 6> generated_scores{};
    for (int i = 0; i < 6; ++i) {
      // Roll a 3d6, add result to rolled_score array
      generated_scores[i] = dnd_roll(options, 3, 6);
      print_rolled_score(i, generated_scores[i]);
    }
    return generated_scores;
  }

  std::array<int, 6> generate_4d6(dice_roller::Options& options) {
    std::array<int, 6> generated_scores{};
    for (int i = 0; i < 6; ++i) {
      // Populate an array of 4 rolls
      std::array<int, 4> rolls{};
      for (int j = 0; j < 4; ++j) {
        int roll = dnd_roll(options, 1, 6);
        rolls[j] = roll;
        if (options.verbose)
          dice_roller::verbosity(options, j, roll);
      }
      // Sum over the three highest values
      std::sort(std::begin(rolls), std::end(rolls));
      int rolled_score = 0;
      for (int j = 1; j < 4; ++j) {
        rolled_score += rolls[j];
      }
      // Append and display the roll result
      generated_scores[i] = rolled_score;
      print_rolled_score(i, rolled_score);
    }
    return generated_scores;
  }

  // TODO : Implement point_buy
  std::array<int, 6> point_buy(dice_roller::Options &options) {
    std::array<int, 6> generated_scores{};
	return generated_scores;
  }


  static void print_response_to_invalid_score(int invalid_score) {
    if (invalid_score > 18)
      std::cout << "You wish!";
    else if (invalid_score < 3)
      std::cout << "That's a bit harsh!";
    else
      std::cout << "That wasn't an available score!";
    std::cout << std::endl;
  }

  static void print_scores_left(const std::array<bool, 6>& assigned,
                                const std::array<int, 6>& generated_scores) {
    std::cout << "Available scores: [";
    for (int i = 0; i < 6; ++i) {
      // Skip writing the value if already assigned
      if (assigned[i])
        continue;
      std::cout << generated_scores[i];
      // Prevent printing comma and space on last element
      if (i != 5) {
        for (int j = i + 1; j < 6; ++j) {
          // If a remaining index is unassigned, current index
          // is not last, thus the comma and space
          if (!assigned[j]) {
            std::cout << ", ";
            break;
          }
        }
      }
    }
    std::cout << "]" << std::endl;
  }

  void assign_generated_scores(Abilities& ab) {
    // Create a copy of the abilities' generated scores
    std::array<int, 6> scores = {};
    for (int i = 0; i < 6; ++i) {
      Ability ability = All_Abilities[i];
      scores[i] = ab.get_score(ability, Score::generated);
    }

    // An array and number to track which scores have been assigned
    std::array<bool, 6> assigned = {false, false, false,
                                    false, false, false};
    int num_assigned = 0;
    std::string retry_prompt = "Score: ";
    bool first_time_asking = true;
    for (int i = 0; i < 6; ++i) {
      // Assign variables
      Ability ability = All_Abilities[i];
      int chosen_score = 0;
      std::string ab_name = ability_names[i];

      if (num_assigned == 5) {
        // Only one value remains; find and assign it
        for (int j = 0; j < 6; ++j) {
          if (!assigned[j])
            chosen_score = scores[j];
        }
        ab.set_score(ability, Score::generated, chosen_score);
        break;
      }

      std::string prompt;
      prompt = "Choose a score to assign to " + ab_name + ": ";
      bool keep_going = true;
      while (keep_going) {
        if (!first_time_asking) {
          print_scores_left(assigned, scores);
        }
        first_time_asking = false;

        // Get choice from user using int_input from dice module
        chosen_score = dice_roller::int_input(prompt, retry_prompt);
        for (int j = 0; j < 6; ++j) {
          // Assign if chosen_score is an unassigned score
          if (chosen_score == scores[j] && !assigned[j]) {
            assigned[j] = true;
            ++num_assigned;
            keep_going = false;
            break;  // Only breaks from for loop
          }
        }

        if (keep_going) {
          print_response_to_invalid_score(chosen_score);
        }
      }  // end while loop
      ab.set_score(ability, Score::active, chosen_score);
    }  // end for loop
  }


  void print_set_of_scores(const std::array<int, 6>& scores) {
    std::cout << "[";
    for (int i = 0; i < 6; ++i) {
      std::cout << std::setw(2) << std::setfill('0') << scores[i];
      if (i != 5)
        std::cout << ", ";
    }
    std::cout << "]\n" << std::endl;
  }

  std::string summary_of_all_scores(Abilities &ab, const Score &flag) {
    std::array<int, 6> scores = ab.get_all_scores_of_type(flag);
    // Use ostringstream to format as if using std::cout
    std::ostringstream summary;
    summary << "Ability Scores" << std::endl
            << "--------------------" << std::endl;
    for (int i = 0; i < 6; ++i) {
      std::string ab_name = ability_names[i];
      summary << std::setw(18) << std::left << ab_name + ": "
              << std::setw(02) << std::right << scores[i] << std::endl;
    }
    summary << "--------------------" << std::endl;
    // Return as a string
    return summary.str();
  }
}
