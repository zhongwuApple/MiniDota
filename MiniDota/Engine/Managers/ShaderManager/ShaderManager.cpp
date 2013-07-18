//
//  ShaderManager.cpp
//  MiniDota
//
//  Created by apple on 12-12-11.
//  Copyright (c) 2012年 apple. All rights reserved.
//

#include "ShaderManager.h"
#include <fstream>
#include <stdio.h>
#include "Global.h"

using namespace std;

map<string, ShaderObject*> ShaderManager::cachedShaders;





ShaderObject* ShaderManager::GetShaderObject( const string& name )
{
    map<string,ShaderObject*>::iterator ite;
    ShaderObject *obj = NULL;
    
    ite = ShaderManager::cachedShaders.find(name);
    if (ite != ShaderManager::cachedShaders.end())
        obj = cachedShaders[name];
    return obj;
}



int ShaderManager::ShaderSize(const string &name)
{
    ifstream objFile(name.c_str());
    objFile.seekg(0,ios::end);
    int length = objFile.tellg();
    return length;
}


void ShaderManager::ReadShader(char *rs, const string& name, int len)
{
    ifstream objFile(name.c_str());
    int cout = 0;
    while (cout<len)
    {
        char c = objFile.get();
        rs[cout] = c;
        cout++;
    }
    rs[len] = '\0';
}






ShaderObject* ShaderManager::LoadShader(const string &shaderName)
{
    ShaderObject *obj = GetShaderObject(shaderName);
    if (obj == NULL)
    {        
        const string& vName = resourcesPath + shaderName + ".vert";
        const string& fName = resourcesPath + shaderName + ".frag";
        
        int vLen = ShaderSize(vName);
        int fLen = ShaderSize(fName);
        char vertexShaderSource[vLen];
        char fragmentShaderSource[fLen];
        ReadShader(vertexShaderSource,vName, vLen);
        ReadShader(fragmentShaderSource,fName, fLen);
        
        GLuint program = BuildProgram(vertexShaderSource, fragmentShaderSource);
        ShaderObject *newObj = (ShaderObject *)malloc(sizeof(ShaderObject));
        ShaderManager::cachedShaders.insert(make_pair(shaderName, newObj));
        newObj->program = program;
        UseShader(newObj);
        return newObj;
    }
    else
    {
        return obj;
    }
    
}






#pragma mark shader 流程处理
GLuint ShaderManager::BuildProgram(const char* vShader, const char* fShader) const
{
    GLuint vertexShader = BuildShader(vShader, GL_VERTEX_SHADER);
    GLuint fragmentShader = BuildShader(fShader, GL_FRAGMENT_SHADER);
    
    GLuint programHandle = glCreateProgram();
    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
    glLinkProgram(programHandle);
    
    GLint linkSuccess;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE)
    {
        GLchar messages[256];
        glGetProgramInfoLog(programHandle, sizeof(messages), 0, &messages[0]);
        cout << messages;
        exit(1);
    }
    return programHandle;
}


GLuint ShaderManager::BuildShader(const char* source, GLenum shaderType) const
{
    GLuint shaderHandle = glCreateShader(shaderType);
    glShaderSource(shaderHandle, 1, &source, 0);
    glCompileShader(shaderHandle);
    
    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
    if (compileSuccess == GL_FALSE)
    {
        GLchar messages[256];
        glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
        cout << messages;
        exit(1);
    }
    return shaderHandle;
}





void ShaderManager::UseShader(ShaderObject *obj)
{
    GLuint program = obj->program;
    glUseProgram(program);
    obj->m_attributes.VPosition = glGetAttribLocation(program, "VPosition");
    obj->m_attributes.VNormal = glGetAttribLocation(program, "VNormal");
    obj->m_attributes.VColor = glGetAttribLocation(program, "VColor");

    obj->m_uniforms.WorldMatrix4x4 = glGetUniformLocation(program, "WorldMatrix4x4");
    obj->m_uniforms.ViewMatrix4x4 = glGetUniformLocation(program, "ViewMatrix4x4");
    obj->m_uniforms.Projection4x4 = glGetUniformLocation(program, "Projection4x4");
    obj->m_uniforms.NormalMatrix3x3 = glGetUniformLocation(program, "NormalMatrix3x3");
    
    obj->m_other.World3x3 = glGetUniformLocation(program, "World3x3");
    obj->m_other.View3x3 = glGetUniformLocation(program, "View3x3");
    obj->m_other.WorldView3x3 = glGetUniformLocation(program, "WorldView3x3");
    
    
    
    //光源基本信息
    obj->m_uniforms.VLightDirection = glGetUniformLocation(program, "VLightDirection");
    obj->m_uniforms.VLightPosition = glGetUniformLocation(program, "VLightPosition");
    
    obj->m_uniforms.VLightAmbientColor = glGetUniformLocation(program, "VLightAmbientColor");
    obj->m_uniforms.VDiffuseColor = glGetUniformLocation(program, "VDiffuseColor");
    obj->m_uniforms.VSpecularColor = glGetUniformLocation(program, "VSpecularColor");
    obj->m_uniforms.VLightAttenuation = glGetUniformLocation(program, "VLightAttenuation");
    
    obj->m_uniforms.FSpotLightCutoff = glGetUniformLocation(program, "FSpotLightCutoff");
    obj->m_uniforms.FSpotLightExponent = glGetUniformLocation(program, "FSpotLightExponent");
    obj->m_uniforms.FSpotlightHalfCutoffCosine = glGetUniformLocation(program, "FSpotlightHalfCutoffCosine");
    obj->m_uniforms.FSpotLightInnerCone = glGetUniformLocation(program, "FSpotLightInnerCone");
    
    //材质
    obj->m_uniforms.VMaterialAmbient = glGetUniformLocation(program, "VMaterialAmbient");
    obj->m_uniforms.VMaterialDiffuse = glGetUniformLocation(program, "VMaterialDiffuse");
    obj->m_uniforms.VMaterialSpecular = glGetUniformLocation(program, "VMaterialSpecular");
    obj->m_uniforms.VMaterialEmissive = glGetUniformLocation(program, "VMaterialEmissive");
    
    obj->m_uniforms.FMaterialShininess = glGetUniformLocation(program, "FMaterialShininess");
    

    
    
}





































