#pragma once

#include "sjb/bot.hpp"
#include "sjb/game.hpp"

namespace sjb {

// Outcome of a single simulated game.
// TODO: flesh out (winner, move count, replay log, ...).
struct GameResult {};

// Plays one game between `first` and `second`, starting from `state`.
GameResult run_game(GameState state, Bot& first, Bot& second);

}  // namespace sjb
