/* phyLS: powerful heightened yielded Logic Synthesis
 * Copyright (C) 2022 */

/**
 * @file lutmap.hpp
 *
 * @brief performs FPGA technology mapping of the network
 *
 * @author Homyoung
 * @since  2022/12/21
 */

#ifndef LUTMAP_HPP
#define LUTMAP_HPP

#include <mockturtle/generators/arithmetic.hpp>
#include <mockturtle/networks/aig.hpp>
#include <mockturtle/traits.hpp>
#include <mockturtle/views/mapping_view.hpp>

#include "../core/lut_mapper.hpp"

using namespace std;
using namespace mockturtle;

namespace alice {

class lutmap_command : public command {
 public:
  explicit lutmap_command(const environment::ptr& env)
      : command(env, "FPGA technology mapping of the network [default = AIG]") {
    add_flag("--mig, -m", "FPGA technology mapping for MIG");
    add_flag("--xag, -g", "FPGA technology mapping for XAG");
    add_flag("--xmg, -x", "FPGA technology mapping for XMG");
    add_flag("--klut, -k", "FPGA technology mapping for k-LUT");
    add_option("--cut_size, -s", cut_size,
               "Maximum number of leaves for a cut [default = 6]");
    add_option(
        "--cut_limit, -l", cut_limit,
        "the input Maximum number of cuts for a node name [default = 25]");
    add_option("--relax_required, -r", relax_required,
               "delay relaxation ratio (%) [default = 0]");
    add_flag("--area, -a", "toggles area-oriented mapping [default = false]");
    add_flag("--recompute_cuts, -c",
             "recompute cuts at each step [default = true]");
    add_flag("--edge, -e", "Use edge count reduction [default = true]");
    add_flag("--cost_function, -f",
             "LUT map with cost function [default = false]");
    add_flag("--dominated_cuts, -d",
             "Remove the cuts that are contained in others [default = true]");
    add_option("--output, -o", filename, "the bench filename");
    add_flag("--verbose, -v", "print the information");
  }

 protected:
  struct lut_custom_cost {
    std::pair<uint32_t, uint32_t> operator()(uint32_t num_leaves) const {
      if (num_leaves < 2u) return {0u, 0u};
      return {num_leaves, 1u}; /* area, delay */
    }

    std::pair<uint32_t, uint32_t> operator()(
        kitty::dynamic_truth_table const& tt) const {
      if (tt.num_vars() < 2u) return {0u, 0u};
      return {tt.num_vars(), 1u}; /* area, delay */
    }
  };

