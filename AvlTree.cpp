#include "AvlTree.h"
#include "Node.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

AvlTree::AvlTree()
{
    size = 0;
    root = new Node();
}

AvlTree::~AvlTree()
{
    delete root;
}

void AvlTree::Insert(string word)
{
    size++;
    PrivateInsert(root, word);
}

void AvlTree::PrivateInsert(Node* n, string word){
    if(n->data == ""){
        n->data = word;
        return;
    }

    if(n->data == word){
        size--;
        return;
    }

    if(n->data > word && n->left == 0){
        Node* newNode = new Node(word);
        n->left = newNode;
        int heightDifference;

        Node* parent = getParent(root, n->data);
        if(parent != 0){
            heightDifference = isBalanced(parent);
            if(heightDifference > 1 || heightDifference < -1){
                balanceTree(heightDifference, parent);
                return;
            }
        }

        heightDifference = isBalanced(root);

        if(heightDifference > 1 || heightDifference < -1){
            balanceTree(heightDifference, root);
            return;
        }

        //if(getHeight(root->left) >= 2){
            //Node* node = getParent(root, word);
            //Node* parentOfNode = getParent(root, node->data);
            //heightDifference = isBalanced(parentOfNode);

            //if(heightDifference > 1 || heightDifference < -1){
                //balanceTree(heightDifference, parentOfNode);
                //return;
            //}
        //}

        return;
    }

    if(n->data > word && n->left != 0){
        PrivateInsert(n->left, word);
        return;
    }

    if(n->data < word && n->right == 0){
        Node* newNode = new Node(word);
        n->right = newNode;

        int heightDifference;

        Node* parent = getParent(root, n->data);
        if(parent != 0){
            heightDifference = isBalanced(parent);
            if(heightDifference > 1 || heightDifference < -1){
                balanceTree(heightDifference, parent);
                return;
            }
        }

        heightDifference = isBalanced(root);

        if(heightDifference > 1 || heightDifference < -1){
            balanceTree(heightDifference, root);
            return;
        }

        //if(getHeight(root->right) >= 2){
            //Node* node = getParent(root, word);
            //Node* parentOfNode = getParent(root, node->data);
            //heightDifference = isBalanced(parentOfNode);

            //if(heightDifference > 1 || heightDifference < -1){
               // balanceTree(heightDifference, parentOfNode);
                //return;
            //}
        //}

        return;
    }

    if(n->data < word && n->right != 0){
        PrivateInsert(n->right, word);
        return;
    }

    return;
}


bool AvlTree::Search(string word){
    return PrivateSearch(root, word);
}

bool AvlTree::PrivateSearch(Node* n, string word){
    if(n->data == word){
        return true;
    }else if(n->data > word && n->left != 0){
        return PrivateSearch(n->left, word);
    }else if(n->data > word && n->left == 0){
        return false;
    }else if(n->data < word && n->right != 0){
        return PrivateSearch(n->right, word);
    }else if(n->data < word && n->right == 0){
        return false;
    }
}

void AvlTree::Remove(string word){

    PrivateRemove(root, word);
    return;
}

void AvlTree::PrivateRemove(Node* n, string word){
    if(n->data == ""){
        return;
    }

    if(n->data == word){
        // 0 children
        if(n->left == 0 && n->right == 0){
            Node* parent = getParent(root, word);

            if(parent->left->data == word){
                parent->left = 0;
            }else{
                parent->right = 0;
            }

            size--;
            return;
        }

        // 2 children
        if(n->left != 0 && n->right != 0){
            Node* nodeToReplace = n->right;

            while(nodeToReplace->left != 0){
                nodeToReplace = nodeToReplace->left;
            }

            Node* nodeToReplaceParent = getParent(root, nodeToReplace->data);

            n->data = nodeToReplace->data;

            if(nodeToReplaceParent->left->data == nodeToReplace->data){
                nodeToReplaceParent->left = 0;
            }else{
                nodeToReplaceParent->right = 0;
            }

            size--;
            return;
        }

        // 1 children
        if((n->left != 0 && n->right == 0) || (n->left == 0 && n->right != 0)){
            if(n->left != 0 && n->right == 0){
                Node* parent = getParent(root, word);
                Node* nodeToReplace = n->left;

                if(parent->left->data == n->data){
                    parent->left = nodeToReplace;
                }else{
                    parent->right = nodeToReplace;
                }

            }else{
                Node* parent = getParent(root, word);
                Node* nodeToReplace = n->right;

                if(parent->left->data == n->data){
                    parent->left = nodeToReplace;
                }else{
                    parent->right = nodeToReplace;
                }
            }

            size--;
            return;
        }

    }

    if(n->data > word){
        if(n->left != 0){
            PrivateRemove(n->left, word);
            return;
        }else{
            return;
        }
    }

    if(n->data < word){
        if(n->right != 0){
            PrivateRemove(n->right, word);
            return;
        }else{
            return;
        }
    }

    return;
}

