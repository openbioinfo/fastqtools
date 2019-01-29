#ifndef __TOOLS_H__
#define __TOOLS_H__

#define MaxMisMatch 10

#include "tools.h"
#include <string>
#include <algorithm>

using namespace std;

void strip(string &s)
{
    s = s.substr(0,s.length()-1);
}

int base2qual(char c)
{
    return int(c) - 33;
}

string & Reverse(string &s)
{
    reverse(s.begin(),s.end());
    return s;
}


string & Complement(string &a)
{
    for (int i=0;i<a.length();i++)
    {
        char t;
        if (a[i] == 'A')
        {
            t = 'T';
        }else if(a[i] == 'T')
        {

            t = 'A';
        }else if(a[i] == 'C')

        {
            t = 'G';
        }else if (a[i] == 'G')
        {
            t = 'C';
        }else{

            t = a[i];
        }
        a[i] = t;
    }
    return a;
}

void MaxCommon(string &s1,string &s2,int &common, int &start1,int &start2)
{
    string seed1 = s1.substr(0,5);
    string seed2 = s1.substr(5,10);
    string seed3 = s1.substr(10,15);
    start1 = 0;
    start2 = s2.find(seed1);
    if (start2 == -1)
    {   
        start2 = s2.find(seed2);
        start1 = 5;
    }
    if (start2 == -1)
    {
        start2 = s2.find(seed3);
        start1 = 10;
    }
    if (start2 == -1)
    {
        return ;
    }
    int mismatch = 0;
    int idx1 = start1;
    int idx2 = start2;

    while(mismatch < MaxMisMatch && idx1 < s1.length() && idx2 < s2.length())
    {
        idx1 = idx1 + 1;
        idx2 = idx2 + 1;
        if (s1[idx1] != s2[idx2])
        {
            mismatch = mismatch + 1;
            if (s1[idx1-1] !=s2[idx2-1])
            {
                mismatch = MaxMisMatch;
            }
        };
        common = common + 1;
    }

}

#endif
