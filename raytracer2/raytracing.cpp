#include <iostream>
#include <fstream>
#include "raytracing.h"
using namespace std;
const float PI=3.141592653589793238462643383;

drawing::drawing(int w, int h) 
{
	width = w;
	height = h;
}

drawing::~drawing() {}

void drawing::init() 
{
	nPrim = 10;
	prim = new primitive* [nPrim];

	prim[0] = new plane(dim3(0,1.0f,0),5.0f);                    //下平面
	prim[0]->getMaterial()->setDiffuse(1.0f);
	prim[0]->getMaterial()->setReflection(0.6f);
	prim[0]->getMaterial()->setColor(color(0.2f,0.1f,0.1f));
	prim[0]->getMaterial()->setRefraction(0);
	prim[0]->setTex();

	prim[1] = new sphere( dim3( 3.0f, 4.0f, -3.0f ), 0.01f);      //白光源1
	prim[1]->getMaterial()->setColor(color(1.0f,1.0f,1.0f));
	((sphere*)prim[1])->setLight();
	prim[2] = new sphere( dim3(-3.0f,5.0f,-1.0f),0.01f);          //白光源2
	prim[2]->getMaterial()->setColor(color(1.0f,1.0f,1.0f));
	((sphere*)prim[2])->setLight();

	prim[3] = new sphere(dim3( 1.8f, -1.0f, 3.0f ), 2.5f);        //黑色球
	prim[3]->getMaterial()->setColor(color(0.7f,0.7f,0.7f));
	prim[3]->getMaterial()->setDiffuse(0);
	prim[3]->getMaterial()->setReflection(0.4f);
	prim[3]->getMaterial()->setRefraction(0);

	prim[4] = new sphere(dim3(-7.7f,-1.8f,9.0f),2);              //紫色球
	prim[4]->getMaterial()->setDiffuse(0.1f);
	prim[4]->getMaterial()->setReflection(1.0f);
	prim[4]->getMaterial()->setColor(color(0.7f,0.1f,1.0f));
	prim[4]->getMaterial()->setRefraction(0);

	prim[5] = new sphere(dim3(-3.0f,1.8f,3.0f),1.5f);            //青色球
	prim[5]->getMaterial()->setDiffuse(0.1f);
	prim[5]->getMaterial()->setReflection(0.9f);
	prim[5]->getMaterial()->setColor(color(0.3f,0.9f,1.0f));
	prim[5]->getMaterial()->setRefraction(0);

	dim3 d[6];
	d[0] = dim3(0,1,0).getNormal();    //上平面
	d[1] = dim3(0,-1,0).getNormal();   //下平面
	d[2] = dim3(1,0,0).getNormal();    //左平面
	d[3] = dim3(0,0,1).getNormal();    //后平面
	d[4] = dim3(-1,0,0).getNormal();   //右平面
	d[5] = dim3(0,0,-1).getNormal();   //前平面
	float s[6] = {-3.5f,5.0f,-2.7f,4.8f,4.7f,-4.0f};
	
	prim[6] = new cube(d,s);                                //立方体
	prim[6]->getMaterial()->setDiffuse(0.2f);
	prim[6]->getMaterial()->setReflection(0.8f);
	prim[6]->getMaterial()->setColor(color(0.8f,0.8f,0.8f));
	prim[6]->getMaterial()->setRefraction(0.3f);

	prim[7] = new plane(dim3(1.0f,0.0f,0),10.0f);            //右平面
	prim[7]->getMaterial()->setDiffuse(0.4f);
	prim[7]->getMaterial()->setReflection(0.8f);
	prim[7]->getMaterial()->setColor(color(0.5f,0.5f,0.5f));
	prim[7]->getMaterial()->setRefraction(0);

	prim[8] = new sphere(dim3(5.0f,2.0f,5.5f),1.5f);         //灰色球
	prim[8]->getMaterial()->setDiffuse(0.1f);
	prim[8]->getMaterial()->setReflection(1.0f);
	prim[8]->getMaterial()->setColor(color(0.8f,0.8f,0.8f));
	prim[8]->getMaterial()->setRefraction(0);

	prim[9] = new plane(dim3(0,0.0f,-1.0f),10.0f);          //后平面
	prim[9]->getMaterial()->setDiffuse(0.2f);
	prim[9]->getMaterial()->setReflection(0.8f);
	prim[9]->getMaterial()->setColor(color(0.5f,0.8f,0.3f));
	prim[9]->getMaterial()->setRefraction(0);

	sx = -4 ; ex = 4;
	sy = -3 ; ey = 3;
	dx = (float)(ex - sx) / (float)width;
	dy = (float)(sy - ey) / (float)height;
}

