//
//  ModelManager.h
//  MiniDota
//
//  Created by apple on 13-2-21.
//  Copyright (c) 2013年 apple. All rights reserved.
//  

#ifndef _CGutModel_h
#define _CGutModel_h

#define MAX_TEXTURE_NAME 128
#define MAP_CUBEMAP   33


#include <iostream>
#include "VectorCustom.h"
#include "MatrixCustom.h"


typedef unsigned int UINT;

// for fixed pipeline material
#define MAX_NUM_TEXTURES 3
#define MAX_TEXCOORDS 3

// auto gen map channel ID
#define MAP_SPHEREMAP 32
#define MAP_CUBEMAP   33
#define MAP_NOOVERWRITE 0xff



#define SUBMIT_TEXTURES	0x01
#define SUBMIT_MTL		0x02
#define SUBMIT_SHADER	0x04
#define SUBMIT_CULLFACE	0x08
#define SUBMIT_BLEND	0x10
#define SUBMIT_FVF		0x20



//*************************************************************************************************************************************************
//*************************************************************************************************************************************************
//*************************************************************************************************************************************************
//主要是 VBO时用到
struct sVertexDecl
{
	// position   m_iPositionOffset 是 vob 时 加载 交叉数组的偏移量  m_iNumPositionElements 是 表示 一个position用(x,y,z) 3个 来表示
    // 在读取数据到时候 模型的 position是(x,y,z) 3 不排除position(x,y,z,w)
	int m_iPositionOffset;
	int m_iNumPositionElements;
	// normal
	int m_iNormalOffset;
	int m_iNumNormalElements;
	// color
	int m_iColorOffset;
	int m_iNumColorElements;
	// texcoord
	int m_iTexcoordOffset[MAX_TEXCOORDS];
	int m_iNumTexcoordElements[MAX_TEXCOORDS];
	// tangent
	int m_iTangentOffset;
	int m_iNumTangentElements;
	// binormal
	int m_iBiNormalOffset;
	int m_iBiNormalElements;
	// stride       交叉数组的步长， 就是单个顶点 在数组里面的步长
	int m_iVertexSize;
    
	sVertexDecl(void)
	{
		m_iPositionOffset = 0;
		m_iNumPositionElements = 3;
		m_iNormalOffset = -1;
		m_iNumNormalElements = 0;
		m_iColorOffset = -1;
		m_iNumColorElements = 0;
		for ( int i=0; i<MAX_TEXCOORDS; i++ )
		{
			m_iTexcoordOffset[i] = -1;
			m_iNumTexcoordElements[i] = 0;
		}
		m_iTangentOffset = -1;
		m_iNumTangentElements = 0;
		m_iBiNormalOffset = -1;
		m_iBiNormalElements = 0;
		m_iVertexSize = 0;
	}
    
	void SetVertexFormat(int PosElems, int NormalElems, int ColorElems,
                         int Tex0Elems=0, int Tex1Elems=0, int Tex2Elems=0, int Tex3Elems=0);
};


//*************************************************************************************************************************************************
//*************************************************************************************************************************************************
//*************************************************************************************************************************************************
//material 基本数据
struct sModelMaterial
{
	Vector3 m_Emissive;
	Vector3 m_Ambient;
	Vector3 m_Diffuse;
	Vector3 m_Specular;
	float   m_fShininess;
    
	bool	m_bCullFace;
	char	m_szBlendMode[16];
	
	int		m_MapChannel[MAX_NUM_TEXTURES];
	char	m_szTexture[MAX_NUM_TEXTURES][MAX_TEXTURE_NAME];
	char	m_szTextureCombine[MAX_NUM_TEXTURES][16];
    
	sModelMaterial(void)
    {
        memset(this, 0, sizeof(sModelMaterial));
    }
    
};


