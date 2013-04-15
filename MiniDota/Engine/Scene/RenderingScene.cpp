//
//  RenderingScene.cpp
//  MiniDota
//
//  Created by apple on 12-12-24.
//  Copyright (c) 2012年 apple. All rights reserved.
//

#include "RenderingScene.h"
#include <cmath>
#include "RenderData.h"
#include "Global.h"
#include "CGutModel.h"
#include "GutModel_OpenGL.h"




CGutModel g_Model;

CGutModel_OpenGL g_Model_OpenGL;

//----------------------------------------------------------------


RenderingScene::~RenderingScene()
{

}

RenderingScene::RenderingScene()
{

}



void RenderingScene::Initialize() 
{
    
    g_view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
    
    
    
    g_projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFovW, g_fAspect, g_fart, g_near);
}


/*
*
*
*   初始化加载模型   使用VBO   将得到的句柄 放到
*
*/
void RenderingScene::InitializeModel( const vector<ISurface*>& surfaces )
{
//    
//    glGenBuffers(1, &vertexBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//    glBufferData(GL_ARRAY_BUFFER, g_iNumGridVertices*sizeof(Vertex_VCN), &g_pGridVertices[0], GL_STATIC_DRAW);
//
//
//    glGenBuffers(1, &indexBuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, g_iNumGridIndices*sizeof(GLushort), &g_pGridIndices[0], GL_STATIC_DRAW);
    
    
//    glGenBuffers(1, &vertexBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//    glBufferData(GL_ARRAY_BUFFER, g_iNumGridVertices*sizeof(Vertex_VCN), NULL, GL_STATIC_DRAW);
//    void *buffers, *ibuffer_pointer;
//    buffers = glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);
//	float *fp = (float *) buffers;
//    for (int i=0; i<g_iNumGridVertices; i++)
//    {
//        Vertex_VCN *vertex = g_pGridVertices + i;
//        
//        for (int i=0; i<3; i++)
//            *fp++ = vertex->m_Position[i];
//        
//        for (int i=0; i<4; i++)
//            *fp++ = vertex->m_Color[i];
//        
//        for (int i=0; i<3; i++)
//            *fp++ = vertex->m_Normal[i];
//    }
//    glUnmapBufferOES(GL_ARRAY_BUFFER);
//    
//    
//    glGenBuffers(1, &indexBuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, g_iNumGridIndices*sizeof(GLushort), NULL, GL_STATIC_DRAW);
//    
//    // copy index array
//    ibuffer_pointer = glMapBufferOES(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY_OES);
//    memcpy(ibuffer_pointer, g_pGridIndices, g_iNumGridIndices*2);
//    glUnmapBufferOES(GL_ELEMENT_ARRAY_BUFFER);
    
    

    string str = resourcesPath + "teapot_notex.gma";
    g_Model.Load_ASCII(str.c_str());
    g_Model_OpenGL.ConvertToOpenGLModel(&g_Model);
    
    
}


/*
 *
 *  把对应的数据 往 shader 传送 
 *
 */
