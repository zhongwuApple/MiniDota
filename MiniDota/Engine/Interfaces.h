//
//  Interfaces.h
//  MiniDota
//
//  Created by apple on 12-12-10.
//  Copyright (c) 2012年 apple. All rights reserved.
//

#ifndef _Interfaces_h
#define _Interfaces_h

#include "VectorCustom.h"
#include <vector>
#include <string>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>




using std::vector;
using std::string;



//允许绘制的数据  VertexBuffer, IndexBuffer VBO后返回的句柄，所以都是可以进行绘制的数据
struct Drawable
{
    GLuint  VertexBuffer;
    GLuint  IndexBuffer;
    int     IndexCount;
};




enum VertexFlags
{
    VertexFlagsNormals = 1 << 0,
    VertexFlagsTexCoords = 1 << 1,
};

enum TextureFormat
{
    TextureFormatGray,
    TextureFormatGrayAlpha,
    TextureFormatRgb,
    TextureFormatRgba,
    TextureFormatPvrtcRgb2,
    TextureFormatPvrtcRgba2,
    TextureFormatPvrtcRgb4,
    TextureFormatPvrtcRgba4,
    TextureFormat565,
    TextureFormat5551,
};

struct TextureDescription
{
    TextureFormat   Format;
    int             BitsPerComponent;
    unsigned   int  width;
    unsigned   int  height;
    int             MipCount;
    GLuint          textureID;
};




//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------


// V-顶点 T 纹理坐标 C 坐标
struct Vertex_VTC
{
    Vector3 position;
    Vector4 color;
    Vector2 texcoord;
};





struct ISurface
{
    virtual int GetVertexCount() const = 0;             //顶点总数
    virtual int GetTriangleIndexCount() const = 0;      //3角性
    virtual void GenerateVertices(vector<float>& vertices,unsigned char flags = 0) const = 0;
    virtual void GenerateTriangleIndices(vector<unsigned short>& indices) const = 0;
    virtual ~ISurface() {}
};








struct IResourceManager
{
    virtual string GetResourcePath() const = 0;
    virtual TextureDescription* LoadImage(const string& filename) = 0;
    virtual ~IResourceManager() {}
};


struct RenderingEngine
{
    virtual void Initialize() = 0;
    virtual void Render()  = 0;
    virtual void UpdateAnimation() = 0;
    virtual void InitializeModel( const vector<ISurface*>& surfaces )= 0;
    virtual ~RenderingEngine(){}
};


struct AbstractScene
{
    float            screenWidth;
    float            screenHeight;
	float            alpha;
    float            fadeSpeed;
	
    virtual void Initialize( RenderingEngine *renderingEngine ) = 0;
    virtual void UpdateSceneWithDelta(float aDelta) = 0;
    virtual ~AbstractScene(){}

};








//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//资源管理
namespace ResourceEngine       { IResourceManager* CreateResourceManager(); }




























































#endif


















































