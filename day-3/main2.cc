#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


// puzzle a: input.txt  == 8153
// puzzle b: input.txt == 2342

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
    std::vector<std::string> vec;
	int score = 0;
	std::ifstream infile("input.txt");
	std::string line;
    int group = 1;
	while(std::getline(infile, line)) {
		if (line.empty())
			continue;
        vec.push_back(line);
        char com;
        if (group % 3 == 0) {
            std::string common = "";
            std::string a = vec.at(0);
            std::string b = vec.at(1);
            std::string c = vec.at(2);
            for (char & aa : a) {
                for (char & bb : b) {
                    if ( aa == bb) {
                        common.append(1, aa);
                    }
                }
            }
            for (char & cc : c) {
                for (char & ee : common) {
                    if (cc == ee)
                        com = cc;
                }
            }
            score += priority(com);
        vec.clear();
        }
        group += 1;
        //score += priority(common);
    }
    std::cout << "Score: " << score << std::endl;
    return 0;
}
