#pragma once

#include <fmt/format.h>

#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <mockturtle/algorithms/mapper.hpp>
#include <sstream>
#include <string>
#include <vector>

#include "assert.h"
#include "base/abc/abc.h"
#include "map/scl/scl.c"
#include "map/scl/sclSize.c"

using namespace pabc;

namespace phyLS {

void read_def_file(std::string file_path,
                   std::vector<mockturtle::node_position> &Vec_position) {
  std::ifstream ifs(file_path, std::ifstream::in);
  assert(ifs.is_open());
  std::string line;
  int cell_size = 0;
  while (std::getline(ifs, line)) {
    if (line.substr(0, 4) == "COMP") {
      while (std::getline(ifs, line)) {
        if (line.substr(0, 3) == "END") {
          break;
        } else {
          // get index of AIG node
          int index;
          std::string res;
          std::string::size_type found_b = line.find_first_of("_");
          std::string::size_type found_e = line.find_last_of("_");
          while (found_b != found_e - 1) {
            res += line[found_b + 1];
            found_b++;
          }
          index = std::stoi(res);
          cell_size = index;
          // read next line
          std::getline(ifs, line);
          // get position of AIG node
          bool is_x = true;
          std::string position = "";
          for (char c : line) {
            if (std::isdigit(c)) {
              position += c;
            } else if (!position.empty()) {
              if (is_x) {
                Vec_position[index].x_coordinate = std::stoi(position);
                position.clear();
                is_x = false;
              } else {
                Vec_position[index].y_coordinate = std::stoi(position);
                position.clear();
              }
            } else {
              continue;
            }
          }
        }
      }
    } else if (line.substr(0, 4) == "PINS") {
      while (std::getline(ifs, line)) {
        if (line.substr(0, 3) == "END") {
          break;
        } else if (line.find("input") != std::string::npos &&
                   line.find("clk") == std::string::npos) {
          // get input position
          std::string::size_type found_1 = line.find("_");
          std::string::size_type found_2 = line.find("+");
          int index;
          std::string res;
          while (found_1 != found_2 - 2) {
            res += line[found_1 + 1];
            found_1++;
          }
          index = std::stoi(res);
          std::getline(ifs, line);
          std::getline(ifs, line);
          bool is_x = true;
          std::string position_input = "";
          for (char c : line) {
            if (std::isdigit(c)) {
              position_input += c;
            } else if (!position_input.empty()) {
              if (is_x) {
                Vec_position[index + 1].x_coordinate =
                    std::stoi(position_input);
                position_input.clear();
                is_x = false;
              } else {
                Vec_position[index + 1].y_coordinate =
                    std::stoi(position_input);
                position_input.clear();
              }
            } else {
              continue;
            }
          }
        } else if (line.find("output") != std::string::npos) {
          // get input position
          std::string::size_type found_1 = line.find("_");
          std::string::size_type found_2 = line.find("+");
          int index;
          std::string res;
          while (found_1 != found_2 - 2) {
            res += line[found_1 + 1];
            found_1++;
          }
          index = std::stoi(res);
          std::getline(ifs, line);
          std::getline(ifs, line);
          bool is_x = true;
          std::string position_output = "";
          for (char c : line) {
            if (std::isdigit(c)) {
              position_output += c;
            } else if (!position_output.empty()) {
              if (is_x) {
                Vec_position[index + cell_size + 1].x_coordinate =
                    std::stoi(position_output);
                position_output.clear();
                is_x = false;
              } else {
                Vec_position[index + cell_size + 1].y_coordinate =
                    std::stoi(position_output);
                position_output.clear();
              }
            } else {
              continue;
            }
          }
        } else {
          continue;
        }
      }
    } else {
      continue;
    }
  }
}

void read_pl_file(std::string file_path,
                  std::vector<mockturtle::node_position> &Vec_position,
                  uint32_t ntk_size) {
  std::ifstream ifs(file_path, std::ifstream::in);
  assert(ifs.is_open());
  std::string line;
  uint32_t index;
  Vec_position.reserve(ntk_size);
  while (getline(ifs, line)) {
    if (line[0] == 'U') {
      continue;
    } else {
      for (char c : line) {
        std::string str_number = "";
        uint32_t a = 0;
        if (c == ':') {
          break;
        }
        if (std::isdigit(c)) {
          str_number += c;
        } else {
          if (!str_number.empty()) {
            if (a == 0) {
              index = std::stoi(str_number);
              str_number = "";
              a++;
            } else if (a == 1) {
              Vec_position[index].x_coordinate = std::stoi(str_number);
              str_number = "";
              a++;
            } else if (a == 2) {
              Vec_position[index].y_coordinate = std::stoi(str_number);
              str_number = "";
              a = 0;
            }
          }
        }
      }
    }
  }
  ifs.close();
}

void read_def_file_abc(std::string file_path, Vec_Int_t **VecNP) {
  std::ifstream ifs(file_path, std::ifstream::in);
  assert(ifs.is_open());
  std::string line;
  int cell_size = 0;
  while (std::getline(ifs, line)) {
    if (line.substr(0, 4) == "COMP") {
      while (std::getline(ifs, line)) {
        if (line.substr(0, 3) == "END") {
          break;
        } else {
          // get index of AIG node
          int index;
          std::string res;
          std::string::size_type found_b = line.find_first_of("_");
          std::string::size_type found_e = line.find_last_of("_");
          while (found_b != found_e - 1) {
            res += line[found_b + 1];
            found_b++;
          }
          index = std::stoi(res);
          cell_size = index;
          // read next line
          std::getline(ifs, line);
          // get position of AIG node
          bool is_x = true;
          std::string position = "";
          for (char c : line) {
            if (std::isdigit(c)) {
              position += c;
            } else if (!position.empty()) {
              if (is_x) {
                pabc::Vec_IntPush(VecNP[index - 1], std::stoi(position));
                position.clear();
                is_x = false;
              } else {
                pabc::Vec_IntPush(VecNP[index - 1], std::stoi(position));
                position.clear();
              }
            } else {
              continue;
            }
          }
        }
      }
    } else if (line.substr(0, 4) == "PINS") {
      while (std::getline(ifs, line)) {
        if (line.substr(0, 3) == "END") {
          break;
        } else if (line.find("input") != std::string::npos &&
                   line.find("clk") == std::string::npos) {
          // get input position
          std::string::size_type found_1 = line.find("_");
          std::string::size_type found_2 = line.find("+");
          int index;
          std::string res;
          while (found_1 != found_2 - 2) {
            res += line[found_1 + 1];
            found_1++;
          }
          index = std::stoi(res);
          std::getline(ifs, line);
          std::getline(ifs, line);
          bool is_x = true;
          std::string position_input = "";
          for (char c : line) {
            if (std::isdigit(c)) {
              position_input += c;
            } else if (!position_input.empty()) {
              if (is_x) {
                pabc::Vec_IntPush(VecNP[index], std::stoi(position_input));
                position_input.clear();
                is_x = false;
              } else {
                pabc::Vec_IntPush(VecNP[index], std::stoi(position_input));
                position_input.clear();
              }
            } else {
              continue;
            }
          }
        } else if (line.find("output") != std::string::npos) {
          // get input position
          std::string::size_type found_1 = line.find("_");
          std::string::size_type found_2 = line.find("+");
          int index;
          std::string res;
          while (found_1 != found_2 - 2) {
            res += line[found_1 + 1];
            found_1++;
          }
          index = std::stoi(res);
          std::getline(ifs, line);
          std::getline(ifs, line);
          bool is_x = true;
          std::string position_output = "";
          for (char c : line) {
            if (std::isdigit(c)) {
              position_output += c;
            } else if (!position_output.empty()) {
              if (is_x) {
                pabc::Vec_IntPush(VecNP[index + cell_size],
                                  std::stoi(position_output));
                position_output.clear();
                is_x = false;
              } else {
                pabc::Vec_IntPush(VecNP[index + cell_size],
                                  std::stoi(position_output));
                position_output.clear();
              }
            } else {
              continue;
            }
          }
        } else {
          continue;
        }
      }
    } else {
      continue;
    }
  }
}

void npTrans(std::vector<mockturtle::node_position> np, Vec_Int_t **VecNP) {
  for (int i = 1; i < np.size(); i++) {
    pabc::Vec_IntPush(VecNP[i - 1], np[i].x_coordinate);
    pabc::Vec_IntPush(VecNP[i - 1], np[i].y_coordinate);
  }
}

double stime_of_res(std::string lib_file, std::string netlist_file,
                    std::vector<mockturtle::node_position> np) {
  Abc_Ntk_t *pNtk;
  pabc::Abc_Frame_t *pAbc = pabc::Abc_FrameGetGlobalFrame();
  SC_DontUse dont_use = {0};
  SC_Lib *pLib =
      Scl_ReadLibraryFile(pAbc, (char *)(lib_file.c_str()), 1, 0, dont_use);
  ABC_FREE(dont_use.dont_use_list);
  Abc_SclLoad(pLib, (SC_Lib **)&pAbc->pLibScl);
  if (pAbc->pLibScl) {
    Abc_SclInstallGenlib(pAbc->pLibScl, 0, 0, 0);
    Mio_LibraryTransferCellIds();
  }

  if (Abc_FrameReadLibGen() == NULL) {
    Abc_Print(-1, "Cannot read mapped design when the library is not given.\n");
  }
  for (auto &x : netlist_file) {
    if (x == '>' || x == '\\') x = '/';
  }
  pNtk = Io_Read((char *)(netlist_file.c_str()), IO_FILE_VERILOG, 1, 0);

  // set defaults
  int fUseWireLoads = 1;
  int fPrintPath = 0;

  Vec_Int_t **VecNP;  // vector<vector<int>>
  VecNP = ABC_ALLOC(Vec_Int_t *, Abc_NtkNodeNum(pNtk) + Abc_NtkPiNum(pNtk) +
                                     Abc_NtkPoNum(pNtk));
  for (int i = 0;
       i < Abc_NtkNodeNum(pNtk) + Abc_NtkPiNum(pNtk) + Abc_NtkPoNum(pNtk); i++)
    VecNP[i] = Vec_IntAlloc(2);
  phyLS::npTrans(np, VecNP);
  pNtk->vPlace = VecNP;

  for (int j = 0;
       j < Abc_NtkNodeNum(pNtk) + Abc_NtkPiNum(pNtk) + Abc_NtkPoNum(pNtk);
       j++) {
    for (int i = 0; i < Vec_IntSize(VecNP[j]); i++)
      std::cout << Vec_IntEntry(VecNP[j], i) << " ";
    std::cout << std::endl;
  }

  return Abc_SclTimePerformdelay(pLib, pNtk, 0, fUseWireLoads, 0, fPrintPath,
                                 0);
}

}  // NAMESPACE phyLS
