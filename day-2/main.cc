#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

//The winner of the whole tournament is the player with the highest score.
// Your total score is the sum of your scores for each round.
// The score for a single round is the score for the shape you selected
// 1 for Rock A
// 2 for Paper B
// 3 for Scissors C
// plus the score for the outcome of the round
// 0 if you lost
// 3 if the round was a draw
// and 6 if you won.

// Rock X
// Paper Y
// Scissors Z


int playScore(char k)
{
	switch (k) {
	case 'X': return 1;
	case 'Y': return 2;
	case 'Z': return 3;
	}
	return 0;
}

int winScore(char me, char op)
{
	if (me == 'X' && op == 'A')
		return 3;
	if (me == 'Y' && op == 'B')
		return 3;
	if (me == 'Z' && op == 'C')
		return 3;

	if (me == 'X' && op == 'C')
		return 6;
	if (me == 'Y' && op == 'A')
		return 6;
	if (me == 'Z' && op == 'B')
		return 6;
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
		char me = 0;
		for (char & c : line) {
			if (isspace(c))
				continue;
			if (!op) {
				op = c;
				continue;
			}
			if (!me) {
				me = c;
				local += playScore(c);
			}
		}
		local += winScore(me, op);
		score += local;
    }
	std::cout << "Score: " << score << std::endl;
    return 0;
}
