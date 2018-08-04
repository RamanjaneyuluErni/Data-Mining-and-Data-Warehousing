#include<bits/stdc++.h>
#define BIN_SIZE 3
using namespace std;

int main()
{
	int data[]={15,21,8,4,21,28,24,25,34};
	double f = ceil(sizeof data/sizeof data[0]);
	int n= ((int)f);
	int b= n/BIN_SIZE,i=0,j=0,c=0;
	vector<int> bin[b]; 
	int sum[b]; memset(sum,0,sizeof sum);
	sort(data,data+n);
	cout<<"Hi "<<endl;
	while(i<b || c<n) 
	{
		for(j=0;j<bin[i].size();j++,c++) 
		{
			bin[i].push_back(data[c]);
			sum[i]+=data[c];
		}
		i++;
	}
	
	cout<<"Hello "<<endl;
	for(i=0;i<b;i++) 
	{
		cout<<"BIN "<<(i+1)<<"  ";
		if(bin[i].size()<=2) continue;
		for(j=1;j<bin[i].size()-1;j++) 
		{
			if(abs(bin[i][j]-bin[i][0])<abs(bin[i][j]-bin[i][BIN_SIZE])) 
			{
				bin[i][j]=bin[i][0];
			}
			else bin[i][j]=bin[i][BIN_SIZE];
		}
		
		for(j=0;j<BIN_SIZE;j++) 
		{
			cout<<bin[i][j]<<" ";
		}
		cout<<endl;
	}
}
