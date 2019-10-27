#ifndef GRAPH__H
#define GRAPH__H
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <set>
#include <algorithm>
#include <queue>
#include "pqueue.cpp"
// You may include more libraries.

using namespace std;
class node;

class edge
{
	// You may add more variables and functions in this class
	public:
		node* Origin;
		node* Dest;
		float weight;
		edge() {
			Origin = NULL;
			Dest = NULL;
			weight = 0;
			};
		edge(node* a, node* b, float c){
			Origin = a;
			Dest = b;
			weight = c;
			};
		friend bool operator < (edge a, edge b);
		friend bool operator == (edge a, edge b);
		friend bool operator > (edge a, edge b);
};
class node
{
	// You may add more variables and functions in this class
	public:
		int visit; // flag to check if the node has been already visited
		string name;
		float dist;
		node* prev;
		vector<edge> edges; // edges connected to node
		node(){
			visit = 0;
			name = "";
			dist = 0;
		}
		node(int f, string n){
			visit = f;
			name = n;
			dist = 0;
		}
		friend bool operator < (node a, node b);
		friend bool operator == (node a, node b);
		friend bool operator > (node a, node b);
};

class tree
{
	public:
		tree() {
		};
		set<node*> treeS;
};

class Graph
{
	public:
		vector<node*> Mst; // minimum spanning tree
		vector<node*> friends;
		vector<edge> connections;
		Graph(char* filename, bool isUnitLength);
		void display(node* temp);// displays the graph

		bool Reachable(string start, string dest);
		vector<node*> Prims();
		vector<node*> Kruskal(); //runs kruskal algorithm and returns the Minimum spanning tree
		vector<string> Dijkstra(string start, string dest, float &d);

		//helper functions
		set<int> difference(set<int> first, set<int> second);
		int find_min(vector <node*> temp);
		int find_node(vector<set<node*> >cloud, node* temp);
};

#endif

