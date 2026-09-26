#pragma once

#include "sjb/game.hpp"

namespace sjb {

// Common interface every bot (random, greedy, heuristic, minimax, ...)
// implements. The simulator only ever talks to a bot through this.
class Bot {
public:
    virtual ~Bot() = default;

    // Given the current state, return the move this bot wants to play.
    // TODO: thread a time budget through here once you know the
    // competition's per-move time limit.
    virtual Move choose_move(const GameState& state) = 0;
};

}  // namespace sjb
