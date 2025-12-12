#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

#include "../utils.cpp"
#include "../grid.cpp"

bool process(std::string &in, const std::vector<aoc::ull> &test) {
	
	aoc::ull size{0};
	aoc::ull lower{0};
	aoc::ull higher{0};
	aoc::ull i{0};

	aoc::for_all_substrings(in, " ", [&size, &lower, &higher, &i, &test](std::string str){

		if (size == 0) {
			aoc::for_all_numbers<aoc::ull>(str, [&size](aoc::ull nr, aoc::ull, aoc::ull){
				if (size == 0) {
					size = nr;
				} else {
					size *= nr;
				}
			});
			return;
		}

		lower += std::stoi(str) * test.at(i);
		higher += std::stoi(str) * 9;
		i++;

	});

	if (lower > size) {
		return false;
	}
	if (higher <= size) {
		return true;
	}

	std::cout << "Need more processing" << std::endl;

	return false; // TMP
}

//"41x36: 23 31 20 25 24 32"
//24

int main() {
	std::string line;
	std::ifstream file_in;

	aoc::ull sum{0};
	std::vector<aoc::grid> preseents;
	std::vector<aoc::ull> test = {6, 7, 7, 7, 5, 7};


	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {

			if(line.size() == 2) {
				preseents.push_back({});
				continue;
			}

			if(line.size() == 3) {
				preseents.back().append_line(line);
				continue;
			}

			if(line.empty()) {				
				continue;
			}

			if(line.size() > 10) {
				if (process(line, test)) {
					sum++;
				}
			}
		}
		file_in.close();
	}

	std::cout << sum << std::endl;

	return 0;
}
