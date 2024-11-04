/* phyLS: powerful heightened yielded Logic Synthesis
 * Copyright (C) 2022 */

/**
 * @file exprsim.hpp
 *
 * @brief simulate a expression and return a truth table
 *
 * @author Homyoung
 * @since  2022/12/14
 */

#ifndef EXPRSIM_HPP
#define EXPRSIM_HPP

#include "../store.hpp"

using namespace std;

namespace alice {

class exprsim_command : public command {
 public:
  explicit exprsim_command(const environment::ptr& env)
      : command(env, "expression simulation, return a truth table") {
    add_flag("--verbose, -v", "print the information");
    add_option("-e,--expression", expression,
               "creates truth table from expression");
    add_flag("-n,--new", "adds new store entry");
    add_option("-m,--max_num_vars", max_num_vars,
               "set the maximum number of variables");
  }

 protected:
  void execute() {
    clock_t begin, end;
    double totalTime;
    auto& opt_ntks = store<optimum_network>();
    begin = clock();
    if (opt_ntks.empty() || is_set("new")) opt_ntks.extend();
    /* find max var */
    uint32_t num_vars{0u};
    for (auto c : expression) {
      if (c >= 'a' && c <= 'p')
        num_vars = std::max<uint32_t>(num_vars, c - 'a' + 1u);
    }
    if (is_set("max_num_vars"))
      num_vars = max_num_vars > num_vars ? max_num_vars : num_vars;
    kitty::dynamic_truth_table tt(num_vars);
    if (kitty::create_from_expression(tt, expression)) {
      optimum_network opt;
      opt.function = tt;
      opt.network = expression;
      opt_ntks.current() = opt;
      std::cout << fmt::format("tt: 0x{}", kitty::to_hex(opt.function))
                << std::endl;

      store<optimum_network>().extend();
      store<optimum_network>().current() = opt;
    }
    end = clock();
    totalTime = (double)(end - begin) / CLOCKS_PER_SEC;
    cout.setf(ios::fixed);
    cout << "[CPU time]   " << setprecision(2) << totalTime << " s" << endl;
  }

 private:
  std::string expression = "";
  uint32_t max_num_vars = 0u;
};

ALICE_ADD_COMMAND(exprsim, "Verification")

}  // namespace alice

#endif