void RenderingScene::TransferDataWithShader( ShaderObject *sob )
{
    glUseProgram(sob->program);
    
    
//    glEnableVertexAttribArray(sob->m_attributes.VPosition);
//    glEnableVertexAttribArray(sob->m_attributes.VColor);
//    glEnableVertexAttribArray(sob->m_attributes.VNormal);
    
    
    //矩阵
    glUniformMatrix4fv(sob->m_uniforms.Projection4x4, 1, 0, (float *)&g_projection_matrix);
    glUniformMatrix4fv(sob->m_uniforms.ViewMatrix4x4, 1, 0, (float *)&g_view_matrix);
    glUniformMatrix4fv(sob->m_uniforms.WorldMatrix4x4, 1, 0, (float *)&g_world_matrix);
    
//    g_normalMatrix = g_world_matrix.ToMatrix3().Inverse().Transpose(); //这里不求逆矩阵
//    glUniformMatrix3fv(sob->m_uniforms.NormalMatrix, 1, 0, (float *)&g_normalMatrix);
    
    Matrix3x3 tmpWorld3x3 = g_world_matrix.ToMatrix3();
    Matrix3x3 tmpView3x3 = g_view_matrix.ToMatrix3();
    Matrix3x3 tmpWorldView3x3 = (g_world_matrix * g_view_matrix).ToMatrix3();
    
    
    glUniformMatrix3fv(sob->m_other.World3x3, 1, 0, (float *)&tmpWorld3x3);
    glUniformMatrix3fv(sob->m_other.View3x3, 1, 0, (float *)&tmpView3x3);
    glUniformMatrix3fv(sob->m_other.WorldView3x3, 1, 0, (float *)&tmpWorldView3x3);
    
    
    //光源基本设置
    glUniform4fv(sob->m_uniforms.VLightPosition, 1, (float *)activatedLightPosition);
    glUniform3fv(sob->m_uniforms.VLightDirection, 1, (float *)activatedLightDirection);
    
    
    glUniform3fv(sob->m_uniforms.VLightAmbientColor, 1, (float *)activatedLightAmbientColor);
    glUniform3fv(sob->m_uniforms.VDiffuseColor, 1, (float *)activatedLightDiffuseColor);
    glUniform3fv(sob->m_uniforms.VSpecularColor, 1, (float *)activatedLightSpecularColor);
    glUniform3fv(sob->m_uniforms.VLightAttenuation, 1, (float *)activatedLightAttenuation);
    
    
//    glUniform1f(sob->m_uniforms.FSpotLightCutoff, FastMath::Cos(FastMath::DegreeToRadian(g_fSpotLightCutoff)));
//    glUniform1f(sob->m_uniforms.FSpotLightExponent, g_fSpotLightExponent);
//    float spotcutoff = FastMath::DegreeToRadian( g_fSpotLightCutoff * 0.5f);
//    glUniform1f(sob->m_uniforms.FSpotlightHalfCutoffCosine, FastMath::Cos(spotcutoff));
    
    
    glUniform1fv(sob->m_uniforms.FSpotLightCutoff, 1, (float *)activatedLightSpotLightCutoff );
    glUniform1fv(sob->m_uniforms.FSpotLightExponent, 1, (float *)activatedLightSpotLightExponent );
    glUniform1fv(sob->m_uniforms.FSpotlightHalfCutoffCosine, 1, (float *)activatedLightSpotlightHalfCutoffCosine);
    
    
    //材质基本设置
//    glUniform3fv(sob->m_uniforms.VMaterialAmbient, 1, (float *)&g_Simulation.m_vMaterialAmbient);
//    glUniform3fv(sob->m_uniforms.VMaterialDiffuse, 1, (float *)&g_Simulation.m_vMaterialDiffuse);
//    glUniform3fv(sob->m_uniforms.VMaterialEmissive, 1, (float *)&g_Simulation.m_vMaterialEmissive);
//    glUniform3fv(sob->m_uniforms.VMaterialSpecular, 1, (float *)&g_Simulation.m_vMaterialSpecular);
//    glUniform1f(sob->m_uniforms.FMaterialShininess, g_Simulation.m_fMaterialShininess);
    
    
}


void RenderingScene::Render() 
{
    LightManager();

    glClearColor(0.0f, 0.0f, 0.0f, 1);
    // 清除画面
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
//    glDisable(GL_CULL_FACE);
    
   
    
    
    
    ShaderManager *shader =  (ShaderManager *)&ShaderManager::Instance();
    ShaderObject *sob = shader->LoadShader("Directional.es2");
    TransferDataWithShader(sob);
    
//    int stride = sizeof(Vertex_VCN);
//    const GLvoid *colorOffset = (const GLvoid *)sizeof(Vector3);
//    const GLvoid *normalOffset = (const GLvoid *)(sizeof(Vector4) + sizeof(Vector3));
//    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//    glVertexAttribPointer(sob->m_attributes.VPosition, 3, GL_FLOAT, 0, stride, 0);
//    glVertexAttribPointer(sob->m_attributes.VColor, 4, GL_FLOAT, 0, stride, colorOffset);
//    glVertexAttribPointer(sob->m_attributes.VNormal, 3, GL_FLOAT, 0, stride, normalOffset);
//    
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
//    glDrawElements (GL_TRIANGLE_STRIP, g_iNumGridIndices, GL_UNSIGNED_SHORT, 0);

    
    
    
    g_Model_OpenGL.Render(sob);
    
}




/*
* 模型渲染
*/
void RenderingScene::ModelRender()
{

    
}



















void RenderingScene::UpdateAnimation()
{

}


































































