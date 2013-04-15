//
//  VectorCustom.h
//  MiniDota
//
//  Created by apple on 12-12-10.
//  Copyright (c) 2012年 apple. All rights reserved.
//

#ifndef _VectorCustom_h
#define _VectorCustom_h
#include "Vector4_Reference.h"




typedef Vector4CPU<float> Vector4;

typedef Vector3CPU<float> Vector3;

typedef Vector2CPU<float> Vector2;

typedef Vector3CPU<int> IVector3;





inline IVector3 Vector3Normalize(IVector3 &a)
{
    IVector3 result = a;
    result.Normalize();
    return result;
}


inline IVector3 operator-(const IVector3 &a, const IVector3 &b)
{
	IVector3 c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return c;
}



inline IVector3 Vector3CrossProduct(IVector3 &a, IVector3 &b)
{
	IVector3 c;
	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return c;
}

//注意 这里内积是int类型
inline int Vector3Dotf(IVector3 &a, IVector3 &b)
{
	int result = a.x * b.x + a.y * b.y + a.z * b.z;
	return result;
}


inline IVector3 Vector3Dot(IVector3 &a, IVector3 &b)
{
	IVector3 c = Vector3Dotf(a, b);
	return c;
}



//***************************************************************************************************************************************************
//***************************************************************************************************************************************************
//***************************************************************************************************************************************************
//***************************************************************************************************************************************************
//***************************************************************************************************************************************************
//***************************************************************************************************************************************************
//***************************************************************************************************************************************************
//Vector3 f

inline Vector3 Vector3Normalize(Vector3 &a)
{
    Vector3 result = a;
    result.Normalize();
    return result;
}




inline Vector3 Vector3CrossProduct(Vector3 &a, Vector3 &b)
{
	Vector3 c;
	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return c;
}





inline float Vector3Dotf(Vector3 &a, Vector3 &b)
{
	float result = a.x * b.x + a.y * b.y + a.z * b.z;
	return result;
}


inline Vector3 Vector3Dot(Vector3 &a, Vector3 &b)
{
	Vector3 c = Vector3Dotf(a, b);
	return c;
}



inline Vector3 Vector3Min(Vector3 &a, Vector3 &b)
{
    Vector3 result;
    result.x = a.x < b.x ? a.x : b.x ;
    result.y = a.y < b.y ? a.y : b.y ;
    result.z = a.z < b.z ? a.z : b.z ;
    return result;
}

inline Vector3 Vector3Max(Vector3 &a, Vector3 &b)
{
    Vector3 result;
    result.x = a.x > b.x ? a.x : b.x ;
    result.y = a.y > b.y ? a.y : b.y ;
    result.z = a.z > b.z ? a.z : b.z ;
    return result;
}




inline bool operator==(Vector3 &a, Vector3 &b)
{
	bool result = (a.x==b.x && a.y==b.y && a.z==b.z );
	return result;
}



inline bool operator!=(Vector3 &a, Vector3 &b)
{
	bool result = (a.x==b.x && a.y==b.y && a.z==b.z );
	return !result;
}

inline Vector3 operator+(const Vector3 &a, const Vector3 &b)
{
	Vector3 c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return c;
}

inline Vector3 operator-(const Vector3 &a, const Vector3 &b)
{
	Vector3 c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return c;
}

inline Vector3 operator*(float f, const Vector3 &v)
{
	Vector3 result;
	result.x = f * v.x;
	result.y = f * v.y;
	result.z = f * v.z;
	return result;
}

inline Vector3 operator*(const Vector3 &v, float f)
{
	Vector3 result;
	result.x = f * v.x;
	result.y = f * v.y;
	result.z = f * v.z;
	return result;
}







//***************************************************************************************************************************************************
//***************************************************************************************************************************************************
//***************************************************************************************************************************************************
//***************************************************************************************************************************************************
//***************************************************************************************************************************************************
//***************************************************************************************************************************************************
//***************************************************************************************************************************************************
//Vector4 f

inline bool operator==(Vector4 &a, Vector4 &b)
{
	bool result = (a.x==b.x && a.y==b.y && a.z==b.z && a.w==b.w);
	return result;
}



inline bool operator!=(Vector4 &a, Vector4 &b)
{
	bool result = (a.x==b.x && a.y==b.y && a.z==b.z && a.w==b.w);
	return !result;
}

inline Vector4 operator+(const Vector4 &a, const Vector4 &b)
{
	Vector4 c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	c.w = a.w + b.w;
	return c;
}

inline Vector4 operator-(const Vector4 &a, const Vector4 &b)
{
	Vector4 c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	c.w = a.w - b.w;
	return c;
}

inline Vector4 operator*(float f, const Vector4 &v)
{
	Vector4 result;
	result.x = f * v.x;
	result.y = f * v.y;
	result.z = f * v.z;
	result.w = f * v.w;
	return result;
}

inline Vector4 operator*(const Vector4 &v, float f)
{
	Vector4 result;
	result.x = f * v.x;
	result.y = f * v.y;
	result.z = f * v.z;
	result.w = f * v.w;
	return result;
}



inline float VectorDotf(Vector4 &a, Vector4 &b)
{
	float result = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return result;
}

inline Vector4 VectorDot(Vector4 &a, Vector4 &b)
{
	Vector4 c = VectorDotf(a,b);
	return c;
}





inline Vector3 VectorMin(Vector3 &a, Vector4 &b)
{
    Vector3 result;
    result.x = a.x < b.x ? a.x : b.x ;
    result.y = a.y < b.y ? a.y : b.y ;
    result.z = a.z < b.z ? a.z : b.z ;
    return result;
}

inline Vector3 VectorMax(Vector3 &a, Vector4 &b)
{
    Vector3 result;
    result.x = a.x > b.x ? a.x : b.x ;
    result.y = a.y > b.y ? a.y : b.y ;
    result.z = a.z > b.z ? a.z : b.z ;
    return result;
}












#endif












































