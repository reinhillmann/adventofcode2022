#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <set>

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

// int findFirstMarkerPos(const std::string &line, int cnt) {
//     std::set<char> charmap;
//     for (auto i=0; i<line.length() - 4; i++) {
//         for (int j=0; j<cnt; j++) {
//             charmap.insert(line.at(i+j));
//         }
//         if (charmap.size() == cnt) {
//             return i+cnt;
//         }
//         charmap.clear();
//     }
//     return -1;
// }

int main() {
    std::cout << "Advent of Code. Day 7. https://adventofcode.com/2022/day/7\n";
    std::vector<std::string> lines = readFile("input.txt");

    // std::for_each(lines.begin(), lines.end(),
    //     [](auto line) {
    //         if (line.length() == 0) return;
    //         std::cout << "Part 1: " << findFirstMarkerPos(line, 4) << " : " << line << "\n";
    //     });

    return 0;
}

