#pragma once

#include "sjb/bot.hpp"

namespace sjb::bots {

class GreedyBot : public Bot {
public:
    Move choose_move(const GameState& state) override;
};

}  // namespace sjb::bots
