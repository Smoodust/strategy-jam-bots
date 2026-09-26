#pragma once

// TODO: define the actual game here.

#include <vector>
namespace sjb {

struct Point {
	int x;
	int y;
};

struct Edge {
	Point from;
	Point to;
};

struct DiscardedEdge {
	Edge edge;
	int turnWhen;
};

struct GameState {
	int turnNum;
	double scorePlayerA;
	double scorePlayerB;
	std::vector<Point> currentNodesPlayerA;
	std::vector<Edge> edgesPlayerA; // edges would be presented in chronological way
	std::vector<DiscardedEdge> discardedEdgesPlayerA;
	std::vector<Point> currentNodesPlayerB;
	std::vector<Edge> edgesPlayerB;
	std::vector<DiscardedEdge> discardedEdgesPlayerB;
};

using Move = Edge;

}  // namespace sjb
