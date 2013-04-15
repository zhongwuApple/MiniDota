//
//  VBOManager.cpp
//  MiniDota
//
//  Created by apple on 13-3-18.
//  Copyright (c) 2013年 apple. All rights reserved.
//

#include "GutModel_OpenGL.h"

sModelMaterial_OpenGL *CGutModel_OpenGL::s_pMaterialOverwrite = NULL;
GLuint CGutModel_OpenGL::s_ShaderOverwrite = 0;
GLuint CGutModel_OpenGL::s_TextureOverwrite[MAX_NUM_TEXTURES] = {0,0,0};
GLuint CGutModel_OpenGL::s_MapOverwrite[MAX_NUM_TEXTURES] = {MAP_NOOVERWRITE, MAP_NOOVERWRITE, MAP_NOOVERWRITE};



/*
*
*删除VBO 中的  vertexBuffer  和  indexBuffer
*
*/
sModelVertexChunk_OpenGL::~sModelVertexChunk_OpenGL()
{
	if ( m_VertexBufferID )
	{
		glDeleteBuffers(1, &m_VertexBufferID);
		m_VertexBufferID = 0;
	}
    
	if ( m_IndexBufferID )
	{
		glDeleteBuffers(1, &m_IndexBufferID);
		m_IndexBufferID = 0;
	}
}



/*
 *
 *删除VBO 中的 textures
 *
 */
void sModelMaterial_OpenGL::Release(void)
{
	for ( int i=0; i<MAX_NUM_TEXTURES; i++ )
	{
		if ( m_Textures[i] )
		{
			glDeleteTextures(1, &m_Textures[i]);
			m_Textures[i] = 0;
		}
	}
}


/*
*
*   对材质进行设置
*   
*/
void sModelMaterial_OpenGL::Submit(ShaderObject *sob, sModelVertexChunk_OpenGL *pVChunk)
{

//    m_Emissive.ConsoleOutput();
//    m_Ambient.ConsoleOutput();
//    m_Diffuse.ConsoleOutput();
//    m_Specular.ConsoleOutput();
//    printf("%f \n",m_fShininess);
        
    glUniform3fv(sob->m_uniforms.VMaterialEmissive, 1, (float *)&m_Emissive[0]);
    glUniform3fv(sob->m_uniforms.VMaterialAmbient, 1, (float *)&m_Ambient[0]);
    glUniform3fv(sob->m_uniforms.VMaterialDiffuse, 1, (float *)&m_Diffuse);
    glUniform3fv(sob->m_uniforms.VMaterialSpecular, 1, (float *)&m_Specular[0]);
    glUniform1f(sob->m_uniforms.FMaterialShininess, m_fShininess);

    if (m_bCullFace)
        glEnable(GL_CULL_FACE);
    else
        glEnable(GL_CULL_FACE);
    
    
    if ( m_bBlend )
    {
        glEnable(GL_BLEND);
        glBlendFunc(m_SrcBlend, m_DestBlend);
    }
    else
    {
        glDisable(GL_BLEND);
    }
    
    
	
    
}



void CGutModel_OpenGL::Release(void)
{
	if ( m_pMeshArray )
	{
		delete [] m_pMeshArray;
		m_pMeshArray = NULL;
	}
    
	if ( m_pMaterialArray )
	{
		for ( int i=0; i<m_iNumMaterials; i++ )
		{
			m_pMaterialArray[i].Release();
		}
        
		delete [] m_pMaterialArray;
		m_pMaterialArray = NULL;
	}
}







//********************************************************************************************************************************************
//********************************************************************************************************************************************
//********************************************************************************************************************************************
//********************************************************************************************************************************************
//********************************************************************************************************************************************
//********************************************************************************************************************************************








/*
*
*
*   主要将 CGutModel 中 的 数据copy给 GutModel_OpenGL
*   包括 Vertexs, Material, Texture 等
*/

