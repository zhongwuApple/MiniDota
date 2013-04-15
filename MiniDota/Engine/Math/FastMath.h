//
//  FastMath.h
//  MiniDota
//
//  Created by apple on 13-1-28.
//  Copyright (c) 2013年 apple. All rights reserved.
//

#ifndef _FastMath_h
#define _FastMath_h

#define MATH_PI 3.141592653f
#include <math.h>


namespace FastMath
{
    
    
    template<class T> inline void Swap(T &a, T &b)
    {
        T c = b;
        b = a;
        a = c;
    }
    
    
    inline float DegreeToRadian(float r)
    {
        float radian = r * (MATH_PI / 180.0f);
        return radian;
    }
    
    inline float DegToRad(float r)
    {
        return DegreeToRadian(r);
    }
    
    inline float RadianToDegree(float r)
    {
        float degree = r * (180.0f / MATH_PI);
        return degree;
    }
    
    inline float RadToDeg(float r)
    {
        return RadianToDegree(r);
    }
    
    inline float Abs(float v)
    {
        float result = fabsf(v);
        return result;
    }
    
    inline float Sqrt(float v)
    {
        float result = sqrtf(v);
        return result;
    }
    
    
    
    inline float Sin(float radian)
    {
        float result = sinf(radian);
        return result;
    }
    
    // -pi < p_Angle < pi
    inline float FastSin(float p_Angle)
    {
        const float Factor1 = 4.0f / MATH_PI;
        const float Factor2 = 4.0f / (MATH_PI * MATH_PI);
        return (Factor1 * p_Angle) - (Factor2 * p_Angle * fabs(p_Angle));
    }
    
    inline float ASin(float v)
    {
        float result = (float) asin(v);
        return result;
    }
    
    inline float Cos(float radian)
    {
        float result = cosf(radian);
        return result;
    }
    
    inline float ACos(float v)
    {
        float result = (float) acos(v);
        return result;
    }
    
    inline void SinCos(float radian, float &sinvalue, float &cosvalue)
    {
        sinvalue = sinf( radian);
        cosvalue = cosf( radian);
    }
    
    inline float Tan(float radian)
    {
        float result = tanf(radian);
        return result;
    }
    
    inline float Cot(float radian)
    {
        float result = 1/tanf(radian);
        return result;
    }
    
    inline float Lerp(float a, float b, float t)
    {
        return a + (b-a) * t;
    }
    
    inline float frac(float a)
    {
        return a - (int)a;
    }
    
};























#endif




























































