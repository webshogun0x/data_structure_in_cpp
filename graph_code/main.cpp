// main.cpp
#include <iostream>
#include "Graph.hpp"

int main() {

    Graph neighborhood;
    
    // Add different places in a neighborhood
    std::cout << "Building our neighborhood map!" << std::endl;
    neighborhood.addPlace("Home");
    neighborhood.addPlace("School");
    neighborhood.addPlace("Park");
    neighborhood.addPlace("Library");
    neighborhood.addPlace("Ice Cream Shop");
    
    // Connect places with paths
    neighborhood.addPath("Home", "School");
    neighborhood.addPath("Home", "Park");
    neighborhood.addPath("School", "Library");
    neighborhood.addPath("Park", "Ice Cream Shop");
    neighborhood.addPath("Library", "Park");
    neighborhood.addPath("School", "Home");  // Can go back home from school
    
    // Print the whole neighborhood
    std::cout << "\nOur Neighborhood Map:" << std::endl;
    neighborhood.printGraph();
    
    // See if we can go directly from home to the ice cream shop
    std::string from = "Home";
    std::string to = "Ice Cream Shop";
    if (neighborhood.hasDirectPath(from, to)) {
        std::cout << "\nYou can go directly from " << from << " to " << to << "!" << std::endl;
    } else {
        std::cout << "\nYou cannot go directly from " << from << " to " << to << "." << std::endl;
    }
    
    // Where can we go from the park?
    std::cout << "\nFrom the Park, you can go to: ";
    auto parkNeighbors = neighborhood.getNeighbors("Park");
    bool first = true;
    for (const auto& place : parkNeighbors) {
        if (!first) std::cout << ", ";
        std::cout << place;
        first = false;
    }
    std::cout << std::endl;
    
    // Count paths from home
    std::cout << "\nThere are " << neighborhood.countPaths("Home") 
              << " different paths from Home." << std::endl;
    
    return 0;
}