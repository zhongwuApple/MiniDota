//
//  ModelManager.cpp
//  MiniDota
//
//  Created by apple on 13-2-21.
//  Copyright (c) 2013年 apple. All rights reserved.
//  Load_ASCII

#include "CGutModel.h"
#include <cfloat>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

/*
 * OutputVertexBuffer 主要是copy CGutModel中的数据到 pBuffer中， 因为外面 vob用到
 */
void sModelVertexChunk::OutputVertexBuffer(void *pBuffer)
{
	float *fp = (float *) pBuffer;
    
	for ( int v=0; v<m_iNumVertices; v++ )
	{
		sModelVertex *pVertex = m_pVertexArray + v; //获取一个顶点的指针 来源于 m_pVertexArray
        
		if ( m_VertexDecl.m_iPositionOffset >= 0 )
		{
			for ( int i=0; i<m_VertexDecl.m_iNumPositionElements; i++ )
			{
				*fp++ = pVertex->m_Position[i];
			}
		}
        
		if ( m_VertexDecl.m_iNormalOffset >= 0 )
		{
			for ( int i=0; i<m_VertexDecl.m_iNumNormalElements; i++ )
			{
				*fp++ = pVertex->m_Normal[i];
			}
		}
        
		if ( m_VertexDecl.m_iColorOffset >= 0 )
		{
			for ( int i=0; i<m_VertexDecl.m_iNumColorElements; i++ )
			{
				*fp++ =  pVertex->m_Color[i];
			}
			fp++;
		}
        
		for ( int t=0; t<MAX_TEXCOORDS; t++ )
		{
			if ( m_VertexDecl.m_iTexcoordOffset[t] >= 0 )
			{
				for ( int i=0; i<m_VertexDecl.m_iNumTexcoordElements[t]; i++ )
				{
					*fp++ = pVertex->m_Texcoord[t][i];
				}
			}
		}
        
		if ( m_VertexDecl.m_iTangentOffset >=0 )
		{
			memcpy(fp, &pVertex->m_Tangent, 12);
			fp+=3;
            
			memcpy(fp, &pVertex->m_BiNormal, 12);
			fp+=3;
		}
	}
    
}



