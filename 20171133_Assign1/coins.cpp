#include <cmath>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <vector>
#include <ctime>
class coin
{
private:
	float x;
	float y;
	float radius;
public:
	coin(){};
	coin(float xpos,float ypos,float rad)
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
		// x = 0, y = 0;
		glBegin(GL_TRIANGLE_FAN);

		float yellow[4] = {1.0f, 1.0f , 0.0f, 1.0f};
		float orange[4] = {1.0f, 0.5f , 0.0f, 1.0f};
		float black[4] = {0.0f, 0.0f , 0.0f, 1.0f};
		glMaterialfv ( GL_FRONT, GL_AMBIENT, black );
		glMaterialfv ( GL_FRONT, GL_DIFFUSE, yellow );

		glVertex3f(x, y, -0.1f);
		for (int i = 0; i <= 20; i++)
		    glVertex3f ((x + (radius * cos(i * twicePi / 20))), (y + (radius * sin(i * twicePi / 20))),-0.1f);
		for (int i = 0; i <= 20; i++)
		{
			if(i%2==0)
				glMaterialfv ( GL_FRONT, GL_DIFFUSE, orange );
			else
				glMaterialfv ( GL_FRONT, GL_DIFFUSE, black );
		    glVertex3f ((x + (radius*1.5f * cos(i * twicePi / 20))), (y + (radius*1.5f * sin(i * twicePi / 20))),-0.09f);
		}
		glEnd();
	}
};

class Coins
{
private:
	std::vector<coin> coins;
	int randomint(int mini,int maxi)
	{
		return rand()%(maxi-mini+1)+mini;
	}
public:
	Coins(){srand((unsigned) time(0));}
	void Coinsinit(int n)
	{
		for(int i=0;i<n;i++)
			coins.push_back(coin(randomint(-100,100),randomint(-100,100),1));
	}
	void draw()
	{
		for(coin c:coins)
			c.draw();
	}
	bool collision(float xpos, float ypos, float size)
	{
		for(int i=0;i<coins.size();i++)
			if(coins[i].collision(xpos,ypos,size))
			{
				coins.erase(coins.begin()+i);
				coins.push_back(coin(randomint(-100,100),randomint(-100,100),1));
				return true;
			}
		return false;
	}
};