Node* AvlTree::getParent(Node* n,string word){
    if(word == root->data){
        return 0;
    }

    if(n->left != 0 && n->left->data == word){
        return n;
    }

    if(n->right != 0 && n->right->data == word){
        return n;
    }

    if(n->data > word){
        return getParent(n->left, word);
    }else{
        return getParent(n->right, word);
    }
}

void AvlTree::inorder(){
    if(root->data == ""){
        return;
    }
    PrivateInorder(root);
    cout << "\n";
}

void AvlTree::postorder(){
    if(root->data == ""){
        return;
    }
    PrivatePostorder(root);
    cout << "\n";
}

void AvlTree::preorder(){
    if(root->data == ""){
        return;
    }
    PrivatePreorder(root);
    cout << "\n";
}

void AvlTree::PrivateInorder(Node* n){
    if(n->left != 0){
        PrivateInorder(n->left);
    }

    cout << n->data << " ";

    if(n->right != 0){
        PrivateInorder(n->right);
    }
}

void AvlTree::PrivatePostorder(Node* n){
    if(n->left != 0){
        PrivateInorder(n->left);
    }

    if(n->right != 0){
        PrivateInorder(n->right);
    }

    cout << n->data << " ";
}

void AvlTree::PrivatePreorder(Node* n){
    cout << n->data << " ";

    if(n->left != 0){
        PrivateInorder(n->left);
    }

    if(n->right != 0){
        PrivateInorder(n->right);
    }
}


int AvlTree::getHeight(Node* n){
    if(n == 0){
        return -1;
    }

    int leftHeight = getHeight(n->left);
    int rightHeight = getHeight(n->right);

    if(leftHeight > rightHeight){
        return leftHeight + 1;
    }else{
        return rightHeight + 1;
    }
}

int AvlTree::isBalanced(Node* n){
    if(n == 0){
        return 0;
    }

    int lh = getHeight(n->left);
    int rh = getHeight(n->right);

    if(lh == -1){
        lh = 0;
    }else{
        lh++;
    }

    if(rh == -1){
        rh = 0;
    }else{
        rh++;
    }

    return lh - rh;
}

Node* AvlTree::getNodeToRotate(string direction, Node* n){
    string dir = direction;
    int heightDifference;
    Node* currentNode = n;

    while(dir != "stop"){
        if(dir == "left"){
            currentNode = currentNode->left;

            heightDifference = isBalanced(currentNode);

            if(heightDifference > 1){
                dir = "left";
            }else if(heightDifference < -1){
                dir = "right";
            }else{
                dir = "stop";
            }
        }else if(dir == "right"){
            currentNode = currentNode->right;

            heightDifference = isBalanced(currentNode);

            if(heightDifference > 1){
                dir = "left";
            }else if(heightDifference < -1){
                dir = "right";
            }else{
                dir = "stop";
            }
        }
    }

    return getParent(root, currentNode->data);
}

