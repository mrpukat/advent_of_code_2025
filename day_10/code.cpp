#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <queue>
#include <map>

#include "../utils.cpp"


struct instructions {
	std::string ligthGoal;
	std::string ligthState;
	std::vector<std::vector<int>> buttons; // figure our correct buttion
	std::vector<int> woltState;
	std::vector<int> woltGoal;
};

instructions pre_process(std::string &in) {

	instructions inst;

	aoc::for_all_substrings(in, " ", [&inst](std::string str){

		if(str.find("[") != std::string::npos) {
			str.pop_back();
			str.erase(0, 1);
			inst.ligthGoal = str;
		} else if (str.find("(") != std::string::npos) {
			inst.buttons.push_back({});
			aoc::for_all_numbers<int>(str,[&inst](int nr, int, int){
				inst.buttons.back().push_back(nr);
			});
		} else if (str.find("{") != std::string::npos) {
			aoc::for_all_numbers<int>(str,[&inst](int nr, int, int){
				inst.woltGoal.push_back(nr);
			});
		}

	});

	inst.ligthState = std::string(inst.ligthGoal.size(), '.');
	inst.woltState = std::vector<int>(inst.ligthGoal.size(), 0);

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

	states.push({inst.ligthState, 0});

	while(!states.empty()) {

		std::pair<std::string, int> a = states.front();
		states.pop();

		int depth = a.second + 1;

		for (std::vector<int> buttion : inst.buttons) {
			std::string newState = pressButtion(a.first, buttion);

			if (newState == inst.ligthGoal) {
				return depth;
			}

			states.push({newState, depth});
		}
	}

	assert(false);

	return 0;
}

std::vector<int> pressButtion2(std::vector<int> state,const std::vector<int> &button) {

	for(int i : button) {
		state.at(i)++;
	}

	return std::move(state);
}

// Works but is to slow
// It clears the sample input with no dely but to slow for real inpit
aoc::ull process2(const instructions &inst) {

	std::map<std::vector<int>, bool> memory;
	std::queue<std::pair<std::vector<int>,int>> states;

	states.push({inst.woltState, 0});

	while(!states.empty()) {

		std::pair<std::vector<int>, int> state = states.front();
		states.pop();

		if(memory.count(state.first) != 0) {
			continue;
		}

		memory[state.first] = true; // Do not test again

		int depth = state.second + 1;

		bool allPathBlocked{true};
		for (const std::vector<int> &buttion : inst.buttons) {
			std::vector<int> newState = pressButtion2(state.first, buttion);

			if (newState == inst.woltGoal) {
				return depth;
			}

			bool valid{true};

			if(memory.count(newState) != 0) {
				continue;
			}

			for (int i{0}; i < newState.size(); ++i) {
				if(newState.at(i) > inst.woltGoal.at(i)) {
					memory[std::move(newState)] = false;
					valid = false;
					break;
				}
			}

			if (valid) {
				allPathBlocked = false;
				states.push({newState, depth});
			}
		}

		if(allPathBlocked) {
			memory[std::move(state.first)] = false;
		}
	}

	assert(false);

	return 0;
}


int main() {
	std::string line;
	std::ifstream file_in;

	aoc::ull sum{0}, sum2{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			instructions intr = pre_process(line);
			sum += process(intr);
			sum2 += process2(intr);
			std::cout << sum << " " << sum2 << std::endl;
		}
		file_in.close();
	}

	std::cout << "Part 1: " << sum << std::endl;
	std::cout << "Part 2: " << sum2 << std::endl;

	return 0;
}
