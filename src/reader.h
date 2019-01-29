#ifndef __READER_H__
#define __READER_H__

#include <iostream>
#include "fastqReader.h"


class reader
{

  public:
    
    pairReader &pr;
    reader(pairReader &pi): pr(pi){};
    void length_filter(bool flag,int len=80);
    void quality_filter(bool flag, float max_minqual_frac=0.3,int qual=20);
    void nbase_filter(bool flag,float max_percent=0.1);
    void adaptor_autofilter(bool flag);


};



#endif
