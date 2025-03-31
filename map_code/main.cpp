// main.cpp
#include <iostream>
#include "Map.hpp"

int main() {
    // Create a map of children and their favorite toys
    Map<std::string, std::string> favoriteToys;
    
    // Add children and their favorite toys
    std::cout << "Adding kids and their favorite toys:" << std::endl;
    favoriteToys.put("Emma", "Teddy Bear");
    std::cout << "Emma's favorite toy is a Teddy Bear" << std::endl;
    
    favoriteToys.put("Jack", "Toy Cars");
    std::cout << "Jack's favorite toy is Toy Cars" << std::endl;
    
    favoriteToys.put("Sophia", "Building Blocks");
    std::cout << "Sophia's favorite toy is Building Blocks" << std::endl;
    
    // Let's see how many children we have
    std::cout << "\nWe have " << favoriteToys.size() << " children in our map" << std::endl;
    
    // Look up a child's favorite toy
    std::string child = "Jack";
    if (favoriteToys.contains(child)) {
        std::cout << child << "'s favorite toy is: " << favoriteToys.get(child) << std::endl;
    }
    
    // Jack gets a new favorite toy
    std::cout << "\nJack has a new favorite toy!" << std::endl;
    favoriteToys.put("Jack", "Robot");
    std::cout << "Now Jack's favorite toy is: " << favoriteToys.get("Jack") << std::endl;
    
    // List all the children
    std::cout << "\nChildren in our list:" << std::endl;
    for (const auto& name : favoriteToys.getKeys()) {
        std::cout << "- " << name << std::endl;
    }
    
    // List all the favorite toys
    std::cout << "\nFavorite toys:" << std::endl;
    for (const auto& toy : favoriteToys.getValues()) {
        std::cout << "- " << toy << std::endl;
    }
    
    // Remove a child from our map
    std::cout << "\nEmma moved to a different school" << std::endl;
    favoriteToys.remove("Emma");
    
    // Check who's still in our map
    std::cout << "Children still in our list:" << std::endl;
    for (const auto& name : favoriteToys.getKeys()) {
        std::cout << "- " << name << " loves " << favoriteToys.get(name) << std::endl;
    }
    
    return 0;
}