void sModelMesh::Load_ASCII(FILE *pFile)
{
	const int BufferSize = 256;
	char szBuffer[BufferSize];
	char sz_Tag[BufferSize];
	char sz_Content[BufferSize];
	int i,j;
	fgets(szBuffer, BufferSize, pFile); // {
    
	fgets(szBuffer, BufferSize, pFile); // matrix
	fgets(szBuffer, BufferSize, pFile); // {
	for ( int r=0; r<4; r++ )
	{
		fgets(szBuffer, BufferSize, pFile); // x,y,z
		sscanf(szBuffer, "%f,%f,%f", &m_Matrix[r][0], &m_Matrix[r][1], &m_Matrix[r][2]);
	}
	fgets(szBuffer, BufferSize, pFile); // }
    
	fgets(szBuffer, BufferSize, pFile); // buffers n
	sscanf(szBuffer, "%s %d", sz_Tag, &m_iNumVertexChunks);
	
	m_iNumFaces = 0;
	m_iNumVertices = 0;
    
	m_vMin.Set(FLT_MAX);
	m_vMax.Set(-FLT_MAX);
    
	if ( m_iNumVertexChunks )
	{
		m_pVertexChunks = new sModelVertexChunk[m_iNumVertexChunks];
		for ( i=0; i<m_iNumVertexChunks; i++ )
		{
			fgets(szBuffer, BufferSize, pFile); // {
            
			sModelVertexChunk *pBuffer = m_pVertexChunks + i;
			fgets(szBuffer, BufferSize, pFile); // vertices n
			sscanf(szBuffer, "%s %d", sz_Tag, &pBuffer->m_iNumVertices);
			fgets(szBuffer, BufferSize, pFile); // format
			sscanf(szBuffer, "%s %s", sz_Tag, sz_Content);
			fgets(szBuffer, BufferSize, pFile); // {
			
			m_iNumVertices += pBuffer->m_iNumVertices;
            
			bool bVertex = false;
			bool bNormal = false;
			bool bColor = false;
			bool bTangentSpace = false;
			int  iNumUVs = 0;
			int  strLen = strlen(sz_Content);
            
			for ( int s=0; s<strLen; s++ )
			{
				switch(sz_Content[s])
				{
                    case 'v':
                        bVertex = true;
                        break;
                    case 'n':
                        bNormal = true;
                        break;
                    case 'c':
                        bColor = true;
                        break;
                    case 't':
                        iNumUVs = sz_Content[++s] - '0';
                        break;
                    case '_':
                        break;
                    case 'p':
                    case 'q':
                        bTangentSpace = true;
                        break;
                    default:
                        break;
				}
			}
            
            
//******************************************************************************
//start 计算交叉数组的步长和个个值(position ,normal ,uv等)之间的跨度， vsize
			int vsize = 0;
			if ( bVertex )
			{
				pBuffer->m_VertexDecl.m_iPositionOffset = vsize;
				pBuffer->m_VertexDecl.m_iNumPositionElements = 3;
				vsize += 4*3;
			}
            
			if ( bNormal )
			{
				pBuffer->m_VertexDecl.m_iNormalOffset = vsize;
				pBuffer->m_VertexDecl.m_iNumNormalElements = 3;
				vsize += 4*3;
			}
            
			if ( bColor )
			{
				pBuffer->m_VertexDecl.m_iColorOffset = vsize;
				pBuffer->m_VertexDecl.m_iNumColorElements = 4;
				vsize += 4;
			}
            
			for ( j=0; j<iNumUVs; j++ )
			{
				pBuffer->m_VertexDecl.m_iTexcoordOffset[j] = vsize;
				pBuffer->m_VertexDecl.m_iNumTexcoordElements[j] = 2;
				vsize += 4*2;
			}
            
			if ( bTangentSpace )
			{
				pBuffer->m_VertexDecl.m_iTangentOffset = vsize;
				pBuffer->m_VertexDecl.m_iNumTangentElements = 3;
				vsize += 4 * 3;
                
				pBuffer->m_VertexDecl.m_iBiNormalOffset = vsize;
				pBuffer->m_VertexDecl.m_iBiNormalElements = 3;
				vsize += 4 * 3;
			}
            
//			if ( vsize==0 )
//			{
//				int a=0;
//			}
            
			pBuffer->m_VertexDecl.m_iVertexSize = vsize;
//******************************************************************************
//end 计算交叉数组的步长和个个值(position ,normal ,uv等)之间的跨度， vsize
    
			if ( pBuffer->m_iNumVertices )
			{
				pBuffer->m_pVertexArray = new sModelVertex[pBuffer->m_iNumVertices];
			}
            
			printf(".");
            
			for ( j=0; j<pBuffer->m_iNumVertices; j++ )
			{
				sModelVertex *pVertex = pBuffer->m_pVertexArray + j;
				
				Vector3 &position = pVertex->m_Position;
				Vector3 &normal = pVertex->m_Normal;
				Vector4 &color = pVertex->m_Color;
				Vector3 *pUV = pVertex->m_Texcoord;
				Vector3 &tangent = pVertex->m_Tangent;
				Vector3 &binormal = pVertex->m_BiNormal;
                
				fgets(szBuffer, BufferSize, pFile);
				char *pLoc = szBuffer;
                
				if ( bVertex )
				{
					pLoc = strstr(pLoc, " ");
					sscanf(pLoc, "%f,%f,%f", &position[0], &position[1], &position[2]);
					position[3] = 1.0f;
                    
					m_vMin = Vector3Min(m_vMin, position);
					m_vMax = Vector3Max(m_vMax, position);
				}
                
				if ( bNormal )
				{
					pLoc = strstr(pLoc+1, " ");
					pLoc = strstr(pLoc+1, " ");
					sscanf(pLoc, "%f,%f,%f", &normal[0], &normal[1], &normal[2]);
					normal[3] = 1.0f;
				}
                
				if ( bColor )
				{
					pLoc = strstr(pLoc+1, " ");
					pLoc = strstr(pLoc+1, " ");
					sscanf(pLoc, "%f,%f,%f,%f", &color[0], &color[1], &color[2], &color[3]);
				}
                
				for ( int t=0; t<iNumUVs && t<MAX_TEXCOORDS; t++ )
				{
					pLoc = strstr(pLoc+1, " ");
					pLoc = strstr(pLoc+1, " ");
					sscanf(pLoc, "%f,%f", &pUV[t][0], &pUV[t][1]);
				}
                
				if ( bTangentSpace )
				{
					pLoc = strstr(pLoc+1, " ");
					pLoc = strstr(pLoc+1, " ");
					sscanf(pLoc, "%f,%f,%f", &tangent[0], &tangent[1], &tangent[2]);
                    
					pLoc = strstr(pLoc+1, " ");
					pLoc = strstr(pLoc+1, " ");
					sscanf(pLoc, "%f,%f,%f", &binormal[0], &binormal[1], &binormal[2]);
				}
                
				if ( (j & 0xff)==0 )
					printf(".");
			}
			
			fgets(szBuffer, BufferSize, pFile); // }
            
			fgets(szBuffer, BufferSize, pFile); // triangle_list_indices n
			sscanf(szBuffer, "%s %d", sz_Tag, &pBuffer->m_iNumIndices);
			if ( pBuffer->m_iNumIndices )
				pBuffer->m_pIndexArray = new unsigned short[pBuffer->m_iNumIndices];
			fgets(szBuffer, BufferSize, pFile); // {
			for ( j=0; j<pBuffer->m_iNumIndices/3; j++ )
			{
				int a,b,c;
				fgets(szBuffer, BufferSize, pFile);
				sscanf(szBuffer, "%d %d %d", &a, &b, &c);
				unsigned short *p = pBuffer->m_pIndexArray + j*3;
				p[0] = a; p[1] = b; p[2] = c;
			}
			fgets(szBuffer, BufferSize, pFile); // }
            
			fgets(szBuffer, BufferSize, pFile); // batches n
			sscanf(szBuffer, "%s %d", sz_Tag, &pBuffer->m_iNumBatches);
			if ( pBuffer->m_iNumBatches )
				pBuffer->m_pBatchArray = new sModelBatch[pBuffer->m_iNumBatches];
			fgets(szBuffer, BufferSize, pFile); // {
			for ( j=0; j<pBuffer->m_iNumBatches; j++ )
			{
				sModelBatch *pBatch = pBuffer->m_pBatchArray + j;
                
				fgets(szBuffer, BufferSize, pFile); // material n
				sscanf(szBuffer, "%s %d", sz_Tag, &pBatch->m_iMaterialID);
				fgets(szBuffer, BufferSize, pFile); // faces n
				sscanf(szBuffer, "%s %d", sz_Tag, &pBatch->m_iNumPrimitives);
				fgets(szBuffer, BufferSize, pFile); // index_begin n
				sscanf(szBuffer, "%s %d", sz_Tag, &pBatch->m_iIndexArrayBegin);
                
				pBatch->m_iNumIndices = pBatch->m_iNumPrimitives * 3;
				pBatch->m_iIndexArrayEnd = pBatch->m_iIndexArrayBegin + pBatch->m_iNumIndices;
                
				m_iNumFaces += pBatch->m_iNumPrimitives;
			}
			fgets(szBuffer, BufferSize, pFile); // }
            
			fgets(szBuffer, BufferSize, pFile); // }
		}
	}
    
	printf(".\n");
	fgets(szBuffer, BufferSize, pFile); // }
}







