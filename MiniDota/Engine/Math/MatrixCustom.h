//
//  Matrix4x4.h
//  MiniDota
//
//  Created by apple on 12-12-10.
//  Copyright (c) 2012年 apple. All rights reserved.
//

#ifndef _MatrixCustom_h
#define _MatrixCustom_h

#include "Matrix4x4_Reference.h"
#include "VectorCustom.h"

typedef Matrix4x4CPU<float> Matrix4x4;


typedef Matrix3x3CPU<float> Matrix3x3;




inline bool operator==(Matrix4x4 &a, Matrix4x4 &b)
{
    
	bool result = a.m_Vec0==b.m_Vec0 && a.m_Vec1==b.m_Vec1 && a.m_Vec2==b.m_Vec2 && a.m_Vec3==b.m_Vec3;
	return result;
}

inline bool operator!=(Matrix4x4 &a, Matrix4x4 &b)
{
	bool result = a.m_Vec0!=b.m_Vec0 || a.m_Vec1!=b.m_Vec1 || a.m_Vec2!=b.m_Vec2 || a.m_Vec3!=b.m_Vec3;
	return result;
}

inline Matrix4x4 operator+(const Matrix4x4 &a, float f)
{
	Matrix4x4 result = a;
	result += f;
	return result;
}

inline Matrix4x4 operator+(float f, const Matrix4x4 &a)
{
	Matrix4x4 result = a;
	result += f;
	return result;
}

inline Matrix4x4 operator+(const Matrix4x4 &a, const Matrix4x4 &b)
{
	Matrix4x4 result;
	result.m_Vec0 = a.m_Vec0 + b.m_Vec0;
	result.m_Vec1 = a.m_Vec1 + b.m_Vec1;
	result.m_Vec2 = a.m_Vec2 + b.m_Vec2;
	result.m_Vec3 = a.m_Vec3 + b.m_Vec3;
	return result;
}


inline Matrix4x4 operator-(const Matrix4x4 &a, float f)
{
	Matrix4x4 result = a;
	result -= f;
	return result;
}

inline Matrix4x4 operator-(float f, const Matrix4x4 &a)
{
	Matrix4x4 result = a;
	result -= f;
	return result;
}

inline Matrix4x4 operator-(const Matrix4x4 &a, const Matrix4x4 &b)
{
	Matrix4x4 result;
	result.m_Vec0 = a.m_Vec0 - b.m_Vec0;
	result.m_Vec1 = a.m_Vec1 - b.m_Vec1;
	result.m_Vec2 = a.m_Vec2 - b.m_Vec2;
	result.m_Vec3 = a.m_Vec3 - b.m_Vec3;
	return result;
}


inline Vector4 operator*(const Vector4 &v, const Matrix4x4 &m)
{
	Vector4 result;
	result.x = v.x*m.m_00 + v.y*m.m_10 + v.z*m.m_20 + v.w*m.m_30;
	result.y = v.x*m.m_01 + v.y*m.m_11 + v.z*m.m_21 + v.w*m.m_31;
	result.z = v.x*m.m_02 + v.y*m.m_12 + v.z*m.m_22 + v.w*m.m_32;
	result.w = v.x*m.m_03 + v.y*m.m_13 + v.z*m.m_23 + v.w*m.m_33;
	return result;
}

inline Vector4 operator*(Matrix4x4 &matrix, Vector4 &vec)
{
	Vector4 result;
	result[0] = VectorDot(vec, matrix[0]).GetX();
	result[1] = VectorDot(vec, matrix[1]).GetX();
	result[2] = VectorDot(vec, matrix[2]).GetX();
	result[3] = VectorDot(vec, matrix[3]).GetX();
	return result;
}

inline Matrix4x4 operator*(const Matrix4x4 &a, const Matrix4x4 &b)
{
	Matrix4x4 result;
	result.m_Vec0 = a.m_Vec0 * b;
	result.m_Vec1 = a.m_Vec1 * b;
	result.m_Vec2 = a.m_Vec2 * b;
	result.m_Vec3 = a.m_Vec3 * b;
	return result;
}


inline Matrix4x4 operator*(const Matrix4x4 &a, float f)
{
	Matrix4x4 result;
	result.m_Vec0 = a.m_Vec0 * f;
	result.m_Vec1 = a.m_Vec1 * f;
	result.m_Vec2 = a.m_Vec2 * f;
	result.m_Vec3 = a.m_Vec3 * f;
	return result;
}

inline Matrix4x4 operator*(float f,const Matrix4x4 &a)
{
	Matrix4x4 result;
	result.m_Vec0 = a.m_Vec0 * f;
	result.m_Vec1 = a.m_Vec1 * f;
	result.m_Vec2 = a.m_Vec2 * f;
	result.m_Vec3 = a.m_Vec3 * f;
	return result;
}




#endif











































