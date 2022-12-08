#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int matchScore(char k)
{
	switch (k) {
	case 'X': return 0;
	case 'Y': return 3;
	case 'Z': return 6;
	}
	return 0;
}

int strategy(char op, char target)
{
    switch (target) {

        case 'X':
            if (op == 'A') return 3;
            if (op == 'B') return 1;
            if (op == 'C') return 2; 
            break;
        case 'Y':
            if (op == 'A') return 1;
            if (op == 'B') return 2;
            if (op == 'C') return 3;
            break;
        case 'Z':
            if (op == 'A') return 2;
            if (op == 'B') return 3;
            if (op == 'C') return 1;
            break;
    }
    return 0;
}

int main() {
	std::vector<int> vec;
	std::ifstream infile("input.txt");
	std::string line;
	int score = 0;
	while(std::getline(infile, line)) {
		if (line.empty())
			continue;
		int local = 0;
		char op = 0;
		char target = 0;
		for (char & c : line) {
			if (isspace(c))
				continue;
			if (!op) {
				op = c;
				continue;
			}
			if (!target) {
				target = c;
			}
		}
        local += matchScore(target);
        local += strategy(op, target);
        score += local;
    }
	std::cout << "Score: " << score << std::endl;
    return 0;
}
