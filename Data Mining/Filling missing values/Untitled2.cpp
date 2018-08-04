#include<bits/stdc++.h>
using namespace std;
bool prime(int n)
{
    if (n==2 || n==1) return 0;
    int c=0;
    for (int i=2;i<=n/2;i++)  
	{
		if (n%i==0) c++;
		if(c>=2) return 1;
	}
    return 0;
}
int checksquare(int n)
{
	int a=sqrt(n);
	if(n==a*a) return 1;
	else return 0;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,k,p=0;
		cin>>n;
		vector<int>v;
		for(int i=0;i<n;i++) 
		{
			cin>>k;
		    if(checksquare(k) || prime(k)) v.push_back(k);
		}
		for(int i=0;i<v.size();i++) cout<<v[i]<<" ";cout<<endl;
		while(v.size())
		{
			int num=v[0];
			int one=0,two=0;
			if(checksquare(num)) 
			{
				num=sqrt(num);
				v.push_back(num);
				v[0]=num;
			}
			else if(num==2) 
			{
				swap(v[0],v[v.size()-1]);
				v.pop_back();
			}
			else
			{
				for(int i=2;i<=num/2;i++)
			    {
			    	if(num%i==0)
			        {
		    		 if(one==0) one=i;
					 else
					 {
						two=i;break;
					 }
			        }
		        }
		        swap(v[0],v[v.size()-1]);
			    v.pop_back();
			    if(checksquare(one) || prime(one)) v.push_back(one);
			    if(checksquare(two) || prime(two)) v.push_back(two);
			}
			p=(p+1)%2;
			for(int i=0;i<v.size();i++) cout<<v[i]<<" ";cout<<endl;
		}
		if(p) cout<<"Friend"<<endl;
		else cout<<"Appu"<<endl;	
	}
	return 0;
}
