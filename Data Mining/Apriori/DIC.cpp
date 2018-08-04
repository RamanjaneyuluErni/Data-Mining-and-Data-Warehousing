#include<bits/stdc++.h>
using namespace std;
typedef map< vector<int>,pair<int,int> >Mymap;
Mymap DC,DS,SC,SS;
vector<int>vec_items;
void printMap(Mymap &trans)
{
	Mymap::iterator it=trans.begin();
	for(;it!=trans.end();it++)
	{
		vector<int> v =it->first;
		for(int i=0;i<v.size();i++) cout<<"I"<<v[i]<<" ";
		cout<<"   "<<it->second.first<<endl;
	}
}
void get_one_itemset_dc(ifstream &file,int &total)
{
	while(!file.eof())
	{
		string str;
		getline(file,str,'I');
		getline(file,str,'\n');
		char *items=new char[str.length()];
		strcpy(items,str.c_str());
		char *tok=strtok(items," ");
		while(tok)
		{
			if(tok[0]=='I') tok=tok+1;
			vector<int> v;
			v.push_back(atoi(tok));
			if(DC.find(v)==DC.end()) 
			{
				DC[v]=make_pair(0,0);
				vec_items.push_back(atoi(tok));
			}
			tok=strtok(NULL," ");
		}
		total++;
	}
	
}
void get_trans(vector< vector<int> >&trans,ifstream &file,int p)
{
	cout<<"\ntransactions\n";
	for(int i=0;i<p;i++)
	{
		string str;
		getline(file,str,'I');
		getline(file,str,'\n');
		char *items=new char[str.length()];
		strcpy(items,str.c_str());
		char *tok=strtok(items," ");
		vector<int> v;
		while(tok)
		{
			if(tok[0]=='I') tok=tok+1;
			int item=atoi(tok);
			v.push_back(item);
			tok=strtok(NULL," ");
		}
		for(int i=0;i<v.size();i++) cout<<v[i]<<" ";cout<<endl;
		trans.push_back(v);
	}
}
void update(vector<int> temp,vector<int> final,int size,int start)
{
	if(final.size() == size)
	{
		if(DS.find(final)!=DS.end()) DS[final].first++;
		if(DC.find(final)!=DC.end()) DC[final].first++;
		return;
	}
	else
	{
		for(int i=start;i<temp.size();i++)
		{
			final.push_back(temp[i]);
			update(temp,final,size,i+1);
			final.pop_back();
		}
	}
}
void check(vector<int> temp,vector<int> final,int size,int start,bool &status)
{
	if(final.size() == size)
	{
		if(DS.find(final)==DS.end() && SS.find(final)==SS.end()) status=false;
		return;
	}
	else
	{
		for(int i=start;i<temp.size();i++)
		{
			final.push_back(temp[i]);
			if(status)check(temp,final,size,i+1,status);
			final.pop_back();
		}
	}
}
bool check_subsets(vector<int> superset)
{
	bool status=true;
	for(int i=1;i<superset.size();i++)
	{
		vector<int> final;
		check(superset,final,i,0,status);
		if(status==false) return false;	
	}
	return true;
}
int main()
{
	int p=3,curt=0,total=0,thresh=2,c=1;
	ifstream file;
	file.open("myTrans.txt");
	get_one_itemset_dc(file,total);
	cout<<"Initial DC\n";
	printMap(DC);
	sort(vec_items.begin(),vec_items.end());
	cout<<"\nitems : ";
	for(int i=0;i<vec_items.size();i++) cout<<vec_items[i]<<" "; cout<<endl;
	
	while(!DC.empty() || !DS.empty())
	{
		if(curt==0)
		{
			file.close();
			file.open("myTrans.txt");
		}
		vector<vector<int> >trans;
		get_trans(trans,file,p);
		curt=(curt+p)%total;
		for(int i=0;i<trans.size();i++)
		{
			vector<int> temp=trans[i];
			for(int j=1;j<=temp.size();j++)
			{
				vector<int> final;
			    update(temp,final,j,0);
			}	
		
		}
		vector< vector<int> >add;
		vector< vector<int> >added_DC;
		for(Mymap::iterator it=DC.begin();it!=DC.end();)
		{
			if(it->second.first>=thresh)
			{
				vector<int> v=it->first;
				DS[it->first]=it->second;
				it++;
				DC.erase(v);
				added_DC.push_back(v);
			}
			else it++;
		}
		for(int i=0;i<added_DC.size();i++)
		{
	        vector<int> super=added_DC[i];
			vector<int> superset;
			for(int i=0;i<vec_items.size();i++)
			{
				if(find(super.begin(),super.end(),vec_items[i])!=super.end()) continue;
				superset=super;
				superset.push_back(vec_items[i]);
				sort(superset.begin(),superset.end());
				if(check_subsets(superset)) add.push_back(superset); // adding superset to DC	
			}
		}
		for(Mymap::iterator it=DS.begin();it!=DS.end();) 
		{
		  int k=it->second.second+p;
		  if(k>=total)
		  {
		  	SS[it->first]=it->second; 
		  	vector<int> x=it->first; it++;
		  	DS.erase(x);
		  }
		  else
		  {
		  	it->second.second+=p; it++;
		  }
		}
		
		for(Mymap::iterator it=DC.begin();it!=DC.end();)
		{
		  int k=it->second.second+p;
		  if(k>=total)
		  {
		  	SC[it->first]=it->second;
		  	vector<int> x=it->first;it++;
		  	DC.erase(x);
		  }
		  else
		  {
		  	it->second.second+=p;it++;
		  }
		}
		for(int i=0;i<add.size();i++) DC[add[i]]=make_pair(0,0);
			
		cout<<"AFTER ITERATION:"<<c<<endl;
		cout<<"PRINTING SS:"<<endl;
		printMap(SS);
		cout<<"PRINTING SC:"<<endl;
		printMap(SC);
		cout<<"PRINTING DS:"<<endl;
		printMap(DS);
		cout<<"PRINTING DC:"<<endl;
		printMap(DC);
		c++;
	}
	cout<<"\nFinal Frequent Itemsets\n";
	printMap(SS);
	return 0;
}
