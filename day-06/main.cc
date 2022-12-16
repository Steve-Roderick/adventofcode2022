#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <stack>
#include <string>
#include <list>
#include <stdbool.h>
#include <unordered_set>

#define ELF_PACKET_LENGTH 14
int main(int argc, char *argv[]) {
    std::ifstream infile("input.txt");
    std::string line;
    std::getline(infile, line);
    std::list<char> seen;
    int packet_index = 0;
    for (char d : line) {
        seen.push_back(d);
        if (seen.size() > ELF_PACKET_LENGTH) {
            seen.pop_front();
        }
        std::unordered_set<char> u(
                std::begin(seen),
                std::end(seen));
        if (u.size() == ELF_PACKET_LENGTH) {
            packet_index++;
            break;
        }
        packet_index++;
    }
    std::cout << packet_index << std::endl;
}
