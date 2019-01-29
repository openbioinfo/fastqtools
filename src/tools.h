
#ifndef __TOOLS_H__
#define __TOOLS_H__
#include <string>

using namespace std;

void strip(string & s);
string& Reverse(string &s);
string& Complement(string &s);
int base2qual(char c);
void MaxCommon(string &s1,string &s2,int& common,int& start1, int& start2);
#endif

