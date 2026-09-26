#include "sjb/rules.hpp"
#include "sjb/game.hpp"
#include <algorithm>

namespace sjb {

long long cross(const Point& a, const Point& b, const Point& c) {
    return 1LL * (b.x - a.x) * (c.y - a.y)
         - 1LL * (b.y - a.y) * (c.x - a.x);
}

// Check if point p lies on segment a-b
bool onSegment(const Point& a, const Point& b, const Point& p) {
    return std::min(a.x, b.x) <= p.x && p.x <= std::max(a.x, b.x) &&
           std::min(a.y, b.y) <= p.y && p.y <= std::max(a.y, b.y) &&
           cross(a, b, p) == 0;
}

// Check if two edges/segments intersect
bool segmentsIntersect(const Edge& e1, const Edge& e2) {
    Point p1 = e1.from, q1 = e1.to;
    Point p2 = e2.from, q2 = e2.to;

    long long o1 = cross(p1, q1, p2);
    long long o2 = cross(p1, q1, q2);
    long long o3 = cross(p2, q2, p1);
    long long o4 = cross(p2, q2, q1);

    // General case: points are on opposite sides of each other's line
    if (((o1 > 0 && o2 < 0) || (o1 < 0 && o2 > 0)) &&
        ((o3 > 0 && o4 < 0) || (o3 < 0 && o4 > 0))) {
        return true;
    }

    // Special cases: collinear points touching the segment
    if (o1 == 0 && onSegment(p1, q1, p2)) return true;
    if (o2 == 0 && onSegment(p1, q1, q2)) return true;
    if (o3 == 0 && onSegment(p2, q2, p1)) return true;
    if (o4 == 0 && onSegment(p2, q2, q1)) return true;

    return false;
}

std::vector<Move> legal_moves(const GameState& state) {
    std::vector<Move> results;
    for (auto& node : state.currentNodesPlayerA) {
        for (int dx = -3; dx <= 3; dx++) {
            if (dx == 0) continue;
            if (node.x + dx < 0 || node.x + dx >= 19) continue;
            for (int dy = -3; dy <= 3; dy++) {
                if (dy == 0) continue;
                if (node.y + dy < 0 || node.y + dy >= 19) continue;
                Point point = { node.x + dx, node.y + dy };
                Edge move = {node, point};
                bool isIllegal = false;
                for (auto& edge : state.edgesPlayerA) {
                    if (segmentsIntersect(edge, move)) {
                        isIllegal = true;
                        break;
                    }
                }
                if (isIllegal) continue;
                int countOfCrossedEnemyLines = 0;
                for (auto& edge : state.edgesPlayerB) {
                    if (segmentsIntersect(edge, move)) {
                        countOfCrossedEnemyLines++;
                    }
                    if (countOfCrossedEnemyLines >= 2) {
                        break;
                    }
                }
                if (countOfCrossedEnemyLines >= 2) continue;
                results.push_back(move);
            }
        }
    }
    return results;
}

void apply_move(GameState& /*state*/, const Move& /*move*/) {
    // TODO
}

void undo_move(GameState& /*state*/, const Move& /*move*/) {
    // TODO
}

bool is_player_a_move(const GameState &state) {
    if (state.turnNum == 0) {
        return true;
    }
    return ((state.turnNum - 1) / 2) % 2 == 1;
}

bool is_terminal(const GameState& state) {
    return state.turnNum >= 120;
}

}  // namespace sjb
