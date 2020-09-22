#include <cmath>
#include <cstdlib>
#include <GL/glut.h>
#include <glm/glm.hpp>
class Ground
{
private:
public:
	int size;
	int numWall=1;
	glm::vec3 position;
	float angle=0.0;
	float bounds[4];
	Ground()
	{
		position = glm::vec3(0.0f, -1.0f, 0.0f);
		float x=101.0f-14/4.0f;
		bounds[0]=-x;//left
		bounds[1]=+x;//right
		bounds[2]=+x;//front
		bounds[3]=-x;//back
	}
	bool finish(float i,float j)
	{
		return (i>=2*(-50+200/size) and i<=2*(-50+300/size) and j>=2*(50-100/size));
	}
	void draw()
	{
		float tile=2.0f;
		glBegin(GL_QUADS);
		glNormal3d(0, 0, -1);
		for(int i=-50;i<=50;i++)
			for(int j=-50;j<=50;j++)
			{
				float green[4] = {0.5f, 1.0f , 0.5f, 1.0f};
				float darkgreen[4] = {0.4f, 0.9f , 0.4f, 1.0f};
				float black[4] = {0.0f, 0.0f , 0.0f, 1.0f};
				float grey[4] = {0.3f, 0.3f , 0.3f, 1.0f};
				float white[4] = {1.0f, 1.0f , 1.0f, 1.0f};
				glMaterialfv ( GL_FRONT, GL_AMBIENT, black);
				if((i+j+1000)%2==0)
				{
					if((i>=-50+200/size and i<=-50+300/size and j>=50-100/size) or (i>=50-300/size and i<=50-200/size and j<=-50+100/size))
						glMaterialfv ( GL_FRONT, GL_DIFFUSE, white );
					else
						glMaterialfv ( GL_FRONT, GL_DIFFUSE, green );
				}
				else
				{
					if((i>=-50+200/size and i<=-50+300/size and j>=50-100/size) or (i>=50-300/size and i<=50-200/size and j<=-50+100/size))
						glMaterialfv ( GL_FRONT, GL_DIFFUSE, grey );						
					else
						glMaterialfv ( GL_FRONT, GL_DIFFUSE, darkgreen );
				}
				glVertex3f(i*tile+tile/2.0f, j*tile-tile/2.0f, 0.0f);
				glVertex3f(i*tile+tile/2.0f, j*tile+tile/2.0f, 0.0f);
				glVertex3f(i*tile-tile/2.0f, j*tile+tile/2.0f, 0.0f);
				glVertex3f(i*tile-tile/2.0f, j*tile-tile/2.0f, 0.0f);
			}
		glEnd();
	}
};