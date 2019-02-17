#ifndef DND_DICE_HPP
#define DND_DICE_HPP

int dnd_roll(int num_dice, int num_sides, dice_roller::Options options);
int d10_display(int d10_value);

int d100_roller(int num_dice, dice_roller::Options options);
int d10_roller(int num_dice, dice_roller::Options options);
int d3_roller(int num_dice, dice_roller::Options options);
int d2_roller(int num_dice, dice_roller::Options options);

#endif //DND_DICE_HPP
