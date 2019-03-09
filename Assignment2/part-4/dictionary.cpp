#ifndef __DICTIONARY_CPP
#define __DICTIONARY_CPP
#include "dictionary.h"
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <chrono>
using namespace std;

Dictionary::Dictionary() {
	
    wordsTree = new BST<string>();
}

Dictionary::~Dictionary(){
    
}

void Dictionary::initialize(string wordsFile) {

	ifstream in_file;
	in_file.open((wordsFile + ".txt").c_str());
	
	if (in_file.fail())
	{
		cout << "Error : Reading file. \n";
		return;
	}
	
	string item;
	while (!in_file.eof())
	{
		getline(in_file, item, '\n');
        cout<<item<<endl;
        wordsTree->insert(item, item);
	}
	cout<<"Done"<<endl;
    in_file.close();
    return;
}

bool Dictionary::deleteWord(string word) {
    if(!wordsTree->search(word))
    {
        return false;
    }
    else
    {
        wordsTree->delete_node(word);
        return true;
    }
}
bool Dictionary::editWord(string oldWord, string newWord) {

	node<string> *oldNode = wordsTree->search(oldWord);
	if (oldNode == NULL)
	{
		return false;
	}
	else
	{
		wordsTree->insert(newWord, newWord);
		wordsTree->delete_node(oldWord);
        return true;
	}	

}
bool Dictionary::insertWord(string word) {
	wordsTree->insert(word, word);
    return true;
}
node<string>* Dictionary::findWord(string word) {
	auto start = std::chrono::system_clock::now();

    // TODO your code here
    node<string>* temp = wordsTree->search(word);
    if(temp){
        cout<<"found"<<endl;
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    cout << "findWord() took " << elapsed_seconds.count() << "sec to search for " << word << endl;
    return NULL; // TODO
}

#endif

int main() {
    string srt, srt1;
    Dictionary d1;
    cout<<"Initializing tree"<<endl;
    d1.initialize("words");
    cout<<"testing delete words"<<endl;
    cin>>srt;
    if (d1.deleteWord(srt))
    {
        cout<<"passed"<<endl;
    }
    cout<<"testing insert"<<endl;
    if(d1.insertWord("matloob"))
    {
        cout<<"passed"<<endl;
    }
    cout<<"testing edit word"<<endl;
    if(d1.editWord("matloob","altaf"))
    {
        cout<<"passed"<<endl;
    }
    string w[26] = {"gopherberries","asterion","shemaka","close-clipped","jumbo","kernelless","focusless","prohydrotropic","economists","bostic","homotransplant","xns","vapouriser","outbarring","inoxidized","unlarcenous","wainscot-joinde","zellamae","deperditely","red-shirted","theistic","yogism","lecithinase","misguidedly","nongarrulous","quarantinable"};
    for(int i= 0; i<26; i++)
    {
        d1.findWord(w[i]);
    }
	return 0;
}
