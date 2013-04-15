//
//  VBOManager.h
//  MiniDota
//
//  Created by apple on 13-3-18.
//  Copyright (c) 2013年 zhongwu. All rights reserved.
//
//  VBOManager 主要是 将 Model数据加载到 VBO中，进行管理的
//
#ifndef _GutModel_OpenGL_h
#define _GutModel_OpenGL_h

#include <iostream>
#include "CGutModel.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "ShaderManager.h"

struct sModelVertexChunk_OpenGL
{
	int m_iNumVertices;
	int m_iNumIndices;
    
	GLuint m_VertexBufferID;
	GLuint m_IndexBufferID;
    
	// 给不支持 vertex buffer object 的机器使用.
//	void *m_pVertexBuffer;
//	unsigned short *m_pIndexBuffer;
    
	int m_iNumBatches;
	sModelBatch *m_pBatchArray;
    
	// vertex decl
	sVertexDecl m_VertexDecl;
    
	sModelVertexChunk_OpenGL(void)
	{
		m_iNumVertices = 0;
		m_VertexBufferID = 0;
		
		m_iNumIndices = 0;
		m_IndexBufferID = 0;
        
//		m_pVertexBuffer = NULL;
//		m_pIndexBuffer = NULL;
        
		m_iNumBatches = 0;
		m_pBatchArray = NULL;
	}
    
	~sModelVertexChunk_OpenGL();
    
};

struct sModelMesh_OpenGL
{
	int m_iNumVertexChunks;
	sModelVertexChunk_OpenGL *m_pVertexChunk;
    
	sModelMesh_OpenGL(void)
	{
		m_iNumVertexChunks = 0;
		m_pVertexChunk = NULL;
	}
    
	~sModelMesh_OpenGL()
	{
		if ( m_pVertexChunk )
		{
			delete [] m_pVertexChunk;
			m_pVertexChunk = NULL;
		}
	}
};



struct sModelMaterial_OpenGL
{
	Vector3 m_Emissive;
	Vector3 m_Ambient;
	Vector3 m_Diffuse;
	Vector3 m_Specular;
	float   m_fShininess;
	
	bool	m_bBlend;
	GLuint  m_SrcBlend;
	GLuint  m_DestBlend;
    
	bool	m_bCullFace;
    
	int		m_MapChannel[MAX_NUM_TEXTURES];
	GLuint  m_Textures[MAX_NUM_TEXTURES];
	
	void Submit(ShaderObject *sob, sModelVertexChunk_OpenGL *pVChunk=NULL);
    
	sModelMaterial_OpenGL(void)
	{
		m_Emissive.Set(0.0f);
		m_Ambient.Set(0.0f);
		m_Diffuse.Set(1.0f);
		m_Specular.Set(0.0f);
		m_fShininess = 20;
        
		m_bCullFace = true;
		m_bBlend = false;
        
		m_SrcBlend = GL_ONE;
		m_DestBlend = GL_ZERO;
        
		for ( int i=0; i<MAX_NUM_TEXTURES; i++ )
		{
			m_MapChannel[i] = 0;
			m_Textures[i] = 0;
		}
	}
    
	void Release(void);
};




/*
******************************************************************************************************************************************************
******************************************************************************************************************************************************
******************************************************************************************************************************************************
******************************************************************************************************************************************************
******************************************************************************************************************************************************
******************************************************************************************************************************************************
*/







class CGutModel_OpenGL
{
    
public:
	int m_iNumMeshes;
	sModelMesh_OpenGL *m_pMeshArray;
	//
	int m_iNumMaterials;
	// fixed pipeline material;
	sModelMaterial_OpenGL *m_pMaterialArray;
	// shader material
	int m_iVertexSize;
	//
	static GLuint s_ShaderOverwrite;
	static sModelMaterial_OpenGL *s_pMaterialOverwrite;
	static GLuint s_TextureOverwrite[MAX_NUM_TEXTURES];
	static GLuint s_MapOverwrite[MAX_NUM_TEXTURES];
public:
	CGutModel_OpenGL(void)
	{
		m_iNumMeshes = 0;
		m_pMeshArray = NULL;
        
		m_iNumMaterials = 0;
		m_pMaterialArray = NULL;
        
		m_iVertexSize = 0;
	}
    
	~CGutModel_OpenGL()
	{
		Release();
	}
    
	void Release(void);
	bool ConvertToOpenGLModel(CGutModel *pModel);
	void RenderMesh(bool bSubmitMaterial = true);
	void Render( ShaderObject *sob );
	// overwrite
	static void SetShaderOverwrite(GLuint shader) { s_ShaderOverwrite = shader; }
	static void SetTextureOverwrite(int index, GLuint texid) { s_TextureOverwrite[index] = texid; }
	static void SetMapOverwrite(int index, int map) { s_MapOverwrite[index] = map; }
	static void SetMaterialOverwrite(sModelMaterial_OpenGL *pMtl) { s_pMaterialOverwrite = pMtl; }
    
    
    
    
    

    
};









































































#endif





















































