bool drawing::render()                            
{	
	ofstream ofs("e:\\raytracer.txt");//打开文件
	int x,y;
	vy = (float)ey;                            
	for(y = 0; y < height; y++) 
	{
		vx = (float)sx;
		for(x = 0; x < width; x++) 
		{
			float angle1,angle2;                             //angle1是光线方向与z轴正向的夹角；angle2是光线在xoy平面的投影与x轴正向的夹角
			for(int a=1;a<9;a++)                
			{
				angle1=10.0*a;
				float r=tan(angle1*PI/180.0);
				float z=1.0;
				for(int b=1;b<a*2;b++)
				{
					angle2=(90.0/(a*2.0))*b;
					float temp1=cos(angle2*PI/180.0),temp2=sin(angle2*PI/180.0);
					float x1=r*temp1, y1=r*temp2; dim3 dir1(x1,y1,z);
					float x2=r*temp1, y2=-r*temp2;dim3 dir2(x2,y2,z);
					float x3=-r*temp1,y3=r*temp2; dim3 dir3(x3,y3,z);
					float x4=-r*temp1,y4=-r*temp2;dim3 dir4(x4,y4,z);
					dim3 dir[4]={dir1.getNormal(),dir2.getNormal(),dir3.getNormal(),dir4.getNormal()};
					dim3 ori(vx,vy,0);
					for(int i=0;i<4;i++)
					{
						float dist;
						color test(0,0,0);
						ray r=ray(ori,dir[i]);
						primitive* prim = raytrace(r,test,1,dist,1.0f);
						int red = (int)(test.m_x * 256);
						int green = (int)(test.m_y * 256);
						int blue = (int)(test.m_z * 256);
						if(red > 255) red = 255;
						if(green > 255) green = 255;
						if(blue > 255) blue = 255;
						if(red==0&&green==0&&blue==0)
						{
							cout<<"方向("<<dir[i].m_x<<","<<dir[i].m_y<<","<<dir[i].m_z<<"),像素坐标("<<vx<<","<<vy<<","<<"0)的光线无效"<<endl;
							ofs<<"方向("<<dir[i].m_x<<","<<dir[i].m_y<<","<<dir[i].m_z<<"),像素坐标("<<vx<<","<<vy<<","<<"0)的光线无效"<<endl;//数据写入文件
						}
						else
						{
							cout<<"方向("<<dir[i].m_x<<","<<dir[i].m_y<<","<<dir[i].m_z<<"),像素坐标("<<vx<<","<<vy<<","<<"0)的光线RGB三通道值分别为:"<<red<<" "<<green<<" "<<blue<<endl;
							ofs<<"方向("<<dir[i].m_x<<","<<dir[i].m_y<<","<<dir[i].m_z<<"),像素坐标("<<vx<<","<<vy<<","<<"0)的光线RGB三通道值分别为:"<<red<<" "<<green<<" "<<blue<<endl;//数据写入文件
						}
						/*while(true)
						{
							int c=getchar();
							if (c=='\n')
								break;
						}*/
					}
				}
			}
			vx += dx;
		}
		vy += dy;
	}
	ofs.close();//关闭文件
	return true;
}

