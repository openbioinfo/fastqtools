#include "tools.h"
#include "fastqReader.h"
#include "reader.h"
#include "cmdline.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc,char *argv[])
{
    cmdline::parser a;
    // mantoray
    a.add<string>("r1",'1',"first pair of fastqs",true,"");
    a.add<string>("r2",'2',"second pair of fastqs",true,"");
    a.add<string>("prefix",'p',"output prefix",true,"");
    
    // optional
    a.add<bool>("cut-adaptor",'c',"auto cut adaptor",false,true);
    a.add<float>("max-q15-ratio",'q',"maximum ratio base below q15",false,0.5);
    a.add<float>("max-nbase-ratio",'n',"maximum ratio of nbase",false,0.1);
    a.add<int>("min-read-length",'l',"minimum length of read",false,30);
    a.add("no-qual",'Q',"dont do quality filter");
    a.add("no-nbase",'N',"dont do nbase filter");
    a.add("no-length",'L',"dont do length filter");

    a.parse_check(argc,argv);

    string q1 = a.get<string>("r1");
    string q2 = a.get<string>("r2");
    string prefix = a.get<string>("prefix");
    bool adaptor_flag = a.get<bool>("cut-adaptor");
    float lowqualRatio = a.get<float>("max-q15-ratio");
    float nbaseRatio = a.get<float>("max-nbase-ratio");
    int minLen = a.get<int>("min-read-length");
    bool qual_flag = true;
    bool length_flag = true;
    bool nbase_flag = true;
    if (a.exist("no-qual")) qual_flag = false;
    if (a.exist("no-length")) length_flag = false;
    if (a.exist("no-nbase")) nbase_flag = false;

    cout << qual_flag << endl;
    cout << nbase_flag << endl;
    cout << length_flag << endl;
    pairReader pr;
    pr.load(q1,q2);
    pairWriter pw(prefix);

    while(pr.next())
    {
        reader read(pr);
        read.quality_filter(qual_flag,lowqualRatio);
        read.nbase_filter(nbase_flag,nbaseRatio);
        read.length_filter(length_flag,minLen);
        read.adaptor_autofilter(adaptor_flag);
        pw.write(pr);   
    }
    pw.close();
}

