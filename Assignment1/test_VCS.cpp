#include "VCS.cpp"
#include<iostream>
#include<cstdlib>
#include<vector>
#include<ctime>
using namespace std;

string dict = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
int dictlength = dict.length();
struct test_VCS
{
	string data;
	string message;
	int time_stamp;
	test_VCS(string d, string m, int t){
		data = d;
		message = m;
		time_stamp = t;
	}
};
string generate_string(int length)
{
	string ret = "";
	for(int i=0; i<length; i++)
	{
		ret+=dict[rand()%dictlength];
	}
	return ret;
}

vector<test_VCS> generate_randomly()
{
	vector<test_VCS> ret;
	string data = "";
	for(int i=0; i<200; i++)
	{
		data = data+generate_string(rand()%10);
		string msg = generate_string(rand()%10);
		test_VCS node = test_VCS(data,msg,i);
		ret.push_back(node);
	}
	return ret;
}

void test_VCS_dispatcher()
{
	srand (time(NULL));
	string filename = "testfile";
	vector<test_VCS> test = generate_randomly();
	int total = 0;
	int points = 0;
	cout<<"INITIALIZING "<<endl;
	VCS vcs(filename);
	cout<<"COMMITING "<<endl;
	for(int i=0; i<200; i++)
	{
		ofstream file;
		string fname = filename+".txt";
		file.open(fname.c_str());
		file<<test[i].data;
		file.close();
		vcs.commit(test[i].message);
	}
	cout<<"TESTING UNDO ";
	bool undo = true;
	for(int i=1; i<100; i++)
	{
		string data = vcs.undo();
		ifstream file;
		string fname = filename+".txt";
		file.open(fname.c_str());
		string fdata;
		file>>fdata;
		file.close();
		//cout<<endl<<data<<endl<<" and "<<endl<<test[200-i-1].data<<endl;
		if(data!=test[200-i-1].data || data!=fdata)
		{
			undo = false;
			break;
		}
	}
	if(undo)
	{
		cout<<"PASSED."<<endl;
		total+=13;
		points+=13;
	}
	else
	{
		cout<<"FAILED."<<endl;
		total+=13;
	}
	cout<<"TESTING REDO ";
	bool redo = true;
	for(int i=101; i<200; i++)
	{
		string data = vcs.redo();
		ifstream file;
		string fname = filename+".txt";
		file.open(fname.c_str());
		string fdata;
		file>>fdata;
		file.close();
		//cout<<endl<<data<<endl<<" and "<<endl<<test[200-i-1].data<<endl;
		if(data!=test[i].data || data!=fdata)
		{
			redo = false;
			break;
		}
	}
	if(redo)
	{
		cout<<"PASSED."<<endl;
		total+=10;
		points+=10;
	}
	else
	{
		cout<<"FAILED."<<endl;
		total+=10;
	}
	cout<<"TESTING REVERT ";
	bool revert = true;
	for(int i=0; i<50; i++)
	{
		int index = rand()%200;
		string data = vcs.revert(index);
		ifstream file;
		string fname = filename+".txt";
		file.open(fname.c_str());
		string fdata;
		file>>fdata;
		file.close();
		if(data!=test[index].data || data!=fdata)
		{
			revert = false;
			break;
		}
		if(index>0)
		{
			string data = vcs.undo();
			if(data!=test[index-1].data)
			{
				revert = false;
				break;
			}
			vcs.redo();
		}
		if(index<199)
		{
			string data = vcs.redo();
			if(data!=test[index+1].data)
			{
				revert = false;
				break;
			}
			vcs.undo();
		}
	}
	if(revert)
	{
		cout<<"PASSED."<<endl;
		total+=5;
		points+=5;
	}
	else
	{
		cout<<"FAILED."<<endl;
		total+=5;
	}
	cout<<"POINTS: "<<points<<"/"<<total<<endl;

}

int main()
{
	test_VCS_dispatcher();
}