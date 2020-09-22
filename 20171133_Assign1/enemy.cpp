#include <cmath>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <stdio.h>
#include <ctime>
#include <iostream>
class Enemy
{
private:
	float black[4] = {0.0f, 0.0f , 0.0f, 1.0f};
	float white[4] = {1.0f, 1.0f , 1.0f, 1.0f};
	float red[4] = {1.0f, 0.1f , 0.1f, 1.0f};
	float brown[4] = {0.3f, 0.3f , 0.1f, 1.0f};
	float blue[4] = {0.3f, 0.3f , 1.0f, 1.0f};
	float lightYellow[4] = {1.0f, 1.0f , 0.4f, 1.0f};
	bool vertical[20][20],horizontal[20][20];
	int n;
	float distance;
	float travelled;
	glm::vec3 *playerPos;
	int randomint(int mini,int maxi)
	{
		return rand()%(maxi-mini+1)+mini;
	}
	int decide()
	{
		int possible[4],n=0;
		if(not vertical[prev[0]][prev[1]-1])possible[n++]=3;
		if(not vertical[prev[0]][prev[1]])possible[n++]=4;
		if(not horizontal[prev[0]-1][prev[1]])possible[n++]=1;
		if(not horizontal[prev[0]][prev[1]])possible[n++]=2;
		if(abs(position.x-playerPos->x)<3*distance and abs(position.y-playerPos->y)<3*distance)
		{
			speed=0.35f;
			if(abs(position.y-playerPos->y)<2*distance and abs(position.x-playerPos->x)<distance/2.0f)
			{
				if(position.y>playerPos->y)
					for(int i=0;i<n;i++)if(possible[i]==2)return 2;
				if(position.y<playerPos->y)
					for(int i=0;i<n;i++)if(possible[i]==1)return 1;
			}
			if(abs(position.x-playerPos->x)<2*distance and abs(position.y-playerPos->y)<distance/2.0f)
			{
				if(position.x>playerPos->x)
					for(int i=0;i<n;i++)if(possible[i]==4)return 4;
				if(position.x<playerPos->x)
					for(int i=0;i<n;i++)if(possible[i]==3)return 3;
			}
		}
		else
			speed=distance/2.0f;
		if(seen)
			speed=0.35f;
		return possible[randomint(0,n-1)];
	}
public:
	glm::vec3 position;
	glm::vec3 velocity;
	int prev[2];
	int direction;
	float size;
	float speed;
	bool seen;
	Enemy(){}
	void EnemyInit(bool v[20][20],bool h[20][20],int n, glm::vec3 *playerposition)
	{
		seen=false;
		distance=200.0f/n;
		size=distance/2.0f;
		travelled=0.0f;
		playerPos=playerposition;
		speed=distance;
		for(int i=0;i<=n+1;i++)
			for(int j=0;j<=n+1;j++)
			{
				vertical[i][j]=true;
				horizontal[i][j]=true;
			}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				vertical[i][j]=v[i][j];
				horizontal[i][j]=h[i][j];
			}
		position.x=0.0f;
		position.y=0.0f;
		prev[0]=n/2+1;prev[1]=n/2+1;
		srand((unsigned) time(0));
		direction=decide();
	}
	void tick()
	{
		if(direction==1)
			position.y+=speed;
		else if(direction==2)
			position.y-=speed;
		else if(direction==3)
			position.x+=speed;
		else if(direction==4)
			position.x-=speed;
		travelled+=speed;
		if(travelled>=distance)
		{
			if(direction==1)
				prev[0]-=1;
			else if(direction==2)
				prev[0]+=1;
			else if(direction==3)
				prev[1]-=1;
			else if(direction==4)
				prev[1]+=1;
			position.x=-(distance*prev[1]-100.0f)+distance/2.0f;
			position.y=-(distance*prev[0]-100.0f)+distance/2.0f;
			direction=decide();
			travelled=0;
		}
	}
	bool kill(float x,float y)
	{
		if(abs(position.x-x)>=size)
			return false;
		if(abs(position.y-y)>=size)
			return false;
		return true;
	}
	void draw()
	{
		glBegin(GL_QUADS);

		glMaterialfv ( GL_FRONT, GL_AMBIENT, black);
		glMaterialfv ( GL_FRONT, GL_DIFFUSE, red);

		//face
		glVertex3f(position.x+size/2.0f, position.y+size/2.0f, -1.0f);
		glVertex3f(position.x-size/2.0f, position.y+size/2.0f, -1.0f);
		glVertex3f(position.x-size/2.0f, position.y-size/2.0f, -1.0f);
		glVertex3f(position.x+size/2.0f, position.y-size/2.0f, -1.0f);		

		//eyes
		glMaterialfv ( GL_FRONT, GL_DIFFUSE, lightYellow);
		glVertex3f(position.x-size*0.25+size*0.1f, position.y+size*0.25f+size*0.0f, -1.01f);
		glVertex3f(position.x-size*0.25-size*0.1f, position.y+size*0.25f+size*0.1f, -1.01f);
		glVertex3f(position.x-size*0.25-size*0.1f, position.y+size*0.25f-size*0.1f, -1.01f);
		glVertex3f(position.x-size*0.25+size*0.1f, position.y+size*0.25f-size*0.1f, -1.01f);

		glVertex3f(position.x+size*0.25+size*0.1f, position.y+size*0.25f+size*0.1f, -1.01f);
		glVertex3f(position.x+size*0.25-size*0.1f, position.y+size*0.25f+size*0.0f, -1.01f);
		glVertex3f(position.x+size*0.25-size*0.1f, position.y+size*0.25f-size*0.1f, -1.01f);
		glVertex3f(position.x+size*0.25+size*0.1f, position.y+size*0.25f-size*0.1f, -1.01f);

		glEnd();

 		glBegin(GL_TRIANGLES);
		//teeth
			glMaterialfv ( GL_FRONT, GL_DIFFUSE, white);
			for(int i=-3;i<=3;i++)
			{
				glVertex3f(i*size*0.1f+position.x+size*0.05, position.y-size*0.25f+size*0.1f, -1.01f);
				glVertex3f(i*size*0.1f+position.x-size*0.05, position.y-size*0.25f+size*0.1f, -1.01f);
				glVertex3f(i*size*0.1f+position.x		   , position.y-size*0.45f+size*0.1f, -1.01f);
			}
		glEnd();
 	}
};