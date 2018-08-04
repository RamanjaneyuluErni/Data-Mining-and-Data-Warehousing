#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#define UNKNOWN -10000
int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("MissingInput.txt");
	fout.open("MissingInput2.txt");
	int c=1;
	int count1=0, count2=0;
		int sum1=0, sum2=0;
	while(!fin.eof()) 
	{
		int i=0;
		char num1[100],num2[100];
		string s; int i1=0; int i2=0; 
		getline(fin,s);
		cout<<s<<endl;
		if(s[i]==' ')
		{
			//cout<<"Hello "<<endl;
			break;
		}
		//cout<< c++ <<endl;
		if(s[i]=='-') 
		{
			//fout<<"NA- "; 
			i+=2;
		}
		else
		{
			while(s[i]!='-') i++; i+=2;
		}
		//For first number
		if(s[i]=='_') 
		{
			//fout<<mean1<<" ";
			i+=3;
		}
		else
		{
			while(s[i]!=' ') num1[i1++]=s[i++]; i++; num1[i1]='\0';
			sum1+= atoi(num1); count1++;
		}
		//For second number
		if(i<s.length() && s[i]=='_') 
		{
			//fout<<mean1<<" ";
			//while(!(s[i]>='0' && s[i]<='9')) i++;
		}
		else
		{
			while(i<s.length()) num2[i2++]=s[i++]; i++; num2[i2]='\0';
			sum2+= atoi(num2); count2++;
		}
		
	}
	
	int mean1 = sum1/count1, mean2 = sum2/count2;
	fin.close();
	
	
	fin.open("MissingInput.txt");
	while(!fin.eof()) 
	{
		int i=0;
		char num1[100],num2[100];
		string s; int n1; int n2;
		getline(fin,s);
		cout<<s<<endl;
		if(s[i]==' ')
		{
			//cout<<"Hello "<<endl;
			break;
		}
		//cout<< c++ <<endl;
		if(s[i]=='-') 
		{
			fout<<"NA- "; i+=2;
		}
		else
		{
			while(s[i]!='-') fout<<s[i++]; fout<<s[i++]<<"  "; i++;
		}
		//For first number
		if(s[i]=='_') 
		{
			fout<<mean1<<" ";
			i+=3;
		}
		else
		{
			while(s[i]!=' ') fout<<s[i++]; i++; fout<<" ";
		}
		//For second number
		if(i<s.length() && s[i]=='_') 
		{
			fout<<mean2<<" ";
			//while(!(s[i]>='0' && s[i]<='9')) i++;
		}
		else
		{
			while(i<s.length()) fout<<s[i++];  fout<<" ";
		}
		fout<<endl;
	}
	fin.close();
	fout.close();
	fout.open("MissingInput.txt");
	fin.open("MissingInput2.txt");
	while(!fin.eof()){
		string s;
		getline(fin,s);
		fout<<s<<endl;
	}
}
