//
//  SceneController.cpp
//  MiniDota
//
//  Created by apple on 12-12-24.
//  Copyright (c) 2012年 apple. All rights reserved.
//

#include "SceneController.h"
#include "ApplicationScene.h"
#include "RenderingScene.h"

SceneController* SceneController::singleObj=NULL;



void SceneController::Initialize()
{
    controller = new ApplicationScene();
    renderingScene = new RenderingScene();
    controller->Initialize(renderingScene);
    
    renderingScene->Initialize();
}

void SceneController::updateCurrentSceneWithDelta(float aDelta)
{
    controller->UpdateSceneWithDelta(aDelta);
}

void SceneController::renderCurrentScene() const
{
    renderingScene->Render();
}








































































