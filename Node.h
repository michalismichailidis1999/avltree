#ifndef NODE_H
#define NODE_H
#include <string>
#include <iostream>

using namespace std;


class Node
{
    public:
        Node();
        Node(string word);
        string data;
        Node* left;
        Node* right;
};

#endif // NODE_H
