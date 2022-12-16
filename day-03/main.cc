#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


// puzzle a: input.txt  == 8153

// 27: A == 65 == > upper - 38
// 1:  a == 97 ==> lower - 96
int priority(char common)
{
    int offset = 96;
    if (std::isupper(common))
        offset = 38;
    return ((int) common) - offset;
}

int main() {
	std::vector<int> vec;
	std::ifstream infile("input.txt");
	std::string line;
	int score = 0;
	while(std::getline(infile, line)) {
		if (line.empty())
			continue;
        size_t len = line.length();
        if (len % 2)
            std::cout << "Line length uneven!\n";
        size_t half = len / 2.0;
        std::string pa = line.substr(0, half);
        std::string pb = line.substr(half, -1);
        char common;
        for (char & a : pa) {
            for (char & b : pb) {
                if ( a == b) {
                    common = a;
                }
            }
        }
        score += priority(common);
    }
    std::cout << "Score: " << score << std::endl;
    return 0;
}
