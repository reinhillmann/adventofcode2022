#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>

struct Move {
    int from;
    int to;
    int count;
};

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

int numberOfStacks(const std::string &line) {
    int len = line.length();
    int i = 1;
    while (true) {
        int test = (i * 3) + (i - 1);
        if (test == len) return i;
        if (i++ > 10) {
            std::cerr << "Input in incorrect format.\n";
            exit(1);
        }
    }
}

std::vector<char> parseStackLine(const int numberOfStacks, const std::string &line) {
    std::vector<char> values;
    for (int i=0; i<numberOfStacks; i++) {
        std::string s = line.substr(i * 3 + i, 3);
        if (s[0] == '[') {
            values.push_back(s[1]);
        } else {
            values.push_back('.');
        }
    }
    return values;
}

std::vector<std::vector<char>> generateStacks(const std::vector<std::string> &lines) {
    int stackCount = numberOfStacks(lines[0]);
    std::vector<std::vector<char>> stacks;
    for (int i=0; i<stackCount; i++) {
        stacks.push_back(std::vector<char>());
    }

    int i=0;
    while (lines[i].length() > 0) {
        if (lines[i][1] == '1') break;
        std::vector<char> values = parseStackLine(stackCount, lines[i]);
        for (int n=0; n<stackCount; n++) {
            if (values[n] != '.') {
                stacks[n].push_back((values[n]));
            }
        }
        i++;
    }
    return stacks;
}

std::vector<Move> generateMoves(const std::vector<std::string> &lines) {
    std::vector<Move> moves;

    bool parsing = false;
    for (auto line: lines) {
        if (line.length() == 0) {
            // Turn on parsing.
            parsing = true;
            continue;
        };
        if (parsing) {
            Move m;
            int space1 = line.find(' ');
            int space2 = line.find(' ', space1+1);
            int space3 = line.find(' ', space2+1);
            int space4 = line.find(' ', space3+1);
            int space5 = line.find(' ', space4+1);
            int end = line.length() - 1;
            m.count = std::stoi(line.substr(space1+1, space2-(space1+1)));
            m.from = std::stoi(line.substr(space3+1, space4-(space3+1))) - 1; // 0 based index
            m.to = std::stoi(line.substr(space5+1, end-(space5))) - 1; // 0 based index
            moves.push_back(m);
        }
    }
    return moves;
}

void part1(const std::vector<std::string> &lines) {
    std::vector<std::vector<char>> stacks = generateStacks(lines);
    std::vector<Move> moves = generateMoves(lines);

    for (auto m: moves) {
        for (int i=0; i<m.count; i++) {
            char value = stacks[m.from].front();
            stacks[m.from].erase((stacks[m.from].begin()));
            stacks[m.to].insert(stacks[m.to].begin(), value);  // move at start of stack.
        }
    }
    for (auto s: stacks) {
        std::cout << s[0];
    }
    std::cout << "\n";
}

void part2(const std::vector<std::string> &lines) {
    std::vector<std::vector<char>> stacks = generateStacks(lines);
    std::vector<Move> moves = generateMoves(lines);

    for (auto m: moves) {
        for (int i=0; i<m.count; i++) {
            char value = stacks[m.from].front();
            stacks[m.from].erase((stacks[m.from].begin()));
            stacks[m.to].insert(stacks[m.to].begin()+i, value);  // move after others that were added.
        }
    }
    for (auto s: stacks) {
        std::cout << s[0];
    }
    std::cout << "\n";
}

int main() {
    std::cout << "Advent of Code. Day 5. https://adventofcode.com/2022/day/5\n";
    std::vector<std::string> lines = readFile("input.txt");
    part1(lines);
    part2(lines);
    return 0;
}

