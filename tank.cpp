// Snigdho, Tanveer Feisal
// 12-20164-1


#include <stdio.h>
#include <GL/glut.h>
#include<math.h>
 
int move, angle, screen_margin = 140;

void myDisplay(void);
void myInit(void);
void drawTank();
void drawBackground();
void DrawCircleBoundary(float cx, float cy, float r, int num_segments);
void DrawCircleBody(float cx, float cy, float r, int num_segments);
void specialKeys(int key, int x, int y);

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(960, 540);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("Tank");
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(specialKeys);
	myInit();
	glutMainLoop();
}


void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawBackground();				//background portion

	glPushMatrix();					// tank portion
	glTranslatef(move, angle, 0);
	drawTank();
	glPopMatrix();
	
	glFlush();
}

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 960.0, 0.0, 540.0);
}

void specialKeys(int key, int x, int y)
{

	if (key == GLUT_KEY_RIGHT && screen_margin < 500)
	{
		move += 10;
		screen_margin += 10;
	}

	else if (key == GLUT_KEY_LEFT && screen_margin > 80)
	{
		move -= 10;
		screen_margin -= 10;
	}

	glutPostRedisplay();
}

void DrawCircleBoundary(float cx, float cy, float r, int num_segments)
{

	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 

		glVertex2f(x + cx, y + cy);//output vertex 

	}
	glEnd();
}

void DrawCircleBody(float cx, float cy, float r, int num_segments)
{

	glBegin(GL_POLYGON);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 

		glVertex2f(x + cx, y + cy);//output vertex 

	}
	glEnd();
}

void drawTank()
{
	glBegin(GL_QUADS);       // backgroung color of wheels
	glColor3f(0.0, 0.1, 0.0);
	glVertex2i(120, 130);
	glVertex2i(150, 80);
	glVertex2i(370, 80);
	glVertex2i(400, 130);
	glEnd();

	glColor3f(0.1, 0.3, 0.1);
	for (int i = 160; i < 380; i += 40)  // wheel body
		DrawCircleBody(i, 100, 20, 30);


	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1);
	for (int i = 160; i < 380; i += 40)  // wheel boundary
		DrawCircleBoundary(i, 100, 20, 30);

	glLineWidth(3);
	glBegin(GL_LINE_STRIP);		// chain
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(120, 130);
	glVertex2i(150, 80);
	glVertex2i(370, 80);
	glVertex2i(400, 130);
	glEnd();

	glBegin(GL_QUADS);       // color of side of front upper wheel portion
	glColor3f(0.15, 0.4, 0.15);
	glVertex2i(100, 170);
	glVertex2i(120, 116);
	glVertex2i(400, 116);
	glVertex2i(420, 170);

	glColor3f(0.2, 0.55, 0.2);  // color of front upper wheel portion
	glVertex2i(100, 170);
	glVertex2i(420, 170);
	glVertex2i(418, 190);
	glVertex2i(102, 190);

	glColor3f(0.2, 0.55, 0.2);  // color of rear upper wheel portion
	glVertex2i(106, 240);
	glVertex2i(414, 240);
	glVertex2i(412, 256);
	glVertex2i(108, 256);
	glEnd();

	glBegin(GL_TRIANGLES);  // rear upper wheel portion- side triangles
	glColor3f(0.0, 0.15, 0.0);

	glVertex2i(106, 240);
	glVertex2i(116, 230);
	glVertex2i(126, 240);

	glVertex2i(414, 240);
	glVertex2i(404, 230);
	glVertex2i(404, 240);

	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.13, 0.3, 0.13);  // color of middle portion
	glVertex2i(110, 190);
	glVertex2i(410, 190);
	glVertex2i(404, 240);
	glVertex2i(116, 240);

	glColor3f(0.2, 0.5, 0.2);  // pipe
	glVertex2i(350, 225);
	glVertex2i(550, 225);
	glVertex2i(550, 236);
	glVertex2i(350, 236);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.25, 0.6, 0.25);  // upper part of pipe holder
	glVertex2i(150, 210);
	glVertex2i(360, 234);
	glVertex2i(356, 260);
	glVertex2i(220, 260);
	glVertex2i(154, 236);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.16, 0.4, 0.16);  // side part of pipe holder
	glVertex2i(150, 200);
	glVertex2i(360, 200);
	glVertex2i(360, 234);
	glVertex2i(220, 234);
	glVertex2i(150, 210);
	glEnd();
}

void drawBackground()
{
	glLineWidth(1);

	glBegin(GL_QUADS);       // backgroung color
	glColor3f(0.3, 0.99, 0.4); // ground
	glVertex2i(0, 0);
	glVertex2i(960, 0);
	glVertex2i(960, 320);
	glVertex2i(0, 320);

	glColor3f(0.3, 0.7, 0.8);  // sky
	glVertex2i(0, 320);
	glVertex2i(960, 320);
	glVertex2i(960, 540);
	glVertex2i(0, 540);

	glColor3f(0.8, 0.0, 0.0);  // wall
	glVertex2i(0, 300);
	glVertex2i(450, 300);
	glVertex2i(450, 360);
	glVertex2i(0, 360);
	glEnd();


	glColor3f(0.0, 0.0, 0.0);		// drawing bricks
	int x = 0;
	for (int j = 300; j < 360; j += 12){
		for (int i = 0; i < 450; i += 30){
			glBegin(GL_LINE_LOOP);

			if (x % 2 == 0)
			{
				glVertex2i(i, j);
				glVertex2i(i + 30, j);
				glVertex2i(i + 30, j + 12);
				glVertex2i(i, j + 12);
			}
			else
			{
				glVertex2i(i - 15, j);
				glVertex2i(i + 15, j);
				glVertex2i(i + 15, j + 12);
				glVertex2i(i - 15, j + 12);
			}

			glEnd();
		}
		x++;
	}


	glBegin(GL_QUADS);
	glColor3f(0.55, 0.2, 0.2);

	glVertex2i(160, 280);		// first 2 quads for left tree
	glVertex2i(200, 280);
	glVertex2i(192, 320);
	glVertex2i(168, 320);

	glVertex2i(168, 320);
	glVertex2i(192, 320);
	glVertex2i(200, 360);
	glVertex2i(160, 360);

	glVertex2i(520, 300);		// next 2 quads for right tree
	glVertex2i(560, 300);
	glVertex2i(552, 340);
	glVertex2i(528, 340);

	glVertex2i(528, 340);
	glVertex2i(552, 340);
	glVertex2i(560, 380);
	glVertex2i(520, 380);
	glEnd();

	glColor3f(0.2, 0.7, 0.2);			// first 3 for first tree
	DrawCircleBody(180, 388, 40, 50);
	DrawCircleBody(148, 380, 28, 50);
	DrawCircleBody(212, 380, 28, 50);

	DrawCircleBody(540, 408, 40, 50);	// first 3 for first tree
	DrawCircleBody(508, 400, 28, 50);
	DrawCircleBody(572, 400, 28, 50);

	glColor3f(0.5, 0.5, 0.7);
	DrawCircleBody(700, 480, 40, 50); //cloud
	DrawCircleBody(760, 500, 32, 50);
	DrawCircleBody(750, 465, 28, 50);
	DrawCircleBody(798, 480, 30, 50);

	glColor3f(0.99, 0.9, 0.5);
	DrawCircleBody(80, 480, 30, 50);	//sun
}
