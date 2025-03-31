#include "stack.h"
#include <iostream>
#include <string>
using namespace std;

constexpr int nums[] = {1 ,2, 3, 4, 5};
constexpr const char * strs[] = {"one", "two", "three", "four", "five"};

int main(){
    try{
        Stack <int> s1(5);
        cout << "s1 size" << s1.size() << endl;
        cout << "s1 top" << s1.top() << endl;
    
        for (int i: nums) {
            s1.push(i);
        }

        cout << "s1 top after pushes: " << s1.top() <<endl;
        cout << "s1 is " << (s1.isFull()? "" : "not") << endl;
        while (!s1.isEmpty()){
            cout << "popped" << s1.pop() << endl;
        }
    
    }
    catch(StackException & e){
        cout <<"Stack erorr" << e.what() << '\n';
    }

    try{
        Stack <string> ss(5);
        cout << "ss size " << ss.size() << endl;
        cout << "ss top " << ss.top() << endl;
        for (const char * s : strs) {
            ss.push(s);
        }
        cout << "ss top after push" << ss.top() << endl;
        cout << "ss is: " << (ss.isFull() ? "": "not") << endl;

        while (!ss.isEmpty()){
            cout << "popped" << ss.pop() << endl;
        } 
    }
    catch(const std::exception& e)
    {
        cout <<"Stack Error" << e.what() << '\n';
    }
    
}