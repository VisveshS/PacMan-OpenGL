#include <cmath>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include "ground.cpp"
#include "maze.cpp"
#include "enemy.cpp"
#include "coins.cpp"
#include "obstacles.cpp"
#include "firstaid.cpp"
#include "battery.cpp"
#include "godeye.cpp"
#include <iostream>
#define unitTime 10
#define GODEYETIME 300.0f
class Player
{
private:
	Ground *ground;
	Maze *maze;
	Enemy *enemy;
	Coins *coins;
	Obstacles *obstacles;
	Firstaids *firstaids;
	Batterys *batterys;
	Godeyes *godeyes;
	float black[4] = {0.0f, 0.0f , 0.0f, 1.0f};
	float yellow[4] = {1.0f, 1.0f , 0.1f, 1.0f};
	float brown[4] = {0.3f, 0.3f , 0.1f, 1.0f};
	float blue[4] = {0.3f, 0.3f , 1.0f, 1.0f};
	float zoom_speed;
	int tickbig=0;
	int godeyetime;
public:
	bool godeye;
	int score;
	float health;
	float size;
	GLfloat quadratic;
	GLfloat cutoff;
	glm::vec3 position;
	glm::vec3 velocity;
	float speed;
	float zoom;
	float zoom_direction;
	Player(Ground *g,Maze *m,Enemy *e,Coins *c, Obstacles *o,Firstaids *f,Batterys *b,Godeyes *ep)
	{
		score=0;
		health = 1.0f;
		cutoff = 90.0f;
		quadratic = 20.0f;
		position = glm::vec3(0.0f, 0.0f, -50.0f);
		speed = 0.5f;
		zoom = 30.0f;
		zoom_speed = 2.0f;
		godeyetime=0;
		ground = g;
		maze = m;
		enemy = e;
		coins = c;
		obstacles = o;
		firstaids = f;
		batterys = b;
		godeyes = ep;
	}
	float timeleft(void)
	{
		return float(godeyetime/GODEYETIME);
	}
	void zooming()
	{
		zoom += zoom_speed*zoom_direction;
		if(zoom<10.0f)
			zoom=10.0f;
		else if(zoom>100.0f)
			zoom=100.0f;
	}
	void lightInit()
	{
		glEnable(GL_LIGHTING);
		glShadeModel(GL_SMOOTH);
		glLightfv ( GL_LIGHT0, GL_SPOT_CUTOFF, &cutoff);
		glLightfv ( GL_LIGHT0, GL_SPOT_EXPONENT, &quadratic);
		glEnable(GL_LIGHT0);
	}
	int tick()
	{
		tickbig++;
		if(tickbig==unitTime)
			tickbig=0,quadratic+=0.2f;
		glLightfv ( GL_LIGHT0, GL_SPOT_CUTOFF, &cutoff);
		glLightfv ( GL_LIGHT0, GL_SPOT_EXPONENT, &quadratic);
		zooming();
		bool collide=false;
		glm::vec3 temp = glm::vec3(position.x+(velocity.x*speed), position.y+(velocity.y*speed), position.z+(velocity.z*zoom));
		// collision with ground
		collide = collide or temp.x>=ground->bounds[1] or temp.x<=ground->bounds[0] or temp.y>=ground->bounds[2] or temp.y<=ground->bounds[3];
		collide = collide or maze->collision(temp.x,temp.y,size);
		if(coins->collision(temp.x,temp.y,size))
			score++;
		health-=0.17*obstacles->collision(temp.x,temp.y,size);
		if(batterys->collision(temp.x,temp.y,size))quadratic=20.0f;
		if(firstaids->collision(temp.x,temp.y,size))
			health=1.0f;
		if(godeyes->collision(temp.x,temp.y,size))
			godeye=true,godeyetime=0,zoom=100,cutoff=180,enemy->seen=true;
		if(godeye and godeyetime>GODEYETIME)
			godeyetime=0,godeye=false,zoom=30,cutoff=90,enemy->seen=false;
		else if(godeye)
			godeyetime++;
		if(not collide)
			position = temp;
		if(ground->finish(position.x,position.y))
			return 1;
		if(enemy->kill(position.x,position.y) or health<=0)
			return -1;
		return 0;
	}
	void lightFollow()
	{
		float pos[4] = { position.x, position.y, -50, 1};
		glLightfv ( GL_LIGHT0, GL_POSITION, pos);
	}

	void draw()
	{
		glBegin(GL_QUADS);

		glMaterialfv ( GL_FRONT, GL_AMBIENT, black);
		glMaterialfv ( GL_FRONT, GL_DIFFUSE, yellow);

		//face
		glVertex3f(position.x+size/2.0f, position.y+size/2.0f, -1.0f);
		glVertex3f(position.x-size/2.0f, position.y+size/2.0f, -1.0f);
		glVertex3f(position.x-size/2.0f, position.y-size/2.0f, -1.0f);
		glVertex3f(position.x+size/2.0f, position.y-size/2.0f, -1.0f);		

		//eyes
		glMaterialfv ( GL_FRONT, GL_DIFFUSE, brown);
		glVertex3f(position.x-size*0.25+size*0.1f, position.y+size*0.25f+size*0.1f, -1.01f);
		glVertex3f(position.x-size*0.25-size*0.1f, position.y+size*0.25f+size*0.1f, -1.01f);
		glVertex3f(position.x-size*0.25-size*0.1f, position.y+size*0.25f-size*0.1f, -1.01f);
		glVertex3f(position.x-size*0.25+size*0.1f, position.y+size*0.25f-size*0.1f, -1.01f);

		glVertex3f(position.x+size*0.25+size*0.1f, position.y+size*0.25f+size*0.1f, -1.01f);
		glVertex3f(position.x+size*0.25-size*0.1f, position.y+size*0.25f+size*0.1f, -1.01f);
		glVertex3f(position.x+size*0.25-size*0.1f, position.y+size*0.25f-size*0.1f, -1.01f);
		glVertex3f(position.x+size*0.25+size*0.1f, position.y+size*0.25f-size*0.1f, -1.01f);

		//mouth
		glVertex3f(position.x-size*0.25-size*0.1f, position.y-size*0.25f+size*0.1f, -1.01f);
		glVertex3f(position.x-size*0.15-size*0.1f, position.y-size*0.45f+size*0.1f, -1.01f);
		glVertex3f(position.x+size*0.15+size*0.1f, position.y-size*0.45f+size*0.1f, -1.01f);
		glVertex3f(position.x+size*0.25+size*0.1f, position.y-size*0.25f+size*0.1f, -1.01f);

		glEnd();
	}
};