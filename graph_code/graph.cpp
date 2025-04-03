// Graph.cpp
#include "Graph.hpp"
#include <iostream>

void Graph::addPlace(const std::string& place) {
    // If the place doesn't exist yet, add it with an empty set of connections
    if (connections.find(place) == connections.end()) {
        connections[place] = std::set<std::string>();
    }
}

void Graph::addPath(const std::string& from, const std::string& to) {
    // Make sure both places exist in our graph
    addPlace(from);
    addPlace(to);
    connections[from].insert(to);
}

bool Graph::hasDirectPath(const std::string& from, const std::string& to) const {
    // Check if 'from' exists in our graph
    auto it = connections.find(from);
    if (it == connections.end()) {
        return false;
    }
    
    // Check if 'to' is directly connected to 'from'
    return it->second.find(to) != it->second.end();
}

std::set<std::string> Graph::getNeighbors(const std::string& place) const {
    // Return empty set if place doesn't exist
    auto it = connections.find(place);
    if (it == connections.end()) {
        return std::set<std::string>();
    }

    return it->second;
}

std::vector<std::string> Graph::getAllPlaces() const {
    std::vector<std::string> places;
    for (const auto& pair : connections) {
        places.push_back(pair.first);
    }
    return places;
}

int Graph::countPaths(const std::string& place) const {
    auto it = connections.find(place);
    if (it == connections.end()) {
        return 0;
    }
    return it->second.size();
}

void Graph::printGraph() const {
    for (const auto& pair : connections) {
        std::cout << pair.first << " connects to: ";
        if (pair.second.empty()) {
            std::cout << "nowhere";
        } else {
            bool first = true;
            for (const auto& neighbor : pair.second) {
                if (!first) {
                    std::cout << ", ";
                }
                std::cout << neighbor;
                first = false;
            }
        }
        std::cout << std::endl;
    }
}