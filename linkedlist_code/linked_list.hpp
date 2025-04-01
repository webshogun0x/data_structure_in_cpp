#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <memory>
#include <optional>
#include <functional>
#include <stdexcept>
#include <initializer_list>
#include <iterator>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        
        // Perfect forwarding constructor
        template <typename U>
        requires std::convertible_to<U, T>
        explicit Node(U&& value) : data(std::forward<U>(value)), next(nullptr) {}
    };
    
    std::unique_ptr<Node> head;
    Node* tail = nullptr;
    size_t node_count = 0;

public:
    // Iterator implementation
    class iterator {
    private:
        Node* current;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        explicit iterator(Node* node) : current(node) {}
        
        reference operator*() const { return current->data; }
        pointer operator->() const { return &(current->data); }
        
        // Pre-increment
        iterator& operator++() {
            current = current->next.get();
            return *this;
        }
        
        // Post-increment
        iterator operator++(int) {
            iterator temp = *this;
            current = current->next.get();
            return temp;
        }
        
        bool operator==(const iterator& other) const {
            return current == other.current;
        }
        
        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
    };
    
    // Constructors
    LinkedList() = default;
    
    LinkedList(std::initializer_list<T> init) {
        for (const auto& item : init) {
            push_back(item);
        }
    }
    
    // Rule of five
    ~LinkedList() = default;  // unique_ptr handles cleanup
    
    LinkedList(const LinkedList& other) {
        for (const auto& item : other) {
            push_back(item);
        }
    }
    
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            for (const auto& item : other) {
                push_back(item);
            }
        }
        return *this;
    }
    
    LinkedList(LinkedList&& other) noexcept = default;
    LinkedList& operator=(LinkedList&& other) noexcept = default;
    
    // Iterator functions
    [[nodiscard]] iterator begin() const noexcept { return iterator(head.get()); }
    [[nodiscard]] iterator end() const noexcept { return iterator(nullptr); }
    
    // Core operations
    template <typename U>
    requires std::convertible_to<U, T>
    void push_front(U&& value) {
        auto new_node = std::make_unique<Node>(std::forward<U>(value));
        
        if (empty()) {
            head = std::move(new_node);
            tail = head.get();
        } else {
            new_node->next = std::move(head);
            head = std::move(new_node);
        }
        
        ++node_count;
    }
    
    template <typename U>
    requires std::convertible_to<U, T>
    void push_back(U&& value) {
        auto new_node = std::make_unique<Node>(std::forward<U>(value));
        
        if (empty()) {
            head = std::move(new_node);
            tail = head.get();
        } else {
            tail->next = std::move(new_node);
            tail = tail->next.get();
        }
        
        ++node_count;
    }
    
    std::optional<T> pop_front() {
        if (empty()) {
            return std::nullopt;
        }
        
        T value = std::move(head->data);
        head = std::move(head->next);
        
        if (!head) {
            tail = nullptr;
        }
        
        --node_count;
        return value;
    }
    
    [[nodiscard]] bool empty() const noexcept {
        return node_count == 0;
    }
    
    [[nodiscard]] size_t size() const noexcept {
        return node_count;
    }
    
    void clear() noexcept {
        head.reset();
        tail = nullptr;
        node_count = 0;
    }
    
    [[nodiscard]] const T& front() const {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }
    
    [[nodiscard]] T& front() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }
    
    [[nodiscard]] const T& back() const {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return tail->data;
    }
    
    [[nodiscard]] T& back() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return tail->data;
    }
    
    // Find first occurrence of value
    [[nodiscard]] iterator find(const T& value) const {
        for (auto it = begin(); it != end(); ++it) {
            if (*it == value) {
                return it;
            }
        }
        return end();
    }
    
    // Remove first occurrence of value
    bool remove(const T& value) {
        if (empty()) {
            return false;
        }
        
        if (head->data == value) {
            pop_front();
            return true;
        }
        
        Node* current = head.get();
        while (current->next && current->next->data != value) {
            current = current->next.get();
        }
        
        if (current->next) {
            if (current->next.get() == tail) {
                tail = current;
            }
            current->next = std::move(current->next->next);
            --node_count;
            return true;
        }
        
        return false;
    }
    
    // Apply function to each element
    void for_each(const std::function<void(T&)>& func) {
        for (auto it = begin(); it != end(); ++it) {
            func(*it);
        }
    }
};

#endif // LINKED_LIST_HPP