bool CGutModel_OpenGL::ConvertToOpenGLModel(CGutModel *pModel)
{
	if ( pModel->m_iNumMeshes==0 )
		return false;
    
//*******************************************************************************
//start 主要是 texture, material
	int i,j;
    //
	m_iNumMaterials = pModel->m_iNumMaterials;
//	char szTextureName[256];
    
	if ( m_iNumMaterials )
	{
		m_pMaterialArray = new sModelMaterial_OpenGL[m_iNumMaterials];
		if ( NULL==m_pMaterialArray )
			return false;
        
		sModelMaterial_OpenGL *target = m_pMaterialArray;
		sModelMaterial *source = pModel->m_pMaterialArray;
        
		for ( i=0; i<m_iNumMaterials; i++, target++, source++ )
		{
            
			target->m_bCullFace = source->m_bCullFace;
            
			target->m_Emissive = source->m_Emissive;
			target->m_Ambient = source->m_Ambient;
			target->m_Diffuse = source->m_Diffuse;
			target->m_Specular = source->m_Specular;
			target->m_fShininess = source->m_fShininess;
            
			if ( !strcmp(source->m_szBlendMode, "replace") )
			{
				target->m_bBlend = false;
			}
			else
			{
				target->m_bBlend = true;
				
				if ( !strcmp(source->m_szBlendMode, "blend") )
				{
					target->m_SrcBlend = GL_SRC_ALPHA;
					target->m_DestBlend = GL_ONE_MINUS_SRC_ALPHA;
				}
				else if ( !strcmp(source->m_szBlendMode, "subtrace") )
				{
					target->m_SrcBlend = GL_ONE;
					target->m_DestBlend = GL_ONE;
				}
				else if ( !strcmp(source->m_szBlendMode, "add") )
				{
					target->m_SrcBlend = GL_ONE;
					target->m_DestBlend = GL_ONE;
				}
				else
				{
					target->m_SrcBlend = GL_ONE;
					target->m_DestBlend = GL_ZERO;
					target->m_bBlend = false;
				}
			}
            
//纹理方面
			for ( j=0; j<MAX_NUM_TEXTURES; j++ )
			{
				if ( source->m_szTexture[j][0] )
				{
//					sprintf(szTextureName, "%s%s", CGutModel::GetTexturePath(), source->m_szTexture[j]);
//					if ( source->m_MapChannel[j]==MAP_CUBEMAP )
//					{
//						target->m_Textures[j] = GutLoadCubemapTexture_OpenGL(szTextureName);
//					}
//					else
//					{
//						target->m_Textures[j] = GutLoadTexture_OpenGL(szTextureName);
//					}
				}
				else
				{
					target->m_Textures[j] = 0;
				}
				target->m_MapChannel[j] = source->m_MapChannel[j];
			}
            
		}
	}
    
//end 主要是 texture, material
//*******************************************************************************

    
    
    

//*******************************************************************************
//start 主要是 vertex与index 加载到vbo中
    
	m_iNumMeshes = pModel->m_iNumMeshes;
	m_pMeshArray = new sModelMesh_OpenGL[m_iNumMeshes];
	if ( NULL==m_pMeshArray )
		return false;
    
//  copy Vertexs Data
	void *vbuffer_pointer, *ibuffer_pointer;
    
	for ( i=0; i<m_iNumMeshes; i++ )
	{
		sModelMesh *pMeshSource = pModel->m_pMeshArray + i;
		sModelMesh_OpenGL *pMesh = m_pMeshArray + i;
        
		pMesh->m_iNumVertexChunks = pMeshSource->m_iNumVertexChunks;
		pMesh->m_pVertexChunk = new sModelVertexChunk_OpenGL[pMesh->m_iNumVertexChunks];
		if ( NULL==pMesh->m_pVertexChunk )
			return false;
        
		for ( j=0; j<pMesh->m_iNumVertexChunks; j++ )
		{
			sModelVertexChunk *pVertexChunkTarget = &pMeshSource->m_pVertexChunks[j];
			sModelVertexChunk_OpenGL *pVertexChunk = pMesh->m_pVertexChunk + j;
			pVertexChunk->m_VertexDecl = pVertexChunkTarget->m_VertexDecl;
            
			pVertexChunk->m_iNumVertices = pVertexChunkTarget->m_iNumVertices;
			int vbuffer_size = pVertexChunk->m_iNumVertices * pVertexChunk->m_VertexDecl.m_iVertexSize;
            
			pVertexChunk->m_iNumIndices = pVertexChunkTarget->m_iNumIndices;
			int ibuffer_size = pVertexChunk->m_iNumIndices * 2;
            

			
            glGenBuffers(1, &pVertexChunk->m_VertexBufferID);
            glBindBuffer(GL_ARRAY_BUFFER, pVertexChunk->m_VertexBufferID);
            glBufferData(GL_ARRAY_BUFFER, vbuffer_size, NULL, GL_STATIC_DRAW);

            // copy vertex array
            vbuffer_pointer = glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);
            pVertexChunkTarget->OutputVertexBuffer(vbuffer_pointer);
            glUnmapBufferOES(GL_ARRAY_BUFFER);

            // create opengl index buffer object
            glGenBuffers(1, &pVertexChunk->m_IndexBufferID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pVertexChunk->m_IndexBufferID);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibuffer_size, NULL, GL_STATIC_DRAW);

            // copy index array
            ibuffer_pointer = glMapBufferOES(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY_OES);
            memcpy(ibuffer_pointer, pVertexChunkTarget->m_pIndexArray, ibuffer_size);
            glUnmapBufferOES(GL_ELEMENT_ARRAY_BUFFER);
            
            
            
            
			pVertexChunk->m_iNumBatches = pVertexChunkTarget->m_iNumBatches;
			if ( pVertexChunk->m_iNumBatches )
			{
				pVertexChunk->m_pBatchArray = new sModelBatch[pVertexChunk->m_iNumBatches];
				if ( NULL==pVertexChunk->m_pBatchArray )
					return false;
				memcpy(pVertexChunk->m_pBatchArray, pVertexChunkTarget->m_pBatchArray,
                       sizeof(sModelBatch) * pVertexChunk->m_iNumBatches);
			}
		}
	}
    
