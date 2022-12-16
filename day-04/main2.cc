#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <stdbool.h>
// A1 464
// A2 770

std::tuple<int, int>
parse2(std::string line)
{
    int p = line.find("-");
    std::string sx = line.substr(0, p);
    std::string sy = line.substr(p+1, -1);
    int x = std::stoi(sx);
    int y = std:: stoi(sy);
    return std::make_tuple(x, y);
}

std::tuple<int, int, int, int>
parse(std::string line)
{
    int p = line.find(",");
    std::string elf_a = line.substr(0, p);
    std::string elf_b = line.substr(p+1, -1);
    int ax, ay; // Elf A from X,Y
    int bx, by; // Elf B from X,Y
    std::tie(ax, ay) = parse2(elf_a);
    std::tie(bx, by) = parse2(elf_b);
    return std::tie(ax, ay, bx, by);
}

int overlap(int w, int x, int y, int z)
{
    return (y >= w && y <= x) || (w >= y && w <= z);
}

int main() {
	std::ifstream infile("input.txt");
	std::string line;
	int count = 0;
	while(std::getline(infile, line)) {
		if (line.empty())
			continue;
        int ax, ay, bx, by;
        std::tie(ax, ay, bx, by) = parse(line);
        count += overlap(ax, ay, bx, by);
    }
    std::cout << "Count: " << count << std::endl;
    return 0;
}
