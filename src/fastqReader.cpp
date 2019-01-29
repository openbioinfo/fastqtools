#include "fastqReader.h"
#include <fstream>


void fastqReader::load(string fq)
{
    fp.open(fq.c_str());
}

int fastqReader::nextline(void)
{
    if ( fp.peek() == EOF)
    {
        return 0;
    }
    getline(fp,id);
    getline(fp,seq);
    getline(fp,flag);
    getline(fp,qual);
    return 1;
}

pairReader::pairReader()
{
    filter = false;
}

void pairReader::load(string fq1,string fq2)
{
    r1.load(fq1);
    r2.load(fq2);
}

int pairReader::next()
{
    if (r1.nextline() && r2.nextline()){
        return 1;
    }else{
        return 0;
    }
}


pairWriter::pairWriter(string prefix)
{
    string fq1 = prefix + "_R1.fastq";
    string fq2 = prefix + "_R2.fastq";
    f1.open(fq1.c_str(),ios::app);
    f2.open(fq2.c_str(),ios::app);
}


void pairWriter::write(pairReader &pr)
{
    if (pr.filter)
    {
        return ;
    }
    f1 << pr.r1.id << endl;
    f1 << pr.r1.seq << endl;
    f1 << pr.r1.flag << endl;
    f1 << pr.r1.qual  << endl;

    f2 << pr.r2.id << endl;
    f2 << pr.r2.seq << endl;
    f2 << pr.r2.flag << endl;
    f2 << pr.r2.qual << endl;
}

void pairWriter::close()
{

    f1.close();
    f2.close();

}


