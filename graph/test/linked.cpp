#include <iostream>

class Node {

    public:
    Node * next;
    int x;
    Node ( int x ) {
        this->x = x;
        this->next = nullptr;
    }
};

class LinkedList{
    Node * head;
    Node * tail;
    public:
        LinkedList () {
            this->head = nullptr;
            this->tail = nullptr;
        }
        void addBegin ( int x ) {
            Node * temp = new Node(x);
            if ( head == nullptr && tail == nullptr ) {
                head = temp;
                tail = temp;
                return;
            } 
            temp->next = head;
            head = temp;
        } 
        void display () {
            Node * cur = head;
            while ( cur != nullptr ) {
                std::cout << cur->x << " ->";
                cur = cur->next;
            }
        }
        void reverse () {
            Node * prev = nullptr, *temp = nullptr, *cur = head;
            while ( cur != nullptr ) {
                temp = cur->next;
                cur->next = prev;
                prev = cur;
                cur = temp;
            }
            head = prev;
            tail = prev;
        }
};

int main () {
    LinkedList list;
    list.addBegin(10);
    list.addBegin(20);
    list.addBegin(30);
    list.reverse();
    list.display();
    return 0;
}
