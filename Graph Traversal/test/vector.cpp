#include <iostream>
#include <vector>
class Stack {
    std::vector<int> Array;
    int top;
    int size;
    public:
        Stack ( int size ) {
            top = -1;
            this->size = size;
        }
        void push( int x ) {
            if ( top == size -1 ) {std::cout << "Stack is full";return;}
            Array.push_back(x);
            top++;
        }
        int pop() {
            if (top == -1) return -1;
            return Array[top--];
        }
};

int main () {
    Stack s(10);
    s.push(10);
    s.push(20);
    s.push(30);

    std::cout << "The popped element is " << s.pop() << std::endl;
    std::cout << "The popped element is " << s.pop() << std::endl;
    std::cout << "The popped element is " << s.pop() << std::endl;
    return 0;
}