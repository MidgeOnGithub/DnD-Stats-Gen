
#ifndef DND_STATS_GEN_DICE_H
#define DND_STATS_GEN_DICE_H

int int_input(std::string initial_prompt = "");
int roll_dice(int d_count = 0, int d_sides = 0, bool verbose = false, bool slow = false, int wait = 250);

#endif //DND_STATS_GEN_DICE_H
