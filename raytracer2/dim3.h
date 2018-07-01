#ifndef DIM3_H_
#define DIM3_H_

#include <math.h>

class dim3 
{
public:
	dim3() : m_x(0),m_y(0),m_z(0) {}
	dim3(float x, float y, float z) 
	{
		m_x = x;
		m_y = y;
		m_z = z;
	}
	float m_x, m_y, m_z;
	float dot(dim3& v) 
	{ 
		return m_x*v.m_x + m_y*v.m_y + m_z*v.m_z; 
	}
	dim3 cross(dim3 v) 
	{ 
		return dim3( m_y * v.m_z - m_z * v.m_y, m_z * v.m_x - m_x * v.m_z, m_x * v.m_y - m_y * v.m_x ); 
	}
	float getLength() 
	{
		return  sqrtf(m_x*m_x + m_y * m_y + m_z * m_z);
	}
	dim3 getNormal() 
	{
		float temp = 1/sqrtf(m_x*m_x + m_y*m_y + m_z*m_z);
		return dim3(m_x * temp, m_y * temp, m_z * temp);
	}
	dim3 operator -() 
	{
		return dim3( -1 * m_x,-1 * m_y,-1 * m_z );
	} 
	friend dim3 operator + (const dim3& left, const dim3& right) 
	{
		return dim3(left.m_x + right.m_x,left.m_y + right.m_y, left.m_z + right.m_z);
	}
	friend dim3 operator - (const dim3& left, const dim3& right) 
	{
		return left + ( -1 * right);
	}
	friend dim3 operator / (const dim3& left, float f) 
	{
		return dim3(left.m_x / f, left.m_y /f ,left.m_z / f);
	}
	friend dim3 operator * (float f, const dim3& right) 
	{
		return dim3(f * right.m_x, f * right.m_y, f * right.m_z);
	}
	friend dim3 operator * (const dim3& left, const dim3& right) 
	{
		return dim3(left.m_x*right.m_x,left.m_y*right.m_y,left.m_z*right.m_z);
	}
};

typedef	dim3 color;

#endif