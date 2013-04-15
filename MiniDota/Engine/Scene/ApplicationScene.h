//
//  ApplicationScene.h
//  EX1
//
//  Created by apple on 12-12-20.
//  Copyright (c) 2012年 apple. All rights reserved.
//


#ifndef _ApplicationScene_h
#define _ApplicationScene_h

#include <iostream>
#include "Interfaces.h"
#include "RenderingScene.h"


class ApplicationScene : public AbstractScene
{
    
public:
    ~ApplicationScene();
    void Initialize( RenderingEngine *renderingEngine );
    void UpdateSceneWithDelta(float aDelta);

private:
    
    RenderingEngine *m_renderingEngine;
    
    
};






























































#endif































































