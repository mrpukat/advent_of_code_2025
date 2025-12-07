#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ranges>
#include <queue>

#include "../utils.cpp"
#include "../grid.cpp"

struct coords {
	int x;
	int y;
};

int step(aoc::grid &grid, std::queue<coords> &process, const coords &pos) {
	if (pos.y + 1 == grid.higth()) {
		return 0;
	}

	if (grid.at(pos.x, pos.y + 1) == '|') {
		return 0;
	}

	if (grid.at(pos.x, pos.y + 1) == '^') {
		
		if (pos.x - 1 >= 0) {
			grid.set(pos.x -1, pos.y + 1, '|');
			process.push({pos.x -1, pos.y + 1});
		}
		if (pos.y + 1 != grid.with()) {
			grid.set(pos.x + 1, pos.y + 1, '|');
			process.push({pos.x + 1, pos.y + 1});
		}

		return 1;
	} else {
		grid.set(pos.x, pos.y + 1, '|');
		process.push({pos.x, pos.y + 1});
	}

	return 0;
}


int process(aoc::grid &grid) {

	std::queue<coords> process;
	int splits{0};

	grid.find('S', [&process](int x, int y){
		process.push({x, y});
	});

	while (!process.empty()) {
		coords pos = process.front();
		process.pop();

		splits += step(grid, process, pos);
	}

	return splits;
}


int main() {
	std::string line;
	std::ifstream file_in;

	aoc::grid grid{};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			grid.append_line(line);
		}
		file_in.close();
	}

	std::cout << process(grid) << std::endl;

	return 0;
}
