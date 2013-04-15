//
//  Matrix 基础构成  m_00 到 m_33 16个基本构成变量， 或者 m_00 到 m_22 9个变量
//  为了方便 提供行访问， 在 4*4矩阵中 m_Vec0 表示取第一行 m_Vec0 == ( m[0][0], m[0][1], m[0][2], m[0][3] )
//
//  这个结构组成  分几部分  1,构造方法， 2, set,get的封装， 3 操作符重载
//
//

#ifndef _Matrix4x4_Reference_h
#define _Matrix4x4_Reference_h
#include "VectorCustom.h"


    
    
    
    

    
    
    
    
//********************************************************************************************************************************************************
//********************************************************************************************************************************************************
//********************************************************************************************************************************************************

template <typename T>
struct Matrix3x3CPU
{
public:
    union
    {
        struct
        {
            float m_00, m_01, m_02;
            float m_10, m_11, m_12;
            float m_20, m_21, m_22;
        };
        
        struct
		{
			Vector4 m_Vec0, m_Vec1, m_Vec2;
		};
    };
    
    
    void ConsoleOutput(void)
    {
        printf("\t(%5.6f,%5.6f,%5.6f)\n", m_00, m_01, m_02);
        printf("\t(%5.6f,%5.6f,%5.6f)\n", m_10, m_11, m_12);
        printf("\t(%5.6f,%5.6f,%5.6f)\n", m_20, m_21, m_22);
    }
    
//--------------------------------------------------------------------------------------------------------------------------------------------------
//构造函数 S
    inline Matrix3x3CPU()
    {
    }
    
    inline Matrix3x3CPU(
                   float f00, float f01, float f02,
                   float f10, float f11, float f12,
                   float f20, float f21, float f22
                   )
    {
        m_00 = f00; m_01 = f01; m_02 = f02;
        m_10 = f10; m_11 = f11; m_12 = f12;
        m_20 = f20; m_21 = f21; m_22 = f22;
    }
    
    
    
    inline void Identity(void)
	{
		
		m_00 = 1.0f; m_01 = 0.0f; m_02 = 0.0f;
		m_10 = 0.0f; m_11 = 1.0f; m_12 = 0.0f;
		m_20 = 0.0f; m_21 = 0.0f; m_22 = 1.0f;
	}
    
//构造函数 E    
//--------------------------------------------------------------------------------------------------------------------------------------------------


    //求行列式
    inline T Determinant() const
    {
        T result;
        
        T r1 = m_00*m_11*m_22 + m_01*m_12*m_20 + m_02*m_10*m_21;
        T r2 = m_02*m_11*m_20 + m_00*m_12*m_21 + m_01*m_10*m_22;
        result = r1 - r2 ;
        return result;
    }
    
    
    inline Matrix3x3CPU Inverse()
    {
        T det = 1.0f/Determinant();
        
        T a11 = ( m_11*m_22 - m_12*m_21 ) * det;
        T a12 = ( m_02*m_21 - m_01*m_22 ) * det;
        T a13 = ( m_01*m_12 - m_02*m_11 ) * det;
        
        T a21 = ( m_12*m_20 - m_10*m_22 ) * det;
        T a22 = ( m_00*m_22 - m_02*m_20 ) * det;
        T a23 = ( m_02*m_10 - m_00*m_12 ) * det;
        
        T a31 = ( m_10*m_21 - m_11*m_20 ) * det;
        T a32 = ( m_01*m_20 - m_00*m_21 ) * det;
        T a33 = ( m_00*m_11 - m_01*m_10 ) * det;
        
        Matrix3x3CPU result(a11, a12, a13,
                            a21, a22, a23,
                            a31, a32 ,a33);

        
        return result;
    }
    
    
    inline Matrix3x3CPU &Transpose(void)
	{
		FastMath::Swap(m_01,m_10);
		FastMath::Swap(m_02,m_20);
		FastMath::Swap(m_12,m_21);
        
		return *this;
	}
    
};
    
    
    
    
    

