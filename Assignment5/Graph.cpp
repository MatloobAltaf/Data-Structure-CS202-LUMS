#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"


Graph::Graph(char* file, bool isUnitLength=false)
{
	ifstream in_file;
	in_file.open(file);
	
	if (in_file.fail())
	{
		cout << "Error reading file!\n";
		exit(1);
	}
	
	string temp;
	in_file >> temp;
	in_file >> temp;
	while (temp != "CONNECTIONS")
	{
		node* temp_node = new node(0, temp);
		friends.push_back(temp_node);
		in_file >> temp;
		
	}
	
	while (!in_file.eof())
	{
		node* temp_origin;
		node* temp_dest;
		string sTemp1, sTemp2;
		float temp_weight;
		
		in_file >> sTemp1;
		for(int i=0; i<friends.size();i++){
			if(sTemp1 == friends[i]->name){
			temp_origin = (friends[i]);
			break;
			}
		}

		in_file >> sTemp2;
		for(int i=0; i<friends.size();i++){
			if(sTemp2 == friends[i]->name){
			temp_dest = (friends[i]);
			break;
			}
		}
		
		in_file >> temp_weight;
		
		if(isUnitLength){
			temp_weight = 1;
		}

		edge temp_edge1(temp_origin, temp_dest, temp_weight);
		temp_origin->edges.push_back(temp_edge1);
		connections.push_back(temp_edge1);
				
		edge temp_edge2(temp_dest, temp_origin, temp_weight);
		temp_dest->edges.push_back(temp_edge2);
	}
	
}

void Graph::display(node* temp)
{
	if(temp->visit)
		return;
	
	cout << "Person: " << temp->name;
	temp->visit = 1;
	for(int i=0; i< temp->edges.size(); i++)
	{
		if(!temp->edges[i].Origin->visit || !temp->edges[i].Dest->visit)
		cout << "->" << temp->edges[i].weight << endl;
		display(temp->edges[i].Origin);
		display(temp->edges[i].Dest);
	}
}

bool Graph::Reachable(string start, string dest)
{
	node* oNode;
	for(int i=0; i<friends.size();i++){
		if(start == friends[i]->name){
		oNode = (friends[i]);
		break;
		}
	}
	node* dNode;
	for(int i=0; i<friends.size();i++){
		if(dest == friends[i]->name){
		dNode = (friends[i]);
		break;
		}
	}

	  // Base case 
    if (oNode == dNode){
    	return true; 
	}
    // Mark all the vertices as not visited 
    for (int i = 0; i < friends.size(); i++) {
		friends[i]->visit = 0;
	}
  
    // Create a queue for BFS 
    queue<node*> myQueue; 
  
    // Mark the current node as visited and enqueue it 
    oNode->visit = 1; 
    myQueue.push(oNode); 
  
    while (!myQueue.empty()) 
    { 
        // Dequeue a vertex from queue and print it 
        oNode = myQueue.front(); 
        myQueue.pop(); 
  
        // Get all adjacent vertices of the dequeued vertex s 
        // If a adjacent has not been visited, then mark it visited 
        // and enqueue it 
        for (int i = 0; i < oNode->edges.size(); i++) 
        { 
            // If this adjacent node is the destination node, then  
            // return true 
            if (oNode->edges[i].Dest == dNode) 
                return true; 
  
            // Else, continue to do BFS 
            if (!oNode->edges[i].Dest->visit) 
            { 
                oNode->edges[i].Dest->visit = 1; 
                myQueue.push(oNode->edges[i].Dest); 
            } 
        } 
    } 
      
    // If BFS is complete without visiting dest
    return false; 

}

vector<node*> Graph::Prims()
{

//        int n = friends.size();
//    set<node*> B, N, diff;
//    tree;        //make tree with same node as graph
//    B.insert(friends[i]);     //insert start node in the B set

//    for(int u = 0; u<n; u++) {
//       N.insert(friends[i]); //add all vertices in the N set
//    }

//    while(B != N) {
//       int min = 9999;             //set as infinity
//       int v, par;
//       diff = difference(N, B);    //find the set N - B

//       for(int u = 0; u < n; u++) {
//          if(B.find(u) != B.end()) {
//             list<node>::iterator it;
//             for(it = friends[u].begin(); it != friends[u].end(); it++) {
//                if(diff.find(it->dest) != diff.end()) {
//                   if(min > it->cost) {
//                      min = it->cost;    //update cost
//                      par = u;
//                      v = it->dest;
//                   }
//                }
//             }
//          }
//       }

//       B.insert(v);
//       tree.addEdge(par, v, min);
//       tree.addEdge(v, par, min);
//    }
//    return tree;
}

vector<node*> Graph::Kruskal()
{
	
	pqueue<edge> p_edges(connections);
	
	vector<edge> edges_mst;
	
	tree nodes;
	
	vector<set<node*> >cloud;
	for (int i = 0; i < friends.size(); i++){
		set<node*> temp;
		temp.insert(friends[i]);
		cloud.push_back(temp);
	}
	
	while (p_edges.numE > 0){
		edge min_edge = p_edges.ExtractMin();
		
		int origin_index = find_node(cloud, min_edge.Origin);
		int dest_index = find_node(cloud, min_edge.Dest);
		
		if (origin_index != dest_index){
			edges_mst.push_back(min_edge);
			
			cloud[origin_index].insert(cloud[dest_index].begin(), cloud[dest_index].end());
			cloud.erase(cloud.begin() + dest_index);
		}
	}
	
	for (int i = 0; i < edges_mst.size(); i++){	
		cout << edges_mst[i].Origin->name << " " << edges_mst[i].Dest->name << " " << edges_mst[i].weight << endl;
	}
	
	vector<node*> result;
	return result;

}

