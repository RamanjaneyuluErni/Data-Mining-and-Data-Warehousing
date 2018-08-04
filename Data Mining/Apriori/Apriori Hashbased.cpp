#include<bits/stdc++.h>
using namespace std;
typedef map<vector<int>,int> Mymap;
typedef vector<int>Myvec;
struct node
{
	vector< vector<int> >vec;
	int count;
}bucket[7];
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
	cout<<endl;
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
void print_hash()
{
	cout<<"hash table :\n";
	for(int i=0;i<7;i++)
	{
		cout<<i<<"\t"<<bucket[i].count<<"\t";
		for(int j=0;j<bucket[i].vec.size();j++)
		{
			Myvec v=bucket[i].vec[j];
			for(int k=0;k<2;k++) cout<<v[k]<<" ";
			cout<<"\t";
		}
		cout<<endl;
	}
}
void create_hashtable(Myvec &v)
{
	for(int i=0;i<v.size()-1;i++)
	{
		Myvec final;
		final.push_back(v[i]);
		for(int j=i+1;j<v.size();j++)
		{
			final.push_back(v[j]);
			int hash_val=(v[i]*10+v[j])%7; 
			bucket[hash_val].vec.push_back(final);
			bucket[hash_val].count++;
			final.pop_back();
		}
	}
}
Mymap Candidate(Mymap &trans,int thresh)
{
	Mymap ret;
	for(int i=0;i<7;i++)
	{
		if(bucket[i].count>=thresh)
		{
			for(int j=0;j<bucket[i].vec.size();j++)
		    {
		    	Myvec v=bucket[i].vec[j];
		    	ret[v]++;
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
bool pruning(Myvec &vec,Mymap &prev,int thresh)
{
	map<vector<int>,int>::iterator k=prev.begin();
	for(;k!=prev.end();k++)
	{
	  if(k->second<thresh)
	  {
	    Myvec v1=k->first;
	    int i=0,j=0;
	    for(i=0;i<v1.size();i++)
	    {
	    	if(find(vec.begin(),vec.end(),v1[i])!=vec.end()) j++;
		}
		if(j==v1.size()) return false;
	  }
    }
    return true;
}
Mymap Candidate_generate(Mymap &trans,Mymap &prev,int thresh)
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
	    	    if(pruning(second,prev,thresh)) ret[second] = 0;
			}
		}
	}
	return ret;
}
bool Frequency_count(Mymap &trans,Mymap &prev,int count,int thresh,int val)
{
	if(!trans.size()) false;
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
	prev=ret;
	threshold(ret,thresh);
	printMap(ret);	
	if(ret.size())
	{
   	  cout<<"L:"<<val<<endl;
	  printMap(ret);
	  cout<<endl;
	}
	trans=Candidate_generate(ret,prev,thresh);
	return valid;
}

int main()
{
	Mymap trans;
    ifstream file("myTrans.txt");
    while(!file.eof())
    {
    	string str;
    	getline(file,str,'I');
    	getline(file,str,'\n');
    	char *allitems=new char[str.length()];
    	strcpy(allitems,str.c_str());
    	char *tok=strtok(allitems," ");
    	Myvec v1;
    	while(tok)
    	{
    		Myvec v2;
    		if(tok[0]=='I') tok=tok+1;
    		int item=atoi(tok);
    		v1.push_back(item);
    		v2.push_back(item);
    		trans[v2]++;
    		tok=strtok(NULL," ");
        }
        create_hashtable(v1);	
	}
	file.close();
	print_hash();
	cout<<endl;
	int thresh,val=1,count=3;
	cout<<"Enter Threshold Value : ";cin>>thresh;
	cout<<"C:"<<val<<endl;
	printMap(trans);
	threshold(trans,thresh);
	cout<<"L:"<<val++<<endl;
	printMap(trans);
	trans=Candidate(trans,thresh);
	cout<<"C:"<<val<<endl;
	printMap(trans);
	threshold(trans,thresh);
	cout<<"L:"<<val++<<endl;
	printMap(trans);
	Mymap prev=trans;
	trans=Candidate_generate(trans,prev,thresh);
	while(Frequency_count(trans,prev,count++,thresh,val++));
	file.close();
	return 0;
}
