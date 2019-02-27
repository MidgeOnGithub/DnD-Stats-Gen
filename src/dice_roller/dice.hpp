#ifndef DICE_ROLLER_HPP
#define DICE_ROLLER_HPP

#include <string>

namespace dice_roller {

  struct Options {
    Options() : verbose(false), slow(false), wait_time(750) {};
    bool verbose;
    bool slow;
    int wait_time;
  };

  int int_input(std::string prompt = "",
                std::string retry_prompt = "Number : ");

  void wait_time_adjustment(Options& options);

  int roll_dice(Options& options, int dice = 0,
                int sides = 0);

  void verbosity(Options& options, int which_die,
                 int landing);
}

#endif //DICE_ROLLER_HPP
