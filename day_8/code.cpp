#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <map>

#include "../utils.cpp"

struct node {
	aoc::ull x{0}, y{0}, z{0};
};

struct edge {
	int a{0}, b{0};
	aoc::ull w{0};

	bool operator<(const edge& other) const {
        return w < other.w;
    }
};


node pre_process(std::string &in) {

	node n;

	aoc::for_all_numbers<aoc::ull>(in, [&n](aoc::ull nr, int, int){
		if(n.x == 0) {
			n.x = nr;
		} else if (n.y == 0) {
			n.y = nr;
		} else if (n.z == 0) {
			n.z = nr;
		} else {
			assert(false);
		}
	});

	return n;
}

std::vector<edge> process_nodes(const std::vector<node> &nodes) {

	std::vector<edge> edges;

	for (int i{0}; i < nodes.size(); ++i) {
		for (int j{i+1}; j < nodes.size(); ++j) {

			aoc::ull d = 0;
			d += (nodes.at(i).x - nodes.at(j).x) * (nodes.at(i).x - nodes.at(j).x);
			d += (nodes.at(i).y - nodes.at(j).y) * (nodes.at(i).y - nodes.at(j).y);
			d += (nodes.at(i).z - nodes.at(j).z) * (nodes.at(i).z - nodes.at(j).z);

			edges.push_back({i, j, d});
		}
	}

	std::sort(edges.begin(), edges.end());

	return edges;
}

class UnionFind {
public:
	UnionFind(int N) : rank(N, 1), parent(N) {
		std::iota(parent.begin(), parent.end(), 0);
	}

	int findSet(int i) {
		return (parent.at(i) == i) ? i : (parent.at(i) = findSet(parent.at(i))); 
	}

	bool isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
	}

	void unionSet(int i, int j) {
		if (!isSameSet(i, j)) {
			int x = findSet(i);
			int y = findSet(j);

			if (rank.at(x) > rank.at(y)) {
				parent.at(y) = x;
				// Not part: for aoc
				rank.at(x) += rank.at(y);
				rank.at(y) = 0;
			} else {
				parent.at(x) = y;
				// Not part: for aoc
				rank.at(y) += rank.at(x); 
				rank.at(x) = 0;
			}
		}
	}


	std::vector<int> parent, rank;

};

aoc::ull process(const std::vector<edge> &edges, int N, int iter) {

	UnionFind uf(N);
	for (int i{0}; i < edges.size(); ++i) {
		const edge &E = edges.at(i);

		std::cout << "Testing: " << E.a << " and " << E.b << std::endl;
		if (!uf.isSameSet(E.a, E.b)) {
			std::cout << "Union!" << std::endl;
			uf.unionSet(E.a, E.b);
		}

		iter--;
		if(iter == 0 && iter != -1) {
			break;
		}

	}

	std::vector<int> rankList = uf.rank;

	std::sort(rankList.begin(), rankList.end());

	std::copy(rankList.begin(), rankList.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	return rankList.back() * rankList.at(rankList.size()-2) * rankList.at(rankList.size()-3);
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

	std::vector<edge> edges = process_nodes(nodes);

	std::cout << process(edges, nodes.size(), 1000) << std::endl;

	return 0;
}
