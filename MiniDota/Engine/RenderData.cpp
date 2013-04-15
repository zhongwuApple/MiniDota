//
//  RenderData.cpp
//  MiniDota
//
//  Created by apple on 13-1-16.
//  Copyright (c) 2013年 apple. All rights reserved.
//

#include "RenderData.h"

//-----------------------------------------------------
Vector4  activatedLightPosition[MAX_ACTIVATED_LIGHTS];
Vector3  activatedLightDirection[MAX_ACTIVATED_LIGHTS];

Vector3  activatedLightAmbientColor[MAX_ACTIVATED_LIGHTS];
Vector3  activatedLightDiffuseColor[MAX_ACTIVATED_LIGHTS];
Vector3  activatedLightSpecularColor[MAX_ACTIVATED_LIGHTS];
Vector3  activatedLightAttenuation[MAX_ACTIVATED_LIGHTS];


float   activatedLightSpotLightCutoff[MAX_ACTIVATED_LIGHTS];
float   activatedLightSpotLightExponent[MAX_ACTIVATED_LIGHTS];
float   activatedLightSpotlightHalfCutoffCosine[MAX_ACTIVATED_LIGHTS];
float   activatedLightSpotLightInnerCone[MAX_ACTIVATED_LIGHTS];
//-----------------------------------------------------

Light    g_lights[3];



// 镜头位置
Vector3 g_eye(0.0f, 0.0f, 2.0f);
// 镜头对准的点
Vector3 g_lookat(0.0f, 0.0f, 0.0f);
// 镜头正上方的方向
Vector3 g_up(0.0f, 1.0f, 0.0f);


// 镜头转换矩阵
Matrix4x4 g_view_matrix;
// 对象旋转矩阵
Matrix4x4 g_world_matrix;

Matrix4x4 g_projection_matrix;

Matrix3x3 g_normalMatrix;












GraphicsDevice_Simulation g_Simulation;

int g_iNumGridVertices = 0;
int g_iNumGridIndices = 0;
int g_iNumGridTriangles = 0;
Vertex_VCN *g_pGridVertices = NULL;

unsigned short *g_pGridIndices = NULL;








// `生成x_grids * y_grids个格子的棋盘格模型`
bool GenerateGrids(int x_grids, int y_grids, Vertex_VCN **ppVertices, int &num_vertices, unsigned short **ppIndices, int &num_indices, int &num_triangles)
{
	const int triangles_per_row = x_grids * 2;
	const int indices_per_row = triangles_per_row + 2;
    
	num_vertices = (x_grids + 1) * (y_grids + 1);
//	Vertex_VCN *pVertices = (Vertex_VCN *) GutAllocate16BytesAlignedMemory(sizeof(Vertex_VCN)*num_vertices);
    
    Vertex_VCN *pVertices = (Vertex_VCN *)malloc(sizeof(Vertex_VCN) * num_vertices);
    
	*ppVertices = pVertices;
	if ( pVertices==NULL )
		return false;
    
	num_indices = indices_per_row * y_grids;
	unsigned short *pIndices = new unsigned short[num_indices];
	*ppIndices = pIndices;
	if ( pIndices==NULL )
	{
		return false;
	}
	//` 使用triangle strip时, 三角形数目永远等于索引值数目减去2`
	num_triangles = num_indices-2;
    
	Vector3 vCorner(-0.5f, 0.5f, 0.0f);
	Vector4 vStep(1.0f/float(x_grids), -1.0f/float(y_grids), 0.0f, 0.0f);
	Vector3 vPosition = vCorner;
	Vector3 vNormal(0.0f, 0.0f, 1.0f);
	Vector4 vColor(1.0f, 1.0f, 1.0f, 1.0f);
    
	int x,y;
	int vertex_index = 0;
    
	for ( y=0; y<=y_grids; y++)
	{
		vPosition[0] = vCorner[0];
		for ( x=0; x<=x_grids; x++, vertex_index++)
		{
			pVertices[vertex_index].m_Position = vPosition;
			pVertices[vertex_index].m_Normal = vNormal;
			pVertices[vertex_index].m_Color = vColor;
			vPosition[0] += vStep[0];
		}
		vPosition[1] += vStep[1];
	}
    
	const int vertices_per_row = x_grids + 1;
	bool from_left_to_right = true;
	int  index_index = 0;
    
	for ( y=0; y<y_grids; y++ )
	{
		if ( from_left_to_right )
		{
			// `在奇数列的时候, 三角形从左排到右.`
			pIndices[index_index++] = y * vertices_per_row;
			pIndices[index_index++] = y * vertices_per_row + vertices_per_row;
            
			for ( x=0; x<x_grids; x++ )
			{
				vertex_index = y * vertices_per_row + x;
				pIndices[index_index++] = vertex_index + 1;
				pIndices[index_index++] = vertex_index + 1 + vertices_per_row;
			}
		}
		else
		{
			// `在偶数列的时候, 三角形从右排到左.`
			pIndices[index_index++] = y * vertices_per_row + x_grids;
			pIndices[index_index++] = (y+1) * vertices_per_row + x_grids;
            
			for ( x=x_grids; x>0; x-- )
			{
				vertex_index = y * vertices_per_row + x;
				pIndices[index_index++] = vertex_index - 1;
				pIndices[index_index++] = vertex_index - 1 + vertices_per_row;
			}
		}
		from_left_to_right = !from_left_to_right;
	}
    
	return true;
}




void LightManager(void)
{
    for (int i=0; i<1; i++)
    {
        activatedLightPosition[i] = g_lights[i].lightPosition;
        activatedLightDirection[i] = g_lights[i].lightDirection;
        
        activatedLightAmbientColor[i] = g_lights[i].lightAmbientColor;
        activatedLightDiffuseColor[i] = g_lights[i].lightDiffuseColor;
        activatedLightSpecularColor[i] = g_lights[i].lightSpecularColor;
        activatedLightAttenuation[i] = g_lights[i].lightAttenuation;
        
        activatedLightSpotLightCutoff[i] = g_lights[i].lightSpotLightCutoff;
        activatedLightSpotLightExponent[i] = g_lights[i].lightSpotLightExponent;
        activatedLightSpotlightHalfCutoffCosine[i] = g_lights[i].lightSpotlightHalfCutoffCosine;
    }
    

}



































































