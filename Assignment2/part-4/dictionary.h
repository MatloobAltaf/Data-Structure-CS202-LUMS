#ifndef __DICTIONARY_H
#define __DICTIONARY_H
#include <string>
#include "bst.h"
using namespace std;

class Dictionary {
	private:
	BST<string>* wordsTree;
    public:
    
    Dictionary(); // creates an empty (i.e. without words) Dictionary object
    ~Dictionary(); // frees the memory occupied by nodes containing words

    void initialize(string wordsFile); // populates words read from wordsFile into wordsTree, wordsFile is the name of the file

    node<string>* findWord(string word); // corresponds to node<T>* search(T k) 
    bool deleteWord(string word); // corresponds to void delete_node(T k) 
    bool editWord(string oldWord, string newWord); // changes the key, Therefore, the tree may need to be adjusted to maintain BST property
    bool insertWord(string word); // corresponds void insert(string val, T k)

};

#endif