//********************************************************************************************************************************************************
//********************************************************************************************************************************************************
//********************************************************************************************************************************************************
template <typename T>
struct Matrix4x4CPU
{
public:
    union
	{
		struct
		{
			float m_00, m_01, m_02, m_03;
			float m_10, m_11, m_12, m_13;
			float m_20, m_21, m_22, m_23;
			float m_30, m_31, m_32, m_33;
		};
        
        struct
		{
			Vector4 m_Vec0, m_Vec1, m_Vec2, m_Vec3;
		};
        
	};
    
public:
	inline Matrix4x4CPU()
	{
        
	}
    
    
	inline void Identity(void)
	{
		
		m_00 = 1.0f; m_01 = 0.0f; m_02 = 0.0f; m_03 = 0.0f;
		m_10 = 0.0f; m_11 = 1.0f; m_12 = 0.0f; m_13 = 0.0f;
		m_20 = 0.0f; m_21 = 0.0f; m_22 = 1.0f; m_23 = 0.0f;
		m_30 = 0.0f; m_31 = 0.0f; m_32 = 0.0f; m_33 = 1.0f;
	}
    
    void ConsoleOutput(void)
    {
        printf("\t(%5.2f,%5.2f,%5.2f,%5.2f)\n", m_00, m_01, m_02, m_03);
        printf("\t(%5.2f,%5.2f,%5.2f,%5.2f)\n", m_10, m_11, m_12, m_13);
        printf("\t(%5.2f,%5.2f,%5.2f,%5.2f)\n", m_20, m_21, m_22, m_23);
        printf("\t(%5.2f,%5.2f,%5.2f,%5.2f)\n", m_30, m_31, m_32, m_33);
    }
    
    
    //--------------------------------------------------------------------------------------------------------------------------------------------------
    //构造函数 S
    
	inline Matrix4x4CPU(
                        float f00, float f01, float f02, float f03,
                        float f10, float f11, float f12, float f13,
                        float f20, float f21, float f22, float f23,
                        float f30, float f31, float f32, float f33
                        )
	{
		m_00 = f00; m_01 = f01; m_02 = f02; m_03 = f03;
		m_10 = f10; m_11 = f11; m_12 = f12; m_13 = f13;
		m_20 = f20; m_21 = f21; m_22 = f22; m_23 = f23;
		m_30 = f30; m_31 = f31; m_32 = f32; m_33 = f33;
	}
    
    
    //构造函数 E
    //--------------------------------------------------------------------------------------------------------------------------------------------------
    
    
    
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    //Set 与 Get S
    
    inline void SetColumn(int column, Vector4 &vec)
	{
		float *p = &m_00 + column;
		p[0] = vec.GetX();
		p[4] = vec.GetY();
		p[8] = vec.GetZ();
		p[12] = vec.GetW();
	}
    
    inline void SetColumn(int column, Vector3 &vec)
	{
		float *p = &m_00 + column;
		p[0] = vec.GetX();
		p[4] = vec.GetY();
		p[8] = vec.GetZ();
		p[12] = 0;
	}
    
    inline Vector3 GetRow_3(int row)
	{
        Vector4 *rows = &m_Vec0;
        Vector4 &v4 = rows[row];
		return Vector3(v4.GetX(), v4.GetY(), v4.GetZ());
	}
    
	inline Vector3 GetColumn_3(int column)
	{
		Vector3 vec;
		float *p = &m_00 + column;
		vec.SetX(p[0]);
		vec.SetY(p[4]);
		vec.SetZ(p[8]);
		return vec;
	}
    
    inline Vector4 &GetRow(int row)
	{
		Vector4 *rows = &m_Vec0;
		return rows[row];
	}
    
	inline Vector4 GetColumn(int column)
	{
		Vector4 vec;
		float *p = &m_00 + column;
        
		vec.SetX(p[0]);
		vec.SetY(p[4]);
		vec.SetZ(p[8]);
		vec.SetW(p[12]);
        
		return vec;
	}
    
    //Set 与 Get E
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    
    
    
    
    
    //**************************************************************************************************************************************************
    //操作符 -S
    
    inline float &operator() (int i, int j)
	{
		return GetRow(i)[j];
	}
    
