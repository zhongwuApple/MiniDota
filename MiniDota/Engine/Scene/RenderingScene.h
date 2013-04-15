//
//  RenderingScene.h
//  MiniDota
//
//  Created by apple on 12-12-24.
//  Copyright (c) 2012年 apple. All rights reserved.
//



#ifndef _RenderingScene_h
#define _RenderingScene_h

#include <iostream>
#include "Interfaces.h"
#include "ShaderManager.h"

class RenderingScene : public RenderingEngine
{
public:
    void Initialize() ;
    void InitializeModel( const vector<ISurface*>& surfaces );
    void Render()  ;
    void ModelRender();
    
    void UpdateAnimation() ;
    ~RenderingScene();
    RenderingScene();
    
private:
    void TransferDataWithShader(ShaderObject *sob);
    
private:
    vector<Drawable> m_drawables;
    
    
    
    
//测试变量 VBO
    GLuint vertexBuffer, indexBuffer;
    
    
};

#endif 






















































