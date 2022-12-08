#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
	std::vector<int> vec;
	std::ifstream infile("input.txt");
	std::string line;
	int elf_acc = 0;
	while(std::getline(infile, line)) {
		if (line.empty()) {
			vec.push_back(elf_acc);
			elf_acc = 0;
		} else {
			elf_acc += std::stoi(line);
		}
	}
    vec.push_back(elf_acc);

    // Cal for top elf.
    int max = *std::max_element(vec.begin(), vec.end());
    std::cout << "Max Cal: " << max << std::endl;

    // Cal for top three elf.
    std::sort(vec.begin(), vec.end());
    int top_three = 0;
    for (int i = 0; i < 3 && i < vec.size(); i++) {
        top_three += vec.back();
        vec.pop_back();
    }
    std::cout << "Top Cals: " << top_three << std::endl;
    return 0;
}

