#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ranges>

#include "../utils.cpp"

void pre_process(std::string &in, std::vector<std::vector<int>> &math_grid) {

	if (math_grid.empty()) {
		int size{0};
		aoc::for_all_numbers<int>(in, [&math_grid, &size](int nr, int, int){
			++size;
		});
		math_grid.insert(math_grid.begin(), size, std::vector<int>{});
	}

	int i{0};
	aoc::for_all_numbers<int>(in, [&math_grid, &i](int nr, int, int){
		math_grid.at(i).push_back(nr);
		++i;
	});
}

aoc::ull performOpperation(aoc::ull l, aoc::ull r, char opperation){

	if (l == 0) {
		return r;
	}

	switch (opperation)
	{
	case '*':
		return l * r;
		break;
	case '+':
		return l + r;
		break;
	default:
		std::cout << opperation << std::endl;
		assert(false);
	}

}


aoc::ull process(std::string &in, const std::vector<std::vector<int>> &math_grid) {

	int i{0};
	aoc::ull res{0};
	aoc::for_all_substrings(in, " ", [&math_grid, &i, &res](std::string opperator){

		if (opperator.empty()) {
			return;
		}

		aoc::ull subRes{0};
		assert(opperator.size() == 1);
		for (int nr : math_grid.at(i)) {
			subRes = performOpperation(subRes, nr, opperator.at(0));
		}

		res += subRes;
		std::cout << subRes << std::endl;
		++i;
	});

/*
	std::cout<< in << std::endl;
	for (const std::vector<int> &sub : math_grid) {
		std::copy(sub.begin(), sub.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
	}
*/


	return res;
}


int main() {
	std::string line;
	std::ifstream file_in;

	std::vector<std::vector<int>> math_grid;

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			if (!std::any_of(line.begin(), line.end(), ::isdigit)) {
				break;
			}
			pre_process(line, math_grid);
		}
		file_in.close();
	}

	std::cout << process(line, math_grid) << std::endl;

	return 0;
}
