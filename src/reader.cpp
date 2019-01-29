
#include "reader.h"
#include "tools.h"

//reader::reader(pairReader &pi){}


void reader::length_filter(bool flag,int len)
{
   if ( not flag ) return;
   if ( pr.r1.seq.length() < len or pr.r2.seq.length() < len)
   {
        pr.filter = true;
   }

}


void reader::quality_filter(bool flag,float max_minqual_frac,int qual)
{
    if (not flag ) return ;

    int lowqualnum1 = 0;
    int lowqualnum2 = 0;
    for (int i=0;i<pr.r1.qual.length()-1;i++)
    {
        int lowqual1 = base2qual(pr.r1.qual[i]);
        if ( lowqual1 < qual )
        {
            lowqualnum1 = lowqualnum1 + 1;
        }
    }

    if ( float(lowqualnum1)/pr.r1.qual.length() > max_minqual_frac )
    {
        pr.filter = true;
        return ;
    }

    for (int i=0;i<pr.r2.qual.length()-1;i++)
    {
        int lowqual2 = base2qual(pr.r2.qual[i]);
        if (lowqual2 < qual)
        {
            lowqualnum2 = lowqualnum2 + 1;
        }   
    }
    if ( float(lowqualnum2)/pr.r2.qual.length() > max_minqual_frac ) 
    {
        pr.filter = true;
        return ;
    }

}


void reader::nbase_filter(bool flag,float max_percent)
{
    if (not flag) return;
    int nbase1 = 0;
    for (int i=0;i<pr.r1.seq.length()-1;i++)
    {
        if (pr.r1.seq[i] == 'N') nbase1 = nbase1 + 1;
    }

    if ( float(nbase1) / (pr.r1.seq.length() -1) > max_percent )
    {
        pr.filter = true;
        return ;   
    }

    int nbase2 = 0;
    for (int i=0;i<pr.r2.seq.length()-1;i++)
    {
        if (pr.r2.seq[i] == 'N') nbase2 = nbase2 + 1;
    }

    if (float(nbase2)/(pr.r2.seq.length()-1) > max_percent)
    {
        pr.filter = true;
        return ;
    }

}

void reader::adaptor_autofilter(bool flag)
{
    if (not flag) return ;
    string r1seq = pr.r1.seq;
    string r2seq_rc = Reverse(Complement(pr.r2.seq));
    string r2qual_r = Reverse(pr.r2.qual);
    int c = 0;
    int s1 = 0;
    int s2 = 0;

    MaxCommon(r1seq,r2seq_rc,c,s1,s2);
    float ratio = float(c) / (s1 + r2seq_rc.length()-s2);
    // adaptor condition as follows 
    //cout << s1 << " " << s2 << " " << c << " " << ratio <<  endl;

    if ( ratio > 0.9  && s1 < s2)
    {
        pr.r1.seq = pr.r1.seq.substr(s1,c);
        pr.r1.qual = pr.r1.qual.substr(s1,c);
    
        r2seq_rc = r2seq_rc.substr(s2,c);
        r2qual_r = r2qual_r.substr(s2,c);
    
        pr.r2.seq = Reverse(Complement(r2seq_rc));
        pr.r2.qual = Reverse(r2qual_r);
    }
    
}




