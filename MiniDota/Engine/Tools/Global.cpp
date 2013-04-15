//
//  GlobalFunction.cpp
//  MiniDota
//
//  Created by apple on 13-1-16.
//  Copyright (c) 2013年 apple. All rights reserved.
//

#include "Global.h"
#include "VectorCustom.h"




// right hand coord system
// eye = `镜头位置`
// lookat = `镜头对准的位置`
// up = `镜头正上方的方向`
Matrix4x4 GutMatrixLookAtRH(Vector3 &eye, Vector3 &lookat, Vector3 &up)
{
	Vector3 up_normalized = Vector3Normalize(up);
	Vector3 zaxis = eye - lookat; zaxis.Normalize();
	Vector3 xaxis = Vector3CrossProduct(up_normalized, zaxis);
	Vector3 yaxis = Vector3CrossProduct(zaxis, xaxis);

	Matrix4x4 matrix;
	matrix.Identity();

	matrix.SetColumn(0, xaxis);
	matrix.SetColumn(1, yaxis);
	matrix.SetColumn(2, zaxis);
    
    matrix[3][0] = -Vector3Dot(xaxis, eye)[0];
	matrix[3][1] = -Vector3Dot(yaxis, eye)[0];
	matrix[3][2] = -Vector3Dot(zaxis, eye)[0];
    
	return matrix;
}







// OpenGL native right hand system
// fovy = `垂直方向的视角`
// aspect = `水平方向视角对重直方向视角的比值`
// z_hear = `镜头可以看到的最近距离`
// z_far = `镜头可以看到的最远距离`
Matrix4x4 GutMatrixPerspectiveRH_OpenGL(float fovy, float aspect,
										float z_near, float z_far)
{
	Matrix4x4 matrix;
	matrix.Identity();
    
	float fovy_radian = FastMath::DegreeToRadian(fovy);
	float yscale =  FastMath::Cot(fovy_radian/2.0f);
	float xscale = yscale * aspect;
    
	matrix[0][0] = xscale;
	matrix[1][1] = yscale;
	matrix[2][2] = (z_far + z_near)/(z_near - z_far);
	matrix[2][3] = -1.0f;
	matrix[3][2] = 2.0f * z_far * z_near / (z_near - z_far);
	matrix[3][3] = 0.0f;

	return matrix;
}











































