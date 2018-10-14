#include<GL/glut.h>
#include<GL/gl.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctime>
#define MAXIMUM 50
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define ROWS 70
#define COLOUMNS 70
#define Frames 7
void Food_locating();
void initGrid(int,int);
void Making_snake();
void generate_food(int&,int&);
int initialX=20,endX=20,initialY=20,endY=20;
bool game_over=false;
int s0 = 7;
int s1 =7;
int food=1;
int p,q;
int x_coord,y_coord;
short D0 = RIGHT, D1 = UP;
// initial position of the snakes 
int Xt[100]={0,0,0};
int Yt[100] = {1,2,3};
int Xt1[100]={10,10,10};
int Yt1[100] = {15,15,15};
void initGrid(int a,int b)
{
	x_coord=a;
	y_coord=b;

}
void generate_food(int &a,int &b)
{
	int minimum = 1,X = x_coord-2, Y = y_coord-2;
	srand(time(NULL));
	a = minimum + rand() % (X - minimum);
	b = minimum + rand() % (Y - minimum);
}

void Food_locating()
{
if(food==1){
	generate_food(p,q);
	food = 0;
	glColor3f(1.0,0.0,0.0);
	glRectf(p,q,p+1,q+1);
}
else
{
	glColor3f(1.0,0.0,0.0);
	glRectf(p,q,p+1,q+1);

}
}
void Making_snake()
{
for(int i=1;i<s0;i++)
{
	Xt[i] = Xt[i-1];
	Yt[i] = Yt[i-1];
}
for(int i=1;i<s1;i++)
{
	Xt1[i] = Xt1[i-1];
	Yt1[i] = Yt1[i-1];
}
if(D0==RIGHT)
	{
		Xt[0]++;
	}
	else if(D0==LEFT)
	{
		Xt[0]--;
	}
    else if(D0==UP)
	{
		Yt[0]++;
	}
	else if(D0==DOWN)
	{
		Yt[0]--;
	}
 if(D1==RIGHT)
	{
		Xt1[0]++;
	}
	else if(D1==LEFT)
	{
		Xt1[0]--;
	}
	
	else if(D1==UP)
	{
		Yt1[0]++;
	}
	else if(D1==DOWN)
	{
		Yt1[0]--;
	}

for(int i=0;i<s0;i++)
{
	glColor3f(1.0,0.0,0.0);
	glRectd(Xt[i],Yt[i],Xt[i]+1,Yt[i]+1);
}
for(int i=0;i<s1;i++)
{
	glColor3f(0.0,0.0,1.0);
	glRectd(Xt1[i],Yt1[i],Xt1[i]+1,Yt1[i]+1);
}
if(Xt[0]==0 || Xt[0]==x_coord-1 || Yt[0]==0|| Yt[0] == y_coord-1)
	game_over=true;
if(Xt1[0]==0 || Xt1[0]==x_coord-1 || Yt1[0]==0|| Yt1[0] == y_coord-1)
	game_over=true;
for(int i=1;i<s0;i++)
{
	if(Xt[0]==Xt[i] && Yt[0] == Yt[i])
	{
		game_over=true;
		break;
	}
}
	for(int i=1;i<s1;i++)
	{
		if(Xt1[0]==Xt1[i] && Yt1[0] == Yt1[i])
		{
			game_over=true;
			break;
		}
	}
	for(int i=0;i<s1;i++)
	{
		if(Xt[0]==Xt1[i] && Yt[0] == Yt1[i])
		{
			game_over=true;
			break;
		}
	}
	for(int i=0;i<s0;i++)
	{
		if(Xt1[0]==Xt[i] && Yt1[0] == Yt[i])
		{
			game_over=true;
			break;
		}
	}
	if(food==0)
	{
		if(Xt[0]==p&&Yt[0]==q)
		{
			s0++;
			if(s0>MAXIMUM)
			{
				s0=MAXIMUM;
			}
			food=1; 
		}
		if(Xt1[0]==p&&Yt1[0]==q)
		{
			
			s1++;
			if(s1>MAXIMUM)
			{
				s1=MAXIMUM;
			}
			food=1; 
		}
		
	}
}




void shape(int a,int b)
{
	glViewport(0,0,(GLsizei)a,(GLsizei)b);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,COLOUMNS,0.0,ROWS,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);

}



void init()
{
	glClearColor(0.0,0.0,0.0,0.0);
	initGrid(COLOUMNS,ROWS-10);
}


void timerfun(int)
{
	
	glutPostRedisplay();
	glutTimerFunc(1000/Frames,timerfun,0);

}


 void Displaying()
{
	glClear(GL_COLOR_BUFFER_BIT);
	if(!game_over){
	Making_snake();
	Food_locating();}
	glutSwapBuffers();
}


void keyboardfun(unsigned char key,int i,int j)
{
if(key == 'w'){
	if(D1!=DOWN)
 	 D1=UP;}
else if(key == 's'){
	if(D1!=UP)
		D1=DOWN;}
else if(key == 'd'){
	if(D1!=LEFT)
		D1=RIGHT;}
else if(key == 'a'){
	if(D1!=RIGHT)
		D1=LEFT;}
if(key == 'u'){
	if(D0!=DOWN)
 	 D0=UP;}
else if(key == 'j'){
	if(D0!=UP)
		D0=DOWN;}
else if(key == 'k'){
	if(D0!=LEFT)
		D0=RIGHT;}
else if(key == 'h'){
	if(D0!=RIGHT)
		D0=LEFT;}
}
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500,500);
	glutCreateWindow("SNAKE_GAME");
	glutDisplayFunc(Displaying);
	glutReshapeFunc(shape);
	glutTimerFunc(0,timerfun,0);
	glutKeyboardFunc(keyboardfun);
	init();
	glutMainLoop();
	return 0;
}
