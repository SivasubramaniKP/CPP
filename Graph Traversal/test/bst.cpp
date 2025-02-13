#include <iostream>
#include <vector>
#include <deque>
class Node {
    public:
        int val;
        Node * left;
        Node * right;
        Node ( int x ) {
            this->val = x;
            this->right = nullptr;
            this->left = nullptr;
        }
};

class Queue {
    public:
    std::deque<Node *> arr;
    
    void Enqueue ( Node * x ) {
        arr.push_back(x);
    }
    Node * Dequeue () {
        if ( arr.empty() ) {
            return nullptr;
        }
        Node * x = arr.front();
        arr.pop_front();
        return x;
    }
    int getLength () {
        return arr.size();
    }
};

class BST {
    public:
    Node * root;
    BST () {
        this->root = nullptr;
    }

    void insert(int x) {
        this->root = InsertHelper(root, x);
    }
    void Inorder() {
        InorderHelper(root);
    }
    void Delete(int x) {
        this->root = deleteHelper(root, x);
    }

    void levelOrder () {
        Queue * queue = new Queue();
        std::vector<std::vector<int>> result;
        queue->Enqueue(root);
        while ( !queue->arr.empty() ) {
            std::vector<int> level;
            int nElements = queue->getLength();
            for ( int i = 0; i < nElements; i++ ) {
                Node * node = queue->Dequeue();
                if ( node != nullptr ) {
                    level.push_back(node->val);
                    queue->Enqueue(node->left);
                    queue->Enqueue(node->right);
                }
            }
            if ( !level.empty() ) {
                result.push_back(level);
            }
        }
        for ( std::vector<int> i : result ) {
            for ( int j : i ) {
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
        delete queue;
    }

    private:
        Node * InsertHelper ( Node * root, int x ) {
            if ( root == NULL ) return new Node(x);
            if ( x > root->val ) root->right = InsertHelper(root->right, x);
            else if ( x < root->val ) root->left = InsertHelper(root->left, x);
            else return root;
        }
        void InorderHelper ( Node * root ) {
            if ( root != NULL ) {
                InorderHelper(root->left);
                std::cout << root->val << std::endl;
                InorderHelper(root->right);
            }
        }
        int findMin ( Node * root ) {
            if ( root->left == nullptr ) {
                return root->val;
            }
            return findMin(root->left);
        }
        Node * deleteHelper( Node * root, int x ) {
            if ( root == nullptr ) return nullptr;
            if ( x < root->val ) root->left = deleteHelper(root->left,x );
            else if ( x > root->val ) root->right = deleteHelper(root->right, x);
            else {
                if ( root->left == nullptr || root->right ==nullptr ) {
                    Node * temp = ( root->left != nullptr ) ? root->left : root->right;
                    if ( temp == nullptr ) {
                        root = nullptr;
                    } else {
                        *root = *temp;
                    }
                } else {
                    int x = findMin(root->right);
                    root->val = x;
                    root->right = deleteHelper(root->right, x);
                }
            }
            return root;
        }
};

int main () {
    BST * tree = new BST();
    tree->insert(20);
    tree->insert(30);
    tree->insert(10);
    tree->insert(5);
    tree->insert(6);
    tree->levelOrder();

    return 0;  
}