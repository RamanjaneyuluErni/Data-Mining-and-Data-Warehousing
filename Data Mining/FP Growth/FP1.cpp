#include<bits/stdc++.h>
using namespace std;
int thres=2;
struct tnode;
typedef tnode *tptr;
struct tnode{
	int data;int count;
	vector<tptr> child;
	tptr parent;
	tptr next; 
};
tptr createnode(int d)
{
	tptr t=new tnode();t->data=d;t->count=0;
	t->parent=t->next=NULL;
	return t;
}
void addtrans(tptr top,vector<int> trans)
{
	tptr t=top;
	for(int i=0;i<trans.size();i++)
	{
		int j=0;tptr cur;
		for(j=0;j<t->child.size();j++)
		{
			 cur=t->child[j];
			 if(cur->data==trans[i])
			 {
			 	break;
			 }
		}
		if(j==t->child.size())
		{
			t->child.push_back(createnode(trans[i]));
			cur=t->child[t->child.size()-1];
			cur->parent=t;
		}
		cur->count+=1;
		t=cur;
	}
}
vector<pair<int,int> > allitems;
bool mysort1(pair<int,int> p1,pair<int,int> p2)
{
	if(p1.second<p2.second) return 0;
	return 1;
}
bool mysort2(int a,int b)
{
	int i,j;
	for(i=0;i<allitems.size()&&allitems[i].first!=a;i++);
	for(j=0;j<allitems.size()&&allitems[j].first!=b;j++);
	if(allitems[i].second<allitems[j].second) return 0;
	if(allitems[i].second>allitems[j].second) return 1;
	if(allitems[i].first<allitems[j].first) return 1;
	return 0;
}
void getallitems()
{
	ifstream in;in.open("myTrans.txt");
	vector<int> temp;
	while(!in.eof())
	{
		char s[100];
		in.getline(s,100,'\n');
		//cout<<"s="<<s<<endl;
	//	if(!in.eof())
		{
			int i;
			for(i=0;i<strlen(s);i++)
			{
				if(s[i]=='I')
				{
					break;
				}
			}
			int sum=0,j;i++;
			for(j=i;j<strlen(s);j++)
			{
				if(s[j]=='I')
				{
					if(sum!=0)
					temp.push_back(sum);
					sum=0;
				}
				else if(s[j]>='0'&&s[j]<='9')
				{
					sum=sum*10+(s[j]-'0');
				}
				else
				{
					continue;
				}
				//cout<<"sum="<<sum<<endl;
			}
			temp.push_back(sum);
		}
	}
	sort(temp.begin(),temp.end());
	allitems.push_back(make_pair(temp[0],1));
	int c=0;
	for(int i=1;i<temp.size();i++)
	{
		if(temp[i]!=temp[i-1])
		{
			allitems.push_back(make_pair(temp[i],0));
			c++;
		}
		allitems[c].second++;
	}
	in.close();
}
bool find(int k)
{
	for(int i=0;i<allitems.size();i++)
	{
		if(allitems[i].first==k)
		{
			return 1;
		}
	}
	return 0;
}
void print(vector<int> temp)
{
	sort(temp.begin(),temp.end());
	for(int i=0;i<temp.size();i++)
	cout<<temp[i]<<" ";
	cout<<endl;
}
void formthetree(tptr top)
{
	ifstream in;in.open("myTrans.txt");
	while(!in.eof())
	{
		char s[100];
		in.getline(s,100,'\n');
		vector<int> temp;
		//cout<<"s="<<s<<endl;
	//	if(!in.eof())
		{
			int i;
			for(i=0;i<strlen(s);i++)
			{
				if(s[i]=='I')
				{
					break;
				}
			}
			int sum=0,j;i++;
			for(j=i;j<strlen(s);j++)
			{
				if(s[j]=='I')
				{
					if(sum!=0&&find(sum))
					temp.push_back(sum);
					sum=0;
				}
				else if(s[j]>='0'&&s[j]<='9')
				{
					sum=sum*10+(s[j]-'0');
				}
				else
				{
					continue;
				}
				//cout<<"sum="<<sum<<endl;
			}
			if(find(sum))
			temp.push_back(sum);
			sort(temp.begin(),temp.end(),mysort2);
		//	print(temp);
			addtrans(top,temp);
		}
	
	}
	in.close();
}
void printtree(tptr root)
{
	tptr rand;
	queue<tptr> q;q.push(root);q.push(rand);
	while(!q.empty())
	{
		tptr cur=q.front();q.pop();
		if(cur==rand)
		{
			cout<<endl;
			if(!q.empty())
			{
				q.push(cur);
			}
		}
		else
		{
			cout<<cur->data<<"-"<<cur->count<<"-";
			if(cur->next!=NULL)
			cout<<cur->next->data;
			else cout<<"null";
			cout<<"-";
			if(cur->parent!=NULL)
			cout<<cur->parent->data;
			cout<<"     ";
			for(int i=0;i<cur->child.size();i++)
			{
				q.push(cur->child[i]);
			}
		}
	}
}
void printallitems()
{
	for(int i=0;i<allitems.size();i++)
	{
		cout<<allitems[i].first<<"-"<<allitems[i].second<<"   ";
	}
	cout<<endl;
}
void makeheader(tptr top,map<int,tptr > &head)
{
	if(top!=NULL)
	{
		if(top->data!=0)
		{
			if(head.find(top->data)==head.end())
			{
				head[top->data]=top;
			}
			else
			{
				tptr cur=head[top->data];
				while(cur->next) cur=cur->next;
				cur->next=top;
			}
		}
		for(int i=0;i<top->child.size();i++)
		makeheader(top->child[i],head);
	}
}
void mining(tptr top,vector<int> alpha,map<int,tptr> head)
{
	//cout<<"PRINTING OF TREE WITH APLHA:";print(alpha);
	//cout<<endl;printtree(top);
	int flag;
	if(top->data!=0&&top->count<thres) return;
	vector<pair<int,int> > ele;
	tptr temp=top;
	while(temp&&temp->child.size()==1)
	{
		ele.push_back(make_pair(temp->data,temp->count));temp=temp->child[0];
	}
	if(!temp)
	{
		//cout<<"ONE PATH ENTERES"<<endl;
		int l=ele.size();
		for(int i=0;i<pow(2,l);i++)
		{
			int k=INT_MAX;vector<int> temp;
			for(int j=0;j<l;j++)
			{
				if(i>>j&1)
				{
					temp.push_back(ele[i].first);
					if(k>ele[i].second) k=ele[i].second;
				}
			}
			for(int j=0;j<alpha.size();j++) temp.push_back(alpha[j]);
			sort(temp.begin(),temp.end());
			cout<<"FREQUENT ITEM SET:";print(temp);cout<<" WITH COUNT="<<k<<endl;
		}
	}
	else
	{
	//	cout<<"MORE THAN ONE PATH ENTERS"<<endl;
		for(map<int,tptr>::iterator it=head.begin();it!=head.end();it++)
		{
			tptr cur=it->second;
			int k=it->first;
			int c=0;
			while(cur)
			{
				c+=cur->count;cur=cur->next;
			}
			if(c>=thres)
			{
				cout<<"FREQUENT ITEM SET:";alpha.push_back(k);print(alpha);alpha.pop_back();cout<<" WITH COUNT="<<c<<endl;
			}
			cur=it->second;
			tptr ttop=createnode(0);
			while(cur)
			{
			//	if(cur->count<thres)
			//	{
			//		cur=cur->next;continue;
			//	}
			int curc=cur->count;
				vector<pair<int,int> > temp;
				tptr bef,down=cur->parent;
				while(down->data!=0)
				{
					temp.push_back(make_pair(down->data,curc));
					down=down->parent;
				}
				tptr t=ttop;
				for(int i=temp.size()-1;i>=0;i--)
				{
					int j;
					for(j=0;j<t->child.size()&&t->child[j]->data!=temp[i].first;j++);
					tptr ttt;
					if(j==t->child.size())
					{
						ttt=createnode(temp[i].first);
						ttt->parent=t;t->child.push_back(ttt);
					}
					else ttt=t->child[j];
					ttt->count+=temp[i].second;
					t=ttt;
				}

				cur=cur->next;
			}
			alpha.push_back(k);
			map<int,tptr> he;makeheader(ttop,he);
			mining(ttop,alpha,he);
			alpha.pop_back();
		}
	}
}
int main()
{
	tptr top=createnode(0);	
	getallitems();
	sort(allitems.begin(),allitems.end(),mysort1);
	vector<pair<int,int> > temp=allitems;
//	printallitems();
	int k;
	for(k=0;k<allitems.size();k++)
	{
		if(allitems[k].second<thres)
		break;
	}
	allitems.resize(k);
//	printallitems();
	map<int,tptr> head;
	formthetree(top);
	makeheader(top,head);
	printtree(top);
	vector<int> alpha;
	mining(top,alpha,head);
	return 0;
}