  void execute() {
    if (is_set("mig")) {
      if (store<mig_network>().size() == 0u)
        std::cerr << "Error: Empty MIG network\n";
      else {
        auto mig = store<mig_network>().current();
        mapping_view mapped_mig{mig};
        phyLS::lut_map_params ps;
        if (is_set("area")) ps.area_oriented_mapping = true;
        if (is_set("relax_required")) ps.relax_required = relax_required;
        if (is_set("cut_size")) ps.cut_enumeration_ps.cut_size = cut_size;
        if (is_set("cut_limit")) ps.cut_enumeration_ps.cut_limit = cut_limit;
        if (is_set("recompute_cuts")) ps.recompute_cuts = false;
        if (is_set("edge")) ps.edge_optimization = false;
        if (is_set("dominated_cuts")) ps.remove_dominated_cuts = false;
        cout << "Mapped MIG into " << cut_size << "-LUT : ";
        phyLS::lut_map(mapped_mig, ps);
        mapped_mig.clear_mapping();
      }
    } else if (is_set("xag")) {
      if (store<xag_network>().size() == 0u)
        std::cerr << "Error: Empty XAG network\n";
      else {
        auto xag = store<xag_network>().current();
        mapping_view mapped_xag{xag};
        phyLS::lut_map_params ps;
        if (is_set("area")) ps.area_oriented_mapping = true;
        if (is_set("relax_required")) ps.relax_required = relax_required;
        if (is_set("cut_size")) ps.cut_enumeration_ps.cut_size = cut_size;
        if (is_set("cut_limit")) ps.cut_enumeration_ps.cut_limit = cut_limit;
        if (is_set("recompute_cuts")) ps.recompute_cuts = false;
        if (is_set("edge")) ps.edge_optimization = false;
        if (is_set("dominated_cuts")) ps.remove_dominated_cuts = false;
        cout << "Mapped XAG into " << cut_size << "-LUT : ";
        phyLS::lut_map(mapped_xag, ps);
        mapped_xag.clear_mapping();
      }
    } else if (is_set("xmg")) {
      if (store<xmg_network>().size() == 0u)
        std::cerr << "Error: Empty XMG network\n";
      else {
        auto xmg = store<xmg_network>().current();
        mapping_view mapped_xmg{xmg};
        phyLS::lut_map_params ps;
        if (is_set("area")) ps.area_oriented_mapping = true;
        if (is_set("relax_required")) ps.relax_required = relax_required;
        if (is_set("cut_size")) ps.cut_enumeration_ps.cut_size = cut_size;
        if (is_set("cut_limit")) ps.cut_enumeration_ps.cut_limit = cut_limit;
        if (is_set("recompute_cuts")) ps.recompute_cuts = false;
        if (is_set("edge")) ps.edge_optimization = false;
        if (is_set("dominated_cuts")) ps.remove_dominated_cuts = false;
        cout << "Mapped XMG into " << cut_size << "-LUT : ";
        phyLS::lut_map(mapped_xmg, ps);
        mapped_xmg.clear_mapping();
      }
    } else if (is_set("klut")) {
      if (store<klut_network>().size() == 0u)
        std::cerr << "Error: Empty k-LUT network\n";
      else {
        auto klut = store<klut_network>().current();
        mapping_view mapped_klut{klut};
        phyLS::lut_map_params ps;
        if (is_set("area")) ps.area_oriented_mapping = true;
        if (is_set("relax_required")) ps.relax_required = relax_required;
        if (is_set("cut_size")) ps.cut_enumeration_ps.cut_size = cut_size;
        if (is_set("cut_limit")) ps.cut_enumeration_ps.cut_limit = cut_limit;
        if (is_set("recompute_cuts")) ps.recompute_cuts = false;
        if (is_set("edge")) ps.edge_optimization = false;
        if (is_set("dominated_cuts")) ps.remove_dominated_cuts = false;
        cout << "Mapped kLUT into " << cut_size << "-LUT : ";
        phyLS::lut_map(mapped_klut, ps);
        mapped_klut.clear_mapping();
      }
    } else {
      if (store<aig_network>().size() == 0u)
        std::cerr << "Error: Empty AIG network\n";
      else {
        auto aig = store<aig_network>().current();
        mapping_view<aig_network, true> mapped_aig{aig};
        phyLS::lut_map_params ps;
        if (is_set("area")) ps.area_oriented_mapping = true;
        if (is_set("relax_required")) ps.relax_required = relax_required;
        if (is_set("cut_size")) ps.cut_enumeration_ps.cut_size = cut_size;
        if (is_set("cut_limit")) ps.cut_enumeration_ps.cut_limit = cut_limit;
        if (is_set("recompute_cuts")) ps.recompute_cuts = false;
        if (is_set("edge")) ps.edge_optimization = false;
        if (is_set("dominated_cuts")) ps.remove_dominated_cuts = false;
        cout << "Mapped AIG into " << cut_size << "-LUT : ";
        if (is_set("cost_function"))
          phyLS::lut_map<decltype(mapped_aig), true, lut_custom_cost>(
              mapped_aig, ps);
        else
          phyLS::lut_map(mapped_aig, ps);
        if (is_set("output")) {
          write_bench(mapped_aig, filename);
        } else {
          mapped_aig.clear_mapping();
        }
      }
    }
  }

 private:
  uint32_t cut_size{6u};
  uint32_t cut_limit{8u};
  uint32_t relax_required{0u};
  std::string filename = "lut.bench";
};

ALICE_ADD_COMMAND(lutmap, "Mapping")

}  // namespace alice

#endif