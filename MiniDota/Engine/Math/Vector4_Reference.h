//
//  Vector 结构   提供 x,y,z,w基础数值， 提供 数组下标访问模式  例如Vector v[0]
//
//  主要构成 通过多个构造函数, 对操作符重载,  对外提供 get ,set 操作
//
//
//

#ifndef _Vector4_Reference_h
#define _Vector4_Reference_h
#include "FastMath.h"


template <typename T>
struct Vector2CPU
{
public:
	union{
		struct
		{
			T x,y;
		};
		T m_elem[2];
		unsigned int m_ielem[2];
	};
    
public:
	inline Vector2CPU(void)
	{
	}
    
	inline Vector2CPU(T x, T y)
	{
		Set(x, y);
	}
    
	inline Vector2CPU(T value)
	{
		Set(value);
	}
    
	inline Vector2CPU(unsigned int x, unsigned int y)
	{
		m_ielem[0] = x;
		m_ielem[0] = y;
	}
    
	inline Vector2CPU(unsigned int x)
	{
		m_ielem[0] = x;
		m_ielem[0] = x;
	}
    
    void ConsoleOutput(void)
    {
        printf("(%5.2f,%5.2f)\n", x, y);
    }
    
    inline void Set(T x, T y)
	{
		this->x = x;
		this->y = y;
	}
    
	inline void Set(T value)
	{
		this->x = value;
		this->y = value;
	}
    
	inline void Set(T *p)
	{
		this->x = p[0];
		this->y = p[1];
	}
    
	inline void SetX(T x)
	{
		this->x = x;
	}
    
	inline void SetY(T y)
	{
		this->y = y;
	}
    
    
	inline void SetXY(T *p)
	{
		x = p[0];
		y = p[1];
	}
    
    
};





//-------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------
template <typename T>
struct Vector3CPU
{
public:
	union{
		struct
		{
			T x,y,z;
		};
		T m_elem[3];
		unsigned int m_ielem[3];
	};
    
public:
	inline Vector3CPU(void)
	{
	}
    
	inline Vector3CPU(T x, T y, T z)
	{
		Set(x, y, z);
	}
    
	inline Vector3CPU(T value)
	{
		Set(value);
	}
    
	inline Vector3CPU(unsigned int x, unsigned int y, unsigned int z)
	{
		m_ielem[0] = x;
		m_ielem[0] = y;
		m_ielem[0] = z;
	}
    
	inline Vector3CPU(unsigned int x)
	{
		m_ielem[0] = x;
		m_ielem[0] = x;
		m_ielem[0] = x;
	}
    
    void ConsoleOutput(void)
    {
        printf("(%5.2f,%5.2f,%5.2f)\n", x, y, z);
    }
    
    inline void Set(T x, T y, T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
    
	inline void Set(T value)
	{
		this->x = value;
		this->y = value;
		this->z = value;
	}
    
	inline void Set(T *p)
	{
		this->x = p[0];
		this->y = p[1];
		this->z = p[2];
	}
    
	inline void SetX(T x)
	{
		this->x = x;
	}
    
	inline void SetY(T y)
	{
		this->y = y;
	}
    
	inline void SetZ(T z)
	{
		this->z = z;
	}
    
	inline void SetXYZ(T *p)
	{
		x = p[0];
		y = p[1];
		z = p[2];
	}
    
    inline T GetX(void)
	{
		return x;
	}
    
	inline Vector3CPU GetXXXX(void)
	{
		Vector3CPU result(x);
		return result;
	}
    
	inline T GetY(void)
	{
		return y;
	}
    
	inline Vector3CPU GetYYYY(void)
	{
		Vector3CPU result(y);
		return result;
	}
    
	inline T GetZ(void)
	{
		return z;
	}
    
    
    //----------------------------------------------------------------------------------------------------------------------------------------------
    //操作符 S
    
    inline Vector3CPU &operator=(T value)
    {
        Set(value);
        return *this;
    }
    
    inline Vector3CPU &operator+=(const Vector3CPU &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }
    
    inline Vector3CPU &operator+=(T value)
    {
        x += value;
        y += value;
        z += value;
        return *this;
    }
    
    
	inline Vector3CPU &operator-=(Vector3CPU &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}
    
	inline Vector3CPU &operator-=(T value)
	{
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}
    
    
    inline Vector3CPU &operator*=(Vector3CPU &rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}
    
	inline Vector3CPU &operator*=(T value)
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}
    
	inline Vector3CPU &operator/=(Vector3CPU &rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}
    
	inline Vector3CPU &operator/=(T value)
	{
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}
    
