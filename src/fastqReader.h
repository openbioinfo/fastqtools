#ifndef __FASTQREADER_H__
#define __FASTQREADER_H__

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class fastqReader
{

  
  public:
    
    string id;
    string seq;
    string flag;
    string qual;
    int nextline(void);
    void load(string fq);

  private:
    ifstream fp;
 
};

class pairReader
{

    public:
        fastqReader r1;
        fastqReader r2;
        bool filter ;
        void load(string fq1, string fq2);
        pairReader();
        int next();
};


class pairWriter
{

    public:
        ofstream f1;
        ofstream f2;
        
        pairWriter(string prefix);
        void write(pairReader &pr);
        void close();
};

#endif
