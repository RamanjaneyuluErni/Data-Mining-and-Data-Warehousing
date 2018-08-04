#include<bits/stdc++.h>
using namespace std;
typedef map<vector<int>,int> Mymap;
typedef vector<int> Myvec;
struct node
{
   Mymap trans;
} s1[10],s2[10],s[10];
void printMap(struct node s[],int thresh,int psize)
{
	thresh=(thresh*psize)/100;
	cout<<"support count : "<<thresh<<endl;
	for(int j=0;j<10;j++)
	{
	  if(s[j].trans.empty()) break;
	  cout<<"L:"<<j+1<<endl;
	  map<vector<int>,int>::iterator it=s[j].trans.begin();
      for(;it!=s[j].trans.end();it++)
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
}
void threshold(struct node s[],struct node sg[],int thresh,int psize)
{
	thresh=(thresh*psize)/100;
	for(int j=0;j<10;j++)
	{
	  if(s[j].trans.empty()) break;
	  map<vector<int>,int>::iterator it=s[j].trans.begin();
      for(;it!=s[j].trans.end();it++)
	  {
		  Myvec v =it->first;
		  if(it->second>=thresh)
		  {
		  	 sg[j].trans[v]=0;
		  }		  
	  }
	}	
}
void update(struct node s[],Myvec &vec,Myvec final,int count,int size)
{
   	if(count==final.size())
   	{
   		s[count-1].trans[final]++;
		return;
    }
    else
    {
       for(int i=size;i<vec.size();i++)
   	   {
   		 final.push_back(vec[i]);
   		 update(s,vec,final,count,i+1);
   		 final.pop_back();
	   }	
	}
   	
}
void do_partition(struct node s[],Myvec &vec)
{
	for(int i=1;i<=vec.size();i++)
	{
		Myvec final;
		update(s,vec,final,i,0);
	}
	
}
void threshold1(struct node s[],int thresh,int size)
{
	thresh=(thresh*size)/100;
	for(int j=0;j<10;j++)
	{
	  if(s[j].trans.empty()) break;
	  map<vector<int>,int>::iterator it=s[j].trans.begin();
      for(;it!=s[j].trans.end();)
	  {
		  Myvec v =it->first;
		  if(it->second<thresh)
		  {
		  	 it++;
		  	 s[j].trans.erase(v);
		  }	
		  else it++;	  
	  }
	}	
}
void frequency_count(struct node s[],Myvec &vec,Myvec final,int count,int size)
{
   	if(count==final.size())
   	{
   		if(s[count-1].trans.find(final)!=s[count-1].trans.end()) 
		 s[count-1].trans[final]++;
		return;
    }
    else
    {
       for(int i=size;i<vec.size();i++)
   	   {
   		 final.push_back(vec[i]);
   		 update(s,vec,final,count,i+1);
   		 final.pop_back();
	   }	
	}
   	
}
void Candidate_update(struct node s[])
{
	ifstream file("myTrans.txt");
    while(!file.eof())
    {
        string str;
    	getline(file,str,'I');
    	getline(file,str,'\n');
    	char *allitems=new char[str.length()];
    	strcpy(allitems,str.c_str());
    	char *tok=strtok(allitems," ");
    	Myvec v; 
    	while(tok)
    	{
    	  if(tok[0]=='I') tok=tok+1;
    	  int item=atoi(tok);
    	  v.push_back(item);
    	  tok=strtok(NULL," ");
        }
		for(int i=1;i<=v.size();i++)
		{
		   Myvec final;
		   frequency_count(s,v,final,i,0);	
		}	
   	}
	file.close();  
}
int main()
{
    ifstream file("myTrans.txt");
    int k=0;
    int total_trans=0;
    while(!file.eof())
    {
    	for(int i=0;i<5;i++)
    	{
    	  	string str;
    	    getline(file,str,'I');
    	    getline(file,str,'\n');
    	    char *allitems=new char[str.length()];
    	    strcpy(allitems,str.c_str());
    	    char *tok=strtok(allitems," ");
    	    Myvec v; 
    	    while(tok)
    	    {
    		  if(tok[0]=='I') tok=tok+1;
    		  int item=atoi(tok);
    		  v.push_back(item);
    		  tok=strtok(NULL," ");
            }	
            if(k==0)do_partition(s1,v);
            else do_partition(s2,v);
            total_trans++;
            if(file.eof()) break;
        }
		k++;
	}
	file.close();
    int thresh;
	cout<<"Enter support(percentage):";
	cin>>thresh;
	cout<<"Local frequent\n";
	int x=total_trans/2;
	int y=total_trans-x;
	printMap(s1,thresh,y);
	cout<<"Local frequent\n";
	printMap(s2,thresh,x);
	threshold(s1,s,thresh,y);
	threshold(s2,s,thresh,x);
	Candidate_update(s);
	threshold1(s,thresh,total_trans);
	cout<<"Global frequent\n";
	printMap(s,thresh,total_trans);
	return 0;
}