	inline Vector4 &operator[](int row)
	{
		return GetRow(row);
	}
    
    
	inline Matrix4x4CPU &operator=(const Matrix4x4CPU &rhs)
	{
		m_Vec0 = rhs.m_Vec0;
		m_Vec1 = rhs.m_Vec1;
		m_Vec2 = rhs.m_Vec2;
		m_Vec3 = rhs.m_Vec3;
        
		return *this;
	}
    
    
	inline Matrix4x4CPU &operator=(float f)
	{
		Vector4 ffff(f);
        
		m_Vec0 = ffff;
		m_Vec1 = ffff;
		m_Vec2 = ffff;
		m_Vec3 = ffff;
        
		return *this;
	}
    
	inline Matrix4x4CPU &operator+=(float f)
	{
		Vector4 ffff(f);
        
		m_Vec0 += ffff;
		m_Vec1 += ffff;
		m_Vec2 += ffff;
		m_Vec3 += ffff;
        
		return *this;
	}
    
	inline Matrix4x4CPU &operator+=(const Matrix4x4CPU &rhs)
	{
		m_Vec0 = m_Vec0 + rhs.m_Vec0;
		m_Vec1 = m_Vec1 + rhs.m_Vec1;
		m_Vec2 = m_Vec2 + rhs.m_Vec2;
		m_Vec3 = m_Vec3 + rhs.m_Vec3;
        
		return *this;
	}
    
	inline Matrix4x4CPU &operator-=(float f)
	{
		Vector4 ffff(f);
        
		m_Vec0 -= f;
		m_Vec1 -= f;
		m_Vec2 -= f;
		m_Vec3 -= f;
        
		return *this;
	}
    
	inline Matrix4x4CPU &operator-=(Matrix4x4CPU &rhs)
	{
		m_Vec0 -= rhs.m_Vec0;
		m_Vec1 -= rhs.m_Vec1;
		m_Vec2 -= rhs.m_Vec2;
		m_Vec3 -= rhs.m_Vec3;
        
		return *this;
	}
    
	inline Matrix4x4CPU &operator*=(float f)
	{
		m_Vec0 *= f;
		m_Vec1 *= f;
		m_Vec2 *= f;
		m_Vec3 *= f;
        
		return *this;
	}
    
	inline Matrix4x4CPU &operator*=(Matrix4x4CPU &rhs)
	{
		m_Vec0 = m_Vec0 * rhs;
		m_Vec1 = m_Vec1 * rhs;
		m_Vec2 = m_Vec2 * rhs;
		m_Vec3 = m_Vec3 * rhs;
        
		return *this;
	}
    
	inline Matrix4x4CPU &operator/=(float f)
	{
		m_Vec0 /= f;
		m_Vec1 /= f;
		m_Vec2 /= f;
		m_Vec3 /= f;
        
		return *this;
	}
    
//  操作符 M
//**************************************************************************************************************************************************
    
    
  
// start 矩阵旋转
//********************************************************************************************************************************************************
    
    // this = Rx * this
	void RotateX( const float radian )
	{
		float Sin, Cos;
		FastMath::SinCos(radian, Sin, Cos);
        
		float Temp10, Temp11, Temp12, Temp13;
		float Temp20, Temp21, Temp22, Temp23;
        
		Temp10 = m_10 * Cos + m_20 * Sin;
		Temp11 = m_11 * Cos + m_21 * Sin;
		Temp12 = m_12 * Cos + m_22 * Sin;
		Temp13 = m_13 * Cos + m_23 * Sin;
        
		Temp20 = m_10 *-Sin + m_20 * Cos;
		Temp21 = m_11 *-Sin + m_21 * Cos;
		Temp22 = m_12 *-Sin + m_22 * Cos;
		Temp23 = m_13 *-Sin + m_23 * Cos;
        
		m_10 = Temp10;
		m_11 = Temp11;
		m_12 = Temp12;
		m_13 = Temp13;
		m_20 = Temp20;
		m_21 = Temp21;
		m_22 = Temp22;
		m_23 = Temp23;
	}
    
	void RotateX_Replace( const float radian )
	{
		float fSin, fCos;
		FastMath::SinCos(radian, fSin, fCos);
        
		m_Vec0.Set(1.0f,  0.0f,  0.0f, 0.0f);
		m_Vec1.Set(0.0f,  fCos,  fSin, 0.0f);
		m_Vec2.Set(0.0f, -fSin,  fCos, 0.0f);
		m_Vec3.Set(0.0f,  0.0f,  0.0f, 1.0f);
	}
    
    
    
