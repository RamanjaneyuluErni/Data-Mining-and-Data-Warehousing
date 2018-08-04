#include<bits/stdc++.h>
using namespace std;
int main()
{
	ifstream fin("database.txt");
	int sum=0,n=0,avg;
	string str;
	while(!fin.eof())
	{
	  n++;
	  getline(fin,str,'\n');
	  char *tuple=new char[str.length()];
	  strcpy(tuple,str.c_str());
	  char *tok=strtok(tuple," ");
	  while(tok)
	  {
	  	if(tok[0]>='0' && tok[0]<='9') {
	  		sum+=atoi(tok);
		  }
	  	tok=strtok(NULL," ");
	  }	  
	}
	avg=sum/n;
	cout<<avg;
	fin.close();
	fstream file("database.txt",fstream::in|fstream::out);
	while(!file.eof())
	{
	  int t=file.tellg();
	  string temp="";
	  getline(file,str,'\n');
	  file.seekp(t,ios::beg);
	  if(str[0]=='\t' && str[str.length()-1]=='\t')
	  {
	  	file<<"unknown  "<<avg;
	  }
	  //else file<<str;
	  else
	  {
	  	char *tuple=new char[str.length()];
	    strcpy(tuple,str.c_str());
	    char *tok=strtok(tuple," ");
	  	if(str[0]=='\t')
	  	{
	  		file<<"unknown  ";
	  		for(int i=0;tok[i];i++)file<<tok[i];
	  		file<<endl;
		}
		else if(str[str.length()-1]=='\t')
		{
			for(int i=0;tok[i];i++) file<<tok[i];
			file<<"   "<<avg<<endl;
		}
	  }
	 // file<<"mnzxfn,cn,"<<endl;
	  //file<<str<<endl;
	  file<<endl;
	}
	file.close();
	return 0;
}
