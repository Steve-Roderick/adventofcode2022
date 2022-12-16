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
//  180000
int is_visible_u(
        std::vector<std::vector<char>> & forest, char tree, int i, int j)
{
    int acc = 0;
    for (int k = i - 1; k >= 0; k--) {
        acc++;
        char next = forest.at(k).at(j);
        if (next >= tree)
            break;
    }
    return acc;
}

int is_visible_d(
        std::vector<std::vector<char>> & forest, char tree, int i, int j)
{
    int acc = 0;
    for (int k = i + 1; k < forest.size(); k++) {
        acc++;
        char next = forest.at(k).at(j);
        if (next >= tree)
            break;
    }
    return acc;
}


int is_visible_l(
        std::vector<std::vector<char>> & forest, char tree, int i, int j)
{
    int acc = 0;
    for (int k = j - 1; k >= 0; k--) {
        acc++;
        char next = forest.at(i).at(k);
        if (next >= tree)
            break;
    }
    return acc;
}


int is_visible_r(
        std::vector<std::vector<char>> & forest, char tree, int i, int j)
{
    int acc = 0;
    for (int k = j + 1; k < forest.at(i).size(); k++) {
        acc++;
        char next = forest.at(i).at(k);
        if (next >= tree)
            break;
    }
    return acc;
}



int countVisibleInner(
        std::vector<std::vector<char>> & f)
{
    int row = f.at(0).size();
    int col = f.size();
    int count = -1;
    for (int i = 0; i < col -1; i++) {
        for (int j = 0; j < row -1; j++) {
            char tree = f.at(i).at(j);
            int a = is_visible_u(f, tree, i, j);
            int b = is_visible_d(f, tree, i, j);
            int c = is_visible_l(f, tree, i, j);
            int d = is_visible_r(f, tree, i, j);
            int t = a * b * c * d;
            if (t > count) {
                count = t;
            }
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
    int visible = countVisibleInner(forest);
    std::cout << visible << std::endl;
}
