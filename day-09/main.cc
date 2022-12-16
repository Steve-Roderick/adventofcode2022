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
#include <utility>

// https://stackoverflow.com/questions/15160889/
// how-can-i-make-an-unordered-set-of-pairs-of-integers-in-c
// https://stackoverflow.com/users/335858/sergey-kalinichenko
struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};


struct knot_state
{
    std::pair<int, int> head;
    std::pair<int, int> head_last;
    std::pair<int, int> head_last_last;
    std::pair<int, int> tail;

    // Insert the X,Y coordinate of the location of the tail into a set
    // so that at the end we can query how many unique locations the tail
    // has visited.
    std::unordered_set<std::pair<int, int>, pair_hash> tail_set;

    void start()
    {
        this->head = std::make_pair(0, 0);
        this->head_last = std::make_pair(0, 0);
        this->head_last_last = std::make_pair(0, 0);
        this->tail = std::make_pair(0, 0);
        this->tail_set.insert(this->tail);
    }

    void print()
    {
        std::cout << "HEAD: " << this->head.first << ", " << this->head.second;
        std::cout << " TAIL: " << this->tail.first << ", " << this->tail.second;
        std::cout << " size=" << this->tail_set.size();
        std::cout << std::endl;
    }
};


std::pair<int, int>
direction_char_to_offsets(char direction)
{
    int x = 0;
    int y = 0;
    switch(direction) {
        case 'U':
            y++;
            break;
        case 'D':
            y--;
            break;
        case 'L':
            x--;
            break;
        case 'R':
            x++;
            break;
        default:
            throw std::invalid_argument("Invalid direction");
    }
    return std::make_pair(x, y);

}

void move_head(
        struct knot_state & state,
        std::pair<int, int> offset,
        int count)
{
    if (count < 0) {
        throw std::invalid_argument("Count is negative");
    }
    int x = offset.first;
    int y = offset.second;
    int moves = 0;
    while (count > 0) {
        state.head.first += x;
        state.head.second += y;
        state.head_last_last = state.head_last;
        state.head_last = state.head;
        int hx = state.head.first;
        int hy = state.head.second;
        int tx = state.tail.first;
        int ty = state.tail.second;

        // Only move tail if greater than one distance away on the X or Y axis.
        if (std::abs(hx - tx) > 1 || std::abs(hy - ty) > 1) {
            // Detect if Head is diagonal to Tail.
            // Diagonality is known if the X's and Y's are both different.
            if (hx != tx && hy != ty) {
                // If diagonal, we can cheat by moving to the heads last last position.
                state.tail = state.head_last_last;
            } else {
                // Otherwise apply simple offset in which way we are moving.
                state.tail.first += x;
                state.tail.second += y;
            }
        }
        state.tail_set.insert(state.tail);
        state.print();
        count--;
        moves++;
    }
}

int main(int argc, char *argv[]) {

    knot_state state;
    state.start();
    std::ifstream infile("input.large");
    std::string line;
    while(std::getline(infile, line)) {
        if (line.empty())
            continue;
        int space_index = line.find_first_of(" ");
        std::string direction_char = line.substr(0, space_index);

        std::pair<int, int> offset =
            direction_char_to_offsets(direction_char.at(0));
        int count = std::stoi(line.substr(space_index + 1, -1));
        std::cout << direction_char << std::endl;
        move_head(state, offset, count);
    }

    std::cout << state.tail_set.size() << std::endl;
}
