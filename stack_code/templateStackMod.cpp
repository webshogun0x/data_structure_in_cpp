#include "stack_mod.hpp"
#include <iostream>
#include <string>
#include <array>

int main() {
    // Using std::array for compile-time arrays
    constexpr std::array nums = {1, 2, 3, 4, 5};
    const std::array<const char*, 5> strs = {"one", "two", "three", "four", "five"};

    // Testing integer stack
    try {
        Stack<int> s1(5);
        std::cout << "s1 capacity: " << s1.capacity() << '\n';
        std::cout << "s1 current size: " << s1.size() << '\n';

        // Push all numbers
        for (int i : nums) {
            s1.push(i);
            std::cout << "Pushed: " << i << '\n';
        }

        std::cout << "s1 top element: " << s1.peek() << '\n';
        std::cout << "s1 is " << (s1.full() ? "" : "not ") << "full\n";

        // Pop all elements
        while (!s1.empty()) {
            std::cout << "Popped: " << s1.pop() << '\n';
        }
    }
    catch (const StackException& e) {
        std::cerr << "Stack error: " << e.what() << '\n';
    }

    // Testing string stack
    try {
        Stack<std::string> ss(5);
        std::cout << "\nss capacity: " << ss.capacity() << '\n';
        std::cout << "ss current size: " << ss.size() << '\n';

        // Push all strings
        for (const char* s : strs) {
            ss.push(std::string(s));  // Explicitly construct std::string
            std::cout << "Pushed: " << s << '\n';
        }

        std::cout << "ss top element: " << ss.peek() << '\n';
        std::cout << "ss is " << (ss.full() ? "" : "not ") << "full\n";

        // Using try_pop() for exception-free popping
        while (auto value = ss.try_pop()) {
            std::cout << "Popped: " << *value << '\n';
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Stack error: " << e.what() << '\n';
    }

    return 0;
}