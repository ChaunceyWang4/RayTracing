#ifndef OBJECT_H_
#define OBJECT_H_

#include "ray.h"

class material 
{
private:
	color m_color;
	float m_refl;
	float m_diff;
	float m_trans;
public:
	material() {}
	void setColor(color& c) 
	{
		m_color = c;	
	}
	color getColor() 
	{
		return m_color; 
	}
	void setDiffuse(float d) 
	{
		m_diff = d; 
	}
	void setReflection(float r) 
	{
		m_refl = r; 
	}
	void setRefraction(float t) 
	{
		m_trans = t; 
	}
	float getDiffuse() 
	{
		return m_diff; 
	}
	float getReflection() 
	{
		return m_refl; 
	}
	float getSpecular()
	{
		return 1- m_diff; 
	}
	float getRefraction() 
	{
		return m_trans; 
	}
};

class primitive 
{
protected:
	material  m_material;
	int tex;
public:
	virtual int getType() = 0;
	virtual int intersect(ray& r, float& d) = 0;
	virtual dim3 getNormal(dim3 p) = 0;
	virtual bool isLight() = 0;
	virtual color getColor(dim3& pos) = 0;
	material* getMaterial() 
	{
		return &m_material; 
	}
	void setMaterial(material& m) 
	{
		m_material = m; 
	}
	void setTex() 
	{
		tex = 1; 
	}
	int getTex() 
	{
		return tex; 
	}
};

class sphere: public primitive 
{
private:
	dim3 m_center;
	float m_radius;
	bool m_light;
public:
	int getType()	
	{
		return 1; 
	}
	sphere(dim3 c, float r):m_center(c), m_radius(r) 
	{
		m_light = false;
	}
	dim3&  getCenter() 
	{
		return m_center; 
	}
	dim3 getNormal(dim3 p) 
	{
		return (p - m_center) / m_radius;
	}
	int	intersect(ray& r, float& d);
	void setLight() 
	{
		m_light = true; 
	}
	bool isLight() 
	{
		return m_light; 
	}
	color getColor(dim3& pos);
};

class plane : public primitive 
{
private:
	dim3 normal;
	float d;
	int tex;
public:
	int getType() 
	{
		return 2; 
	}
	plane(dim3 n,float di) 
	{
		normal = n;
		d = di;
		tex = 0;
	}
	void setTex()
	{
		tex = 1; 
	}
	int intersect(ray& r, float& d);
	dim3 getNormal(dim3 p) 
	{
		return normal; 
	}
	float getD() 
	{
		return d; 
	}
	bool isLight() 
	{
		return false; 
	}
	color getColor(dim3& pos);
};

class cube: public primitive 
{
private:
	dim3 n[6];
	float d[6];
public:
	int getType() 
	{
		return 3;
	}
	cube(dim3* normals, float* scalar) 
	{
		for(int i = 0;i < 6; i++) 
		{
			n[i] = normals[i];
			d[i] = scalar[i];
		}
	}
	bool isLight() 
	{
		return false; 
	}
	int intersect(ray& r,float& d);
	dim3 getNormal(dim3 p);
	color getColor(dim3& pos);
};

#endif