#include<bits/stdc++.h>
#define BIN_SIZE 3
using namespace std;

int main()
{
	int data[]={15,21,8,4,21,28,24,25,34};
	double f = ceil(sizeof data/sizeof data[0]);
	int n= (int)f;
	int b= n/BIN_SIZE,i=0,j=0,c=0;
	vector<int> bin[b]; 
	int sum[b]; 
	memset(sum,0,sizeof sum);
	sort(data,data+n);
	while(i<b || c<n) 
	{
		for(j=0;j<BIN_SIZE;j++,c++) 
		{
			bin[i].push_back(data[c]);
			sum[i]+=data[c];
		}
		i++;
	}
	
	for(i=0;i<b;i++) 
	{
		cout<<"BIN "<<(i+1)<<"  ";
		int binm= sum[i]/bin[i].size();
		for(j=0;j<BIN_SIZE;j++) 
		{
			bin[i][j]=binm;
		}
		for(j=0;j<BIN_SIZE;j++) 
		{
			cout<<bin[i][j]<<" ";
		}
		cout<<endl;
	}
}
