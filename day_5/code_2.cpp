#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include <ranges>

#include "../utils.cpp"

struct idRange{

	void add(aoc::ull nr) {
		if (start == 0) {
			start = nr;
		} else if (end == 0) {
			end = nr;
		} else {
			assert(false);
		}
	}

	bool isConstructed() const {
		return start != 0 && end != 0;
	}

	bool inRange(aoc::ull nr) const {
		return (nr >= start) && (nr <= end);
	}

	aoc::ull start{0};
	aoc::ull end{0};
};

bool tryMerge(idRange &range, idRange &otherRange) {

	// 5-7 vs 1-2
	if (range.start > otherRange.end) {
		return false;
	}

	// 1-2 vs 5-7
	if (range.end < otherRange.start) {
		return false;
	}

	// 5-7 vs 3-8
	if (range.start >= otherRange.start && range.end <= otherRange.end) {
		range = otherRange;
		return true;
	}

	// 3-8 vs 5-7
	if (range.inRange(otherRange.start) && range.inRange(otherRange.end)) {
		return true;
	}

	// 5-7 vs 3-6
	if (!range.inRange(otherRange.start) && range.inRange(otherRange.end)) {
		range.start = otherRange.start;
		return true;
	}

	// 5-7 vs 6-8
	if (range.inRange(otherRange.start) && !range.inRange(otherRange.end)) {
		range.end = otherRange.end;
		return true;
	}

	assert(false);
}

void insertRange(std::vector<idRange> &idManager, idRange newRange) {

	bool merged{false};
	idRange rangeCopy;

	for (auto it = idManager.begin(); it != idManager.end(); ++it) {

		rangeCopy = *it;

		if (tryMerge(rangeCopy, newRange)) {
			it = idManager.erase(it);
			merged = true;
			break;
		}
	}

	if (merged) {
		insertRange(idManager, rangeCopy);
	} else {
		idManager.push_back(newRange);
	}
}

void pre_process(std::vector<idRange> &idManager, std::string &in) {

	idRange newRange;

	aoc::for_all_substrings(in, "-", [&newRange](std::string nr){
		newRange.add(std::stoull(nr));
	});

	assert(newRange.isConstructed());

	insertRange(idManager, newRange);
}

aoc::ull process(const std::vector<idRange> &idManager) {

	aoc::ull sum{0};

	for(const idRange &range : idManager) {
		sum += 1 + (range.end - range.start);
	}

	return sum;
}


int main() {
	std::string line;
	std::ifstream file_in;

	aoc::ull sum{0};
	std::vector<idRange> idManager;

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			if(line.empty()) {
				break;
			}

			pre_process(idManager, line);
		}
		file_in.close();
	}

	std::cout << process(idManager) << std::endl;

	return 0;
}
