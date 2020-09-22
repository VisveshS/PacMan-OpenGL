#include <stdlib.h>
#include "wall.cpp"
#include <vector>
#include <ctime>
#define N 20
class Maze
{
private:
	std::vector<Wall> walls;
	int size;
	float distance;
	float offset;
	int randomint(int mini,int maxi)
	{
		return rand()%(maxi-mini+1)+mini;
	}
	void randMaze(int xv1,int xv2,int yv1,int yv2, int xh1,int xh2,int yh1,int yh2)
	{
		int xvmid=(xv1+xv2)/2, yvmid=(yh1+yh2)/2, xhmid=(xv1+xv2)/2, yhmid=(yh1+yh2)/2;
		if((xv1>xv2 or yv1>yv2) and (xh1>xh2 or yh1>yh2))
			return;
		if(xv1<=xv2 and yv1<=yv2 and xh1<=xh2 and yh1<=yh2)
		{
			int unbroken=randomint(1,4);
			if(unbroken!=1)vertical[randomint(yv1,yvmid)][xvmid]=false;
			if(unbroken!=2)vertical[randomint(yvmid+1,yv2)][xvmid]=false;
			if(unbroken!=3)horizontal[yhmid][randomint(xh1,xhmid)]=false;
			if(unbroken!=4)horizontal[yhmid][randomint(xhmid+1,xh2)]=false;
		}
		else
		{
			for(int i=xv1;i<=xv2;i++)
				for(int j=yv1;j<=yv2;j++)
					vertical[j][i]=false;
			for(int i=xh1;i<=xh2;i++)
				for(int j=yh1;j<=yh2;j++)
					horizontal[j][i]=false;
		}
		randMaze(xv1,xvmid-1,yv1,yvmid,xh1,xhmid,yh1,yhmid-1);
		randMaze(xv1,xvmid-1,yvmid+1,yv2,xh1,xhmid,yhmid+1,yh2);
		randMaze(xvmid+1,xv2,yv1,yvmid,xhmid+1,xh2,yh1,yhmid-1);
		randMaze(xvmid+1,xv2,yvmid+1,yv2,xhmid+1,xh2,yhmid+1,yh2);
	}
public:
	bool vertical[N][N],horizontal[N][N];
	Maze(){}
	void MazeInit(int n)
	{
		srand((unsigned) time(0));
		for(int i=1;i<N;i++)
			for(int j=1;j<N;j++)
			{
				vertical[i][j]=true;
				horizontal[i][j]=true;
			}
		randMaze(1,n-1,1,n,1,n,1,n-1);
		size=n;
		distance=200.0f/size;
		float offset=2.0f/size*13.0f;
		for(int i=1;i<=size;i++)
			for(int j=1;j<size;j++)
				if(vertical[i][j])
					walls.push_back(Wall(-(j*distance-100),-(i*distance-100-distance/2.0f),offset,offset+distance*1.0f));
		for(int i=1;i<size;i++)
			for(int j=1;j<=size;j++)
				if(horizontal[i][j])
					walls.push_back(Wall(-((+j-0.5)*distance-100),-(distance*(i+0.5)-100-distance/2.0f),offset+distance*1.0f,offset));
	};
	bool collision(float xpos, float ypos, float size)
	{
		for(Wall w:walls)
			if(w.collision(xpos,ypos,size))
				return true;
		return false;
	}
	void draw()
	{
		for(Wall w:walls)
			w.draw();
	}
};