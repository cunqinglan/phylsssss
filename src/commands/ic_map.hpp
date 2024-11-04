/* phyLS: powerful heightened yielded Logic Synthesis
 * Copyright (C) 2024 */

/**
 * @file ic_map.hpp
 *
 * @brief Incremental standard cell mapping
 *
 * @author Homyoung
 * @since  2024/10/11
 */

#ifndef IC_MAP_HPP
#define IC_MAP_HPP

#include <iostream>
#include <mockturtle/algorithms/mapper.hpp>
#include <mockturtle/io/genlib_reader.hpp>
#include <mockturtle/io/write_verilog.hpp>
#include <mockturtle/networks/aig.hpp>
#include <mockturtle/utils/tech_library.hpp>
#include <string>

#include "../core/mapper_MCTS.hpp"
#include "../core/properties.hpp"
#include "../core/read_placement_file.hpp"
#include "../core/tonpz.hpp"

namespace alice {

class imap_command : public command {
 public:
  explicit imap_command(const environment::ptr& env)
      : command(env, "Standard cell mapping [default = AIG]") {
    add_option("--output, -o", filename, "the verilog filename");
    add_option("--cut_limit, -c", cut_limit,
               "Maximum number of cuts for a node");
    add_option("--node_position_pl, -p", pl_filename, "the pl filename");
    add_option("--node_position_def, -d", def_filename, "the def filename");
    add_option("--library, -l", library, "standard cell library ");
    add_flag("--verbose, -v", "print the information");
  }

  rules validity_rules() const {
    return {has_store_element<std::vector<mockturtle::gate>>(env)};
  }

 private:
  std::string filename = "techmap.v";
  std::string pl_filename = "";
  std::string def_filename = "";
  std::string library = "";
  uint32_t cut_limit{49u};

  template <typename TT>
  std::string to_hex(const TT& tt) {
    std::string hexstr;
    auto const chunk_size =
        std::min<uint64_t>(tt.num_vars() <= 1 ? 1 : (tt.num_bits() >> 2), 16);

    for_each_block_reversed(tt, [&hexstr, chunk_size](uint64_t word) {
      std::string chunk(chunk_size, '0');

      auto it = chunk.rbegin();
      while (word && it != chunk.rend()) {
        auto hex = word & 0xf;
        if (hex < 10) {
          *it = '0' + static_cast<char>(hex);
        } else {
          *it = 'a' + static_cast<char>(hex - 10);
        }
        ++it;
        word >>= 4;
      }
      hexstr += chunk;
    });
    return hexstr;
  }

 protected:
  void execute() {
    /* derive genlib */
    std::vector<mockturtle::gate> gates =
        store<std::vector<mockturtle::gate>>().current();
    mockturtle::tech_library<5> lib(gates);
    std::vector<mockturtle::gate> gates_small;
    for (auto& x : gates) {
      if (to_hex(x.function) == "8" || to_hex(x.function) == "7" ||
          to_hex(x.function) == "2" || to_hex(x.function) == "1" ||
          to_hex(x.function) == "0")
        gates_small.push_back(x);
    }
    mockturtle::tech_library<5> cri_lib(gates_small);

    mockturtle::map_params ps;
    mockturtle::map_stats st;
    ps.cut_enumeration_ps.cut_limit = cut_limit;
    if (is_set("verbose")) ps.verbose = true;

    stopwatch<>::duration time{0};
    call_with_stopwatch(time, [&]() {
      if (store<aig_network>().size() == 0u) {
        std::cerr << "[e] no AIG in the store\n";
      } else {
        auto aig = store<aig_network>().current();
        std::vector<mockturtle::node_position> np(aig.size() + aig.num_pos());
        phyLS::read_def_file(def_filename, np);
        auto res = mockturtle::map_mcts(aig, library, lib, cri_lib, np, ps, &st);
        if (is_set("output")) write_verilog_with_binding(res, filename);
        std::cout << fmt::format(
            "Mapped AIG into #gates = {}, area = {:.2f}, delay = {:.2f}, "
            "power = {:.2f}, wirelength = {:.2f}, total_wirelength = "
            "{:.2f}\n",
            res.num_gates(), st.area, st.delay, st.power, st.wirelength,
            st.total_wirelength);
      }
    });
    if (is_set("verbose")) st.report();
    std::cout << fmt::format("[CPU time]: {:5.3f} seconds\n", to_seconds(time));
  }
};

ALICE_ADD_COMMAND(imap, "Mapping")

}  // namespace alice

#endif
