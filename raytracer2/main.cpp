#include <iostream>
#include "raytracing.h"
using namespace std;

#define WIDTH	800
#define HEIGHT	600

int main(void)
{
	drawing* raytracer;
	raytracer = new drawing(WIDTH,HEIGHT);
	raytracer->init();
	raytracer->render();
    while(true)
	{
        int c=getchar();
        if (c=='\n')
			break;
    }
	return 0;
}