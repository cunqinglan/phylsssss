#pragma once

#include <cstdint>
#include <limits>
#include <iostream>
#include <unordered_map>
#include <assert.h>
#include <vector>
#include <random>

namespace MCTS{

class SimpleAction
{
public:
  static const size_t action_size { 3 };
  enum Action{
    delta_delay,
    delta_area,
    delta_wirelength
  };
  Action get_action(int const& choice)
  {
    if (choice < 0 || choice >= action_size) 
    {
      std::cerr << "Exceeded action amount boundary\n";
      throw std::out_of_range("Invalid action choice");
    }
    switch (choice)
    {
    case 0:
      return Action::delta_delay;
    case 1:
      return Action::delta_area;    
    case 2:
      return Action::delta_wirelength;
    default:{
      std::cerr<<"axceed action amount boundry\n";
      exit(0);
    } 
    }
  }
};

struct State
{
  // long term effect
  double Q {0};
  // times of a node has been visited
  int N {0};
  // exploration set to encourage exploration
  double U {1.0};
  // reward
  int R {0};
  // blocked if the node is being visited in parallel
  int B{0};
  // blocked child
  int blocked_child{0};
  // if the node is visited, it's 1, vice versus
  bool visited { false };
  // if the node is the root node
  bool is_root {false};
  // if search should be terminated
  bool terminal_flag {false};

  // position of the state
  std::vector<State> children;
  // father node
  State* father { nullptr };
  // index of the node in state network
  std::string position = "R";

  bool terminal()
  {
    return terminal_flag;
  }
};

struct MCTS_para
{
  uint32_t search_iteration { 10 };
  uint32_t level_search { 10 };
  uint32_t sequence_length { 10 };
  uint32_t action_size { 3 };
  double PUCT { 500 };
  double lambda { 0.4 };
};

/*  The input implement should has following funtion:
      reward = take_action(int action) --> with given action, take action and return a reward
      terminal() --> if the agent should be terminated 
    The Position should has following function:
*/
template<typename Implement>
class MCTS_impl
{
  using DictState = std::unordered_map<std::string, State*>;
  using VecSequence = std::vector<char>;
public: 
  explicit MCTS_impl(Implement& MCTS_imple, MCTS_para const& ps): imple(MCTS_imple), param(ps), \
                                                action_size(ps.action_size), search_length_limit(param.sequence_length)
  {
    initialize_MCTS();
  };

  void run()
  {
    std::cout<<"run\n";
    State* node_ptr = &root;
    imple.initialize();
    for ( uint32_t i = 0; i < param.search_iteration; i++ )
    {
      std::cout << "Iteration " << i << std::endl;
      iter(root);
      std::cout << "Current state: " << imple.get_state() << ", Reward: " << imple.get_reward() << std::endl;
    }
  }

  Implement* get()
  {
    if ( !imple.terminal()) {
      std::cerr<<"implement has not terminated!\n";
    }
    return &imple;
  }
private:
  // Initialize nodes in MCTS
  void initialize_MCTS()
  {
    std::cout<<"initialize_mcts\n";
    root.is_root = true;
  }

  // produce a gaussian noise distributed by normal distribution
  template<typename T>
  double gaussian_rand(T m = 0.0, T v = 1)
  {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::normal_distribution<T> gaussian(m, v);

    return gaussian(gen);
  }

  void init_node(State& node)
  {
    for (int i = 0; i < action_size; i++)
    {
      State& child = node.children.emplace_back();
      child.U += gaussian_rand(0.0, 0.2);
    }
  }

  double getValue(State const& node)
  {
    return (node.R + node.Q + node.U);
  }

  int bestAction(State const& node)
  {
    double best_value = std::numeric_limits<double>::min();
    int best_action = -1;
    int crt = -1;
    for (auto const& child : node.children)
    {
      crt++;
      double value = getValue(child);
      if ( value > best_value )
      {
        best_value = value;
        best_action = crt;
      }
    }
    return best_action;
  }

  void simulate(State& node)
  { 
    // generate a seed of random integer
    init_node(node);
  }

  State* iter(State& node)
  {
    std::cout<<"iter\n";
    int i = 0;
    State* res = &node;
    State* r;
    do{
      r = res;
      res = forward(* res);
      i++;
    } while (!r->terminal() && i < search_length_limit);

    if (!res->terminal())
    {
      while (!res->is_root || res->father != nullptr) 
      {
        res = backward(*res);
      }     
    }
    imple.reinit();
    return res;
  }

  // output final result of the implement
  

  // search forward for aquiring reward
  State* forward(State& node)
  {
    if (!node.visited)
    {
      init_node(node);
      node.visited = true;
    }

    int action = bestAction(node);
    if (action < 0)
    {
      std::cerr << "failed to choose an action\n";
      throw std::out_of_range("Not select any choice");
    }
    // the action is an integer
    double reward = imple.take_action(action);
    node.terminal_flag = imple.terminal();

    State& picked_child = node.children[action];
    picked_child.R = reward;
    std::string position = node.position + std::to_string(action);

    // expand a new node if it's unvisited
    if (!picked_child.visited)
    {
      if (state_ntk.find(position) == state_ntk.end())
      {
        picked_child.position = position;  // 设置子节点的位置
        picked_child.father = &node;       // 设置父节点
        state_ntk[position] = &picked_child;
      }
      else
      {
        std::cerr << "node is unvisited but has been in state ntk\n";
        throw std::out_of_range("Invalid action choice");
      }
    }
    return &picked_child;
  }

  State* backward(State& node)
  {
    State* father = node.father;
    father->Q = (node.Q + node.R) * param.lambda;
    node.N++;
    return father;
  }

  Implement& imple;
  MCTS_para const& param;
  DictState state_ntk;
  VecSequence sequence;
  State root;
  int action_size;
  int search_length_limit;
};
} 