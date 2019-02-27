// TODO: Consider running ../data/utils/json_gen.py or otherwise
//  ensuring data JSON files exist
#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "dnd_classes/abilities.hpp"
#include "dnd_scripts/abilities_script.hpp"
#include "dnd_classes/character.hpp"
#include "dnd_scripts/character_script.hpp"
#include "dnd_classes/races.hpp"
#include "dnd_scripts/races_script.hpp"
#include "dice_roller/dice.hpp"

struct Program_Args {
  dice_roller::Options roll_options{};
  std::string f_name;  // Left blank if not given
  bool ephemeral = false;
};

static bool should_file_be_written(Program_Args& args);
static void file_output(std::string file_name, std::string out_text);
static std::array<int, 6> generate_scores(Program_Args& args);

static po::options_description set_cli_args_and_description() {
  po::options_description desc{"  Options"};
  // No spaces between descriptive name and shorthand
  desc.add_options()
      ("help",
       "This help screen.\n")

      ("verbose,v",
       "Verbose switch for the dice roller. "
       "Triggers default `slow` behavior unless `no-slow` is also passed.\n")

      ("no-slow,x",
       "A switch that disables `slow`. Only needed if `verbose` "
       "is desired but without pauses between dice rolls.\n")

      ("slow,s", po::value<int>()->default_value(350),
       "Used to set a custom ms delay between dice rolls. "
       "Depends on `verbose`. Contradicts `no-slow`.\n")

      ("output,o", po::value<std::string>(),
       "Indicates that upon script completion, the program should "
       "output a summary to `file_name`.txt (extension will be "
       "appended by the program) to the working directory.\n")

      ("no-output",
       "Switch to indicate the program should not create "
       "any kind of output file(s). Contradicts `o`.\n");

  return desc;
}

/* "Dirty" function. Alters arguments and returns a bool.
 * Tries to parse and evaluate command line args;
 * the returned bool tells the caller if it should continue. */
static bool parse_args(int argc, const char *argv[],
                       Program_Args& args) {
  po::options_description desc = set_cli_args_and_description();
  try {
    // Parse given command-line arguments into a variable map
    po::variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help")) {
      std::cout << desc << std::endl;
      return false;
    }

    /* TODO: Consider refactoring slow and verbose options
      * by preventing "slow" from being active by default
      * when verbose is given. Verbose could be switched on
      * automatically if/when only slow is given.
      * Maybe slow can activate on double verbose (-vv) */
    // Dice rolling options
    args.roll_options.wait_time = vm["slow"].as<int>();
    if (vm.count("verbose"))
      args.roll_options.verbose = true;
    if (!vm.count("no-slow"))
      args.roll_options.slow = true;

    // File output options
    if (vm.count("no-output")) {
      if (vm.count("output")) {
        std::cerr << "Argument contradiction: -o and --no-output "
                  << "can't be used together."
                  << std::endl;
        return false;
      }
      args.ephemeral = true;
    } else if (vm.count("output")) {
      args.f_name = vm["output"].as<std::string>();
    }

  } catch (const po::error &ex) {
    std::cerr << "Argument Parse Error: "
              << ex.what() << "\n"
              << desc << std::endl;
    return false;
  } catch (std::exception &ex) {  // Other excepts *shouldn't* happen..
    std::cerr << ex.what()<< std::endl;
    return false;
  }

  return true;
}

int main(int argc, const char *argv[]) {
  Program_Args cli_args;
  if (!parse_args(argc, argv, cli_args))
    return 1;

  // Introductory message
  std::cout << "\nWelcome to the DnD Stats Generator!\n"
            << "=================================\n" << std::endl;

  // Get the generated character's name and create the character class
  std::string character_name = CharacterScripts::name_input();
  auto pc = Character(character_name);
  
  // Interface with user to generate and assign ability scores
  std::array<int, 6> generated_scores = generate_scores(cli_args);
  pc.ab.set_all_scores_of_type(Score::generated, generated_scores);
  // TODO: Turn this pretty-print loop into an AbilityScripts
  //  or otherwise re-callable function
  std::cout << "\nGenerated ability scores:\n";
  for (auto& score : generated_scores) {
    std::cout << std::setw(2) << std::setfill('0') << score << " ";
  }
  std::cout << '\n' << std::endl;
  AbilityScripts::assign_generated_scores(pc.ab);

  // Print a summary of the final results
  std::string full_summary = CharacterScripts::write_summary(pc);

  // Offer to output a summary (skip if user specified --no-output)
  if (should_file_be_written(cli_args))
    file_output(cli_args.f_name, full_summary);
  else
    std::cout << "Per your instructions, no output was generated."
              << std::endl;

  // Give exit message and close
  std::cout << "\n=================================\n"
            << "Thanks for using the DnD Stats Generator!"
            << std::endl;
  return 0;
}

static std::array<int, 6> generate_scores(Program_Args& args) {
  // Generate ability scores based on user's method choice
  switch(AbilityScripts::method_choice()) {
    case 1 :
      std::cout << "\nChosen method: 4d6\n" << std::endl;
      return AbilityScripts::generate_4d6(args.roll_options);

    case 2 :
      std::cout << "\nChosen method: 3d6\n" << std::endl;
      return AbilityScripts::generate_3d6(args.roll_options);

    case 3 : // Option not implemented yet, method_choice prevents case
      std::cout << "\nChosen method: Point-Buy\n" << std::endl;
      return AbilityScripts::point_buy(args.roll_options);

    default:
      std::cerr << "Bad method_choice return." << std::endl;
      exit(2);
  }
}

static bool get_confirmation() {
  // Get the first letter for comparison
  std::string confirmation;
  getline(std::cin, confirmation);
  std::string letter = confirmation.substr(0, 1);
  return (letter == "y" || letter == "Y");
}

/* Returns a bool telling main if it should write output to a file. */
static bool should_file_be_written(Program_Args& args) {
  if (args.ephemeral)
    return false;
  if (!args.f_name.empty())
    return true;
  // If command arguments do not give a clear answer, ask user
  std::cout << "Output a character summary to a text file? (y/n): ";
  return get_confirmation();
}

static std::string get_file_name() {
  std::string file_name;
  while (file_name.empty()) {
    std::cout << "What should the file be named? "
                 "(\".txt\" will be appended): ";
    getline(std::cin, file_name);
    // TODO: Handle bad file names (e.g., @%&.txt)
  }
  return file_name + ".txt";
}

static bool file_already_exists(std::string file_name) {
  if (FILE *file = fopen(file_name.c_str(), "r")) {
    fclose(file);
    return true;
  } else {
    return false;
  }
}

/* Write out_text to a file. */
static void file_output(std::string file_name, std::string out_text) {
  if (file_name.empty())
    file_name = get_file_name();
  else
    file_name += ".txt";

  bool good_to_go = false;
  while (!good_to_go) {
    if (file_already_exists(file_name)) {
      std::cout << "Overwrite existing file? (y/n): ";
      if (get_confirmation())
        good_to_go = true;
      else
        file_name = get_file_name();
    } else {
      good_to_go = true;
    }
  }

  std::ofstream file;
  if (file) {
    file.open(file_name.c_str());
    file << out_text;
    file.close();
    std::cout << "Successfully wrote summary to `"
              << file_name << '`' << std::endl;
  } else {
    std::cout << "Sorry, could not successfully open the file!\n"
              << "Check space, memory, and permissions."
              << std::endl;
  }
}
