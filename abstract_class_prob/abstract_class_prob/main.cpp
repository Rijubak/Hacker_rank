#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node {
    Node* next;
    Node* prev;
    int value;
    int key;
    Node(Node* p, Node* n, int k, int val) :prev(p), next(n), key(k), value(val) {};
    Node(int k, int val) :prev(NULL), next(NULL), key(k), value(val) {};
};

class Cache {

protected:
    map<int, Node*> mp; //map the key to the node in the linked list
    int cp;  //capacity
    Node* tail; // double linked list tail pointer
    Node* head; // double linked list head pointer
    virtual void set(int, int) = 0; //set function
    virtual int get(int) = 0; //get function

};

class LRUCache : public Cache {
public:
    int cur_size;
    LRUCache(int capacity)
    {
        cur_size = 0;
        cp = capacity;
        head = new Node(0, 0); //dummy head node
        tail = new Node(head, nullptr, 0, 0); //dummy tail node
        head->next = tail;
    }

    void addNode(Node* node)
    {
        node->prev = head;
        node->next = head->next;

        head->next->prev = node;
        head->next = node;
    }

    void removeNode(Node* node)
    {
        Node* prev_node = node->prev;
        Node* next_node = node->next;

        prev_node->next = next_node;
        next_node->prev = prev_node;

        node->next = nullptr;
        node->prev = nullptr;
    }

    void moveToHead(Node* node)
    {
        removeNode(node);
        addNode(node);
    }

    Node* popTail()
    {
        Node* node = tail->prev;
        removeNode(node);
        return node;
    }

    void set(int key, int val) override
    {
        if (mp.find(key) == mp.end())  //if key doesn't exist
        {
            Node* node = new Node(key, val); //create a new node
            mp[key] = node;
            addNode(node); //add noded to linked list
            cur_size++; 

            if (cur_size > cp) //if current size of linked list is greater than capacity
            {
                Node* node = popTail(); //pop of the tail
                mp.erase(node->key); //remove tail's key from map
                cur_size--; 
            }
        }
        else //key exists in map
        {
            Node* node = mp.at(key); //obtain the node with key
            node->value = val; //obtain value
            moveToHead(node); //move the node to head since it's used most recently
        }


    }

    int get(int key) override
    {
        if (mp.find(key) == mp.end()) return -1;  //if key doesn't exist return -1;
        Node* node = mp[key];      //obtain the node corresponding to the key

        moveToHead(node);    //move the node to head, since it is MRU
        return node->value;          //return the value
    }

};
int main() {
    int n, capacity, i;
    cin >> n >> capacity;
    LRUCache l(capacity);
    for (i = 0; i < n; i++) {
        string command;
        cin >> command;
        if (command == "get") {
            int key;
            cin >> key;
            cout << l.get(key) << endl;
        }
        else if (command == "set") {
            int key, value;
            cin >> key >> value;
            l.set(key, value);
        }
    }
    return 0;
}
