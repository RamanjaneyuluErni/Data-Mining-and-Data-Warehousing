#include<bits/stdc++.h>
using namespace std;
struct data{
	//string rid;
	string details[6];
};
map<string,int> class_label;
map<string,int> check;
vector<string> attribute_list;
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
	print_db(D,n1);
	//set<string> s;
	//for(i=0;i,n1;i++) s.insert(D[i].details[5]);
	for(int i=0;i<n1;i++)
	{
		class_label[D[i].details[5]]++;
	}
	cout<<endl<<"Class labels:"<<endl;
	map<string,int> ::iterator it;
	for(it=class_label.begin();it!=class_label.end();it++)
	{
		cout<<it->first<<" "<<it->second<<endl;
		check[it->first]=1;
	}
	data d;
	while(1)
	{
		cout<<endl;
		for(int i=0;i<5;i++) cin>>d.details[i];
		for(int i=1;i<5;i++)
		{
			for(it=class_label.begin();it!=class_label.end();it++)
			{
				int count=0;
				for(int j=0;j<n1;j++)
				{
					if(D[j].details[5]==it->first && d.details[i]==(D[j].details[i])) count++;
				}
				cout<<it->first<<" "<<d.details[i]<<":"<<count<<endl;
				check[it->first]=check[it->first]*count;
			}
		}
		cout<<endl;
		for(it=check.begin();it!=check.end();it++)
		{
			cout<<it->first<<" "<<(it->second/(pow(class_label[it->first],attribute_list.size()-2)))*1.0*((class_label[it->first]*1.0/14.0))<<endl;
			cout<<class_label[it->first]<<endl;
			check[it->first]=1;
		}
	}
	return 0;
}
