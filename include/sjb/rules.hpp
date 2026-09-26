#pragma once

#include <vector>

#include "sjb/game.hpp"

namespace sjb {

// All legal moves for the side to move in `state`.
std::vector<Move> legal_moves(const GameState& state);

// Applies `move` to `state` in place. Caller must ensure it is legal.
// TODO: design this (and undo_move) as a cheap make/unmake pair instead of
// copying the whole state, once you're using this in a search.
void apply_move(GameState& state, const Move& move);

// Undoes the most recent apply_move(state, move).
void undo_move(GameState& state, const Move& move);

bool is_player_a_move(const GameState& state);

// True once the game has ended (win, loss, draw, ...).
bool is_terminal(const GameState& state);

}  // namespace sjb
