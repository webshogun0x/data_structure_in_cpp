#include "linked_list.hpp"
#include <iostream>
#include <string>

int main() {
    // Create and initialize
    LinkedList<int> numbers{1, 2, 3, 4, 5};
    
    // Add elements
    numbers.push_back(6);
    numbers.push_front(0);
    
    // Iterate using range-based for loop
    std::cout << "Numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";
    
    // Use functional approach
    numbers.for_each([](int& n) { n *= 2; });
    
    // Find element
    auto it = numbers.find(6);
    if (it != numbers.end()) {
        std::cout << "Found: " << *it << "\n";
    }
    
    // Remove element
    numbers.remove(4);
    
    // Pop from front
    if (auto value = numbers.pop_front()) {
        std::cout << "Popped: " << *value << "\n";
    }
    
    // String list example
    LinkedList<std::string> words;
    words.push_back("Hello");
    words.push_back("Modern");
    words.push_back("C++");
    
    std::cout << "First word: " << words.front() << "\n";
    std::cout << "Last word: " << words.back() << "\n";
    
    return 0;
}