#include<bits/stdc++.h>
using namespace std;
typedef map<int,int>Mymap;
typedef vector<int>Myvec;
typedef map<Myvec,int>m1;
typedef map<int,m1>m2;
struct Cnode
{
	int item;
	int freq;
};
typedef struct FPnode
{
   int item;
   int count;
   FPnode *fc;
   FPnode *ns;
}*Fptr;
void printC(struct Cnode s[])
{
   for(int i=0;i<5;i++)
   {
   	  cout<<"I"<<s[i].item<<"\t"<<s[i].freq<<endl;
   }
}
bool compare1(struct Cnode &a,struct Cnode &b)
{
	return a.freq>b.freq;
}
void FPcreate(Fptr &T,Myvec vec)
{
	Fptr t=T;int i=0;
	while(i<vec.size())
	{
		if(t->fc==NULL)
		{
			for(int k=i;k<vec.size();k++)
			{
				t->fc=new FPnode;
				t->fc->item=vec[k];t->fc->count=1;
				t->fc->fc=NULL;t->fc->ns=NULL;
				t=t->fc;
			}
			break;
		}
		else if(t->fc->item==vec[i])
		{
			t->fc->count++;i++;
			t=t->fc;
		}
		else 
		{
			int flag=false;
			if(t->fc->item!=vec[i] && t->fc->ns) // if node have the siblings
			{
			   t=t->fc;
			   while(t->ns && i<vec.size()) 
			   {
				 if(t->ns->item==vec[i])
				 {
					t->ns->count++;
					t=t->ns;i++;flag=true;
					break;
				 }
				 t=t->ns;
			   }	
			}
			else if(t->fc->item!=vec[i] && t->fc->ns==NULL) t=t->fc;
			if(i>=vec.size()) break;
			if(flag && t->fc) continue; //prefix of the type "sibling , first child of sibling and so on...."
			t->ns=new FPnode;
			t->ns->item=vec[i];
			t->ns->fc=NULL;
			t->ns->ns=NULL;
			t->ns->count=1;
			t=t->ns;i++;
		}
	}
}
//void FPprint(Fptr &t);
void Scan_database(Myvec &base_order,Fptr &T)
{
	ifstream file("Mytrans.txt");
	while(!file.eof())
	{
		string str;
        getline(file,str,'I');
   	    getline(file,str,'\n');
   	    char *allitems=new char[str.length()];
        strcpy(allitems,str.c_str());
        char *tok=strtok(allitems," ");
        Myvec v,final;
   	    while(tok)
   	    { 
   		  if(tok[0]=='I') tok=tok+1;
   		  int item=atoi(tok);
   		  v.push_back(item);
   		  tok=strtok(NULL," ");
        }
        for(int i=0;i<base_order.size();i++)
        {
           if(find(v.begin(),v.end(),base_order[i])!=v.end()) final.push_back(base_order[i]);
		}
		//for(int i=0;i<final.size();i++) cout<<final[i]<<" ";cout<<endl;
	    FPcreate(T,final);
	    //FPprint(T);
	}
}
void FPprint(Fptr &t)
{
    if(t==NULL)return;
    Fptr temp=t;
	while(temp!=NULL)
	{
		cout<<"I"<<temp->item<<":"<<temp->count<<"\t";
		FPprint(temp->fc);
		temp=temp->ns;
	}
}
void Conditional_pattern_base(Fptr &T,int itm,m1 &cbpmap,Myvec final)
{
	if(T==NULL) return;
	if(T->item==itm)
	{
		cbpmap[final]=T->count;
		return;
	}
	else
	{
		Fptr G=T;
		while(G)
		{
			final.push_back(G->item);
		  	Conditional_pattern_base(G->fc,itm,cbpmap,final);
		  	final.pop_back();
		  	G=G->ns;
		}
	}
}
int main()
{
    struct Cnode s[5];
    Myvec base_order;
	ifstream file("myTrans.txt");
	while(!file.eof())
    {
    	string str;
        getline(file,str,'I');
   	    getline(file,str,'\n');
   	    char *allitems=new char[str.length()];
        strcpy(allitems,str.c_str());
        char *tok=strtok(allitems," ");
   	    while(tok)
   	    { 
   		  if(tok[0]=='I') tok=tok+1;
   		  int item=atoi(tok);
   		  s[item-1].item=item;
   		  s[item-1].freq++;
   		  tok=strtok(NULL," ");
        }	
	}	
	file.close();
	cout<<"C:1\n";
	sort(s,s+5,compare1);
	int temp;
	for(int i=0;i<5;i++)
	{
		temp=s[i].item;
		base_order.push_back(temp);
	}
	printC(s);
	Fptr T=new FPnode;
	T->item=100;T->count=0;
    T->fc=NULL;T->ns=NULL;	
    Scan_database(base_order,T);
    cout<<"BFT tree printing\n";
    FPprint(T);
    Myvec vec;
    for(int i=base_order.size()-1;i>=0;i--) vec[base_order.size()-1-i]=base_order[i];
    cout<<endl;
    printC(s);
    cout<<"sdmnbm\n";
    m2 trans;
    for(int i=0;i<5;i++)
    {
      m1 cbpmap;
      Myvec final;
      Conditional_pattern_base(T,vec[i],cbpmap,final);
      m1::iterator it=cbpmap.begin();
      for(;it!=cbpmap.end();it++)
      {
      	Myvec v=it->first;
      	for(int i=0;i<v.size();i++) cout<<v[i]<<" ";
      	cout<<" : "<<it->second<<endl;
	  }
      trans[vec[i]]=cbpmap;
	}
	/*m2::iterator it=trans.begin();
	for(;it!=trans.end();it++)
	{
		cout<<it->first<<"\t";
		m1 cbpmap=it->second;
		m1::iterator i=cbpmap.begin();
		for(;i!=cbpmap.end();i++)
		{
			Myvec v=i->first;
			for(int j=0;j<v.size();j++)
			{
				cout<<v[j]<<",";
			}
			cout<<" : "<<i->second<<"    ";
		}
		cout<<endl;
	}*/
	return 0;
}

