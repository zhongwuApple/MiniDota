//
//  TextureManager.cpp
//  MiniDota
//
//  Created by apple on 12-12-11.
//  Copyright (c) 2012年 apple. All rights reserved.
//

#include "TextureManager.h"



map<string, TextureDescription*>TextureManager::cachedTextures;

TextureDescription* TextureManager::GetTexture(const string &name)
{
    TextureDescription *td = NULL;
    map<string, TextureDescription*>::iterator ite;
    ite = cachedTextures.find(name);
    if (ite != cachedTextures.end())
        td = cachedTextures[name];
    return td;
}



void TextureManager::SetTexture(const string &name, TextureDescription *obj)
{
    TextureDescription *td = GetTexture(name);
    if (td != NULL)
    {
        td->Format = obj->Format;
        td->BitsPerComponent = obj->BitsPerComponent;
        td->width = obj->width;
        td->height = obj->height;
        td->MipCount = obj->MipCount;
    }
    else
    {
        cachedTextures.insert(make_pair(name, obj));
    }
}



















