primitive* drawing::raytrace(ray& _ray, color& test, int depth, float& dist,float rindex)   //光线跟踪
{
	if(depth > 6)                                              //跟踪深度为6
		return 0;
	dist = 100000.0f;
	dim3 v;
	primitive* p = 0;
	int result;
	int position;
	for(int i =0 ;i < nPrim; i++)                              //寻找最近的交点
	{
		result = prim[i]->intersect(_ray, dist);               //返回0则无交点，返回1则有交点
		if( result != 0) 
		{
			p = prim[i];
			position = result;
		}
	}
	if(!p)                              //若无交点
	{
		return 0;
	}
	if(p->isLight())                    //是否为光源
	{
		test = color(1,1,1);            //是光源则为白色
	}
	else                                //若有交点且非光源
	{
		v = _ray.getOrigin() + dist * _ray.getDirection();       //判断是否为阴影
		for(int i =0 ; i< nPrim; i++) 
		{
			if(prim[i]->isLight()) 
			{
				dim3 l = ((sphere*)prim[i])->getCenter() - v;
				dim3 n = p->getNormal(v);
				float shadow = 1.0;                             //无阴影
				float ldist = l.getLength();
				l = l.getNormal();
				ray peeler = ray(v + 0.001f * l,l);
				for(int j = 0;j < nPrim; j++) 
				{
					if(prim[j]->isLight() == false && prim[j]->intersect(peeler,ldist)== 1) 
					{
						if(prim[j]->getMaterial()->getRefraction()>0)
						{
							shadow = (float)0.8;                //部分阴影
						}
						else
						{
							shadow = 0;                         //有阴影
							break;
						}
					}
				}
				if(shadow > 0)                                     //无遮挡，无阴影
				{
					if(p->getMaterial()->getDiffuse() >0)          //计算漫发射
					{
						float dot = n.dot(l);
						if(dot >0) 
						{
							float diff = dot * p->getMaterial()->getDiffuse()* shadow;
							test = test + diff * p->getColor(v) * prim[i]->getMaterial()->getColor();
						}
					}
					if(p->getMaterial()->getSpecular() > 0)         //计算镜面反射
					{
						dim3 r = 2.0f * l.dot(n) * n - l;
						float dot = r.dot((-1) * _ray.getDirection());
						if(dot > 0) 
						{
							float spec = powf(dot,20) * p->getMaterial()->getSpecular() * shadow;
							test = test + spec * p->getColor(v) * prim[i]->getMaterial()->getColor();
						}
					}
				}
			}
		}
		if(p->getMaterial()->getReflection() > 0)                              //计算反射光线并递归跟踪
		{
			dim3 n = p->getNormal(v);
			dim3 r = _ray.getDirection() - 2.0f *  n.dot(_ray.getDirection()) * n;
			if(depth < 6) 
			{
				color ref(0,0,0);
				float dist1;
				raytrace(ray(v + 0.001f * r, r.getNormal()),ref,depth + 1,dist1,rindex);
				float refl = p->getMaterial()->getReflection();
				test = test + refl * p->getColor(v) * ref;
			}
		}
		if(p->getMaterial()->getRefraction() >0 && depth < 6)                  //计算折射光线并递归跟踪
		{
			float trans = p->getMaterial()->getRefraction();
			dim3 n =  (float)position * p->getNormal(v);
			dim3 d = (-1) * _ray.getDirection();
			if(position == -1) trans = 1 /trans;
			dim3 t_lat = 1 / trans * (d.dot(n) *n - d);
			float sinsq = t_lat.dot(t_lat);
			if(sinsq <= 1) 
			{
				dim3 t = t_lat - sqrtf(1- sinsq) * n;
				color refr(0,0,0);
				float dist1;
				raytrace(ray(v + 0.001f * t,t),refr,depth+1,dist1,trans);
				test = test + (float)0.9 * refr;
			}
		}	
	}
	return p;
}