#include<bits/stdc++.h>
using namespace std;
int main()
{
	int i,j;
	ifstream fin;
	ofstream fout;
	fout.open("File5.txt");
	fin.open("File4.txt");
	vector<set<int> > v1,v2;
	while(!fin.eof())
	{
		int f,s,c;
		fin>>f>>s>>c;
		set<int> s1;
		s1.insert(f); s1.insert(s);
		v1.push_back(s1);
		//cout<<"Pushed "<<f<<" "<<s<<endl;
	}
	fin.close();
	int n=v1.size();
	for(i=0;i<n-1;i++)
	{
		set<int> s2=v1[i];
		for(j=i+1;j<n;j++)
		{
			set<int> s3=v1[i];
			s3.insert(v1[j].begin(),v1[j].end());
			if(s3.size()==v1[i].size()+1)
 			v2.push_back(s3);
		}
	}
	n=v2.size();
	for(i=0;i<n;i++)
	{
		set<int>::iterator it;
		for(it=v2[i].begin();it!=v2[i].end();it++)
		{
			fout<<(*it)<<" ";
			cout<<(*it)<<" ";
			
		}
		fout<<endl;
		cout<<endl;
	}
	
	fout.close();
}