//********************************************************************************************************************************************************
//********************************************************************************************************************************************************






bool CGutModel::LoadMaterial_ASCII()
{
	char szBuffer[128];
	char szTag[64];
	char szContent[64];
    
    fgets(szBuffer, 128, m_pFile);
    fgets(szBuffer, 128, m_pFile);
    sscanf(szBuffer, "%s %d",szTag, &m_iNumMaterials);
        
    if ( m_iNumMaterials )
    {
        m_pMaterialArray = new sModelMaterial[m_iNumMaterials];
        for ( int i=0; i<m_iNumMaterials; i++)
        {
            sModelMaterial *pMtl = m_pMaterialArray + i;
            fgets(szBuffer, 128, m_pFile); // 读取{
            
            fgets(szBuffer, 128, m_pFile);  //material name
            
//****************************************************************************************************************************
//****************************************************************************************************************************
            //lighting  光源数据
            fgets(szBuffer, 128, m_pFile);  //emissive
            Vector3 *pv = &pMtl->m_Emissive;
            sscanf(szBuffer, "%s %s %f,%f,%f",szTag,szTag, &pv->x, &pv->y, &pv->z);
            
            
            fgets(szBuffer, 128, m_pFile);  //ambient
            pv = &pMtl->m_Ambient;
            sscanf(szBuffer, "%s %s %f,%f,%f",szTag,szTag, &pv->x, &pv->y, &pv->z);
            
            fgets(szBuffer, 128, m_pFile);   //diffuse
            pv = &pMtl->m_Diffuse;
            sscanf(szBuffer, "%s %s %f,%f,%f",szTag,szTag, &pv->x, &pv->y, &pv->z);
            
            fgets(szBuffer, 128, m_pFile);   //specular
            pv = &pMtl->m_Specular;
            sscanf(szBuffer, "%s %s %f,%f,%f",szTag,szTag, &pv->x, &pv->y, &pv->z);
            
            fgets(szBuffer, 128, m_pFile);   //shininess
            sscanf(szBuffer, "%s %s %f", szTag, szTag, &pMtl->m_fShininess);
            pMtl->m_fShininess *= 128.0f;
            
            fgets(szBuffer, 128, m_pFile);   //blendmode
            sscanf(szBuffer, "%s %s %s",szTag,szTag,pMtl->m_szBlendMode);
            
            fgets(szBuffer, 128, m_pFile);   //cullface
            sscanf(szBuffer, "%s %s %s",szTag,szTag,szContent);
            
            if (!strcmp(szContent, "on"))
                pMtl->m_bCullFace = true;
            else
                pMtl->m_bCullFace = false;
            
//****************************************************************************************************************************
//****************************************************************************************************************************
            //textures 贴图
            
            fgets(szBuffer, 128, m_pFile);    //diffuseMap
            sscanf(szBuffer, "%s %s %s %s %s %d", szTag, szTag, szContent, szTag, szTag, &pMtl->m_MapChannel[0]);
            
            // eliminate '\"'
			strcpy(pMtl->m_szTexture[0], &szContent[1]);
			pMtl->m_szTexture[0][ strlen(pMtl->m_szTexture[0]) - 1 ] = '\0';
			if ( !strcmp(pMtl->m_szTexture[0], "None") )
				pMtl->m_szTexture[0][0] = '\0';
            
            
            // lightMap
            fgets(szBuffer, 128, m_pFile);
			sscanf(szBuffer, "%s %s %s %s %s %d", szTag, szTag, szContent, szTag, szTag, &pMtl->m_MapChannel[1]);
            
            // eliminate '\"'
			strcpy(pMtl->m_szTexture[1], &szContent[1]);
			pMtl->m_szTexture[1][ strlen(pMtl->m_szTexture[1]) - 1 ] = '\0';
			if ( !strcmp(pMtl->m_szTexture[1], "None") )
				pMtl->m_szTexture[1][0] = '\0';
            
            
            fgets(szBuffer, 128, m_pFile); // environmentMap
			sscanf(szBuffer, "%s %s %s", szTag, szTag, szContent);
            
            
            
            // eliminate '\"'
			strcpy(pMtl->m_szTexture[2], &szContent[1]);
			pMtl->m_szTexture[2][ strlen(pMtl->m_szTexture[2]) - 1 ] = '\0';
			if ( !strcmp(pMtl->m_szTexture[2], "None") )
				pMtl->m_szTexture[2][0] = '\0';
			else
				//pMtl->m_MapChannel[2] = MAP_SPHEREMAP; // spheremap
				pMtl->m_MapChannel[2] = MAP_CUBEMAP; // cubemap
            
			fgets(szBuffer, 128, m_pFile); // }
            
        }
        
    }
    
    fgets(szBuffer, 128, m_pFile); // }
    
    return true;
}


