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

	prim[0] = new plane(dim3(0,1.0f,0),5.0f);                    //��ƽ��
	prim[0]->getMaterial()->setDiffuse(1.0f);
	prim[0]->getMaterial()->setReflection(0.6f);
	prim[0]->getMaterial()->setColor(color(0.2f,0.1f,0.1f));
	prim[0]->getMaterial()->setRefraction(0);
	prim[0]->setTex();

	prim[1] = new sphere( dim3( 3.0f, 4.0f, -3.0f ), 0.01f);      //�׹�Դ1
	prim[1]->getMaterial()->setColor(color(1.0f,1.0f,1.0f));
	((sphere*)prim[1])->setLight();
	prim[2] = new sphere( dim3(-3.0f,5.0f,-1.0f),0.01f);          //�׹�Դ2
	prim[2]->getMaterial()->setColor(color(1.0f,1.0f,1.0f));
	((sphere*)prim[2])->setLight();

	prim[3] = new sphere(dim3( 1.8f, -1.0f, 3.0f ), 2.5f);        //��ɫ��
	prim[3]->getMaterial()->setColor(color(0.7f,0.7f,0.7f));
	prim[3]->getMaterial()->setDiffuse(0);
	prim[3]->getMaterial()->setReflection(0.4f);
	prim[3]->getMaterial()->setRefraction(0);

	prim[4] = new sphere(dim3(-7.7f,-1.8f,9.0f),2);              //��ɫ��
	prim[4]->getMaterial()->setDiffuse(0.1f);
	prim[4]->getMaterial()->setReflection(1.0f);
	prim[4]->getMaterial()->setColor(color(0.7f,0.1f,1.0f));
	prim[4]->getMaterial()->setRefraction(0);

	prim[5] = new sphere(dim3(-3.0f,1.8f,3.0f),1.5f);            //��ɫ��
	prim[5]->getMaterial()->setDiffuse(0.1f);
	prim[5]->getMaterial()->setReflection(0.9f);
	prim[5]->getMaterial()->setColor(color(0.3f,0.9f,1.0f));
	prim[5]->getMaterial()->setRefraction(0);

	dim3 d[6];
	d[0] = dim3(0,1,0).getNormal();    //��ƽ��
	d[1] = dim3(0,-1,0).getNormal();   //��ƽ��
	d[2] = dim3(1,0,0).getNormal();    //��ƽ��
	d[3] = dim3(0,0,1).getNormal();    //��ƽ��
	d[4] = dim3(-1,0,0).getNormal();   //��ƽ��
	d[5] = dim3(0,0,-1).getNormal();   //ǰƽ��
	float s[6] = {-3.5f,5.0f,-2.7f,4.8f,4.7f,-4.0f};
	
	prim[6] = new cube(d,s);                                //������
	prim[6]->getMaterial()->setDiffuse(0.2f);
	prim[6]->getMaterial()->setReflection(0.8f);
	prim[6]->getMaterial()->setColor(color(0.8f,0.8f,0.8f));
	prim[6]->getMaterial()->setRefraction(0.3f);

	prim[7] = new plane(dim3(1.0f,0.0f,0),10.0f);            //��ƽ��
	prim[7]->getMaterial()->setDiffuse(0.4f);
	prim[7]->getMaterial()->setReflection(0.8f);
	prim[7]->getMaterial()->setColor(color(0.5f,0.5f,0.5f));
	prim[7]->getMaterial()->setRefraction(0);

	prim[8] = new sphere(dim3(5.0f,2.0f,5.5f),1.5f);         //��ɫ��
	prim[8]->getMaterial()->setDiffuse(0.1f);
	prim[8]->getMaterial()->setReflection(1.0f);
	prim[8]->getMaterial()->setColor(color(0.8f,0.8f,0.8f));
	prim[8]->getMaterial()->setRefraction(0);

	prim[9] = new plane(dim3(0,0.0f,-1.0f),10.0f);          //��ƽ��
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
	ofstream ofs("e:\\raytracer.txt");//���ļ�
	int x,y;
	vy = (float)ey;                            
	for(y = 0; y < height; y++) 
	{
		vx = (float)sx;
		for(x = 0; x < width; x++) 
		{
			float angle1,angle2;                             //angle1�ǹ��߷�����z������ļнǣ�angle2�ǹ�����xoyƽ���ͶӰ��x������ļн�
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
							cout<<"����("<<dir[i].m_x<<","<<dir[i].m_y<<","<<dir[i].m_z<<"),��������("<<vx<<","<<vy<<","<<"0)�Ĺ�����Ч"<<endl;
							ofs<<"����("<<dir[i].m_x<<","<<dir[i].m_y<<","<<dir[i].m_z<<"),��������("<<vx<<","<<vy<<","<<"0)�Ĺ�����Ч"<<endl;//����д���ļ�
						}
						else
						{
							cout<<"����("<<dir[i].m_x<<","<<dir[i].m_y<<","<<dir[i].m_z<<"),��������("<<vx<<","<<vy<<","<<"0)�Ĺ���RGB��ͨ��ֵ�ֱ�Ϊ:"<<red<<" "<<green<<" "<<blue<<endl;
							ofs<<"����("<<dir[i].m_x<<","<<dir[i].m_y<<","<<dir[i].m_z<<"),��������("<<vx<<","<<vy<<","<<"0)�Ĺ���RGB��ͨ��ֵ�ֱ�Ϊ:"<<red<<" "<<green<<" "<<blue<<endl;//����д���ļ�
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
	ofs.close();//�ر��ļ�
	return true;
}

primitive* drawing::raytrace(ray& _ray, color& test, int depth, float& dist,float rindex)   //���߸���
{
	if(depth > 6)                                              //�������Ϊ6
		return 0;
	dist = 100000.0f;
	dim3 v;
	primitive* p = 0;
	int result;
	int position;
	for(int i =0 ;i < nPrim; i++)                              //Ѱ������Ľ���
	{
		result = prim[i]->intersect(_ray, dist);               //����0���޽��㣬����1���н���
		if( result != 0) 
		{
			p = prim[i];
			position = result;
		}
	}
	if(!p)                              //���޽���
	{
		return 0;
	}
	if(p->isLight())                    //�Ƿ�Ϊ��Դ
	{
		test = color(1,1,1);            //�ǹ�Դ��Ϊ��ɫ
	}
	else                                //���н����ҷǹ�Դ
	{
		v = _ray.getOrigin() + dist * _ray.getDirection();       //�ж��Ƿ�Ϊ��Ӱ
		for(int i =0 ; i< nPrim; i++) 
		{
			if(prim[i]->isLight()) 
			{
				dim3 l = ((sphere*)prim[i])->getCenter() - v;
				dim3 n = p->getNormal(v);
				float shadow = 1.0;                             //����Ӱ
				float ldist = l.getLength();
				l = l.getNormal();
				ray peeler = ray(v + 0.001f * l,l);
				for(int j = 0;j < nPrim; j++) 
				{
					if(prim[j]->isLight() == false && prim[j]->intersect(peeler,ldist)== 1) 
					{
						if(prim[j]->getMaterial()->getRefraction()>0)
						{
							shadow = (float)0.8;                //������Ӱ
						}
						else
						{
							shadow = 0;                         //����Ӱ
							break;
						}
					}
				}
				if(shadow > 0)                                     //���ڵ�������Ӱ
				{
					if(p->getMaterial()->getDiffuse() >0)          //����������
					{
						float dot = n.dot(l);
						if(dot >0) 
						{
							float diff = dot * p->getMaterial()->getDiffuse()* shadow;
							test = test + diff * p->getColor(v) * prim[i]->getMaterial()->getColor();
						}
					}
					if(p->getMaterial()->getSpecular() > 0)         //���㾵�淴��
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
		if(p->getMaterial()->getReflection() > 0)                              //���㷴����߲��ݹ����
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
		if(p->getMaterial()->getRefraction() >0 && depth < 6)                  //����������߲��ݹ����
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