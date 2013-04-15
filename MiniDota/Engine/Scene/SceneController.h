//
//  SceneController.h
//  MiniDota
//
//  Created by apple on 12-12-24.
//  Copyright (c) 2012年 apple. All rights reserved.
//

#ifndef _SceneController_h
#define _SceneController_h

#include <iostream>
#include "Interfaces.h"


class SceneController
{
    
public:
    AbstractScene               *controller;
    RenderingEngine             *renderingScene;                //主要负责渲染
    
    static SceneController      *singleObj;
    
    void updateCurrentSceneWithDelta(float aDelta);
    void renderCurrentScene() const;
    
    void Initialize();
    
    
    SceneController()
    {
        controller = NULL;
        renderingScene = NULL;
    };
    
    static SceneController* sharedSceneController()
    {
        if (NULL == singleObj)
        {
            singleObj = new SceneController();
        }
        return SceneController::singleObj;
    }
    
    ~SceneController()
    {
        delete singleObj;
    }
    
};


























#endif /* defined(__MiniDota__SceneController__) */






































































