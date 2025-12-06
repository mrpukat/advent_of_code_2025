#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ranges>

#include "../utils.cpp"
#include "../grid.cpp"


int process(aoc::grid &grid) {

	int res{0};

	for(int x{0}; x < grid.with(); ++x) {
		for(int y{0}; y < grid.higth(); ++y) {

			if(grid.at(x, y) != '@') {
				continue;
			}

			int papper{0};
			grid.for_node_neighbour(x, y, true, '@', [&papper](int, int){
				papper++;
			});
			
			if(papper < 4) {
				res++;
				grid.set(x, y, 'x');
			}
		}
	}

	grid.print();

	return res;
}


int main() {
	std::string line;
	std::ifstream file_in;

	aoc::ull sum{0};
	aoc::grid grid{};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			grid.append_line(line);
		}
		file_in.close();
	}

	aoc::ull oldSum{};
	do {
		oldSum = sum;
		sum += process(grid);
	} while(oldSum != sum);

	std::cout << sum << std::endl;

	return 0;
}
