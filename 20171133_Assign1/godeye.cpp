#include <cmath>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <vector>
#include <ctime>
class godeye
{
private:
	float x;
	float y;
	float radius;
public:
	godeye(){};
	godeye(float xpos,float ypos,float rad)
	{
		x=xpos;
		y=ypos;
		radius=rad;
	}
	bool collision(float xpos, float ypos, float size)
	{
		if(2*abs(x-xpos)>(size+2*radius))
			return false;
		if(2*abs(y-ypos)>(size+2*radius))
			return false;
		return true;
	}
	void draw()
	{
		double twicePi = 2.0 * 3.142;
		float radius=0.17f;
		float black[4] = {0.0f, 0.0f , 0.0f, 1.0f};
		float white[4] = {1.0f, 1.0f , 1.0f, 1.0f};
		float brown[4] = {0.6f, 0.6f , 0.3f, 1.0f};
		glMaterialfv ( GL_FRONT, GL_AMBIENT, black );

		glPushMatrix();
		glTranslatef(x,y,-1.3);
		glScalef(2,3,1);
		glMaterialfv ( GL_FRONT, GL_DIFFUSE, black );
		glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0, 0, 0);
			for (int i = 0; i <= 200; i++)
			    glVertex3f (((radius * cos(i * twicePi / 200))), ((radius * sin(i * twicePi / 200))),0);
		glEnd();

		glBegin(GL_QUADS);
			glMaterialfv ( GL_FRONT, GL_DIFFUSE, black );
			glVertex3f(0.5,0,0.1);
			glVertex3f(0,0.3,0.1);
			glVertex3f(-0.5,0,0.1);
			glVertex3f(0,-0.3,0.1);
			glMaterialfv ( GL_FRONT, GL_DIFFUSE, white );
			glVertex3f(0.4,0,0);
			glVertex3f(0,0.2,0);
			glVertex3f(-0.4,0,0);
			glVertex3f(0,-0.2,0);
		glEnd();

		glBegin(GL_TRIANGLES);
			glMaterialfv ( GL_FRONT, GL_DIFFUSE, brown );
			glVertex3f(1,-0.7f,0.2);		
			glVertex3f(-1,-0.7f,0.2);		
			glVertex3f(0,0.7f,0.2);		
		glEnd();
		glPopMatrix();
	}
};

class Godeyes
{
private:
	std::vector<godeye> godeyes;
	int randomint(int mini,int maxi)
	{
		return rand()%(maxi-mini+1)+mini;
	}
public:
	Godeyes(){srand((unsigned) time(0));}
	void Godeyesinit(int n)
	{
		for(int i=0;i<n;i++)
			godeyes.push_back(godeye(randomint(-100,100),randomint(-100,100),2));
	}
	void draw()
	{
		for(godeye c:godeyes)
			c.draw();
		if(randomint(1,40)==1)
		{
			godeyes.erase(godeyes.begin()+randomint(0,godeyes.size()-1));
			godeyes.push_back(godeye(randomint(-100,100),randomint(-100,100),2));
		}
	}
	bool collision(float xpos, float ypos, float size)
	{
		for(int i=0;i<godeyes.size();i++)
			if(godeyes[i].collision(xpos,ypos,size))
			{
				godeyes.erase(godeyes.begin()+i);
				godeyes.push_back(godeye(randomint(-100,100),randomint(-100,100),2));
				return true;
			}
		return false;
	}
};