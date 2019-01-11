
#ifndef DND_DIE_HPP
#define DND_DIE_HPP

int dnd_roll(int num_die, int num_sides, bool verbose = false, bool slow = false, int wait_time = 250);
int d10_display(int d10_value);

int d100_roller(int num_die, int num_sides, bool verbose, bool slow, int wait_time);
int d10_roller(int num_die, int num_sides, bool verbose, bool slow, int wait_time);
int d3_roller(int num_die, int num_sides, bool verbose, bool slow, int wait_time);
int d2_roller(int num_die, int num_sides, bool verbose, bool slow, int wait_time);

#endif //DND_DIE_HPP
