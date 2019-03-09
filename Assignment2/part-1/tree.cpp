#ifndef __TREE_CPP
#define __TREE_CPP
#include "tree.h"

// try to make get_node() and get_file() after tree initialization


Tree::Tree(string data)
{
	//TreeItem* new_node= new TreeItem();
	int id = 1;
	root = new TreeItem(id, data);
	VCS_node vTemp =  VCS_node(data, 0);
	root->container.push_back(vTemp);
	
	// write the rest of the code here
}

Tree::~Tree()
{
}


void Tree::branch(int id)
{
	if(root==NULL)
	{
		return;
	}
	Queue<TreeItem*> q;
	q.enqueue(root);
	while(!q.isEmpty())
	{
		int iSize = q.length();
		while(iSize > 0)
		{
			TreeItem* temp_Item = q.dequeue();
			if(id == temp_Item->id)
			{
				if(temp_Item->child.size() < 9 )
				{
					TreeItem* new_node = new TreeItem(stoi(to_string(temp_Item->id)+to_string(temp_Item->child.size()+1)),temp_Item->latest_data);
					VCS_node vTemp =  VCS_node(temp_Item->latest_data, 0);
					new_node->container.push_back(vTemp);
					temp_Item->child.push_back(new_node);
					return;
				}
				else return;
			}

			for(int i=0; i< temp_Item->child.size(); i++)
			{
				q.enqueue(temp_Item->child[i]);
			}
			iSize--;

		}
		
	}
	
}

void Tree::merge(int src_id,int dst_id)
{
	if(root==NULL)
	{
		return;
	}
	Queue<TreeItem*> q;
	q.enqueue(root);
	while(!q.isEmpty())
	{
		int iSize = q.length();
		while(iSize > 0)
		{
			TreeItem* temp_Item = q.dequeue();
			if(src_id == temp_Item->id)
			{
				if (src_id==dst_id)
				{
					temp_Item->latest_data += temp_Item->latest_data;
				}
				else
				{
					Queue<TreeItem*> q2;
					q2.enqueue(root);
					while(!q2.isEmpty())
					{
						int iSize2 = q2.length();
						while(iSize2 > 0)
						{
							TreeItem* temp_Item2 = q2.dequeue();
							if(dst_id == temp_Item2->id)
							{
								temp_Item2->latest_data += temp_Item->latest_data;
								merge_state mTemp;
								mTemp.src_id = src_id;
								mTemp.dst_id = dst_id;
								history.push_back(mTemp);
								return;	
							}
							for(int j=0; j< temp_Item2->child.size(); j++)
							{
								q2.enqueue(temp_Item2->child[j]);
							}
							iSize2--;
						}
					}
				}
			}

			for(int i=0; i< temp_Item->child.size(); i++)
			{
				q.enqueue(temp_Item->child[i]);
			}
			iSize--;
		}
	}
	return;
}

void Tree::commit(int src_id,string new_data)
{ 
	if(root==NULL)
	{
		return;
	}
	Queue<TreeItem*> q;
	q.enqueue(root);
	while(!q.isEmpty())
	{
		int iSize = q.length();
		while(iSize > 0)
		{
			TreeItem* temp_Item = q.dequeue();
			if(src_id == temp_Item->id)
			{
				temp_Item->latest_data += new_data;
				int iTemp = temp_Item->container.size();
				VCS_node vTemp =  VCS_node(temp_Item->latest_data, iTemp);
				temp_Item->container.push_back(vTemp);
				 return;
			}

			for(int i=0; i< temp_Item->child.size(); i++)
			{
				q.enqueue(temp_Item->child[i]);
			}
			iSize--;

		}
		
	}
}

string Tree::get_file(int id, int t_stamp)
{
	string sEmpty="";
	if(root==NULL)
	{
		return sEmpty;
	}
	Queue<TreeItem*> q;
	q.enqueue(root);
	while(!q.isEmpty())
	{
		int iSize = q.length();
		while(iSize > 0)
		{
			TreeItem* temp_Item = q.dequeue();
			if(id == temp_Item->id)
			{
				for(int j=0; j<temp_Item->container.size(); j++)
				{
					if(t_stamp == temp_Item->container[j].time_stamp)
					{
						return (temp_Item->container[j].data);
					}
				}
			}

			for(int i=0; i< temp_Item->child.size(); i++)
			{
				q.enqueue(temp_Item->child[i]);
			}
			iSize--;

		}
		
	}
	return sEmpty;
} 

TreeItem* Tree::get_node(int id)
{
	if(root==NULL)
	{
		return root;
	}
	Queue<TreeItem*> q;
	q.enqueue(root);
	while(!q.isEmpty())
	{
		int iSize = q.length();
		while(iSize > 0)
		{
			TreeItem* temp_Item = q.dequeue();
			if(id == temp_Item->id)
			{
				return temp_Item;
			}

			for(int i=0; i< temp_Item->child.size(); i++)
			{
				q.enqueue(temp_Item->child[i]);
			}
			iSize--;

		}
		
	}
	return NULL;
} 

vector<merge_state> Tree::merge_history()
{
	return history;
}

void Tree::level_traversal() 
{ 
	if(root==NULL)
	{
		return;
	}
	Queue<TreeItem*> q;
	q.enqueue(root);
	while(!q.isEmpty())
	{
		int iSize = q.length();
		while(iSize > 0)
		{
			TreeItem* temp_Item = q.dequeue();
			std::cout<<temp_Item->latest_data<<"\t";
			std::cout<<temp_Item->id<<"\t\t";
			for(int i=0; i < temp_Item->child.size(); i++)
			{
				q.enqueue(temp_Item->child[i]);
			}
			iSize--;

		}
		std::cout<<"\n";
	}
}

#endif
