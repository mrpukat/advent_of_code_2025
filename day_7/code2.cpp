#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ranges>
#include <map>

#include "../utils.cpp"
#include "../grid.cpp"

struct coords {
	int x;
	int y;

    bool operator<(const coords& other) const
    {
        if (x < other.x)
            return true;
        if (x > other.x)
            return false;
        return y < other.y;
    }
};

aoc::ull step(aoc::grid &grid, const coords &pos, std::map<coords, aoc::ull> &memory) {

	if(memory.count(pos) != 0) {
		return memory.at(pos);
	}

	if (pos.y + 1 == grid.higth()) {
		grid.set(pos.x, pos.y, '|');
		memory[pos] = 1;

		//grid.print();
		//std::cout << 1 << "------------------" << std::endl;

		return 1;
	}

	aoc::ull res{0};
	if (grid.at(pos.x, pos.y + 1) == '^') {
		
		if (pos.x - 1 >= 0) {
			res += step(grid, {pos.x - 1, pos.y + 1}, memory);
		}
		if (pos.y + 1 != grid.with()) {
			res += step(grid, {pos.x + 1, pos.y + 1}, memory);
		}
	} else {
		res = step(grid, {pos.x, pos.y + 1}, memory);
	}

	grid.set(pos.x, pos.y, '|');
	memory[pos] = res;

	//grid.print();
	//std::cout << res << "------------------" << std::endl;

	return res;
}


aoc::ull process(aoc::grid &grid) {

	coords pos;
	grid.find('S', [&pos](int x, int y){
		pos = {x, y};
	});

	std::map<coords, aoc::ull> memory;
	return step(grid, pos, memory);
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
