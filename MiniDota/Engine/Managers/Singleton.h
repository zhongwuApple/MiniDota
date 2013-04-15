//
//  Singleton.h
//  MiniDota
//
//  Created by apple on 12-12-11.
//  Copyright (c) 2012年 apple. All rights reserved.
//

#ifndef _Singleton_h
#define _Singleton_h

class Singleton
{
public:
    static Singleton &Instance()
    {
        static Singleton *sgl;
        if(NULL == sgl)
            sgl = new Singleton();
        return *sgl;
    }
//private:
//    Singleton();
//    Singleton( Singleton const& );
//    ~Singleton();
};



































#endif






































