bool CGutModel::LoadMesh_ASCII()
{
	char szBuffer[128];
	char sz_Tag[64];
    
	fgets(szBuffer, 128, m_pFile); // {
	fgets(szBuffer, 128, m_pFile); // meshes n
	sscanf(szBuffer, "%s %d", sz_Tag, &m_iNumMeshes);
	
	m_iNumFaces = 0;
	m_iNumVertices = 0;
    
	m_pMeshArray = new sModelMesh[m_iNumMeshes];
	if ( m_pMeshArray==NULL )
		return false;
    
    m_vMin.Set(FLT_MAX);
    m_vMax.Set(-FLT_MAX);
    
    for ( int i=0; i<m_iNumMeshes; i++)
    {
        printf("Loading mesh %d/%d\n", i+1, m_iNumMeshes);
        m_pMeshArray[i].Load_ASCII(m_pFile);
        
        m_iNumFaces += m_pMeshArray[i].m_iNumFaces;
        m_iNumVertices += m_pMeshArray[i].m_iNumVertices;
        
        m_vMin = Vector3Min(m_vMin, m_pMeshArray[i].m_vMin);
        m_vMax = Vector3Max(m_vMax, m_pMeshArray[i].m_vMax);
    }
    
    fgets(szBuffer, 128, m_pFile); // } 
    
    return true;
}



bool CGutModel::Load_ASCII(const char *filename)
{
    m_pFile = fopen(filename, "rt");
    if ( NULL == m_pFile)
        return false;
    
	char szBuffer[128];
	char szTag[64], szChunkID[64];
    
    fgets(szBuffer, 128, m_pFile);  //先读取第一行，获取版本号
    
    //判读取文件是否到末尾   feof == ture 表示 读取文件到结尾
    while ( !feof(m_pFile) )
    {
        fgets(szBuffer, 128, m_pFile);
        if (feof(m_pFile))
            break;
        sscanf(szBuffer, "%s %s", szTag, szChunkID);
        
        //strcmp 如果  str1 < str2  retun -1;  str1 == str2  retun 0  str1 > str2 return 1
        if ( !strcmp(szTag, "Begin") )
        {
            if ( !strcmp(szChunkID, "Material") )
            {
                LoadMaterial_ASCII();
            }
            else if( !strcmp(szChunkID, "Mesh") )
            {
                LoadMesh_ASCII();
            }
        }
        
        
    }
    
    
    
    return true;
}


















































































































