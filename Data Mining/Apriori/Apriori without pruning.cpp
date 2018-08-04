#include<bits/stdc++.h>
using namespace std;
typedef map<vector<int>,int> Mymap;
typedef vector<int> Myvec;
void printMap(Mymap &trans)
{
	map<vector<int>,int>::iterator it=trans.begin();
	for(;it!=trans.end();it++)
	{
		Myvec v =it->first;
		for(int i=0;i<v.size();i++)
		{
			cout<<"I"<<v[i]<<" ";
		}
		cout<<"   "<<it->second<<endl;
	}
}
void threshold(Mymap &trans,int thresh)
{
	map<vector<int>,int>::iterator it=trans.begin();
	for(;it!=trans.end();)
	{
		Myvec v =it->first;
		if(it->second<thresh)
		{
			it++;trans.erase(v);
		}
		else it++;
	}
}
Mymap Candidate_generate(Mymap &trans)
{
	Mymap ret;
	map<vector<int>,int>::iterator i=trans.begin();
	map<vector<int>,int>::iterator j;
	for(;i!=trans.end();i++)
	{
		Myvec first = i->first;
		int f=first[first.size()-1];
		first.pop_back();
		j=i;j++;
		for(;j!=trans.end();j++)
		{
			Myvec second = j->first;
		    int s=second[second.size()-1];
	    	second.pop_back();
	    	if(first==second)
	    	{
	    		second.push_back(f);
	    		second.push_back(s);
	    		ret[second] = 0;
			}
		}
	}
	return ret;
}
void update(Mymap &trans,Myvec &vec,Myvec final,int count,bool &ret,int size)
{
   	if(count==final.size())
   	{
   		if(trans.find(final)!=trans.end())
   		{
   			trans[final]++;
			ret=true;
		}
		return;
    }
    else
    {
       for(int i=size;i<vec.size();i++)
   	   {
   		 final.push_back(vec[i]);
   		 update(trans,vec,final,count,ret,i+1);
   		 final.pop_back();
	   }	
	}
   	
}
bool Frequency_count(Mymap &trans,int count,int thresh,int val)
{
	if(!trans.size()) return false;
	ifstream fin("myTrans.txt");
	Mymap ret=trans;
	bool valid=false;
	while(!fin.eof())
	{
		string str;
		getline(fin,str,'I');
		getline(fin,str,'\n');
		char *allitems=new char[str.length()];
		strcpy(allitems,str.c_str());
		char *tok=strtok(allitems," ");
		vector<int>vec;
		while(tok)
		{
			if(tok[0]=='I') tok=tok+1;
			int item=atoi(tok);
			vec.push_back(item);
			tok=strtok(NULL," ");
		}
		vector<int>final;
		bool status=false;
		update(ret,vec,final,count,status,0);
		valid |= status;
	}
	fin.close();
	cout<<"C:"<<val<<endl;
	printMap(ret);
	threshold(ret,thresh);
	if(ret.size())
	{
   	  cout<<"L:"<<val<<endl;
	  printMap(ret);
	  cout<<endl;
	}
	trans=Candidate_generate(ret);
	return valid;
}
int main()
{
	Mymap trans;
	ifstream fin("myTrans.txt");
	while(!fin.eof())
	{
		string str;
		getline(fin,str,'I');
		getline(fin,str,'\n');
		char *allitems=new char[str.length()];
		strcpy(allitems,str.c_str());
		char *tok=strtok(allitems," ");
		while(tok)
		{
			if(tok[0]=='I') tok=tok+1;
			int item=atoi(tok);
			Myvec vec;
			vec.push_back(item);
			trans[vec]++;
			tok=strtok(NULL," ");
		}
	}
	fin.close();
	int thresh,count=2,val=2;	
	cout<<"Enter Threshold Value:";cin>>thresh;
	cout<<"C:1\n";
	printMap(trans);
	threshold(trans,thresh);
	cout<<"L:1"<<endl;
	printMap(trans);
	cout<<endl;
	trans=Candidate_generate(trans);
	while(Frequency_count(trans,count++,thresh,val++));
	fin.close();
	return 0;
}