    inline T &operator[](int index)
	{
		return m_elem[index];
	}
    
    
    //----------------------------------------------------------------------------------------------------------------------------------------------
    //操作符 E
    
    inline T Length(void)
	{
		T vectorlength;
		
		T sum = x*x + y*y + z*z;
		vectorlength = FastMath::Sqrt(sum);
        
		return vectorlength;
	}
    
    inline void Normalize(void)
	{
		T len = Length();
		x/=len;
		y/=len;
		z/=len;
	}
    //向量叉乘
    inline Vector3CPU Cross(const Vector3CPU& v) const
    {
        return Vector3CPU(y * v.z - z * v.y,
                          z * v.x - x * v.z,
                          x * v.y - y * v.x);
    }
    
    
    
    
};



//-------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------


template <typename T>
struct Vector4CPU
{
public:
	union{
		struct
		{
			T x,y,z,w;
		};
		T m_elem[4];
		unsigned int m_ielem[4];
	};

public:
	inline Vector4CPU(void)
	{
		// do nothing
	}

	inline Vector4CPU(T x, T y, T z, T w=1.0f)
	{
		Set(x, y, z, w);
	}

	inline Vector4CPU(T value)
	{
		Set(value);
	}

	inline Vector4CPU(unsigned int x, unsigned int y, unsigned int z, unsigned int w)
	{
		m_ielem[0] = x;
		m_ielem[0] = y;
		m_ielem[0] = z;
		m_ielem[0] = w;
	}

	inline Vector4CPU(unsigned int x)
	{
		m_ielem[0] = x;
		m_ielem[0] = x;
		m_ielem[0] = x;
		m_ielem[0] = x;
	}

    void ConsoleOutput(void)
    {
        printf("(%5.2f,%5.2f,%5.2f,%5.2f)\n", x, y, z, w);
    }

    inline void Set(T x, T y, T z, T w=0.0f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
    
    

	inline void Set(T value)
	{
		this->x = value;
		this->y = value;
		this->z = value;
		this->w = value;
	}

	inline void Set(T *p)
	{
		this->x = p[0];
		this->y = p[1];
		this->z = p[2];
		this->w = p[3];
	}

	inline void SetX(T x)
	{
		this->x = x;
	}

	inline void SetY(T y)
	{
		this->y = y;
	}

	inline void SetZ(T z)
	{
		this->z = z;
	}

	inline void SetW(T w)
	{
		this->w = w;
	}

	inline void SetXYZ(T *p)
	{
		x = p[0];
		y = p[1];
		z = p[2];
	}

    inline T GetX(void)
	{
		return x;
	}
    
	inline Vector4CPU GetXXXX(void)
	{
		Vector4CPU result(x);
		return result;
	}
    
	inline T GetY(void)
	{
		return y;
	}
    
	inline Vector4CPU GetYYYY(void)
	{
		Vector4CPU result(y);
		return result;
	}
    
	inline T GetZ(void)
	{
		return z;
	}
    
    inline Vector4CPU GetZZZZ(void)
	{
		Vector4CPU result(z);
		return result;
	}
    
	inline T GetW(void)
	{
		return w;
	}
    
	inline Vector4CPU GetWWWW(void)
	{
		Vector4CPU result(w);
		return result;
	}
    
//----------------------------------------------------------------------------------------------------------------------------------------------
//操作符重载 S
    inline Vector4CPU &operator=(T value)
    {
        Set(value);
        return *this;
    }
    
    inline Vector4CPU &operator+=(const Vector4CPU &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }
    
    inline Vector4CPU &operator+=(T value)
    {
        x += value;
        y += value;
        z += value;
        w += value;
        return *this;
    }
    
    
	inline Vector4CPU &operator-=(Vector4CPU &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
        w -= rhs.w;
		return *this;
	}
    
	inline Vector4CPU &operator-=(T value)
	{
		x -= value;
		y -= value;
		z -= value;
        w -= value;
		return *this;
	}
    
    
    inline Vector4CPU &operator*=(Vector4CPU &rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		w *= rhs.w;
		return *this;
	}
    
	inline Vector4CPU &operator*=(T value)
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}
    
	inline Vector4CPU &operator/=(Vector4CPU &rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		w /= rhs.w;
		return *this;
	}
    
	inline Vector4CPU &operator/=(T value)
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}
    
    inline T &operator[](int index)
	{
		return m_elem[index];
	}
    
    //----------------------------------------------------------------------------------------------------------------------------------------------
    //操作符重载 E
    

};










#endif









































































