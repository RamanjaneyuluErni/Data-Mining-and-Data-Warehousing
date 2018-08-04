#include<bits/stdc++.h>
using namespace std;
void print_clusters(vector<int>clusters[],vector<int>mean,int k)
{
	for(int i=0;i<k;i++)
	{
		for(int j=0;j<clusters[i].size();j++) cout<<clusters[i][j]<<" ";
		cout<<"  -->  "<<mean[i]<<endl;
	}
}
int check(vector<int>clusters[],vector<int>temp[],int k)
{
	for(int i=0;i<k;i++) 
	{
		if(temp[i]!=clusters[i]) return 0;
	}
	return 1;
}

int main()
{
	int k,n,x=0;
	cout<<"Enter no of elements : ";cin>>n;
	cout<<"Enter elements\n";
	int *data=new int[n];
	for(int i=0;i<n;i++) cin>>data[i];
	cout<<"Enter no of clusters : ";cin>>k;
	vector<int>clusters[k];
	vector<int>mean;
	for(int i=0;i<k;i++) 
	{
		clusters[i].push_back(data[i]);
		mean.push_back(data[i]);
	}
	while(true)
	{
		x++;
		vector<int>temp[k];
		int i,j;
		for(i=0;i<n;i++)
		{
			int min=100000;
			int pos=-1;
			for(j=0;j<k;j++)
			{
				if(abs(data[i]-mean[j])<min)
				{
					pos=j;
					min=abs(data[i]-mean[j]);
				}
			}
			temp[pos].push_back(data[i]);
		}
		if(check(clusters,temp,k)) break;
		vector<int>tmean=mean;
		mean.clear();
		for(i=0;i<k;i++) 
	    {
		   clusters[i]=temp[i];
		   int m=0;
		   for(j=0;j<clusters[i].size();j++) m+=clusters[i][j];
		   int Mymean=m/clusters[i].size();
		   	 int min=100000;
			 int pos=-1;
			 for(int s=0;s<clusters[i].size();s++)
			 {
				if(abs(clusters[i][s]-Mymean)<min)
				{
					pos=s;
					min=abs(clusters[i][s]-Mymean);
				}
			 }
			 mean.push_back(clusters[i][pos]);
		 
        }
        
	}
	cout<<"final output\n";
	print_clusters(clusters,mean,k);
	return 0; 
}
