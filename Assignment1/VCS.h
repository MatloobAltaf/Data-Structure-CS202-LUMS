#ifndef VCS_H
#define VCS_H
#include<fstream>
#include "stack.cpp"
#include "queue.cpp"
using namespace std; 
// A node on a Version Control System is the state of a file at certain time, VCS node contains data in form of a string in it.
struct VCS_node{
	string message;
	int time_stamp;
	VCS_node(){
		message = "";
		time_stamp=0;
	}
	VCS_node (string m, int t){
		time_stamp = t;
		message  = m;
	}
};

// VCS will have a container to store different versions of file, you have to make choice between stack or queue. 
// Also argue in favour of your choice of container.
class VCS{
public:
	// Containers
	Stack<VCS_node> container1;
	Stack<VCS_node> container2;
	string filename;
	int curr_size;
	// Base constructor
	VCS(string fname);
	//Destructor
	~VCS();
	//Functionalities
	void commit(string msg);
	void status();
	string undo();
	string redo();
	string revert(int t_stamp);
};

#endif