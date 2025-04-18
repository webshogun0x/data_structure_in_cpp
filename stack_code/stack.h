#ifndef _STACK
#define _STACK

#include <exception>

class StackException: public::std::exception{
    const char* msg;
    StackException(){};
public:
    explicit StackException(const char* s) throw() : msg(s) {}
    const char * what() const throw() {return msg;}
};

template <typename T> 
class Stack {
private:
    static const int defaultSize = 10;
    static const int maxSize = 1000;
    int _size; 
    int _top;
    T * stackPtr;
public:
    explicit Stack (int s = defaultSize);
    ~Stack () {delete[] stackPtr;}
    T & push(const T &);
    T & pop();
    bool isEmpty() const {return _top < 0;}
    bool isFull() const {return _top >= _size - 1;}
    int top() const {return _top;}
    int size() const {return _size;}
};
template <typename T>
Stack <T>::Stack (int s) {
    if (s > maxSize || s < 1) throw StackException("invalid Stack size");
    else _size = s;
    stackPtr = new T[_size];
    _top = -1; 
}

template <typename T>
T & Stack<T>::push(const T & i) {
    if(isFull()) throw StackException("stack is full");
    return stackPtr[++_top] = i;
}

template <typename T>
T & Stack<T>::pop() {
    if(isEmpty()) throw StackException("stack is empty");
    return stackPtr[_top--];
}
#endif