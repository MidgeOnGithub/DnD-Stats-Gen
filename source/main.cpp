
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "abilities.hpp"
#include "dice_roller/dice.hpp"

bool process_command_line(int argc, const char *argv[],
                          bool& verbose, bool& slow, int& wait_time,
						  std::string& f_name, bool& ephemeral);

void file_output(std::string file_name, std::string output_text);

int main(int argc, const char *argv[]) {

    // Declare variables affected by command-line arguments
    bool verbose = false;
    bool slow = false;
    int wait_time;  // Value will be handled by parser
    std::string f_name;  // To be left blank if not given
    bool ephemeral = false;

	if (!process_command_line(argc, argv, verbose, slow, wait_time,
							  f_name, ephemeral))
	{
		return 1;
	}

    // Introductory message
    std::cout << std::endl << "Welcome to the DnD Stats Generator!" << std::endl
              << "========================================" << std::endl << std::endl;

    // Instantiate abilities class
    auto ab = new abilities();

    // TODO Move part or all of the method-choice code to another function
    // Determine how the user wants to generate ability scores.
    bool good_input = false;
    int countdown = 3;
    while (!good_input)
    {
        // Prevent infinite looping possibility
        if (countdown == 0)
        {
            std::cout << "Failed to get input after three tries -- aborting program." << std::endl;
            exit(2);
        }

        // Prompt the user and check their response
        std::cout << "What method should we use to generate ability scores?" << std::endl
                  << "------------------" << std::endl
                  << "|| 1: " << std::setw(12) << "4d6 ||" << std::endl
                  << "|| 2: " << std::setw(12) << "3d6 ||" << std::endl
                  << "|| 3: " << std::setw(12) << "Point-Buy ||" <<  "  <--  Unimplemented!!!" << std::endl
                  << "------------------" << std::endl
                  << "Choice: ";
        std::string confirm;
        std::getline(std::cin, confirm);
        if (confirm == "1")
        {
            std::cout << std::endl << "Chosen method: 4d6" << std::endl;
            generate_4d6(*ab, verbose, slow, wait_time);
            good_input = true;
        } else if (confirm == "2")
        {
            std::cout << std::endl << "Chosen method: 3d6" << std::endl;
            generate_3d6(*ab, verbose, slow, wait_time);
            good_input = true;
        } else if (confirm == "3")
        {
            //std::cout << std::endl << "Chosen method: Point-Buy" << std::endl;
            //point_buy(ab, verbose);
            std::cout << "This doesn't work yet -- choose another option!" << std::endl;
        } else
        {
            //good_input = false
            std::cout << std::endl;
            countdown--;
        }
    }

    std::cout << std::endl << "Rolled scores: " << ab->print_rolled_scores() << std::endl;

    // Interface with user to assign scores to abilities
    assign_abilities(*ab);

    // Print a summary of the final results
    std::string full_summary = ab->print_ability_summary();
    std::cout << full_summary << std::endl;

    /* Offer to write out full_summary to a file
     * Don't run this code if user specified --no-output in command line
     * Or if they've already given a file name */
    bool write_to_file = false;
    if (!ephemeral)
    {
        if (!f_name.empty())
        {
            write_to_file = true;
        } else
        {
            std::cout << "Would you like to save a character summary to a text file? (y/n): ";
            std::string confirm;
            getline(std::cin, confirm);
            // Get the first letter of confirm for comparison
            std::string letter = confirm.substr(0, 1);
            if (letter == "y" || letter == "Y")
                write_to_file = true;
        }
    }

    if (write_to_file)
    {
        file_output(f_name, full_summary);
        std::cout << "Successfully wrote summary to `" << f_name << ".txt`!" << std::endl;
    }

    // Delete class instances to free memory
    delete ab;

    // Give exit message and close
    std::cout << std::endl << "========================================" << std::endl
              << "Thanks for using the DnD Stats Generator!" << std::endl;

    return 0;
}

/* This function is "dirty", having both side effects and a return value
 * It parses command line args and alter values given by reference
 * It also returns a bool to tell main if the program should continue */
bool process_command_line(int argc, const char *argv[],
                          bool& verbose, bool& slow, int& wait_time, std::string& f_name, bool& ephemeral) {

    try
    {
        // Set command line argument info: names, descriptions, and types
        po::options_description desc{"  Options"};
        // No spaces between descriptive name and shorthand
        desc.add_options()
                ("help",
                 "This help screen.\n")
                ("verbose,v",
                 "Verbose switch -- primarily affects the dice roller. Will trigger the default `slow` unless `no-slow` is also passed.\n")
                ("no-slow,x",
                 "A switch that disables `slow`. Only needed if `verbose` is desired but without pauses between inputs.\n")
                ("slow,s", po::value<int>()->default_value(350),
                 "An optional value (milliseconds) to set a timer between die rolls. Depends on `verbose` and `no-slow`. Do not chain with other options.\n")
                ("output-file-name,o", po::value<std::string>(),
                 "Parameter to output a summary to `file_name`.txt (extension will be appended by the program) to the working directory. Do not chain with other options.\n")
                ("no-output",
                 "Switch to indicate the program should not create any kind of output file(s).\n");

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
            verbose = true;
        if (!vm.count("no-slow"))
            slow = true;
        wait_time = vm["slow"].as<int>();
        if (vm.count("no-output"))
            ephemeral = true;
        if (vm.count("output-file-name")) {
            f_name = vm["output-file-name"].as<std::string>();
        }
    }
        // If argument parsing or evaluating generates an error, state error and exit
    catch (const po::error &ex) {
        std::cerr << "Argument Parse Error: " << ex.what() << std::endl;
        return false;
    }
    catch (std::exception &ex) {
        std::cerr << ex.what()<< std::endl;
        return false;
    }
    return true;
}

void file_output(std::string file_name, std::string output_text) {
    // Get a name for the file if not provided in a command-line argument
    if (file_name.empty())
    {
        while (file_name.empty())
        {
            std::cout << "What should the file be named? (\".txt\" will be appended): ";
            getline(std::cin, file_name);
        }
    }

    // Write full_summary to new file
    std::ofstream file;
    if (file)
    {
        file.open(file_name + ".txt");
        file << output_text;
        file.close();
    } else
    {
        std::cout << "Sorry, could not successfully open the file!" << std::endl
                  << "Check space, memory, and permissions!" << std::endl;
    }
}
