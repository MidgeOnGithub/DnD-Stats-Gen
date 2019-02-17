// Must include first due to pre-processors
// also includes <stdio.h>, <string.h>, <errno.h>, and <stdlib.h>
//#include <Python.h>
// TODO: Consider running ../data/utils/json_gen.py or otherwise ensuring data JSON files exist
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "abilities.hpp"
#include "character.hpp"
#include "dice_roller/dice.hpp"

struct Program_Args
{
    dice_roller::Options roll_options;
    std::string f_name;  // Left blank if not given
    bool ephemeral = false;
};
bool parse_args(int argc, const char *argv[], Program_Args &args);
bool should_file_be_written(Program_Args &args);
void file_output(std::string file_name, std::string out_text);

int main(int argc, const char *argv[])
{
    Program_Args program_args;
	if (!parse_args(argc, argv, program_args))
        return 1;

    // Introductory message
    std::cout << "\nWelcome to the DnD Stats Generator!\n"
              << "=================================\n" << std::endl;
              
    // Get the generated character's name
    std::string character_name;
    // Instantiate Character class
    auto pc = Character();

    // Generate ability scores based on user's method choice
    int method;
    method = method_choice();
    switch(method)
    {
        case 1: std::cout << "\nChosen method: 4d6" << std::endl;
                pc.ab.generate_4d6(program_args.roll_options);
                break;

        case 2: std::cout << "\nChosen method: 3d6" << std::endl;
                pc.ab.generate_3d6(program_args.roll_options);
                break;

        case 3: // Option not implemented yet, method_choice prevents this return
                //std::cout << "\nChosen method: Point-Buy" << std::endl;
                //pc.ab.point_buy(program_args.roll_options);
                break;
    }
    std::cout << std::endl << "Generated ability scores: "
			  << pc.ab.print_rolled_scores() << std::endl;
    // Interface with user to assign scores to character's abilities
    pc.ab.assign_abilities();

    // Print a summary of the final results
    std::string full_summary = pc.print_character_summary();
    std::cout << pc.ab.print_ability_summary() << std::endl;

    // Offer to output a summary (skip if user specified --no-output)
    if (should_file_be_written(program_args))
        file_output(program_args.f_name, full_summary);
    else
        std::cout << "Per your instructions, no output was generated."
		          << std::endl;

    // Give exit message and close
    std::cout << "\n=================================\n"
              << "Thanks for using the DnD Stats Generator!"
			  << std::endl;

    return 0;
}

/* "Dirty" function. Alters argments and returns a bool.
 * Tries to parse and evalutate command line args as needed.
 * The returned bool tells the caller if it should continue. */
bool parse_args(int argc, const char *argv[], Program_Args &args)
{
    try
    {
        // Set command line argument info: names, descriptions, and types
        po::options_description desc{"  Options"};
        // No spaces between descriptive name and shorthand
        desc.add_options()
                ("help",
                 "This help screen.\n")
                ("verbose,v",
                 "Verbose switch -- primarily affects the dice roller."
				 " Triggers `slow` unless `no-slow` is also passed.\n")
                ("no-slow,x",
                 "A switch that disables `slow`. "
				 "Only needed if `verbose` is desired but "
				 "without pauses between inputs.\n")
                ("slow,s", po::value<int>()->default_value(350),
                 "Used to set a custom ms delay between dice rolls. "
				 "Depends on `verbose` and `no-slow`.\n")
                ("output-file-name,o", po::value<std::string>(),
                 "Parameter to output a summary to `file_name`.txt "
				 "(extension will be appended by the program) "
				 "to the working directory.\n")
                ("no-output",
                 "Switch to indicate the program should not create "
				 "any kind of output file(s).\n");

        // Parse given command-line arguments into a variable map
        po::variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);

        // Act according to the presence of given arguments in variable map
        if (vm.count("help"))
        {
            std::cout << desc;
            return false;
        }
        /* TODO If possible prevent `slow` from always being `count`ed due to implicit & default values
         * This would prevent "slow" from being dependent upon verbose, and always firing when verbose is given
         * Instead, verbose could be switched on automatically if/when only slow is given
         * As is, without slow being dependent on verbose, it would be impossible do this
         * Because `slow` would always be fired, obfuscating user's desire for verbosity */
        if (vm.count("verbose"))
            args.roll_options.verbose = true;
        if (!vm.count("no-slow"))
            args.roll_options.slow = true;
            args.roll_options.wait_time = vm["slow"].as<int>();
        if (vm.count("no-output"))
            args.ephemeral = true;
        if (vm.count("output-file-name")) {
            args.f_name = vm["output-file-name"].as<std::string>();
        }
    }
    // TODO: Use help output when only the parsing fails
	// If argument parsing or manipulation fails, state and exit
    catch (const po::error &ex)
    {
        std::cerr << "Argument Parse Error\n"
				  << ex.what() << std::endl;
        return false;
    }
    catch (std::exception &ex)
    {
        std::cerr << ex.what()<< std::endl;
        return false;
    }

    return true;
}

/* Returns a bool telling main if it should write output to a file. */
bool should_file_be_written(Program_Args &args)
{
    if (args.ephemeral)
        return false;
    if (!args.f_name.empty())
        return true;
    // If command arguments do not given a direct answer, ask user
    std::cout << "Output a character summary to a text file? (y/n): ";
    // Get the first letter for comparison
	std::string confirmation;
    getline(std::cin, confirmation);
    std::string letter = confirmation.substr(0, 1);
    if (letter == "y" || letter == "Y")
        return true;
    return false;
}

/* Write out_text to a file named file_name.*/
void file_output(std::string file_name, std::string out_text)
{
    // Get a name for the file if not provided
    if (file_name.empty())
    {
        while (file_name.empty())
        {
            std::cout << "What should the file be named? "
						 "(\".txt\" will be appended): ";
            getline(std::cin, file_name);
        }
    }
    // Write out_text to a new file
    std::ofstream file;
    if (file)
    {
        file.open(file_name + ".txt");
        file << out_text;
        file.close();
        std::cout << "Successfully wrote summary to `"
				  << file_name << ".txt`!" << std::endl;
    } else
    {
        std::cout << "Sorry, could not successfully open the file!\n"
                  << "Check space, memory, permissions." << std::endl;
    }
}
