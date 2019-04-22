#include <stdio.h>
#include<stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include<time.h>
using namespace std;
#define PI 3.1416
float posX=10,posY=0,posZ=0;
float missileX=0,missileY=300,missileZ=0;
bool missilestat= false,dropped=false;
float xx;
void scene();
void ship();
void reset();
void initmissile(int max ,int min)
{
    static bool first = true;
    if (first)
        {
            srand (time(NULL));
                first=false;
        }

	missileX= min+ rand()%(max-min);
}

void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_TRIANGLE_FAN);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 

		glVertex2f(x + cx, y + cy);//output vertex 

	}
	glEnd();
}

void drawoval(GLfloat x, GLfloat y, GLfloat radius)
{
    int triangleAmount = 2000; //# of triangles used to draw circle
    float twicePi = 2.0f * PI;
    glBegin(GL_TRIANGLE_FAN);
        for(int i = 0; i <= triangleAmount;i++) {
            glVertex2f( x + (radius/6 * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount)));
            }
    glEnd();
}
void drawoval2(GLfloat x, GLfloat y, GLfloat radius)
{
    int triangleAmount = 2000; //# of triangles used to draw circle
    float twicePi = 2.0f * PI;
    glBegin(GL_TRIANGLE_FAN);
        for(int i = 0; i <= triangleAmount;i++) {
            glVertex2f( x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius/4 * sin(i * twicePi / triangleAmount)));
            }
    glEnd();
}
void myInit(void)
{
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1200.0, 0.0, 800.0);
}
void ship()
{	glPushMatrix();
	for(int i=0;i<10;i++)
	{
	glTranslatef(posX,posY,posZ);
	}
	
	glBegin(GL_POLYGON);//base
	glColor3f(0,0,0);
	glVertex2i(800,300);
	glVertex2i(1000,300);
	glVertex2i(1100,400);
	glVertex2i(700,400);
	glEnd();


	glBegin(GL_POLYGON);//p1
	glColor3f(0,1,0);
	glVertex2i(750,400);
	glVertex2i(1050,400);
	glVertex2i(1050,450);
	glVertex2i(750,450);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.2,0.5,0.6);
	glVertex2i(740,400);
	glVertex2i(750,400);
	glVertex2i(750,450);
	glVertex2i(740,455);
	glEnd();
	glPopMatrix();
}

void scene()
{
	glPushMatrix();

	glBegin(GL_POLYGON); //Sky  
	glColor3f(0.4, 0.5, 1.0);
	glVertex2i(0, 800);
	glVertex2i(1200, 800);
	glColor3f(0.7, 0.7, 1.0);
	glVertex2i(1200, 0);
	glVertex2i(0, 0);
	glEnd();

	glBegin(GL_POLYGON);//sand
	glColor3f(0.94, 0.94, 0.03);
	glVertex2i(0,0);
	glVertex2i(1200,0);
	glColor3f(0.89, 0.89, 0.46);
	glVertex2i(1200,50);
	glVertex2i(0,150);
	glEnd();

	glBegin(GL_POLYGON);//ocean
	glColor3f(0.35, 0.78, .96);
	glVertex2i(0,150);
	glVertex2i(1200,50);
	glVertex2i(1200,350);
	glVertex2i(0,350);
	glEnd();

	



	glPopMatrix();

}
void drawSun()
{
	glPushMatrix();

	glColor3f(.98, .61, 0.01);
	DrawCircle(900, 700, 40, 1000);// SUN: here the value 900 is the x-axis and 700 is the y-axis and 40 is the radius
 
	glPopMatrix();
}

void drawmissilehorizontal()
{
	glPushMatrix();
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);//upper
	glVertex2i(470,400);
	glVertex2i(520,400);
	glVertex2i(470,450);
	glEnd();
	drawoval2(500,400,80);
	glBegin(GL_POLYGON);//upper
	glVertex2i(470,400);
	glVertex2i(520,400);
	glVertex2i(470,350);
	glEnd();

	drawoval(700,600,80);
	glPopMatrix();
}
void drawmissilevertical()
{
	glPushMatrix();
	
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2i(690,630);
	glVertex2i(690,580);
	glVertex2i(640,630);
	glVertex2i(710,630);
	glVertex2i(710,580);
	glVertex2i(760,630);
	glEnd();
	glColor3f(1.0,0.0,0.0);
	drawoval(700,600,80);
	
	
	
	
	glPopMatrix();
}

void mouse (int button, int state, int x,int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
		missilestat = true;
}
}

void missile()
{
	
	if (missilestat==true)
	{
		
		missileY-=.5;
		
	}
	while (missileY<=-300)
	{
		//dropped=true;
		missileY=300;
		initmissile(400,-600);
		
	}
	
	
	glPushMatrix();
	glTranslatef(missileX, missileY, missileZ);
	drawmissilevertical();
	glPopMatrix();
	cout<<"Y: "<<missileY<<endl;
}
void reset()
{
	posX =10;
	
}

void myDisplay(void)
{
	
	scene();
	drawSun();
	
	ship();
	if(posX==-110)
	{
	
	reset();
	}
	missile();
	
	cout << "POSX: "<<posX<<endl;

	

	glFlush();

	glutPostRedisplay();
	glutSwapBuffers();
}
void keyboard(unsigned char key, int x, int y)
{
	if(key == 'a')
	{
		posX--;
	}
	else if(key == 'd')
	{
		posX++;
	}
	
	glutPostRedisplay();
}

void main(int argc, char** argv)
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1350, 700);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Escape");
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
}