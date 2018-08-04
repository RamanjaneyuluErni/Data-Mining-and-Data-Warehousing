//
//  main.cpp
//  bin_boundary
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
int arr[]={ 2,6,32,34,17,76,51,39,23,98,83,61,16,56,10,95,4,8,9,19};
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
    int put_point=0,get_point=0;
    int a=0,b=0;
    int *temp=new int[freq];
    
    while(getline(fin,str))
    {
        cout<<str<<endl;
        get_point=fin.tellg();
        //cout<<m<<"getpointer\n";
        stringstream ss(str);
        string item;
        int sum=0;
        string binname;
        int k=-1,min=0,max=0;
        while (getline(ss, item, '|'))
        {
            if(k==-1)
                binname=item;
            else if(isdigit(item[0]))
            {
                 temp[k]=atoi(item.c_str());
                if(k==0)
                    min=max=temp[k];
                else
                {
                    if(temp[k]<min)
                        min=temp[k];
                    if(max<temp[k])
                        max=temp[k];
                }
               
                

            }
            k++;
        }
        for(int i=0;i<freq;i++)
        {
            if(max!=temp[i]||min!=temp[i])
            {
                cout<<temp[i]<<" ";
              if(max-temp[i]<temp[i]-min)
                  temp[i]=max;
              else
                  temp[i]=min;
                
            }
        }
        cout<<endl;
        //cout<<k<<"put pointer\n";
        fin.seekp(put_point,ios::beg);
        fin<<binname<<"|";
        for(int j=0;j<freq;j++)
            fin<<temp[j]<<"|";
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
