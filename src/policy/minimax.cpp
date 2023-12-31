#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
  state->get_legal_actions();
  
  int maxval = -2e9;
  auto actions = state->legal_actions;
  Move nextmove;
  for(auto it : actions){
    int val = minimax(state->next_state(it), depth - 1, 0);
    if(val > maxval){
        maxval = val;
        nextmove = it;
    }
  }
  return nextmove;
}

int Minimax::minimax(State * node, int depth, int maximizingPlayer){
    if(!depth && !maximizingPlayer) return node->evaluate();
    if(!depth && maximizingPlayer) return - node->evaluate();

    if(!node->legal_actions.size() && !maximizingPlayer) return node->evaluate();
    if(!node->legal_actions.size() && maximizingPlayer) return - node->evaluate();

    auto actions = node->legal_actions;

    if(maximizingPlayer){
        int maxval = -2e9;
        for(auto it : actions){
            int val = minimax(node->next_state(it), depth - 1, 0);
            if(val > maxval) maxval = val;
        }
        return maxval;
    }else{
        int minval = 2e9;
        for(auto it : actions){
            int val = minimax(node->next_state(it), depth - 1, 1);
            if(val < minval) minval = val;
        }
        return minval;
    }
}