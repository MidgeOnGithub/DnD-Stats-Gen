
#ifndef DND_STATS_GEN_DICE_H
#define DND_STATS_GEN_DICE_H
#endif //DND_STATS_GEN_DICE_H

int int_input(std::string initial_prompt = "");
int roll_dice(int dice_count = 0, int die_sides = 0, bool verbose = false, bool slow = false, int wait = 250);