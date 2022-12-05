#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <numeric>

struct AssignmentPair {
    int start1;
    int end1;
    int start2;
    int end2;

    bool completelyOverlaps() {
        return (start1 <= start2 && end1 >= end2) ||
                (start2 <= start1 && end2 >= end1);
    }

    bool partiallyOverlaps() {
        return completelyOverlaps() ||
               (start1 <= start2 && end1 >= start2)
               || (start1 >= start2 && start1 <= end2);
    }
};

AssignmentPair assignmentFromString(const std::string &line) {
    size_t firstDash = line.find('-');
    size_t secondDash = line.find('-', firstDash+1);
    size_t comma = line.find(',');
    auto ap = AssignmentPair();
    ap.start1 = std::stoi(line.substr(0, firstDash));
    ap.end1 = std::stoi(line.substr(firstDash+1, comma-(firstDash+1)));
    ap.start2 = std::stoi(line.substr(comma+1, secondDash-(comma+1)));
    ap.end2 = std::stoi(line.substr(secondDash+1, line.length()-(secondDash+1)));
    return ap;
}

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

int main() {
    std::cout << "Advent of Code. Day 4. https://adventofcode.com/2022/day/4\n";
    std::vector<std::string> lines = readFile("input.txt");
    {
        int overlaps = 0;
        std::for_each(lines.begin(),
                      lines.end(),
                      [&overlaps](auto line) { overlaps += assignmentFromString(line).completelyOverlaps() ? 1 : 0; });
        std::cout << "(Part 1) Wholly overlaps:   " << overlaps << "\n";
    }
    {
        int overlaps = 0;
        std::for_each(lines.begin(),
                      lines.end(),
                      [&overlaps](auto line) { overlaps += assignmentFromString(line).partiallyOverlaps() ? 1 : 0; });
        std::cout << "(Part 2) Partially overlaps: " << overlaps << "\n";
    }
    return 0;
}

