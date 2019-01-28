#include <iomanip>
#include <iostream>
#include <sstream>

#include "abilities.hpp"

Abilities::Abilities()
{
    // Initialize the dictionary with zeroed values
    for (int i = 0; i < 6; i++)
    {
        score_dict[names[i]] = generated_scores[i];
    }
}

int Abilities::get_ability_score(std::string ability)
{
    if (score_dict.find(ability) == score_dict.end())
        throw std::invalid_argument ("Passed ability does not exist.");
    return score_dict[ability];
}

void Abilities::set_ability_score(std::string ability, int score)
{
    if (score_dict.find(ability) == score_dict.end())
        throw std::invalid_argument ("Passed ability does not exist.");
    else if (score > 20)  // 20 is the maximum per rules
        score = 20;
    score_dict[ability] = score;
}

std::string Abilities::print_ability_scores()
{
    // Use ostringstream to format as if using std::cout
    std::ostringstream scores;
    scores << "[";
    for (int i = 0; i < 6; i++)
    {
        std::string name = get_ability_name(i);
        scores << get_ability_score(name);
		// Don't print a comma and space for the last element
		if (i < 5)
            scores << ", ";
    }
    scores << "]" << std::endl;
    // Return as a string
    return scores.str();
}

int Abilities::get_score_modifier(int i)
{
    if (i > 5)
        throw std::invalid_argument ("score_modifier only has indices 0 - 5.");
    return score_modifiers[i];
}

void Abilities::set_score_modifier(int i, int score)
{
    if (i > 5)
        throw std::invalid_argument ("score_modifier only has indices 0 - 5.");
    else if (score > 20)  // 20 is the maximum per rules
        score = 20;
    score_modifiers[i] = score;
}

int Abilities::get_rolled_score(int i)
{
    if (i > 5)
        throw std::invalid_argument ("generated_scores only has indices 0 - 5.");
    return generated_scores[i];
}

void Abilities::set_rolled_score(int i, int score)
{
    if (i > 5)
        throw std::invalid_argument ("generated_scores only has indices 0 - 5.");
    else if (score > 18)  // 20 is the maximum possible from a roll
        score = 20;
    generated_scores[i] = score;
}

std::string Abilities::print_rolled_scores()
{
    // Use ostringstream to format as if using std::cout
    std::ostringstream scores;
    scores << "[";
    for (int i = 0; i < 6; i++)
    {
        scores << get_rolled_score(i);
		// Don't print a comma and space for the last element
        if (i < 5)  
            scores << ", ";
    }
    scores << "]" << std::endl;
    // Return as a string
    return scores.str();
}

std::string Abilities::get_ability_name(int i)
{
    if (i > 5)
        throw std::invalid_argument ("ability_name only has indices 0 - 5.");
    return names[i];
}

std::string Abilities::print_ability_summary()
{
    // Use ostringstream to format as if using std::cout
    std::ostringstream summary;
    summary << "Ability Scores" << std::endl
            << "--------------------" << std::endl;
    for (int i = 0; i < 6; i++)
    {
        std::string ab_name = get_ability_name(i);
        summary << std::setw(18) << std::left << ab_name + ": "
                << std::setw(02) << std::right << score_dict[ab_name] << std::endl;
    }
    summary << "--------------------" << std::endl;
    // Return as a string
    return summary.str();
}
