#ifndef RAY_H_
#define RAY_H_

#include "dim3.h"

class ray 
{
private:
	dim3  m_origin;
	dim3  m_direction;
public:
	ray(): m_origin(dim3(0,0,0)), m_direction(dim3(0,0,0)) {}
	ray(dim3& origin, dim3& direction ): m_origin(origin), m_direction(direction) {}
	void setOrigin(dim3& origin) 
	{
		m_origin = origin ; 
	}
	void setDirection(dim3& direction) 
	{ 
		m_direction = direction;
	}
	dim3& getOrigin() 
	{
		return m_origin; 
	}
	dim3& getDirection() 
	{
		return m_direction; 
	}
};

#endif