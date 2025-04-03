
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <set>

class Graph {
private:
    std::unordered_map<std::string, std::set<std::string>> connections;

public:
    void addPlace(const std::string& place);
    void addPath(const std::string& from, const std::string& to);
    bool hasDirectPath(const std::string& from, const std::string& to) const;
    std::set<std::string> getNeighbors(const std::string& place) const;
    std::vector<std::string> getAllPlaces() const;
    int countPaths(const std::string& place) const;
    void printGraph() const;
};

#endif