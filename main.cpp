#include <iostream>
#include <fstream>
#include "AvlTree.h"
#include <string>
#include <ctime>

using namespace std;

int main()
{
    AvlTree tree;

    fstream wordsFile("small-file.txt");

    if(wordsFile.is_open()){
        string word;
        int wordsInserted = 0;

        while(wordsFile >> word && wordsInserted < 2500){
            tree.Insert(word);
            wordsInserted++;
        }

         tree.inorder();
         cout << tree.isTreeBalanced() << endl;
         tree.Remove("singular");
         tree.postorder();
         tree.preorder();

        wordsFile.close();
    }else{
        cout << "Something went wrong!";
    }

    return 0;
}
