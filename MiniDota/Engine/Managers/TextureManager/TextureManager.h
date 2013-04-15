//
//  TextureManager.h
//  MiniDota
//
//  Created by apple on 12-12-11.
//  Copyright (c) 2012年 apple. All rights reserved.
//

#ifndef _TextureManager_h
#define _TextureManager_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <iostream>
#include "Singleton.h"
#include <string>
#include <map>
#include "Interfaces.h"

using namespace std;






class TextureManager : public Singleton
{
    
public:
    static map<string,TextureDescription*> cachedTextures;
    
    TextureDescription*  GetTexture(const string &name);
    void SetTexture(const string &name, TextureDescription *obj);
    
private:
    ~TextureManager()
    {
        map<string, TextureDescription*>::iterator ite = cachedTextures.begin();
        while (ite != cachedTextures.end())
        {
            free(ite->second);
            ite++;
        }
    }
};




#endif









































































