#ifndef PAINT_H_
#define PAINT_H_

#include "object.h"

class drawing 
{
public:
	drawing(int w,int h);
	~drawing();
	void init();
	bool render();
	primitive* raytrace(ray& r, color& c, int depth,float& dist,float rindex);
private:
	int width,height;
	primitive** prim;
	int sx, sy , ex, ey;
	float dx, dy;
	float vx,vy;
	int nPrim;
};

#endif