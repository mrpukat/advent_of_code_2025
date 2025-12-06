#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ranges>

#include "../utils.cpp"

int process(std::string in, int &pos) {

	char instuction = in.at(0);
	in.erase(0, 1);
	int movment = std::stoi(in);

	int rot = movment / 100;
	movment %= 100;
	bool wasZero = pos == 0; // Dont like this (make more general)

	std::cout << rot << " : " << pos << std::endl;	

	if(instuction == 'R') {
		pos += movment;
	}
	else if (instuction == 'L') {
		pos -= movment;
	}

	assert(pos > -100);
	assert(pos < 199);

	if(pos < 0){
		pos += 100;
		if (!wasZero && pos != 0) {
			rot++;
		}
	} else if (pos > 99) {
		pos -= 100;
		if (pos != 0) {
			rot++;
		}
	}

	if (pos == 0) {
		rot++;
	}

	std::cout << rot << " : " << pos << std::endl;	
	

	return rot;
}


int main() {
	std::string line;
	std::ifstream file_in;

	int position{50};
	int sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			sum += process(line, position);
			std::cout << line << ": " << position << std::endl;
		}
		file_in.close();
	}

	std::cout << sum << std::endl;

	return 0;
}