//end 主要是 vertex与index 加载到vbo中
//*******************************************************************************
    
	if ( glBindBuffer )
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
    
	return true;
}








void CGutModel_OpenGL::Render( ShaderObject *sob )
{
    
    
    for (int i=0; i<m_iNumMeshes; i++)
    {
        sModelMesh_OpenGL *pMesh = m_pMeshArray + i;
        for ( int j=0; j<pMesh->m_iNumVertexChunks; j++ )
        {
            sModelVertexChunk_OpenGL *pVertexChunk = pMesh->m_pVertexChunk + j;
			sVertexDecl *pVertexDecl = &pVertexChunk->m_VertexDecl;
			
			unsigned int vmem = 0;
            unsigned int imem = 0;
            
            //绑定VBO
            glBindBuffer(GL_ARRAY_BUFFER, pVertexChunk->m_VertexBufferID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pVertexChunk->m_IndexBufferID);
            
            //位置 Position
            if ( pVertexDecl->m_iPositionOffset >= 0 )
			{
                glEnableVertexAttribArray( sob->m_attributes.VPosition );
                glVertexAttribPointer(sob->m_attributes.VPosition, pVertexDecl->m_iNumPositionElements, GL_FLOAT, 0, pVertexDecl->m_iVertexSize, (GLvoid *)(vmem + pVertexDecl->m_iPositionOffset));
            }
            
            //法线 Normal
            if ( pVertexDecl->m_iNormalOffset >= 0 )
            {
                glEnableVertexAttribArray( sob->m_attributes.VNormal );
                glVertexAttribPointer(sob->m_attributes.VNormal, pVertexDecl->m_iNumNormalElements, GL_FLOAT, 0, pVertexDecl->m_iVertexSize, (GLvoid *)(vmem + pVertexDecl->m_iNormalOffset) );
            }
            
            
            //颜色 Color
            if ( pVertexDecl->m_iColorOffset >=0 )
            {
                glEnableVertexAttribArray( sob->m_attributes.VColor );
                glVertexAttribPointer(sob->m_attributes.VColor, pVertexDecl->m_iNumColorElements, GL_UNSIGNED_BYTE, 0, pVertexDecl->m_iVertexSize, (GLvoid *)( vmem + pVertexDecl->m_iColorOffset ) );
            }
            
            
            //一个模型可能有多个材质，所以会多次绘制，在每次绘制的时候 更新材质的数据
            //目前暂时不支持多分枝
            for (int l=0; l<pVertexChunk->m_iNumBatches; l++ )
			{
                sModelBatch *pBatch = pVertexChunk->m_pBatchArray + l;
                unsigned int *ip = (unsigned int *) (imem + pBatch->m_iIndexArrayBegin * 2);
                
                m_pMaterialArray[0].Submit(sob, pVertexChunk);
                
				glDrawElements(GL_TRIANGLES, pBatch->m_iNumPrimitives*3, GL_UNSIGNED_SHORT, ip);
			}
            
            
            
            
        }
        
        
    }
    
    
    
    
    
}






























































