#include "object.h"
#include <iostream>
using namespace std;

int sphere::intersect(ray& r, float& d)            //光线与球体相交测试
{
	dim3 v = r.getOrigin() - m_center;
	float b = -1 * v.dot(r.getDirection());
	float det = (b * b) - v.dot(v) + m_radius * m_radius;
	int	inter = 0;
	if( det > 0) 
	{
		det = sqrt(det);
		float root1 = b + det;
		float root2 = b - det;
		if( root1 > 0) 
		{
			if(root2 < 0) 
			{
				if(root1 < d) 
				{
					d = root1;
					inter = -1;
				}
			}
			else 
			{
				if(root2 < d) 
				{
					d = root2;
					inter = 1;
				}
			}
		}
	}
	return inter;
}

color sphere::getColor(dim3 &pos)                     //球体相交后的返回值颜色
{
	return this->getMaterial()->getColor();
}

int plane::intersect(ray &r, float &di)               //光线与平面相交测试
{
	float temp1 = normal.dot( r.getOrigin());
	float temp2 = normal.dot( r.getDirection());
	float temp = -1 * (temp1 + d) / temp2 ;
	if(temp > 0) 
	{
		if(temp < di) 
		{
			di = temp;
			return 1;
		}	
	}
	return 0;
}

color plane::getColor(dim3& pos)                     //平面相交后的返回值颜色
{
	if(this->getTex() == 1)
	{
		int x = (int)(pos.m_x/2);
		int z = (int)pos.m_z;
		if((x+z)%2 == 0)
		{
			return this->getMaterial()->getColor();
		}
		else
		{
			return (float)0.9*(this->getMaterial()->getColor());
		}
	}
	else
	{
		return this->getMaterial()->getColor();
	}
}

int cube::intersect(ray &ray, float &dist)             //光线与立方体相交测试
{
	float fmax = -10000.0f;
	float fmin = 10000.0f;
	float s;
	float alpha;
	for(int i =0 ;i < 6;i ++) 
	{
		s = ray.getDirection().dot(n[i]);
		if(s==0) 
		{
			if(ray.getOrigin().dot(n[i]) > d[i]) 
				return 0;
			continue;
		}
		alpha = (d[i] - ray.getOrigin().dot(n[i])) / s;
		if(ray.getDirection().dot(n[i]) < 0)
		{
			if(alpha > fmax) 
			{
				if(alpha > fmin) 
				{
					return 0;
				}
				fmax = alpha;
			}
		}
		else 
		{
			if(alpha < fmin) 
			{
				if(alpha < 0 || alpha < fmax) 
				{
					return 0;
				}
				fmin = alpha;
			}
		}
	}
	if(fmax > 0) alpha = fmax;
	else alpha = fmin;
	dist = alpha;
	return 1;
}

color cube::getColor(dim3 &pos)                       //立方体相交后的返回值颜色
{
	return this->getMaterial()->getColor();
}

dim3 cube::getNormal(dim3 pos) 
{
	int k = 0;
	float min = 10000.0f;
	for(int i = 0;i < 6; i++) 
	{
		float temp = abs(n[i].dot(pos) - d[i]);
		if(min > temp) 
		{
			min = temp;
			k = i;
		}
	}
	return n[k];
}
