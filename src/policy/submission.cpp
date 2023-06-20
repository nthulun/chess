#include <cstdlib>

#include "../state/state.hpp"
#include "./submission.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Submission::get_move(State *state, int depth){
  state->get_legal_actions();
  
  int maxval = -2e9;
  auto actions = state->legal_actions;
  Move nextmove;
  for(auto it : actions){
    int val = alphabeta(state->next_state(it), depth - 1, -2e9, 2e9, 0);
    if(val > maxval){
        maxval = val;
        nextmove = it;
    }
  }
  return nextmove;
}

int Submission::alphabeta(State * node, int depth, int alpha, int beta, int maximizingPlayer){
    if(!depth && !maximizingPlayer) return node->evaluate();
    if(!depth && maximizingPlayer) return - node->evaluate();

    if(!node->legal_actions.size() && !maximizingPlayer) return node->evaluate();
    if(!node->legal_actions.size() && maximizingPlayer) return - node->evaluate();

    auto actions = node->legal_actions;

    if(maximizingPlayer){
        int maxval = -2e9;
        for(auto it : actions){
            int val = alphabeta(node->next_state(it), depth - 1, alpha, beta, 0);
            if(val > maxval) maxval = val;
            if(maxval > alpha) alpha = maxval;
            if(alpha >= beta) break;
        }
        return maxval;
    }else{
        int minval = 2e9;
        for(auto it : actions){
            int val = alphabeta(node->next_state(it), depth - 1, alpha, beta, 1);
            if(beta < minval) minval = beta;
            if(val < beta) beta = val;
            if(beta <= alpha) break;
        }
        return beta;
    }
}