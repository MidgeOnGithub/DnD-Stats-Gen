
#ifndef DND_STATS_GEN_SCRIPT_H
#define DND_STATS_GEN_SCRIPT_H

#include "abilities.hpp"

void generate_3d6(abilities* ab, bool verbose = false, bool slow = false, int wait_time = 750);
void generate_4d6(abilities *ab, bool verbose = false, bool slow = false, int wait_time = 750);
void assign_abilities(abilities* ab);

#endif //DND_STATS_GEN_SCRIPT_H