vector<string> Graph::Dijkstra(string start, string dest, float &d)
{
	if(!Reachable(start,dest)){
		vector<string> temp ;
		temp.push_back("Not Connected !");
		for (int i = 0; i < temp.size(); i++)
		{
			cout << temp[i] << " ";	
		}
		return temp;
	}
	//initializing all the distances to infinity
	for (int i = 0; i < friends.size(); i++)
	{
		friends[i]->dist = 999999;
	}
	
	node *source;
	for(int i=0; i<friends.size();i++){
		if(start == friends[i]->name){
		source = (friends[i]);
		break;
		}
	}
	node *destination;
	for(int i=0; i<friends.size();i++){
		if(dest == friends[i]->name){
		destination = (friends[i]);
		break;
		}
	}
	source->dist = 0;
	
	vector<node*> nodes;
	for (int i = 0; i < friends.size(); i++)
	{
		nodes.push_back(friends[i]);
	}
	
	while (nodes.size() > 0)
	{

		int min_index = find_min(nodes);
		node *temp = nodes[min_index];
		
		nodes.erase(nodes.begin()+min_index);
		
		temp->visit = 1;
		for (int i = 0; i < temp->edges.size(); i++){
			if (!temp->edges[i].Dest->visit){
				float new_dist = temp->dist + temp->edges[i].weight;
				
				if (new_dist < temp->edges[i].Dest->dist){
					temp->edges[i].Dest->dist = new_dist;
					temp->edges[i].Dest->prev = temp;
				}
			}	
		}
		
	}
	
	vector<string> result;
	node *ptr = destination;
	while (ptr != source){
		result.push_back(ptr->name);
		ptr = ptr->prev;
	}
	result.push_back(source->name);
	
	
	reverse(result.begin(), result.end());
	
	for (int i = 0; i < result.size(); i++){
		cout << result[i] << "->";	
	}
	return result;
	
}
//Helper functions
set<int> Graph::difference(set<int> first, set<int> second) {
   set<int> :: iterator it;
   set<int> res;

   for(it = first.begin(); it != first.end(); it++) {
      if(second.find(*it) == second.end())
         res.insert(*it);    //add those item which are not in the second list
   }

   return res;    //the set (first-second)
}
int Graph::find_min(vector <node*> temp)
{
	float min = temp[0]->dist;
	int min_index = 0;
	
	for (int i = 1; i < temp.size(); i++)
	{
		if (temp[i]->dist < min)
		{
			min = temp[i]->dist;
			min_index = i; 
		}
	}
	
	return min_index;
}
int Graph::find_node(vector<set<node*> >cloud, node* temp)
{
	for (int i = 0; i < cloud.size(); i++)
	{
		if (cloud[i].find(temp) != cloud[i].end())
		{
			return i;	
		}	
	}	
	
	return -1;
}
bool operator < (edge a, edge b)
{
	if (a.weight < b.weight)
	{
		return true;
	}
	
	return false;
}

bool operator == (edge a, edge b)
{
	if (a.weight == b.weight)
	{
		return true;
	}
	
	return false;
}

bool operator > (edge a, edge b)
{
	if (a.weight > b.weight)
	{
		return true;
	}
	
	return false;
}

bool operator < (node a, node b)
{
	if (a.dist < b.dist)
	{
		return true;
	}
	
	return false;
}

bool operator == (node a, node b)
{
	if (a.dist == b.dist)
	{
		return true;
	}
	
	return false;
}

bool operator > (node a, node b)
{
	if (a.dist > b.dist)
	{
		return true;
	}
	
	return false;
}

int main()
{
	vector<node*>Mst;
	cout << "Welcome to Graphs" << endl;
	int c;
	cout << "Enter Name of File: ";
	char buf[256];
	cin >> buf;
	Graph *g = new Graph(buf, true);
	while(true)
	{
		cout << endl << endl;
		cout << "Press 1 to Exit" << endl;
		cout << "Press 2 to run Kruskal on Graph"<< endl;
		cout << "Press 3 to run Dijsktra on Graph"<< endl;
		cout << "Press 4 to Display a traversal of Graph"<< endl;
		cout << "Press 5 to Display MST"<< endl;
		cout << "Press 6 to Display Connected Components" << endl;
		cin >> c;
		cout << endl;
		
		if(c == 1)
		{
			break;
		}
		if(c == 2)
		{
			 Mst = g->Kruskal();
			 g = new Graph(buf);
		}
		if(c == 3)
		{
			string buff;
			string buff2;
			cout << "Enter Name of Origin: ";
			cin >> buff;
			cout << "Enter Name of Destination: ";
			cin >> buff2;
			float d;
			g->Dijkstra(buff, buff2, d);
		}
		if(c == 4)
		{
			for(int i=0; i< g->friends.size(); i++){
				g->friends[i]->visit = 0;
			}
			g->display(g->friends[0]);
		}
		if(c == 5)
		{
			// if(Mst.size() < 1)
			// {
			// 	cout << "Run Kruskal First" << endl;
			// 	continue;
			// }
			// for(int i=0; i< g->Mst.size(); i++)
			// 	Mst[i]->visit = 0;
			// g->display(Mst[0]);
		}
		if(c == 6) {
				string s,d;
				cout<<"Enter origin name"<<endl;
				cin>>s;
				cout<<"Enter dest name"<<endl;
				cin>>d;
				cout<<"(1 for True/0 for False) There's a connection	"<< g->Reachable(s,d)<<endl;
		}
	}
return 0;
}







#endif
