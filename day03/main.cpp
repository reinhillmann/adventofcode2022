#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <numeric>

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

std::set<char> createSet(std::__wrap_iter<const char *> begin, std::__wrap_iter<const char *> end) {
    std::set<char> result_set;
    std::for_each(begin, end,
          [&result_set] (char c) -> void { result_set.insert(c); });
    return result_set;
};

int scoreForLine(const std::string &line) {
    // Basically, we're looking for intersection(set(first half of line), set(second half of line)).
    // If this was python it would be a one-liner.
    std::set<char> setA = createSet(
            line.begin(), line.begin() + (long)(line.length() / 2));
    std::set<char> setB = createSet(
            line.begin() + (long)(line.length() / 2), line.end());
    std::vector<char> intersection(1);
    std::set_intersection (
            setA.begin(), setA.end(),
            setB.begin(), setB.end(),
            intersection.begin());
    char common = intersection[0];
    return common <= 'Z' ? common - 'A' + 27 : common - 'a' + 1;
}


int scoreForBadges(const std::string &line1, const std::string &line2, const std::string &line3) {
    // We need to find the intersection of line1, line2, and line3.
    // So we: intersection(intersection(set1, set2), set3).
    // But C++ sucks to do this succinctly.
    std::set<char> set1 = createSet(line1.begin(), line1.end());
    std::set<char> set2 = createSet(line2.begin(), line2.end());
    std::set<char> set3 = createSet(line3.begin(), line3.end());

    // Ok first intersection(set1, set2)
    std::vector<char> intersectionAB(set1.size());
    auto intersectionABIterator = std::set_intersection (
            set1.begin(), set1.end(),
            set2.begin(), set2.end(),
            intersectionAB.begin());
    intersectionAB.resize(intersectionABIterator - intersectionAB.begin());
    std::set<char> setAB = createSet(intersectionAB.begin(), intersectionAB.end());

    // Now that we have intersection(A, B) as setAB, do intersection(setAB, set3).
    std::vector<char> intersectionABC(setAB.size());
    auto intersectionABCIterator = std::set_intersection (
            setAB.begin(), setAB.end(),
            set3.begin(), set3.end(),
            intersectionABC.begin());
    intersectionAB.resize(intersectionABCIterator - intersectionABC.begin());

    // By the problem definition, we should have one and only one item that intersects all three sets.
    char common = intersectionABC[0];
    return common <= 'Z' ? common - 'A' + 27 : common - 'a' + 1;
}

int main() {
    std::cout << "Advent of Code. Day 3. https://adventofcode.com/2022/day/3\n";
    std::vector<std::string> lines = readFile("input.txt");

    {
        int score = 0;
        std::for_each(lines.begin(),
                      lines.end(),
                      [&score](auto line) { score += scoreForLine(line); });
        std::cout << "(Part 1) Score:   " << score << "\n";
    }

    {
        int score = 0;
        for (unsigned int i = 0; i < lines.size(); i+=3) {
            const std::string line1 = lines[i];
            const std::string line2 = lines[i+1];
            const std::string line3 = lines[i+2];
            score += scoreForBadges(line1, line2, line3);
        }
        std::cout << "(Part 2) Score:   " << score << "\n";
    }
    return 0;
}

