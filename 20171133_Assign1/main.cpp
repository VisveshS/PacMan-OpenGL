#include <cmath>
#include <ctime>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include "player.cpp"
#include "scoreboard.cpp"
#define offset 0.0f
int mazeSize;
Ground ground;
Maze maze;
Enemy enemy;
Coins coins;
Obstacles obstacles;
Firstaids firstaids;
Batterys batterys;
Godeyes godeyes;
Player player(&ground,&maze,&enemy,&coins,&obstacles,&firstaids,&batterys,&godeyes);
Scoreboard scoreboard;
float white[4] = {1.0f, 1.0f , 1.0f, 1.0f};
void renderScoreboard(void) {
	glDisable(GL_LIGHTING);
	glViewport(0, 0, 500, 100);
	glLoadIdentity();
	gluLookAt(
		0.0f, 0.0f,-10.0f, // 3D coordinate of the camera
		0.0f, 0.0f,0.0f,// target point.
		0.0f, 1.0f, 0.0f); // up vector
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10,-2,2 , 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	scoreboard.drawboard();
	scoreboard.drawcharge(player.quadratic);
	scoreboard.drawhealth(player.health);
	scoreboard.drawscore(player.score);
	if(player.godeye)
		scoreboard.drawgodeyetime(0,8.5,player.timeleft());
}
void renderScene(void) {
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	// Reset transformations
	glViewport(0, 100, 500, 500);
	glLoadIdentity();

	// Setting up the camera's inital position
	gluLookAt(
		player.position.x, player.position.y,player.position.z, // 3D coordinate of the camera
		player.position.x, player.position.y,player.position.z+1,// target point.
		0.0f, 1.0f,  0.0f); // up vector
	player.lightFollow();

	//set zoom
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-player.zoom, +player.zoom,-player.zoom,+player.zoom , 0.1, 100);
	glMatrixMode(GL_MODELVIEW);

	// Draw Game elements
	ground.draw();
	player.draw();
	int finish=player.tick();
	maze.draw();
	enemy.draw();
	enemy.tick();
	coins.draw();
	obstacles.draw();
	firstaids.draw();
	batterys.draw();
	godeyes.draw();
	renderScoreboard();
	
	glutSwapBuffers();
	if(finish!=0)
	{
		std::cout<<(finish==1?"YOU WIN!\n":"YOU DIED\n");
		std::cout<<"coins collected:"<<player.score<<'\n';
		exit(0);
	}
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

    // Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective. 
	glOrtho(-player.zoom, +player.zoom,-player.zoom,player.zoom , 0.1, 100);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void normalKeys(unsigned char key, int x, int y) {
	if(key==27)
		exit(0);
	if(key=='+')
		player.zoom_direction=-1.0f;
	else if(key=='-')
		player.zoom_direction=1.0f;
	else if(key=='0')
		player.zoom=30.0f;
}
void normalKeysUp(unsigned char key, int x, int y) {
	if(key=='+')
		player.zoom_direction=0.0f;
	if(key=='-')
		player.zoom_direction=0.0f;
}
void specialKeys(int key, int x, int y) {
	if(key==GLUT_KEY_UP)
		player.velocity.y=1.0f;
	if(key==GLUT_KEY_DOWN)
		player.velocity.y=-1.0f;
	if(key==GLUT_KEY_RIGHT)
		player.velocity.x=-1.0f;
	if(key==GLUT_KEY_LEFT)
		player.velocity.x=1.0f;
}
void specialKeysUp(int key, int x, int y) {
	if(key==GLUT_KEY_UP)
		player.velocity.y=0.0f;
	if(key==GLUT_KEY_DOWN)
		player.velocity.y=0.0f;
	if(key==GLUT_KEY_RIGHT)
		player.velocity.x=0.0f;
	if(key==GLUT_KEY_LEFT)
		player.velocity.x=0.0f;
}
void init()
{
	player.lightInit();
	player.position = glm::vec3(2*(50-250/mazeSize), 2*(-50+50/mazeSize), -50.0f);
	ground.size=mazeSize;
	maze.MazeInit(mazeSize);
	enemy.EnemyInit(maze.vertical,maze.horizontal,mazeSize, &player.position);
	player.size=enemy.size;
	coins.Coinsinit(50);
	batterys.Batterysinit(10);
	obstacles.Obstaclesinit(10);
	firstaids.Firstaidsinit(10);
	godeyes.Godeyesinit(10);
}

int main(int argc, char **argv) {
	std::cout<<"Enter maze complexity:(10<=size<=18)\n";
	std::cin>>mazeSize;
	if(mazeSize<10 or mazeSize>18)
		return 0;	
	srand((unsigned) time(0));
	// initialise GLUT, and create a Window of some size
	glutInit(&argc, argv);
	glutInitWindowPosition(0,0);
    glutInitWindowSize(500,600);

	// Creating a window with a double buffer window, activated
	// the depth buffer and and selects an RGBA window
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	
	glutCreateWindow("OpenGL-Assignment1-Pacman");

	init();

	// Telling GLUT which function is responsible for rendering
	// called by GLUT everytime the window needs to be painted
	glutDisplayFunc(renderScene);

	// called by GLUT everytime the window is resized
	glutReshapeFunc(changeSize);

	// called by GLUT everytime the window is idle
	glutIdleFunc(renderScene);

	 
	// Call a Function to Process Keyboard Input Here
	glutKeyboardFunc(normalKeys);
	glutKeyboardUpFunc(normalKeysUp);
	glutSpecialFunc(specialKeys);
	glutSpecialUpFunc(specialKeysUp);

	// Initialise a depth buffer
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}	