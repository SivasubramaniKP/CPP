#include <iostream>
#include <vector>

class Queue {
    std::vector<int> Array;
    int size;
    public:
    Queue ( int size ) {
        this->size = size;
    } 
    void Enqueue ( int x ) {
        if ( Array.size() == size ) {
            std::cout << "Queue is full" << std::endl;
            return;
        }
        Array.push_back(x);
    }
    int Dequeue () {
        if ( Array.size() == 0 ) {
            std::cout << "Queue is empty" << std::endl;
            return -1;
        }
        int x = Array.front();
        Array.erase(Array.begin());
        return x;
    }
};

int main () {
    using namespace std;
    Queue q(10);
    q.Enqueue(10);
    q.Enqueue(20);
    q.Enqueue(30);

    cout << q.Dequeue() << endl;
    cout << q.Dequeue() << endl;
    return 0;
}
