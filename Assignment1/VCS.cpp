#ifndef VCS_CPP
#define VCS_CPP
#include "VCS.h"
#include <iostream>
#include <string>
using namespace std;
//base constructor, init
VCS::VCS(string fname)
{
	curr_size=0;
	filename=fname;
	
}

//destructor
VCS::~VCS()
{
	curr_size=0;
}


//time to commit
void VCS::commit(string msg)
{
	string sData="",stemp;
	VCS_node temp = VCS_node(msg,curr_size);
	container1.push(temp);
	string fname = (filename + ".txt").c_str();
	ifstream myFile;
	myFile.open(fname);
	if(myFile.fail())
	{
		return;
	}
	while(myFile>>stemp)
	{
		sData += stemp;
	}
	myFile.close();
	fname= (filename+to_string(curr_size) + ".txt").c_str();
	ofstream retFile;
	retFile.open(fname);
	if(retFile.good())
	{
		retFile<<sData;
	}
	retFile.close();
	curr_size++;

}

//print status of every version
void VCS::status()
{
	int iPrint=5;
	string sLine;
	for(int i=0; i<iPrint;i++)
	{
		ifstream tempFile;
		string sLine = container1.top().message;
		int iTimeStamp = container1.top().time_stamp;
		container2.push(container1.pop());
		cout<<iTimeStamp<< "\n"<<sLine<<endl;
	}
	for(int i=0;i<iPrint;i++)
	{
		container1.push(container2.pop());
	}

}

//goes one step back
string VCS::undo()
{
	container2.push(container1.pop());
	int iTemp = container1.top().time_stamp;
	string sData = "",stemp;
	ifstream myFile;
	myFile.open(filename + to_string(iTemp) + ".txt");
	while(myFile>>stemp)
	{
		sData += stemp;
	}
	myFile.close();

	ofstream newFile;
	newFile.open(filename + ".txt");
	if(newFile.good())
	{
		newFile<<sData;
	}
	return sData;
	
}

//one step ahead
string VCS::redo()
{
	container1.push(container2.pop());
	int iTemp = container1.top().time_stamp;
	string sData = "",stemp;
	ifstream myFile;
	myFile.open(filename + to_string(iTemp) + ".txt");
	while(myFile>>stemp)
	{
		sData += stemp;
	}
	myFile.close();

	ofstream newFile;
	newFile.open(filename + ".txt");
	if(newFile.good())
	{
		newFile<<sData;
	}
	return sData;
	
}

//goes t_stamp step back or ahead
string VCS::revert(int t_stamp)
{
		int iTemp = container1.top().time_stamp;
		if(t_stamp<=iTemp)
		{
			for(int i=0;i<iTemp-t_stamp; i++)
			{
				string s=undo();
			}
		}
		else
		{
			for(int i=0;i < t_stamp -iTemp;i++)
			{
				string t=redo();
			}
		}
	string sData = "",stemp;
	ifstream myFile;
	myFile.open(filename + to_string(t_stamp) + ".txt");
	while(myFile>>stemp)
	{
		sData += stemp;
	}
	myFile.close();

	ofstream newFile;
	newFile.open(filename + ".txt");
	if(newFile.good())
	{
		newFile<<sData;
	}
	return sData;
		
}

#endif

