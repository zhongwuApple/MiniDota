//
//  GlobalFunction.h
//  MiniDota
//
//  Created by apple on 13-1-16.
//  Copyright (c) 2013年 apple. All rights reserved.
//

#ifndef _Global_h
#define _Global_h

#include <iostream>
#include <string>
#include "MatrixCustom.h"
#include "VectorCustom.h"
#include "Interfaces.h"

const string resourcesPath  = ResourceEngine::CreateResourceManager()->GetResourcePath() + "/";


Matrix4x4 GutMatrixLookAtRH(Vector3 &eye, Vector3 &lookat, Vector3 &up);

Matrix4x4 GutMatrixPerspectiveRH_OpenGL(float fovy, float aspect, float z_near, float z_far);

















































#endif 












































































