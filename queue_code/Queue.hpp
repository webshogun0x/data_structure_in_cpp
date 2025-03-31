// Queue.hpp
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <vector>
#include <stdexcept>

template<typename T>
class Queue {
private:
    std::vector<T> elements;

public:
    // Add something to the back of the queue
    void enqueue(const T& item);
    
    // Remove something from the front of the queue
    void dequeue();
    
    // Look at the front item without removing it
    T front() const;
    
    // Check if the queue is empty
    bool isEmpty() const;
    
    // Get the number of items in the queue
    size_t size() const;
};

// Implementation of template class methods
template<typename T>
void Queue<T>::enqueue(const T& item) {
    elements.push_back(item);
}

template<typename T>
void Queue<T>::dequeue() {
    if (!isEmpty()) {
        elements.erase(elements.begin());
    }
}

template<typename T>
T Queue<T>::front() const {
    if (!isEmpty()) {
        return elements.front();
    }
    throw std::out_of_range("Queue is empty");
}

template<typename T>
bool Queue<T>::isEmpty() const {
    return elements.empty();
}

template<typename T>
size_t Queue<T>::size() const {
    return elements.size();
}

#endif // QUEUE_HPP