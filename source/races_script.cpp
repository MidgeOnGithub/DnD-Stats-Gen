#include "races.hpp"

#include <iostream>
#include <fstream>

json race_choice()
{
    json choice;
    // TODO: Use load_data to get initial list of races for selection
    // TODO: Interface with user to select race
    return choice;
}

json load_data()
{
    json data;
    
    // Populate return JSON string using an existing json file
	
    std::ifstream input_file("../data/races.json");
	if (!input_file.is_open()) 
	{
		std::cout << "Failed to open input_file.";
		// TODO: Handle file opening errors
	}
	input_file >> data;
	input_file.close();

    return data;
}