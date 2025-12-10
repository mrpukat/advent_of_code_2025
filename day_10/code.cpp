#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <queue>

#include "../utils.cpp"


struct instructions {
	std::string goal;
	std::vector<std::vector<int>> buttons; // figure our correct buttion
	std::string state;
};

instructions pre_process(std::string &in) {

	instructions inst;

	aoc::for_all_substrings(in, " ", [&inst](std::string str){

		if(str.find("[") != std::string::npos) {
			str.pop_back();
			str.erase(0, 1);
			inst.goal = str;
		} else if (str.find("(") != std::string::npos) {
			inst.buttons.push_back({});
			aoc::for_all_numbers<int>(str,[&inst](int nr, int, int){
				inst.buttons.back().push_back(nr);
			});
		}

		// TODO voltage

	});

	inst.state = std::string(inst.goal.size(), '.');

	return inst;
}

std::string pressButtion(std::string state, std::vector<int> button) {

	for(int i : button) {
		if (state.at(i) == '.') {
			state.at(i) = '#';
		} else {
			state.at(i) = '.';
		}
	}

	return state;

}

aoc::ull process(const instructions &inst) {

	std::queue<std::pair<std::string,int>> states;

	states.push({inst.state, 0});

	while(!states.empty()) {

		std::pair<std::string, int> a = states.front();
		states.pop();

		int depth = a.second + 1;

		for (std::vector<int> buttion : inst.buttons) {
			std::string newState = pressButtion(a.first, buttion);

			if (newState == inst.goal) {
				return depth;
			}

			states.push({newState, depth});
		}
	}

	assert(false);

	return 0;
}

int main() {
	std::string line;
	std::ifstream file_in;

	aoc::ull sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			instructions intr = pre_process(line);
			sum += process(intr);
			//std::cout << sum << std::endl;
		}
		file_in.close();
	}

	std::cout << "Part 1: " << sum << std::endl;

	return 0;
}
