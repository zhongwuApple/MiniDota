//
//  ModelSurface.h
//  MiniDota
//
//
//  
//

#ifndef _ModelSurface_h
#define _ModelSurface_h

#include <iostream>
#include "Interfaces.h"



using namespace std;

class ModelSurface : public ISurface
{
public:
    ModelSurface(const string& name);
    int GetVertexCount() const;                                                     //顶点的总个数
    int GetTriangleIndexCount() const;                                              //顶点索引的总个数
    void GenerateVertices(vector<float>& vertices, unsigned char flags) const;      //顶点数据
    void GenerateTriangleIndices(vector<unsigned short>& indices) const;            //顶点索引 数据 
private:
    string m_name;                   //模型的 路径+文件名称
    vector<IVector3> m_faces;        // 这里 m_faces  存储了 顶点的索引       为了节省空间所以使用的是 int类型而不是 float
    mutable size_t m_faceCount;      // mutable 关键字  在const函数中可以改变变量值
    mutable size_t m_vertexCount;
    static const int MaxLineSize = 128;
    
};



#endif























































