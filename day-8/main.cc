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
#include <cstring>
// small == 21
// large == 1843


int countVisibleOnEdge(
        std::vector<std::vector<char>> & forest)
{
    int row = forest.at(0).size();
    int col = forest.size();
    // Account counting four trees on the outer corners twice.
    return (row * 2) + (col * 2) - 4;
}


bool is_visible_u(
        std::vector<std::vector<char>> & forest, char tree, int i, int j)
{
    for (int k = i - 1; k >= 0; k--) {
        char next = forest.at(k).at(j);
        if (next >= tree)
            return false;
    }
    return true;
}

bool is_visible_d(
        std::vector<std::vector<char>> & forest, char tree, int i, int j)
{
    for (int k = i + 1; k < forest.size(); k++) {
        char next = forest.at(k).at(j);
        if (next >= tree)
            return false;
    }
    return true;
}


bool is_visible_l(
        std::vector<std::vector<char>> & forest, char tree, int i, int j)
{
    for (int k = j - 1; k >= 0; k--) {
        char next = forest.at(i).at(k);
        if (next >= tree)
            return false;
    }
    return true;
}


bool is_visible_r(
        std::vector<std::vector<char>> & forest, char tree, int i, int j)
{
    for (int k = j + 1; k < forest.at(i).size(); k++) {
        char next = forest.at(i).at(k);
        if (next >= tree)
            return false;
    }
    return true;
}



int countVisibleInner(
        std::vector<std::vector<char>> & f)
{
    int row = f.at(0).size();
    int col = f.size();
    int count = 0;
    for (int i = 1; i < col -1; i++) {
        for (int j = 1; j < row -1; j++) {
            char tree = f.at(i).at(j);
            bool seen = false;
            seen |= is_visible_u(f, tree, i, j);
            seen |= is_visible_d(f, tree, i, j);
            seen |= is_visible_l(f, tree, i, j);
            seen |= is_visible_r(f, tree, i, j);
            if (seen)
                count++;
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    std::ifstream infile("input.txt");
    std::string line;

    // Load the forest into a 2d vector of char.
    std::vector<std::vector<char>> forest;
    while(std::getline(infile, line)) {
        if (line.empty())
            continue;
        forest.push_back(std::vector<char>());
        for (char & c : line) {
            forest.back().push_back(c - 48);
        }
    }
    int visible = countVisibleOnEdge(forest);
    visible += countVisibleInner(forest);
    std::cout << visible << std::endl;
}
