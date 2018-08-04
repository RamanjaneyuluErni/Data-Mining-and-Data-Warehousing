//
//  main.cpp
//  bin_median
//
//  Created by Manasa on 10/10/17.
//  Copyright © 2017 adepu. All rights reserved.
#include <iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<sstream>
using namespace std;
int partitions=5;
int freq=4;
int arr[]={ 2,6,32,34,17,76,45,39,23,98,83,61,16,56,10,95,4,8,9,19};
void create_file()
{
    ofstream fout;
    fout.open("items.txt");
    int n = sizeof(arr)/sizeof(arr[0]);
    //cout<<n;
    sort(arr,arr+n);
    int k=0;
    for(int i=1;i<=partitions;i++)
    {
        fout<<"Bin"<<i<<"      |";
        int m=0;
        while(m++<freq&&k<n)
        {
            fout<<arr[k++]<<"|";
        }
        fout<<"******************\n";
    }
    fout.close();
}
void update_file()
{
    fstream fin;
    string str;
    fin.open("items.txt");
    fin.seekp(0,ios::beg);
    int long  put_point=0,get_point=0;
    int a=0,b=0;
    while(getline(fin,str))//reading each line in a text file
    {
        cout<<str<<endl;
        get_point=fin.tellg();
        //cout<<m<<"getpointer\n";
        stringstream tokenizer(str);
        string token,bin_name;
        int k=-1;
        while (getline(tokenizer, token, '|'))//tokenizing
        {
            if(k==-1)
                bin_name=token;
            else if(isdigit(token[0]))
            {
                if(k==((freq/2)-1))
                    a=atoi(token.c_str());
                else if(k==freq/2)
                    b=atoi(token.c_str());
            }
            k++;
        }
        int median;
        if(freq%2==0)
            median=(a+b)/2;
        else
            median=b;
        //cout<<k<<"put pointer\n";
        fin.seekp(put_point+bin_name.length()+1,ios::beg);
        for(int j=0;j<freq;j++)
            fin<<median<<"|";
        fin<<"******";
        put_point=get_point;
        fin.seekg(get_point,ios::beg);
    }
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    create_file();
    update_file();
    return 0;
}
