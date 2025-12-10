#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <map>

#include "../utils.cpp"

struct node {
	aoc::ll x{0}, y{0};

	bool operator==(const node& other) const {
        return x == other.x && y == other.y;
    }
};

struct area {
	// node Index
	int a{0}, b{0};
	aoc::ull w{0}; // the area

	// I lie here to get a reverse sort
	bool operator<(const area& other) const {
        return w > other.w;
    }
};


namespace aoc {
	struct vector {
		aoc::ll x{0}, y{0};
	};
}

node pre_process(std::string &in) {

	node n;

	aoc::for_all_numbers<aoc::ull>(in, [&n](aoc::ull nr, int, int){
		if(n.x == 0) {
			n.x = nr;
		} else if (n.y == 0) {
			n.y = nr;
		} else {
			assert(false);
		}
	});

	return n;
}

std::vector<area> process(const std::vector<node> &nodes) {

	std::vector<area> areas;

	for (int i{0}; i < nodes.size(); ++i) {
		for (int j{i+1}; j < nodes.size(); ++j) {

			aoc::ull x = std::abs(nodes.at(i).x - nodes.at(j).x) + 1;
			aoc::ull y = std::abs(nodes.at(i).y - nodes.at(j).y) + 1;
			aoc::ull w = x*y;

			areas.push_back({i, j, w});

		}
	}

	std::sort(areas.begin(), areas.end());

	return areas;
}


double cross(const aoc::vector &a, const aoc::vector &b) {
	return a.x * b.y - a.y * b.x;
}

const double REALY_LOW_NUMBER = 1e-9;

double dot(const aoc::vector &a, const aoc::vector &b) {
	return a.x * b.x + a.y * b.y;
}

double norm_sq(aoc::vector v) {
	return v.x * v.x + v.y * v.y;
}

// Angel between p->q and p->r
double angle(const node &p, const node &q, const node &r) {
	aoc::vector a{p.x - q.x, p.y - q.y};
	aoc::vector b{p.x - r.x, p.y - r.y};
	return std::acos(dot(a, b) / std::sqrt(norm_sq(a) * norm_sq(b)));
}

// Is there a conter clockwise turn between q and r
// From p perpective
bool ccw(const node &p,const node &q,const node &r) {
	aoc::vector a{q.x - p.x, q.y - p.y};
	aoc::vector b{r.x - p.x, r.y - p.y};
	return cross(a, b) >= 0;
}

bool isInsideBox(const area &a, const node &n, const std::vector<node> &nodes) {

	if (n.x <= nodes.at(a.a).x && n.x <= nodes.at(a.b).x) {
		return false;
	}

	if (n.x >= nodes.at(a.a).x && n.x >= nodes.at(a.b).x) {
		return false;
	}


	if (n.y <= nodes.at(a.a).y && n.y <= nodes.at(a.b).y) {
		return false;
	}

	if (n.y >= nodes.at(a.a).y && n.y >= nodes.at(a.b).y) {
		return false;
	}

	return true;
}

// MEMORYSATION can be done for speedup
bool inInsidePolygon(const node &n, const std::vector<node> &nodes) {

	double sum{0};
	for (int i{0}; i < nodes.size()-1; ++i) {

		// Edge case where node == areaNode
		if (nodes.at(i) == n) {
			return true;
		}


		if(ccw(n, nodes.at(i), nodes.at(i + 1))) {
			sum += angle(n, nodes.at(i), nodes.at(i + 1));
		} else {
			sum -= angle(n, nodes.at(i), nodes.at(i + 1));
		}
	}

	//std::cout << std::fabs(std::fabs(sum) - 2*M_PI) << std::endl;
	return std::fabs(std::fabs(sum) - 2*M_PI) < REALY_LOW_NUMBER;
}

bool BoxIntersect(const area &box, const node &nodeA, const node &nodeB, const std::vector<node> &nodes) {

	aoc::ll boxMinX = std::min(nodes.at(box.b).x, nodes.at(box.a).x);
	aoc::ll boxMinY = std::min(nodes.at(box.b).y, nodes.at(box.a).y);
	aoc::ll boxMaxX = std::max(nodes.at(box.b).x, nodes.at(box.a).x);
	aoc::ll boxMaxY = std::max(nodes.at(box.b).y, nodes.at(box.a).y);

	aoc::ll nodeMinX = std::min(nodeA.x, nodeB.x);
	aoc::ll nodeMinY = std::min(nodeA.y, nodeB.y);
	aoc::ll nodeMaxX = std::max(nodeA.x, nodeB.x);
	aoc::ll nodeMaxY = std::max(nodeA.y, nodeB.y);


	// Vert
	if (nodeMaxX == nodeMinX) {

		if(!(nodeMaxX < boxMaxX && nodeMaxX > boxMinX)) {
			return false;
		}

		if(nodeMinY >= boxMaxY) {
			return false;
		}

		if(nodeMaxY <= boxMinY) {
			return false;
		}

	// Heri
	} else {

		if(!(nodeMaxY < boxMaxY && nodeMaxY > boxMinY)) {
			return false;
		}

		if(nodeMinX >= boxMaxX) {
			return false;
		}

		if(nodeMaxX <= boxMinX) {
			return false;
		}


	}

	return true;
}

aoc::ull process2(std::vector<node> &nodes, const std::vector<area> &areas) {

	nodes.push_back(nodes.at(0));

	for (const area &a : areas) {

		bool correct{true};
		for (int i{0}; i < nodes.size()-1; ++i) {
			correct = correct && !isInsideBox(a, nodes.at(i), nodes);
			correct = correct && !BoxIntersect(a, nodes.at(i), nodes.at(i+1), nodes);
			if (!correct) {
				break;
			}
		}

		if (!correct) {
			continue;
		}

		correct = correct && inInsidePolygon({nodes.at(a.a).x, nodes.at(a.b).y}, nodes);

		if (!correct) {
			continue;
		}

		correct = correct && inInsidePolygon({nodes.at(a.b).x, nodes.at(a.a).y}, nodes);

		if (!correct) {
			continue;
		}

		// DID NOT HELP (test: if box is outside but all nodes are on the edge)
		aoc::ll minX = std::min(nodes.at(a.b).x, nodes.at(a.a).x);
		aoc::ll minY = std::min(nodes.at(a.b).y, nodes.at(a.a).y);
		node middelPoint = {
			minX + std::abs(nodes.at(a.b).x - nodes.at(a.a).x)/2,
			minY + std::abs(nodes.at(a.b).y - nodes.at(a.a).y)/2
		};
		correct = correct && inInsidePolygon(middelPoint, nodes);

		if (correct) {
			return a.w;
		}
	}

	assert(false);

	return 0;
}


int main() {
	std::string line;
	std::ifstream file_in;

	std::vector<node> nodes;

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			nodes.push_back(pre_process(line));
		}
		file_in.close();
	}

	std::vector<area> areas{process(nodes)};
	std::cout << "Part 1: " << areas.at(0).w << std::endl;
	std::cout << "Part 2: " << process2(nodes, areas) << std::endl;

	return 0;
}
