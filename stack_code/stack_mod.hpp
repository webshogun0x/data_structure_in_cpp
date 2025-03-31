#ifndef STACK_HPP
#define STACK_HPP

#include <vector>
#include <stdexcept>
#include <format>

class StackException : public std::runtime_error {
public:
    explicit StackException(const std::string& message) 
        : std::runtime_error(message) {}
};

template <typename T>
class Stack {
public:
    // Constructor with C++20 constraints
    explicit Stack(size_t capacity = default_size) 
        requires (std::movable<T>) {
        if (capacity > max_size || capacity < 1) {
            throw StackException(
                std::format("Invalid stack size: {}. Must be between 1 and {}", 
                           capacity, max_size));
        }
        elements.reserve(capacity);
    }

    // Stack operations with noexcept specifications
    [[nodiscard]] bool empty() const noexcept {
        return elements.empty();
    }

    [[nodiscard]] bool full() const noexcept {
        return elements.size() >= elements.capacity();
    }

    [[nodiscard]] size_t size() const noexcept {
        return elements.size();
    }

    [[nodiscard]] size_t capacity() const noexcept {
        return elements.capacity();
    }

    // Push with perfect forwarding
    template <typename U>
    requires std::convertible_to<U, T>
    T& push(U&& value) {
        if (full()) {
            throw StackException("Stack is full");
        }
        elements.push_back(std::forward<U>(value));
        return elements.back();
    }

    // Pop with optional value semantics
    std::optional<T> try_pop() noexcept {
        if (empty()) {
            return std::nullopt;
        }
        T value = std::move(elements.back());
        elements.pop_back();
        return value;
    }

    // Traditional pop that throws
    T pop() {
        if (empty()) {
            throw StackException("Stack is empty");
        }
        T value = std::move(elements.back());
        elements.pop_back();
        return value;
    }

    // Peek operations
    [[nodiscard]] const T& peek() const {
        if (empty()) {
            throw StackException("Stack is empty");
        }
        return elements.back();
    }

    [[nodiscard]] T& peek() {
        if (empty()) {
            throw StackException("Stack is empty");
        }
        return elements.back();
    }

private:
    static constexpr size_t default_size = 10;
    static constexpr size_t max_size = 1000;
    std::vector<T> elements;
};

#endif // STACK_HPP