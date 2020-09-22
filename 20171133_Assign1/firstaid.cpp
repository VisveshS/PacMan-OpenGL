
#include <cmath>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <vector>
#include <ctime>
class firstaid
{
private:
	float x;
	float y;
	float radius;
public:
	firstaid(){};
	firstaid(float xpos,float ypos,float rad)
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
		float black[4] = {0.0f, 0.0f , 0.0f, 1.0f};
		float white[4] = {1.0f, 1.0f , 1.0f, 1.0f};
		float red[4] = {1.0f, 0.0f , 0.0f, 1.0f};
		glMaterialfv ( GL_FRONT, GL_AMBIENT, black );
		glPushMatrix();
		glTranslatef(x,y,-1.3);
		glScalef(2,2,1);
		glBegin(GL_QUADS);
			glMaterialfv ( GL_FRONT, GL_DIFFUSE, white );
			glVertex3f(1,1,0);
			glVertex3f(1,-1,0);
			glVertex3f(-1,-1,0);
			glVertex3f(-1,1,0);
			glMaterialfv ( GL_FRONT, GL_DIFFUSE, red );
			glVertex3f(0.6f,0.2f,-0.1f);
			glVertex3f(0.6f,-0.2f,-0.1f);
			glVertex3f(-0.6f,-0.2f,-0.1f);
			glVertex3f(-0.6f,0.2f,-0.1f);

			glVertex3f(0.2f,0.6f,-0.1f);
			glVertex3f(0.2f,-0.6f,-0.1f);
			glVertex3f(-0.2f,-0.6f,-0.1f);
			glVertex3f(-0.2f,0.6f,-0.1f);
		glEnd();
		glPopMatrix();
	}
};

class Firstaids
{
private:
	std::vector<firstaid> firstaids;
	int randomint(int mini,int maxi)
	{
		return rand()%(maxi-mini+1)+mini;
	}
public:
	Firstaids(){srand((unsigned) time(0));}
	void Firstaidsinit(int n)
	{
		for(int i=0;i<n;i++)
			firstaids.push_back(firstaid(randomint(-100,100),randomint(-100,100),4));
	}
	void draw()
	{
		for(firstaid c:firstaids)
			c.draw();
	}
	bool collision(float xpos, float ypos, float size)
	{
		for(int i=0;i<firstaids.size();i++)
			if(firstaids[i].collision(xpos,ypos,size))
			{
				firstaids.erase(firstaids.begin()+i);
				firstaids.push_back(firstaid(randomint(-100,100),randomint(-100,100),4));
				return true;
			}
		return false;
	}
};