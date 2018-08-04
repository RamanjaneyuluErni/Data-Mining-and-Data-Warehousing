#include<bits/stdc++.h>
using namespace std;
struct data{
	//string rid;
	string details[6];
};
struct tree_node{
	int tag;
	struct us{
		string label;
		string name;
		vector<string> criterion;
		vector<tree_node*> ptr;
	}u;
};
vector <string> attr_list;
vector<string> attribute_list;
void print_tree(tree_node* t)
{
	//cout<<"tree"<<endl;
	if(t->tag==0)
	{
		cout<<t->u.label<<" "<<endl;
	}
	else
	{
		queue<tree_node*> q;vector<string> c;
		q.push(t);
		q.push(NULL);
		while(!q.empty())
		{
			t=q.front();q.pop();
			if(t==NULL)
			{
				//cout<<"check 3"<<endl;
				cout<<endl;
				for(int i=0;i<(c).size();i++) cout<<c[i]<<"-";
				cout<<endl;
				c.clear();
				if(q.empty())break;
				q.push(NULL);
				//cout<<"check"<<endl;
			}
			else
			{
				//cout<<"check 1"<<endl;
				if(t->tag==1){
					cout<<t->u.name<<" ";
					for(int i=0;i<(t->u.criterion).size();i++)c.push_back(t->u.criterion[i]);
					for(int i=0;i<(t->u.ptr).size();i++)q.push(t->u.ptr[i]);
				}
				else
				{
					cout<<t->u.label<<" ";
				}
				//cout<<"check 2"<<endl;
			}
		}
	}
}
void print_db(data D[],int n)
{
	for(int i=0;i<attribute_list.size();i++)cout<<attribute_list[i]<<"  ";
	cout<<endl;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<6;j++) cout<<D[i].details[j]<<" ";
		cout<<endl;
	}
}
double info(struct data D[],int n,int p)
{
	set<string> s;int i;
	for(int i=0;i<n;i++)
	{
		s.insert(D[i].details[p]);
	}
	double sum=0;set<string> :: iterator m;
	for(i=0,m=s.begin();m!=s.end(),i<s.size();m++,i++)
	{
		string s=*m;double count=0;
		for(int j=0;j<n;j++) if(D[j].details[p]==s) count++;
		sum= sum+(count/n)*(log(count/n)/log(2));
	}
	return -1*sum;
}
double calculate_gain(struct data D[],int n,int p)
{
	set<string> s;
	//queue<int> gains;
	int i;
	for(i=0;i<n;i++)
	{
		s.insert(D[i].details[p]);
	}
	double sum=0;
	set<string> :: iterator m;
	for(i=0,m=s.begin();m!=s.end(),i<s.size();m++,i++)
	{
		string s=*m;//q.top();q.pop();
		double count=0;
		for(int j=0;j<n;j++)
		{
			if(D[j].details[p]==s){
				count=count+1;	
			}
		}
		//cout<<s<<"size "<<count<<endl;
		struct data d[(int)count];int x=0;
		for(int j=0;j<n;j++)
		{
			if(D[j].details[p]==s){
				for(int z=0;z<6;z++) d[x].details[z]=D[j].details[z];
				x++;
			}
		}
		//cout<<s<<endl;print_db(d,x);
		sum=sum+((count)/n)*info(d,x,5);
	}
	//cout<<"info"<<info(D,n,5)<<endl;
	return info(D,n,5)-sum;
}
int selection(struct data D[],int n,vector<string> v)
{
	double max=0;int ind;
	for(int i=0;i<v.size();i++)
	{
		int p=-1;
		for(int j=0;j<attribute_list.size();j++)if(attribute_list[j]==v[i]){
			p=j;break;
		}
		double x=calculate_gain(D,n,p);
		if(x>max)
		{
			max=x;ind=i;
		}
		cout<<v[i]<<" gain= "<<x<<endl;
	}
	cout<<endl;
	return ind;
}
tree_node* generate_tree(struct data D[],int n,vector <string> v)
{
	tree_node* t;t=new tree_node();
	set<string> s;
	for(int i=0;i<n;i++) s.insert(D[i].details[5]);
	if(s.size()==1)
	{
		t->tag=0;
		t->u.label=*s.begin();
		return t;
	}
	else if(attr_list.size()==0)
	{
	    map<string,int>m;
		for(int i=0;i<n;i++) m[D[i].details[5]]++;
		map<string,int>::iterator it=m.begin();
		string str;
		int max=0;
		for(;it!=m.end();it++)
		{
			if(it->second>max)
			{
				max=it->second;
				str=it->first;
			}
		}
		t->tag=0;
		t->u.label=str;
		return t;
	}
	else
	{
		int x=selection(D,n,attr_list);
		string name=attr_list[x];
		cout<<"attr selected :"<<attr_list[x]<<endl;
		attr_list.erase(find(attr_list.begin(),attr_list.end(),name));
		t->tag=1;
		t->u.name=name;
		s.clear();
		int i=0,p;
		for(i=0;i<v.size();i++) if(v[i]==name){p=i;break;}
		for(i=0;i<n;i++)
		{
			s.insert(D[i].details[p]);
		}
		set<string> :: iterator m;
		for(i=0,m=s.begin();m!=s.end(),i<s.size();m++,i++)
		{
			string s=*m;//q.top();q.pop();
			double count=0;
			for(int j=0;j<n;j++)
			{
				if(D[j].details[p]==s){
				count=count+1;	
				}
			}
			tree_node* tr;
			if(count==0)
			{
				tr=new tree_node();
				tr->tag=0;map<string,int> mp;set<string> se;
				for(int z=0;z<n;z++)
				{
					mp[D[z].details[5]]++;se.insert(D[z].details[5]);
				}
				set<string> ::iterator it;string str;int max=0;
				for(it=se.begin();it!=se.begin();it++)
				{
					if(mp[*it]>max)
					{
						max=mp[*it];str=*it;
					}
				}
				tr->u.label=*it;
			}
		//cout<<s<<"size "<<count<<endl;
		else{
			struct data d[(int)count];x=0;
			for(int j=0;j<n;j++)
			{
				if(D[j].details[p]==s){
				for(int z=0;z<6;z++) d[x].details[z]=D[j].details[z];
				x++;
				}
			}
			//print_tree(t);
			tr=generate_tree(d,x,v);
			//print_tree(t);
			}
			if(tr!=NULL)(t->u.ptr).push_back(tr);
			if(tr!=NULL)(t->u.criterion).push_back(s);
			//print_tree(t);
		}
	}
	return t;
}
string decide(tree_node* t,struct data d)
{
	if(t->tag==0)
	{
		return t->u.label;
	}
	else
	{
		int p=-1,j=-1;
		for(int i=0;i<attribute_list.size();i++) if(t->u.name==attribute_list[i]){p=i;break;}
		for(int i=0;i<(t->u.criterion).size();i++) if(t->u.criterion[i]==d.details[p]){j=i;break; }
		if(j!=-1) return decide(t->u.ptr[j],d);
	}
	return "Unpredictable";
}
vector<string> y;
void traverse(tree_node *t)
{
	if(t->tag==0)
	{
		for(int i=0;i<y.size();i++) cout<<y[i]<<" ";
		cout<<t->u.label<<endl;return;
	}
	else
	{
		//cout<<t->u.name<<" ";
		y.push_back(t->u.name);
		for(int i=0;i<(t->u.criterion).size();i++) { //cout<<t->u.criterion[i]<<" ";
			y.push_back(t->u.criterion[i]);
			traverse(t->u.ptr[i]);
			y.erase(find(y.begin(),y.end(),t->u.criterion[i]));
		}
		y.erase(find(y.begin(),y.end(),t->u.name));
	}
}
int main()
{
	ifstream fin("student_db.txt");
	int n1,n2;
	fin>>n1>>n2;
	data D[n1];
	string s;int i=0;
	for(int j=0;j<n2;j++)
	{
		fin>>s;
		attribute_list.push_back(s);
	}
	
	while(!fin.eof())
	{
			for(int j=0;j<6;j++) fin>>D[i].details[j];
			i++;//cout<<i<<endl;print_db(D,i);
	}
	fin.close();
	for(int i=1;i<attribute_list.size()-1;i++) attr_list.push_back(attribute_list[i]);
	for(int i=0;i<attr_list.size();i++)cout<<attr_list[i]<<" ";
	cout<<endl;
	tree_node* t=generate_tree(D,n1,attribute_list);
	cout<<"\n Decision tree :\n";
	print_tree(t);
	cout<<"Paths:\n";
	traverse(t);
	cout<<endl;
	while(1)
	{
		struct data d;
		//cin>>d.rid;
		for(int i=0;i<=4;i++)cin>>d.details[i];
		
		cout<<decide(t,d)<<endl<<endl;
	}
	return 0;
}
