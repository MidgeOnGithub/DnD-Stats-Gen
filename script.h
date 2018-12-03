
#ifndef DND_STATS_GEN_SCRIPT_H
#define DND_STATS_GEN_SCRIPT_H
#endif //DND_STATS_GEN_SCRIPT_H

#include <map>
#include <vector>

void master_script();
void abilities_3d6(std::vector<int> scores[6]);
void assign_abilities(std::vector<int> scores[6], std::map<std::string, int> dict);
void print_ability_scores(std::vector<int> scores);
