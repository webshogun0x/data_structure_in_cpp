// main.cpp
#include <iostream>
#include "Queue.hpp"

int main() {
    // Create a queue for people waiting in line
    Queue<std::string> waitingLine;
    
    // People arrive and join the line
    std::cout << "People joining the ice cream line:" << std::endl;
    waitingLine.enqueue("Emma");
    std::cout << "Emma joined the line" << std::endl;
    
    waitingLine.enqueue("Jack");
    std::cout << "Jack joined the line" << std::endl;
    
    waitingLine.enqueue("Sophia");
    std::cout << "Sophia joined the line" << std::endl;
    
    // Who's first in line?
    std::cout << "\nWho's first in line? " << waitingLine.front() << std::endl;
    
    // How many people are waiting?
    std::cout << "There are " << waitingLine.size() << " people waiting in line" << std::endl;
    
    // People get their ice cream and leave the line
    std::cout << "\nPeople getting their ice cream:" << std::endl;
    while (!waitingLine.isEmpty()) {
        std::cout << waitingLine.front() << " got their ice cream and left the line" << std::endl;
        waitingLine.dequeue();
    }
    
    std::cout << "\nIs the line empty now? " 
              << (waitingLine.isEmpty() ? "Yes!" : "No!") << std::endl;
    
    // Now let's simulate a slide at the playground
    Queue<std::string> slideQueue;
    std::cout << "\nKids waiting for the slide:" << std::endl;
    
    slideQueue.enqueue("Noah");
    slideQueue.enqueue("Lily");
    slideQueue.enqueue("Ethan");
    slideQueue.enqueue("Ava");
    
    std::cout << "There are " << slideQueue.size() << " kids waiting for the slide" << std::endl;
    std::cout << slideQueue.front() << " is next to go down the slide!" << std::endl;
    
    return 0;
}