//
//  ApplicationScene.cpp
//  EX1
//
//  Created by apple on 12-12-20.
//  Copyright (c) 2012年 apple. All rights reserved.
//
            
#include "ApplicationScene.h"
#include "ModelSurface.h"

ApplicationScene::~ApplicationScene()
{
    delete m_renderingEngine;
}


void ApplicationScene::Initialize( RenderingEngine *renderingEngine )
{
    m_renderingEngine = renderingEngine;
    
    //加载资源初始化
//    ModelSurface *ninja = new ModelSurface("Ninja.obj");
    
    vector<ISurface*> surfaces(1);
    surfaces[0] = new ModelSurface("Ninja.obj");
    m_renderingEngine->InitializeModel(surfaces);
    
    for (int i = 0; i < 1; i++)
        delete surfaces[i];

}







void ApplicationScene::UpdateSceneWithDelta(float aDelta)
{
//    printf("逻辑处理:------------------------------");
}












































