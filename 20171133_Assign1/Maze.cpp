#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#define N 21
using namespace std;
bool vertical[N][N],horizontal[N][N];
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
int main()
{
	srand((unsigned) time(0));
	int x,y,i,j;
	cin>>x>>y;
	for(i=1;i<N;i++)
		for(j=1;j<N;j++)
		{
			vertical[i][j]=true;
			horizontal[i][j]=true;
		}
	randMaze(1,x-1,1,y,1,x,1,y-1);
	for(i=1;i<=y;i++)
		for(j=1;j<x;j++)
			cout<<vertical[i][j]<<(j==x-1?'\n':' ');
	cout<<endl;
	for(i=1;i<y;i++)
		for(j=1;j<=x;j++)
			cout<<horizontal[i][j]<<(j==x?'\n':' ');
	return 0;
}