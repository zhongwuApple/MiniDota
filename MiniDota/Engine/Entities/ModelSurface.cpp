//
//  ModelSurface.cpp
//  MiniDota
//
//   这个模型类 主要是将模型加载成 opengl可以的数据， 三角形组合形式为 GL_TRIANGLES
//
//

#include "ModelSurface.h"
#include <list>
#include <fstream>
#include <assert.h>
#include <iostream>
#include "Global.h"


/*
 *
 *  这个构造函数 主要计算 模型的顶点总数 和 将模型的一个个顶点索引数值 存储在一个 vector 容器中 并在存储的时候 处理索引值 使得期符合opengl 的规则
 *  将顶点索引存在到 vector时 是以一个面存储的 而且组合类型是以 GL_TRIANGLES 进行组合。
 *  因为 建模工具 的索引数值 是以1开始，而opengl是以0 开始 索引 有 *face++ -= defaultIv3; 这段代码
*/
ModelSurface::ModelSurface(const string& name) : m_faceCount(0),m_vertexCount(0)
{
    m_name = resourcesPath + name;
    //计算模型面数，同时开辟 m_faces 容器空间
    m_faces.resize(GetTriangleIndexCount() / 3);
    
    ifstream objFile(m_name.c_str());
    vector<IVector3>::iterator face = m_faces.begin();
    
    
    IVector3 defaultIv3 = IVector3(1,1,1);
    
    //读取和计算 顶点索引
    while (objFile)
    {
        char c = objFile.get();
        if (c == 'f')       //这里变量 f 是索引
        {
            assert(face != m_faces.end() && "parse error");
            
            objFile >> face->x >> face->y >> face->z;       //注意这种写法  >>face->x 表示 冲 数据留 objFile 读取 一个 face->x 类型的数据 给 face->x
                                                            //等价于 face->x 被 objfile赋值， 同时 objfile 会自动下移  保证  fece->y 独到的是 对应的Y数据
            
            *face++ -= defaultIv3;
        }
        objFile.ignore(MaxLineSize, '\n');
    }
    assert(face == m_faces.end() && "parse error");
}





/*
 *
 *   获取所有 顶点 总个数        这种算法 把 一行 v 看成一个顶点(x,y,z 坐标)，是因为模型导出到时候决定的
 *
 */
int ModelSurface::GetVertexCount() const
{
    if ( m_vertexCount != 0 )
        return m_vertexCount;
    
    ifstream objFile( m_name.c_str() );
    while (objFile)
    {
        char c = objFile.get();
        if ( c == 'v')
            m_vertexCount++;
        objFile.ignore(MaxLineSize, '\n');
    }
    return m_vertexCount;
}


/*
 *
 *   读取索引总个数 同时计算三角形的面数  
 *
 */
int ModelSurface::GetTriangleIndexCount() const
{
    if (m_faceCount != 0)
        return m_faceCount * 3;
    
    ifstream objFile( m_name.c_str() );
    while (objFile)
    {
        char c = objFile.get();
        if ( 'f' == c )
            m_faceCount++;
    }
    return m_faceCount * 3;
}



/*
 *
 *  把顶点的值 和 法线的值放到同一个 vecto3存储起来 在 vector  中 一个结构体存储 ，类似交叉数组
 *  重点值 这里的法线 是根据 顶点计算的， 有可能有些面数大于顶点数， 所以有些顶点会重复计算
 *  如果模型带有法线则这里不在处理计算法线，只是读取法线而已
*/
void ModelSurface::GenerateVertices( vector<float>& datas, unsigned char flags ) const
{
    struct ObjVertex
    {
        Vector3 Position;
        Vector3 Normal;
    };
    
    datas.resize(GetVertexCount() * 6);     //这里 *6 是因为 要存储 1个顶点的空间是  顶点(x,y,z)和法线(x,y,z)
    ifstream objFile( m_name.c_str());
    
    ObjVertex *vertex = (ObjVertex *) &datas[0];    //  这里定义 vertex 指向 datas 的首地址, 把 vertex当成一个数组指针
    
    
    //读取 顶点坐标， 同时 初始化 normal 
    while ( objFile )
    {
        char c = objFile.get();
        if ( 'v' == c)
        {
            vertex->Normal = Vector3(0.0f,0.0f,0.0f);   //将法线初始化
            Vector3 &position = (vertex++)->Position;   //注意vertex++ 每次++ 相当于  vector 跨 6 个坐标
            objFile >> position.x >> position.y >> position.z;
        }
        objFile.ignore( MaxLineSize, '\n' );
    }
    
    
    //计算法线， 计算原理是 3个顶点形成一个面， 然后计算每个面的法线
    vertex = (ObjVertex *) &datas[0];
    for ( size_t faceIndex = 0; faceIndex < m_faces.size(); ++faceIndex)
    {
        IVector3 face = m_faces[faceIndex];
    
        Vector3 a = vertex[face.x].Position;
        Vector3 b = vertex[face.y].Position;
        Vector3 c = vertex[face.z].Position;
        Vector3 faceNormal = (b-a).Cross(c-a);
        
        vertex[face.x].Normal += faceNormal;
        vertex[face.y].Normal += faceNormal;
        vertex[face.z].Normal += faceNormal;
    }
    
    //归一化法线
    for (int v=0; v<GetVertexCount(); ++v)
        vertex[v].Normal.Normalize();
    
    
}

//主要是 生产 opengl 可以直接加载的 顶点索引 vector
void ModelSurface::GenerateTriangleIndices(vector<unsigned short>& indices) const
{
    indices.resize(GetTriangleIndexCount());
    vector<unsigned short>::iterator index = indices.begin();
    for( vector<IVector3>::const_iterator f = m_faces.begin(); f !=m_faces.end(); ++f )
    {
        *index++ = f->x;
        *index++ = f->y;
        *index++ = f->z;
    }
}


























































