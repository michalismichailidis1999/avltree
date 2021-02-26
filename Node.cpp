#include "Node.h"
#include "AvlTree.h"
#include <iostream>

using namespace std;

Node::Node()
{
    data = "";
    left = 0;
    right = 0;
}

Node::Node(string word)
{
    data = word;
    left = 0;
    right = 0;
}
