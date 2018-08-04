//
//  ss1.cpp
//  files1
//
//  Created by Manasa on 09/10/17.
//  Copyright © 2017 adepu. All rights reserved.
//

#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
int main()
{
    
    fstream fin;
    fin.open("missing_info.txt",ios::in|ios::out);
    char ch;
    string str="missing";
    while(fin>>ch)
    {
        if(ch=='|')
        {
            fin>>ch;
            if(ch=='*')
            {
                int long x=fin.tellg();
                fin.seekp(x-1);
                fin<<"missing";
                x=fin.tellp();
                fin.seekg(x);
            }
            
        }
        
    }
    
    
    return 0;
}
