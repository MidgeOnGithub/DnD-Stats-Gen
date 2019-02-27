#ifndef DND_DICE_HPP
#define DND_DICE_HPP

int dnd_roll(dice_roller::Options& options, int dice, int sides);
int d10_display(int d10_value);

int d100_roller(dice_roller::Options& options, int dice);
int d10_roller (dice_roller::Options& options, int dice);
int d3_roller  (dice_roller::Options& options, int dice);
int d2_roller  (dice_roller::Options& options, int dice);

#endif //DND_DICE_HPP
