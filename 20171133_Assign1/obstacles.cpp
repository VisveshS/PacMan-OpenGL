#include <cmath>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <vector>
#include <ctime>
class obstacle
{
private:
	float x;
	float y;
	float radius;
public:
	obstacle(){};
	obstacle(float xpos,float ypos,float rad)
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
		float yellow[4] = {1.0f, 1.0f , 0.0f, 1.0f};
		glMaterialfv ( GL_FRONT, GL_AMBIENT, black );

		glPushMatrix();
		glTranslatef(x,y,-1.3);
		glScalef(4,4,1);

		glBegin(GL_TRIANGLES);
			glMaterialfv ( GL_FRONT, GL_DIFFUSE, yellow );
			glVertex3f(0,0.5f,0);
			glVertex3f(-0.5f,-0.5f,0);
			glVertex3f(+0.5f,-0.5f,0);
		glEnd();
		glMaterialfv ( GL_FRONT, GL_DIFFUSE, black );
		glBegin(GL_TRIANGLES);
			glVertex3f(0,0.55f,0);
			glVertex3f(-0.55f,-0.55f,0);
			glVertex3f(+0.55f,-0.55f,0);
		glEnd();		
		glBegin(GL_QUADS);
			glVertex3f(-0.1f,0.3f,-0.1f);
			glVertex3f(0.1f,0.3f,-0.1f);
			glVertex3f(0.07f,-0.2f,-0.1f);
			glVertex3f(-0.07f,-0.2f,-0.1f);

			glVertex3f(-0.07f,-0.3f,-0.1f);
			glVertex3f(-0.07f,-0.4f,-0.1f);
			glVertex3f(0.07f,-0.4f,-0.1f);
			glVertex3f(0.07f,-0.3f,-0.1f);
		glEnd();
		glPopMatrix();
	}
};

class Obstacles
{
private:
	std::vector<obstacle> obstacles;
	int randomint(int mini,int maxi)
	{
		return rand()%(maxi-mini+1)+mini;
	}
public:
	Obstacles(){srand((unsigned) time(0));}
	void Obstaclesinit(int n)
	{
		for(int i=0;i<n;i++)
			obstacles.push_back(obstacle(randomint(-100,100),randomint(-100,100),4));
	}
	void draw()
	{
		for(obstacle c:obstacles)
			c.draw();
		if(randomint(1,10)==1)
		{
			obstacles.erase(obstacles.begin()+randomint(0,obstacles.size()-1));
			obstacles.push_back(obstacle(randomint(-100,100),randomint(-100,100),4));
		}
	}
	bool collision(float xpos, float ypos, float size)
	{
		for(int i=0;i<obstacles.size();i++)
			if(obstacles[i].collision(xpos,ypos,size))
			{
				obstacles.erase(obstacles.begin()+i);
				obstacles.push_back(obstacle(randomint(-100,100),randomint(-100,100),4));
				return true;
			}
		return false;
	}
};