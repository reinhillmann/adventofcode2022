#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>

#define ROCK 1
#define PAPER 2
#define SCISSORS 3

#define LOSS 1
#define WIN 3

enum Part { part1, part2 };

std::vector<std::string> readFile(const std::string &file) {
    std::vector<std::string> lines;
    std::ifstream datafile(file);
    while (!datafile.eof()) {
        std::string line;
        getline(datafile, line, '\n');
        lines.push_back(line);
    }
    datafile.close();
    return lines;
}

int calculateScore(int opponent, int mine) {
    int score = mine;  // start with some base points.
    if (mine == opponent) score += 3;  // draw
    else if (opponent == SCISSORS && mine == ROCK) score += 6;  // edge case win
    else if (opponent == ROCK && mine == SCISSORS) score += 0;  // edge case loss
    else if (mine > opponent) score += 6;  // win: rock < paper < scissors
    return score;
}

int determineHandToPlay(int opponent, int result) {
    if (result == LOSS) {
        if (opponent == ROCK) return SCISSORS;
        if (opponent == PAPER) return ROCK;
        if (opponent == SCISSORS) return PAPER;
    }
    if (result == WIN) {
        if (opponent == ROCK) return PAPER;
        if (opponent == PAPER) return SCISSORS;
        if (opponent == SCISSORS) return ROCK;
    }
    return opponent;
}

int scoreForLine(const std::string &line, Part part) {
    int opponent = line.at(0) - '@';
    int result = part == part2 ? line.at(2) - 'W' : 0;  // not used for part1
    int mine = part == part1 ? line.at(2) - 'W' : determineHandToPlay(opponent, result);
    return calculateScore(opponent, mine);
}

int main() {
    std::cout << "Advent of Code. Day 2. https://adventofcode.com/2022/day/2\n";
    std::vector<std::string> lines = readFile("input.txt");

    {
        int score = 0;
        std::for_each(lines.begin(),
                      lines.end(),
                      [&score](auto line) { score += scoreForLine(line, part1); });
        std::cout << "(Part 1) Score:   " << score << "\n";
    }

    {
        int score = 0;
        std::for_each(lines.begin(),
                      lines.end(),
                      [&score](auto line) { score += scoreForLine(line, part2); });
        std::cout << "(Part 2) Score:   " << score << "\n";
    }
    return 0;
}