    // this = Ry * this
	void RotateY( const float radian )
	{
		float Temp00, Temp01, Temp02, Temp03;
		float Temp20, Temp21, Temp22, Temp23;
		float Sin, Cos;
		FastMath::SinCos(radian, Sin, Cos);
        
		Temp00 = m_00 * Cos - m_20 * Sin;
		Temp01 = m_01 * Cos - m_21 * Sin;
		Temp02 = m_02 * Cos - m_22 * Sin;
		Temp03 = m_03 * Cos - m_23 * Sin;
        
		Temp20 = m_00 * Sin + m_20 * Cos;
		Temp21 = m_01 * Sin + m_21 * Cos;
		Temp22 = m_02 * Sin + m_22 * Cos;
		Temp23 = m_03 * Sin + m_23 * Cos;
        
		m_00 = Temp00;
		m_01 = Temp01;
		m_02 = Temp02;
		m_03 = Temp03;
		m_20 = Temp20;
		m_21 = Temp21;
		m_22 = Temp22;
		m_23 = Temp23;
	}
    
	void RotateY_Replace( const float radian )
	{
		float fSin, fCos;
		FastMath::SinCos(radian, fSin, fCos);
        
		m_Vec0.Set( fCos,  0.0f, -fSin, 0.0f);
		m_Vec1.Set( 0.0f,  1.0f,  0.0f, 0.0f);
		m_Vec2.Set(fSin,  0.0f,  fCos, 0.0f);
		m_Vec3.Set( 0.0f,  0.0f,  0.0f, 1.0f);
	}
    
    
    
    
    
    // 矩阵自身对Z旋转 radian弧度
	void RotateZ( const float radian )
	{
		float Temp00, Temp01, Temp02, Temp03;
		float Temp10, Temp11, Temp12, Temp13;
		float Sin, Cos;
		FastMath::SinCos(radian, Sin, Cos);
        
		Temp00 = m_00 * Cos + m_10 * Sin;
		Temp01 = m_01 * Cos + m_11 * Sin;
		Temp02 = m_02 * Cos + m_12 * Sin;
		Temp03 = m_03 * Cos + m_13 * Sin;
        
		Temp10 = m_00 *-Sin + m_10 * Cos;
		Temp11 = m_01 *-Sin + m_11 * Cos;
		Temp12 = m_02 *-Sin + m_12 * Cos;
		Temp13 = m_03 *-Sin + m_13 * Cos;
        
		m_00 = Temp00;
		m_01 = Temp01;
		m_02 = Temp02;
		m_03 = Temp03;
		m_10 = Temp10;
		m_11 = Temp11;
		m_12 = Temp12;
		m_13 = Temp13;
	}
    
    
    //构建一个 对 Z 旋转的矩阵
	void RotateZ_Replace( const float radian )
	{
		float fSin, fCos;
		FastMath::SinCos(radian, fSin, fCos);
        
		m_Vec0.Set( fCos,  fSin, 0.0f, 0.0f);
		m_Vec1.Set(-fSin,  fCos, 0.0f, 0.0f);
		m_Vec2.Set( 0.0f,  0.0f, 1.0f, 0.0f);
		m_Vec3.Set( 0.0f,  0.0f, 0.0f, 1.0f);
	}
    
    
    void Scale_Replace(float x, float y, float z)
	{
		m_Vec0.Set(x, 0, 0, 0);
		m_Vec1.Set(0, y, 0, 0);
		m_Vec2.Set(0, 0, z, 0);
		m_Vec3.Set(0, 0, 0, 1);
	}
    
    
// end 矩阵旋转
//********************************************************************************************************************************************************
    
    
    Matrix3x3CPU<T> ToMatrix3() const
    {
        Matrix3x3CPU<T> result(m_00,m_01,m_02,
                          m_10,m_11,m_12,
                          m_20,m_21,m_22);
        return result;
    }
};

    
    
    
    
    
    
    
 
    
    
    
    
    

#endif



















































