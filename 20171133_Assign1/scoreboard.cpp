#include <cmath>
#include <GL/glut.h>
#include <glm/glm.hpp>
class Scoreboard
{
private:
	float border;
	float numberThickness=0.1f;
public:
	Scoreboard(){border=0.1f;}
	void drawboard()
	{
		glBegin(GL_QUADS);
			glColor3f(0.5f,0.5f,0.5f);
			glVertex3f(10.0f-border, 2.0f-border, -1.2f);
			glVertex3f(-10.0f+border, 2.0f-border, -1.2f);
			glVertex3f(-10.0f+border, -2.0f+border, -1.2f);
			glVertex3f(10.0f-border, -2.0f+border, -1.2f);		
		glEnd();
	}
	void drawcharge(float charge)
	{
		glBegin(GL_QUADS);
			glColor3f(0.3f,0.3f,0.3f);
			glVertex3f(9, -1, -1.3f);
			glVertex3f(9,  0, -1.3f);
			glVertex3f(2,  0, -1.3f);
			glVertex3f(2, -1, -1.3f);

			float pos=charge-20;
			pos*=(9.0f/160.0f);
			pos+=2;
			if(pos>9)
				pos=9;
			glColor3f(0.0f,0.5f,0.7f);
			glVertex3f(9, -1, -1.31f);
			glVertex3f(9,  0, -1.31f);
			glVertex3f(pos,  0, -1.31f);
			glVertex3f(pos, -1, -1.31f);

		glEnd();
	}

	void drawhealth(float health)
	{
		glBegin(GL_QUADS);
			glColor3f(0.3f,0.3f,0.3f);
			glVertex3f(9, 1.5f, -1.3f);
			glVertex3f(9,  0.5f, -1.3f);
			glVertex3f(2,  0.5f, -1.3f);
			glVertex3f(2, 1.5f, -1.3f);

			float pos=1-health;
			if(pos<0)pos=0;
			pos*=7;
			pos+=2;
			if(pos>9)
				pos=9;
			glColor3f(1.0f,0.5f,0.0f);
			glVertex3f(9, 1.5f, -1.31f);
			glVertex3f(9,  0.5f, -1.31f);
			glVertex3f(pos,  0.5f, -1.31f);
			glVertex3f(pos, 1.5f, -1.31f);

		glEnd();
	}
	void drawnumber(int n,float x,float y)
	{
		glColor3f(0.1f,0.1f,0.5f);
		//up
		if(n==0 or n==2 or n==3 or n==5 or n==6 or n==7 or n==8 or n==9)
		{
			glBegin(GL_QUADS);
			glVertex3f(0.5f, 1, -1.3f);
			glVertex3f(0, 1, -1.3f);
			glVertex3f(0, 1-numberThickness, -1.3f);
			glVertex3f(0.5, 1-numberThickness, -1.3f);
			glEnd();
		}
		//down
		if(n==0 or n==2 or n==3 or n==5 or n==6 or n==8 or n==9)
		{
			glBegin(GL_QUADS);
			glVertex3f(0.5f, 0, -1.3f);
			glVertex3f(0, 0, -1.3f);
			glVertex3f(0, numberThickness, -1.3f);
			glVertex3f(0.5, numberThickness, -1.3f);
			glEnd();
		}
		//leftup
		if(n==0 or n==4 or n==5 or n==6 or n==8 or n==9)
		{
			glBegin(GL_QUADS);
			glVertex3f(0.5f, 1, -1.3f);
			glVertex3f(0.5f-numberThickness, 1, -1.3f);
			glVertex3f(0.5f-numberThickness, 0.5+numberThickness/2.0f, -1.3f);
			glVertex3f(0.5f, 0.5+numberThickness/2.0f, -1.3f);
			glEnd();
		}
		//rightup
		if(n==0 or n==1 or n==2 or n==3 or n==4 or n==7 or n==8 or n==9)
		{
			glBegin(GL_QUADS);
			glVertex3f(0, 1, -1.3f);
			glVertex3f(numberThickness, 1, -1.3f);
			glVertex3f(numberThickness, 0.5+numberThickness/2.0f, -1.3f);
			glVertex3f(0, 0.5+numberThickness/2.0f, -1.3f);
			glEnd();
		}
		//leftdown
		if(n==0 or n==2 or n==6 or n==8)
		{
			glBegin(GL_QUADS);
			glVertex3f(0.5, 0.5-numberThickness/2.0f, -1.3f);
			glVertex3f(0.5-numberThickness, 0.5-numberThickness/2.0f, -1.3f);
			glVertex3f(0.5-numberThickness, 0, -1.3f);
			glVertex3f(0.5, 0, -1.3f);
			glEnd();
		}
		//rightdown
		if(n==0 or n==1 or n==3 or n==4 or n==5 or n==6 or n==7 or n==8 or n==9)
		{
			glBegin(GL_QUADS);
			glVertex3f(0, 0.5-numberThickness/2.0f, -1.3f);
			glVertex3f(numberThickness, 0.5-numberThickness/2.0f, -1.3f);
			glVertex3f(numberThickness, 0, -1.3f);
			glVertex3f(0, 0, -1.3f);
			glEnd();
		}
		//middle
		if(n==2 or n==3 or n==4 or n==5 or n==6 or n==8 or n==9)
		{
			glBegin(GL_QUADS);
			glVertex3f(0.5f, 0.5-numberThickness/2.0f, -1.3f);
			glVertex3f(0, 0.5-numberThickness/2.0f, -1.3f);
			glVertex3f(0, 0.5+numberThickness/2.0f, -1.3f);
			glVertex3f(0.5, 0.5+numberThickness/2.0f, -1.3f);
			glEnd();
		}
		glPopMatrix();
	}
	void drawscore(int n)
	{
		int i=-5;
		if(n==0)
			drawnumber(-5,i++,0);
		while(n>0)
		{
			glPushMatrix();
			glTranslatef(i++,-0.25,-1);
			drawnumber(n%10,0,0);
			glPopMatrix();
			n/=10;
		}
	}
	void drawgodeyetime(float x,float y,float fraction)
	{
		float radius=0.75;
		double twicePi = 2.0 * 3.142;
		glColor3f(0.8f,0.8f,1);
		glPushMatrix();
		glRotatef(90,0,0,1);
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(x, y, -1.3f);
		for (int i = 200*fraction; i <= 200; i++)
		    glVertex3f ((x + (radius * cos(i * twicePi / 200))), (y + (radius * sin(i * twicePi / 200))),-1.3f);
		glEnd();
		radius=0.8;
		glColor3f(0,0,0);
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(x, y, -1.3f);
		for (int i = 200*fraction; i <= 200; i++)
		    glVertex3f ((x + (radius * cos(i * twicePi / 200))), (y + (radius * sin(i * twicePi / 200))),-1.3f);
		glEnd();
		glPopMatrix();
	}
};