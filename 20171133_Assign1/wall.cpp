#include <cmath>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <stdio.h>
class Wall
{
private:
	float x;
	float y;
	float sx;
	float sy;
public:
	Wall(){};
	Wall(float xpos,float ypos,float len,float bre)
	{
		x=xpos;
		y=ypos;
		sx=len;
		sy=bre;
	}
	bool collision(float xpos, float ypos, float size)
	{
		if(2*abs(x-xpos)>(size+sx))
			return false;
		if(2*abs(y-ypos)>(size+sy))
			return false;
		return true;
	}
	void draw()
	{
		glBegin(GL_QUADS);

		float brown[4] = {0.6f, 0.6f , 0.3f, 1.0f};
		float black[4] = {0.0f, 0.0f , 0.0f, 1.0f};
		glMaterialfv ( GL_FRONT, GL_AMBIENT, black );
		glMaterialfv ( GL_FRONT, GL_DIFFUSE, black );

		glVertex3f(x+sx/2.0f, y+sy/2.0f, -1.0f);
		glVertex3f(x-sx/2.0f, y+sy/2.0f, -1.0f);
		glVertex3f(x-sx/2.0f, y-sy/2.0f, -1.0f);
		glVertex3f(x+sx/2.0f, y-sy/2.0f, -1.0f);

		glEnd();		
	}
};