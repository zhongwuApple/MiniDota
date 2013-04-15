//
//  RenderData.h
//  MiniDota
//
//  Created by apple on 13-1-16.
//  Copyright (c) 2013年 apple. All rights reserved.
//

#ifndef _RenderData_h
#define _RenderData_h

#include <iostream>
#include "MatrixCustom.h"
#include "VectorCustom.h"

#define MAX_ACTIVATED_LIGHTS 2
#define NUM_LIGHTS 16

//start 动态的多光源管理( 经过计算和剔除  最后丢个 GPU 的光源   一般不超过4盞灯 )

extern Vector4  activatedLightPosition[];
extern Vector3  activatedLightDirection[];

extern Vector3  activatedLightAmbientColor[];
extern Vector3  activatedLightDiffuseColor[];
extern Vector3  activatedLightSpecularColor[];
extern Vector3  activatedLightAttenuation[];


extern float   activatedLightSpotLightCutoff[];
extern float   activatedLightSpotLightExponent[];
extern float   activatedLightSpotlightHalfCutoffCosine[];
extern float   activatedLightSpotLightInnerCone[];

//end 动态的多光源管理


//原始的光源数据
struct Light
{
    Vector4     lightPosition;
    Vector3     lightDirection;
    
    Vector3     lightAmbientColor;
    Vector3     lightDiffuseColor;
    Vector3     lightSpecularColor;
    Vector3     lightAttenuation;
    
    float       lightSpotLightCutoff;
    float       lightSpotLightExponent;
    float       lightSpotlightHalfCutoffCosine;
    float       lightSpotLightInnerCone;
};

extern Light    g_lights[];






//常量
const float g_fFovW = 45.0f;
const float g_fAspect = 480/320.0f;
const float g_fart = 0.1f;
const float g_near = 100.0f;



// 镜头位置
extern Vector3 g_eye;
// 镜头对准的点
extern Vector3 g_lookat;
// 镜头正上方的方向
extern Vector3 g_up;

// 镜头转换矩阵
extern Matrix4x4 g_view_matrix;
// 对象旋转矩阵
extern Matrix4x4 g_world_matrix;

extern Matrix4x4 g_projection_matrix;

extern Matrix3x3 g_normalMatrix;




struct Vertex_VCN
{
	Vector3 m_Position; // 顶点位置
	Vector4 m_Color;	// 顶点颜色
	Vector3 m_Normal;	// 顶点法线
};










// 常数定义
const int	g_iMaxNumGrids = 100;
const int	g_iMaxNumGridVertices = (g_iMaxNumGrids+1) * (g_iMaxNumGrids+1);
const int	g_iMaxNumGridIndices = g_iMaxNumGrids * (g_iMaxNumGrids * 2 + 2);

// 格子模型数据
extern int	g_iNumGridVertices;
extern int	g_iNumGridIndices;
extern int	g_iNumGridTriangles;
extern Vertex_VCN *g_pGridVertices;

extern unsigned short *g_pGridIndices;









struct GraphicsDevice_Simulation
{
    Vector3 m_vAmbientLight;
	
	Vector3 m_vMaterialAmbient;
	Vector3 m_vMaterialDiffuse;
	Vector3 m_vMaterialSpecular;
	Vector3 m_vMaterialEmissive;
    
    float m_fMaterialShininess;
};


extern GraphicsDevice_Simulation g_Simulation;


// 生成格子的函数
bool GenerateGrids(int x_grids, int y_grids,
				   Vertex_VCN **ppVertices, int &num_vertices,
				   unsigned short **ppIndices, int &num_indices,
				   int &num_triangles);







void LightManager(void);        //光源管理








































#endif

































































