
#ifndef DND_STATS_GEN_SCRIPT_H
#define DND_STATS_GEN_SCRIPT_H
#endif //DND_STATS_GEN_SCRIPT_H

#include "abilities.h"

void generate_3d6(abilities* ab);
void generate_4d6_drop(abilities* ab);
void assign_abilities(abilities* ab);
bool is_last_unassigned(int check_index);
