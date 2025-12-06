#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ranges>

#include "../utils.cpp"
#include "../grid.cpp"

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


aoc::ull process(std::string &in, const aoc::grid &math_grid) {

	math_grid.print();

	int x{0};
	aoc::ull res{0};
	aoc::for_all_substrings(in, " ", [&math_grid, &x, &res](std::string opperator){

		if (opperator.empty()) {
			return;
		}

		std::vector<int> equation;
		std::vector<char> preString;

		do {
			preString.clear();

			for (int y{0}; y < math_grid.higth(); ++y) {
				if (math_grid.at(x, y) == ' ') {
					continue;
				}

				preString.push_back(math_grid.at(x, y));
			}
			++x;
			std::string str(preString.begin(), preString.end());
			std::cout << x << ": " << str << std::endl;

			if (str.empty()) {
				break;
			}


			equation.push_back(std::stoi(str));
//			std::copy(equation.begin(), equation.end(), std::ostream_iterator<int>(std::cout, " "));
//			std::cout << std::endl;
		} while (x < math_grid.with());


		aoc::ull subRes{0};
		std::cout << "opperator: " << opperator << std::endl;
		assert(opperator.size() == 1);
		for (int nr : equation) {
			subRes = performOpperation(subRes, nr, opperator.at(0));
		}


		res += subRes;
//		std::cout << subRes << std::endl;

	});

	return res;
}


int main() {
	std::string line;
	std::ifstream file_in;

	aoc::grid math_grid;

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			if (!std::any_of(line.begin(), line.end(), ::isdigit)) {
				break;
			}
			math_grid.append_line(line);
		}
		file_in.close();
	}

	std::cout << process(line, math_grid) << std::endl;

	return 0;
}
