#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ranges>

#include "../utils.cpp"

bool repetes(const std::string &str, int parts) {

	if (str.size() % parts != 0) {
		return false;
	}

	int len = str.size() / parts;

	std::string repeable = str.substr(0, len);
	bool repete{true};
	
	for (int j{len}; j < str.size(); j += len) {
		repete = repete && (repeable == str.substr(j, len));
	}

	return repete;
}

bool checkValid(std::string str){
	return repetes(str, 2);
}

bool checkValid2(std::string str){

	for (int i{2}; i <= str.size(); ++i) {
		if(repetes(str, i)) {
			return true;
		}

	}

	return false;
}

aoc::ull process(std::string &in) {

	aoc::ull sum{0};

	aoc::for_all_substrings(in, ",", [&sum](std::string&& substr){

		std::vector<aoc::ull> tmpContainer;

		if(substr.empty()) {
			return;
		}

		aoc::for_all_substrings(substr, "-", [&tmpContainer](std::string&& nr ) {
			tmpContainer.push_back(std::stoull(nr));
		});

		assert(tmpContainer.size() == 2);

		for (aoc::ull i{tmpContainer.at(0)}; i <= tmpContainer.at(1); ++i) {
			if (checkValid2(std::to_string(i))) {
				sum += i;
			}
		}

	});


	return sum;
}


int main() {
	std::string line;
	std::ifstream file_in;

	aoc::ull sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			sum += process(line);
		}
		file_in.close();
	}

	std::cout << sum << std::endl;

	return 0;
}
