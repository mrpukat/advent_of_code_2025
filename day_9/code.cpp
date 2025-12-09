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
};

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

aoc::ull process(const std::vector<node> &nodes) {

	aoc::ull larges_aria{0};

	for (int i{0}; i < nodes.size(); ++i) {
		for (int j{i+1}; j < nodes.size(); ++j) {

			aoc::ull x = std::abs(nodes.at(i).x - nodes.at(j).x) + 1;
			aoc::ull y = std::abs(nodes.at(i).y - nodes.at(j).y) + 1;
			aoc::ull aria = x*y;

			if (aria > larges_aria) {
				//std::cout << i << " " << j << " " << aria << std::endl;
				larges_aria = aria;
			}

		}
	}

	return larges_aria;
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

	std::cout << process(nodes) << std::endl;

	return 0;
}