//*************************************************************************************************************************************************
//*************************************************************************************************************************************************
//*************************************************************************************************************************************************
//单个顶点的数据， 这里数据是加载到 VBO中的 也是交叉数组的其中一部分 这里的数据全部是 vector3 因为加载模型的原始数据是 vector3
struct sModelVertex
{
	Vector3 m_Position;
	Vector3 m_Normal;
	Vector4 m_Color;
	Vector3 m_Texcoord[MAX_TEXCOORDS];
	Vector3 m_Tangent;
	Vector3 m_BiNormal;
};



struct sModelBatch
{
	int m_iMaterialID;
	int m_iNumPrimitives;
	int m_iIndexArrayBegin;
	int m_iIndexArrayEnd;
	int m_iNumIndices;
	int m_iNumVertices;
};


struct sModelVertexChunk
{
	int m_iNumPrimitives;
	int m_iNumVertices;             //当前buffer下的总模块数
	int m_iNumIndices;
	int m_iNumBatches;
    
	sVertexDecl m_VertexDecl;
    
	sModelVertex *m_pVertexArray;
	unsigned short *m_pIndexArray;
	sModelBatch *m_pBatchArray;
    
	sModelVertexChunk(void)
	{
		m_iNumVertices = 0;
		m_iNumIndices = 0;
		m_iNumBatches = 0;
        
		m_pVertexArray = NULL;
		m_pIndexArray =NULL;
		m_pBatchArray = NULL;
	}
    
	~sModelVertexChunk()
	{
		if ( m_pVertexArray )
		{
			delete [] m_pVertexArray;
			m_pVertexArray = NULL;
		}
        
		if ( m_pIndexArray )
		{
			delete [] m_pIndexArray;
			m_pIndexArray = NULL;
		}
	}
    
	void OutputVertexBuffer(void *p);
};


//*************************************************************************************************************************************************
//*************************************************************************************************************************************************
//*************************************************************************************************************************************************
//网格
struct sModelMesh
{
    Matrix4x4        m_Matrix;          //可能是整个模型的 object 坐标
    
    int m_iNumFaces, m_iNumVertices;
    //  bounding box
	Vector3 m_vMin, m_vMax;            //用于计算camera far ,near
    
    int m_iNumVertexChunks;            //buffers 的数字
    sModelVertexChunk *m_pVertexChunks;
    
	sModelMesh(void)
	{
		m_iNumVertexChunks = 0;
		m_pVertexChunks = NULL;
		m_Matrix.Identity();
	}
    
    ~sModelMesh()
	{
		if ( m_pVertexChunks )
		{
			delete [] m_pVertexChunks;
			m_pVertexChunks = NULL;
		}
	}
    
	void Load_ASCII(FILE *pFile);
	void Load_BINARY(FILE *pFile);
    
};


//*************************************************************************************************************************************************
//*************************************************************************************************************************************************
//*************************************************************************************************************************************************
// 目前这个函数还没有完全
class CGutModel
{
    
public:
    int m_iNumMaterials;            //Materials 总数
	int m_iNumMeshes;               // mesh 总数
	int m_iNumFaces;                // face 总数
	int m_iNumVertices;             //  vertices 总数
    
    Vector3         m_vMin;         //用于计算camera far ,near
    Vector3         m_vMax;         //用于计算camera far ,near
    Vector3         m_vSize;        //可能计算 VBO 交叉数据 
    
    FILE            *m_pFile;
    
    sModelMaterial  *m_pMaterialArray;   // 对于一个模型来说 可能有多个 Material 所以用数组
    sModelMesh      *m_pMeshArray;       // 对于一个模型来说 可能有多个 mesh 所以用数组
    
public:

    ~CGutModel(){};
    CGutModel(){};

    bool LoadMaterial_ASCII();
    bool LoadMesh_ASCII();
    
    bool Load_ASCII(const char *filename);
    
    
//    std::map<std::string, ModelSurface*> caches;        //存储加载过的模型


};












































#endif





































































