string* AvlTree::getRotation(Node* n){
    Node* currentNode = n;
    string* rotation = new string[2];

    int lh;
    int rh;

    for(int i = 0; i < 2; i++){
        lh = getHeight(currentNode->left);
        rh = getHeight(currentNode->right);

        if(lh > rh){
            rotation[i] = "left";
            currentNode = currentNode->left;
        }else{
            rotation[i] = "right";
            currentNode = currentNode->right;
        }
    }

    return rotation;
}

void AvlTree::balanceTree(int heightDifference, Node* n){
    string direction = (heightDifference > 0) ? "left" : "right";

    Node* nodeToRotate = getNodeToRotate(direction, n);

    string* rotation = getRotation(nodeToRotate);

    if(rotation[0] == "left" && rotation[1] == "left"){
        LL(nodeToRotate);
        return;
    }

    if(rotation[0] == "left" && rotation[1] == "right"){
        LR(nodeToRotate);
        return;
    }

    if(rotation[0] == "right" && rotation[1] == "right"){
        RR(nodeToRotate);
        return;
    }

    if(rotation[0] == "right" && rotation[1] == "left"){
        RL(nodeToRotate);
        return;
    }
}


void AvlTree::LL(Node* n){
    Node* child = n->left;

    Node* temp = new Node(n->data);

    if(n->right != 0){
        temp->right = n->right;
    }

    if(child->right != 0){
        temp->left = child->right;
    }

    child->right = temp;

    Node* parentOfNode = getParent(root, n->data);

    if(parentOfNode != 0){
        if(parentOfNode->left->data == n->data){
            parentOfNode->left = child;
        }else{
            parentOfNode->right = child;
        }
    }else{
        root = child;
    }
}

void AvlTree::LR(Node* n){
    Node* child = n->left;
    Node* grandChild = child->right;

    Node* tempLeft = new Node(child->data);

    if(child->left != 0){
        tempLeft->left = child->left;
    }

    if(grandChild->left != 0 || grandChild->right != 0)
    {
        if(grandChild->left != 0){
            tempLeft->right = grandChild->left;
        }else{
            tempLeft->right = grandChild->right;
        }
    }

    Node* tempRight = new Node(n->data);

    if(n->right != 0){
        tempRight->right = n->right;
    }

    grandChild->left = tempLeft;
    grandChild->right = tempRight;

    Node* parentOfNode = getParent(root, n->data);

    if(parentOfNode != 0){
        if(parentOfNode->left->data == n->data){
            parentOfNode->left = grandChild;
        }else{
            parentOfNode->right = grandChild;
        }
    }else{
        root = grandChild;
    }
}

void AvlTree::RR(Node* n){
    Node* child = n->right;

    Node* temp = new Node(n->data);

    if(n->left != 0){
        temp->left = n->left;
    }

    if(child->left != 0){
        temp->right = child->left;
    }

    child->left = temp;

    Node* parentOfNode = getParent(root, n->data);

    if(parentOfNode != 0){
        if(parentOfNode->left->data == n->data){
            parentOfNode->left = child;
        }else{
            parentOfNode->right = child;
        }
    }else{
        root = child;
    }
}

void AvlTree::RL(Node* n){
    Node* child = n->right;
    Node* grandChild = child->left;

    Node* tempLeft = new Node(n->data);

    if(n->left != 0){
        tempLeft->left = n->left;
    }

    if(grandChild->left != 0 || grandChild->right != 0)
    {
        if(grandChild->left != 0){
            tempLeft->right = grandChild->left;
        }else{
            tempLeft->right = grandChild->right;
        }
    }

    Node* tempRight = new Node(child->data);

    if(child->right != 0){
        tempRight->right = child->right;
    }

    grandChild->left = tempLeft;
    grandChild->right = tempRight;

    Node* parentOfNode = getParent(root, n->data);

    if(parentOfNode != 0){
        if(parentOfNode->left->data == n->data){
            parentOfNode->left = grandChild;
        }else{
            parentOfNode->right = grandChild;
        }
    }else{
        root = grandChild;
    }
}

bool AvlTree::isTreeBalanced(){
    int heightDifference = getHeight(root);

    if(heightDifference > 1 || heightDifference < -1){
        return true;
    }else{
        return false;
    }
}
