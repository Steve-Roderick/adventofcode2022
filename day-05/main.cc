#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <stack>
#include <string>
#include <stdbool.h>
// A == TLFGBZHCN
// B == QRQFHFWCL
//
void loadState(
        std::ifstream & infile,
        std::vector<std::stack<char>> & dock)
{
    std::vector<std::string> start;
    std::string line;
    int count = 0;
    bool stop_load = false;
    while(std::getline(infile, line)) {
        if (! stop_load) {
            if (line.length() >= 2) {
                if (line[0] == ' ' && line[1] == '1') {
                    stop_load = true;
                    break;
                }
            }
            start.push_back(line);
        }
    }
    std::reverse(start.begin(), start.end());
    for (std::string st : start) {
        int col = -1;
        int space_count = 0;
        for (char ch : st) {
            if (ch == ' ') {
                space_count++;
                if (space_count == 3) {
                    col++;
                    space_count = 0;
                }
                continue;
            }
            if (ch == ']') {
                space_count = 0;
                continue;
            }
            if (ch == '[') {
                space_count = 0;
                col++;
                continue;
            }
            space_count = 0;
            if (dock.size() == col) {
                std::stack<char> empty_stack;
                dock.push_back(empty_stack);
            }
            dock.at(col).push(ch);
        }
    }
}


int main(int argc, char *argv[]) {
    int mover = 9000;
    if (argc == 2 && argv[1][0] == '2') {
        mover = 9002;
    }
    std::vector<std::stack<char>> dock;
    std::ifstream infile("input.txt");
    loadState(infile, dock);
    std::string line;
    while(std::getline(infile, line)) {
        if (line.empty())
            continue;
        int move = line.find("move ", 0);
        int from = line.find("from ", 0);
        int to   = line.find("to ", 0);
        int n = std::stoi(line.substr(move + 5, from));
        int a = std::stoi(line.substr(from + 5, to));
        int b = std::stoi(line.substr(to + 3, -1));
        a--; // Convert to zero-index-ed.
        b--; // Convert to zero-index-ed.
        if (mover == 9000) {
            for (int i = 0; i < n; i++) {
                char move_it = dock.at(a).top();
                dock.at(a).pop();
                dock.at(b).push(move_it);
            }
        } else if (mover == 9002) {
            // Use intermediate stack to maintain order on moves.
            std::stack<char> buf;
            for (int i = 0; i < n; i++) {
                buf.push(dock.at(a).top());
                dock.at(a).pop();
            }
            while (!buf.empty()) {
                dock.at(b).push(buf.top());
                buf.pop();
            }
        }
    }
    // Print solution.
    for (std::stack<char> st : dock) {
        std::cout << st.top();
    }
    std::cout << std::endl;
    return 0;
}
