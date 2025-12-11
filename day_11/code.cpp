#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

#include "../utils.cpp"

void pre_process(std::string &in, std::map<std::string, std::vector<std::string>> &graph) {

	std::string node;
	aoc::for_all_substrings(in, ":", [&node, &graph](std::string str){

		if (node.empty()) {
			node = str;
			graph[node] = {};
			return;
		}

		aoc::for_all_substrings(str, " ", [&node, &graph](std::string str){

			if(str.empty()) {
				return;
			}

			graph[node].push_back(str);
		});
	});
}

struct state {
	bool foundA, foundB;
	std::string pos;

	    bool operator<(const state& other) const {
        if (foundA != other.foundA) return foundA < other.foundA;
        if (foundB != other.foundB) return foundB < other.foundB;
        return pos < other.pos;
    }
};

aoc::ull process(state location, const std::map<std::string, std::vector<std::string>> &graph, std::map<state, aoc::ull> &memory) {
	
	if (location.pos == "out") {
		if (location.foundA && location.foundB) {
			memory[location] = 1;
			return 1;
		} else {
			memory[location] = 0;
			return 0;
		}
	}

	if(location.pos == "fft") {
		location.foundA = true;
	}
	if(location.pos == "dac") {
		location.foundB = true;
	}

	aoc::ull sum{0};

	for (std::string node : graph.at(location.pos)) {

		state newLocation = location;
		newLocation.pos = node;

		if (memory.count(newLocation) != 0) {
			sum += memory.at(newLocation);
		} else {
			sum += process(newLocation, graph, memory);
		}
	}

	memory[location] = sum;
	return sum;
}

int main() {
	std::string line;
	std::ifstream file_in;

	aoc::ull sum{0};
	std::map<std::string, std::vector<std::string>> graph;

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			pre_process(line, graph);
		}
		file_in.close();
	}

	std::map<state, aoc::ull> memory;

	std::cout << process({false, false, "svr"}, graph, memory) << std::endl;

	return 0;
}
