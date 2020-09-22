#include <cmath>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <vector>
#include <ctime>
class battery
{
private:
	float x;
	float y;
	float radius;
public:
	battery(){};
	battery(float xpos,float ypos,float rad)
	{
		x=xpos;
		y=ypos;
		radius=rad;
	}
	bool collision(float xpos, float ypos, float size)
	{
		if(2*abs(x-xpos)>(size+radius))
			return false;
		if(2*abs(y-ypos)>(size+radius))
			return false;
		return true;
	}
	void draw()
	{
		float black[4] = {0.0f, 0.0f , 0.0f, 1.0f};
		float grey[4] = {0.4f, 0.4f , 0.4f, 1.0f};
		float yellow[4] = {1.0f, 1.0f , 0.0f, 1.0f};
		glMaterialfv ( GL_FRONT, GL_AMBIENT, black );

		glPushMatrix();
		glTranslatef(x,y,-1.3);
		glScalef(1,2,1);
		glMaterialfv ( GL_FRONT, GL_DIFFUSE, grey );
		glBegin(GL_QUADS);
			glVertex3f(-1,-1,0);
			glVertex3f(-1,+1,0);
			glVertex3f(+1,+1,0);
			glVertex3f(+1,-1,0);

			glVertex3f(-0.5f,+1,0);
			glVertex3f(+0.5f,+1,0);
			glVertex3f(+0.5f,+1.2f,0);
			glVertex3f(-0.5f,+1.2f,0);
		glEnd();
		glMaterialfv ( GL_FRONT, GL_DIFFUSE, yellow );
		glPushMatrix();
		glTranslatef(0,0,-0.1);
			glBegin(GL_TRIANGLES);
				glVertex3f(0,0.8f,0);
				glVertex3f(0.5f,-0.2,0);
				glVertex3f(-0.1f,-0.2,0);

				glVertex3f(0,-0.8f,0);
				glVertex3f(-0.5f,0.2,0);
				glVertex3f(0.1f,0.2,0);
			glEnd();
		glPopMatrix();
		glPopMatrix();
	}
};

class Batterys
{
private:
	std::vector<battery> batterys;
	int randomint(int mini,int maxi)
	{
		return rand()%(maxi-mini+1)+mini;
	}
public:
	Batterys(){srand((unsigned) time(0));};
	void Batterysinit(int n)
	{
		for(int i=0;i<n;i++)
			batterys.push_back(battery(randomint(-100,100),randomint(-100,100),4));
	}
	void draw()
	{
		for(battery c:batterys)
			c.draw();
	}
	bool collision(float xpos, float ypos, float size)
	{
		for(int i=0;i<batterys.size();i++)
			if(batterys[i].collision(xpos,ypos,size))
			{
				batterys.erase(batterys.begin()+i);
				batterys.push_back(battery(randomint(-100,100),randomint(-100,100),4));
				return true;
			}
		return false;
	}
};