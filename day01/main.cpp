#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

std::vector<std::string> readFile(const std::string &file) {
    std::vector<std::string> lines(5000);
    std::ifstream datafile(file);
    if (!datafile) {
        std::cerr << "Could not find file: " << file << "\n";
        exit(-1);
    }
    while (!datafile.eof()) {
        std::string line;
        getline(datafile, line, '\n');
        lines.push_back(line);
    }
    datafile.close();
    return lines;
}

std::vector<int> sumGroups(const std::vector<std::string> &lines) {
    std::vector<int> totals(100);
    auto pushGroupTotal = [&totals](int &total) {
        if (total == 0) return;
        totals.push_back(total);
        total = 0;
    };
    int sum = 0;

    for (auto const &line: lines) {
        if (line.length() > 0) {
            sum += stoi(line);
            continue;
        }
        pushGroupTotal(sum);
    }
    pushGroupTotal(sum);
    return totals;
}


int main() {
    std::cout << "Advent of Code. Day 1. https://adventofcode.com/2022/day/1\n";
    std::vector<std::string> lines = readFile("input.txt");
    std::vector<int> totals = sumGroups(lines);
    std::sort(totals.begin(), totals.end(), std::greater<>());

    auto part1 = std::accumulate(totals.begin(), totals.begin() + 1, 0);
    std::cout << "(Part 1) Max:   " << part1 << "\n";
    auto part2 = std::accumulate(totals.begin(), totals.begin() + 3, 0);
    std::cout << "(Part 2) Total: " << part2 << "\n";
    return 0;
}

