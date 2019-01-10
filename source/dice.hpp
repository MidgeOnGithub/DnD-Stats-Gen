
#ifndef DND_STATS_GEN_DICE_H
#define DND_STATS_GEN_DICE_H

int int_input(std::string initial_prompt = "", std::string retry_prompt = "");
int roll_die(int num_die = 0, int num_sides = 0,
             bool verbose = false, bool slow = false, int wait_time = 250);

#endif //DND_STATS_GEN_DICE_H
