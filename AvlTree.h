#ifndef AVLTREE_H
#define AVLTREE_H
#include "Node.h"


class AvlTree
{
    public:
        AvlTree();
        ~AvlTree();
        void Insert(string word);
        void Remove(string word);
        bool Search(string word);
        void postorder();
        void preorder();
        void inorder();
        bool isTreeBalanced();

    private:
        int size;
        Node* root;

        void PrivateInsert(Node* n, string word);
        void PrivateRemove(Node* n, string word);
        bool PrivateSearch(Node* n, string word);
        Node* getParent(Node* n, string word);
        void PrivatePostorder(Node* n);
        void PrivatePreorder(Node* n);
        void PrivateInorder(Node* n);
        int getHeight(Node* n);
        int isBalanced(Node* n);
        void balanceTree(int heightDifference, Node* n);
        string* getRotation(Node* n);
        Node* getNodeToRotate(string direction, Node* n);
        void LL(Node* n);
        void LR(Node* n);
        void RR(Node* n);
        void RL(Node* n);
};

#endif // AVLTREE_H
