#ifndef __TREE_H
#define __TREE_H
#include <cstdlib>
#include <vector>
#include <iostream>
#include <cstring>
#include "queue.cpp"

using namespace std;

struct merge_state{
	int src_id;
	int dst_id;
};

struct VCS_node{
	string data;
	int time_stamp;
	VCS_node(){
		data = "";
		time_stamp=0;
	}
	VCS_node (string d, int t){
		data  = d;
		time_stamp = t;		
	}
};


struct TreeItem
{
	int id;
	string latest_data;	
	vector<TreeItem*> child; 
	vector <VCS_node> container;

	TreeItem()
	{
		id = 0;
		latest_data = "";
	}

	TreeItem(int Id, string Val)
	{
		this->id = Id;
		this->latest_data = Val;		
	}
};


class Tree
{
	TreeItem *root;
	vector<merge_state> history;

public:
	// Constructor
	Tree(string data); 

	// Destructor
	~Tree();
	

	// Memeber Functions
	void branch(int id);
	void merge(int src_id, int dst_id);
	void commit(int id,string new_data);
	TreeItem* get_node(int id);
	string get_file(int id,int t_stamp);
	vector<merge_state> merge_history();
	void level_traversal();

	/*You can add additional functions if necessary*/
};
#endif
