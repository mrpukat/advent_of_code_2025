#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ranges>

#include "../utils.cpp"

std::string process(std::string &in, int start, int depth) {

	if (depth == 0) {
		return "";
	}

	char flargest{'.'};
	int pos{0};

	for (int i{start}; i + depth <= in.size(); ++i) {
		if (in.at(i) > flargest) {
			flargest = in.at(i);
			pos = i + 1;
		} 
	}

	assert(flargest != '.');

	std::string res{flargest};
	res.append(process(in, pos, depth -1));

	return res;
}


int main() {
	std::string line;
	std::ifstream file_in;

	aoc::ull sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			sum += std::stoull(process(line, 0, 12)); // Change to 12
		}
		file_in.close();
	}

	std::cout << sum << std::endl;

	return 0;
}
