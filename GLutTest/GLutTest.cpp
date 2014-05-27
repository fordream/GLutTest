// GLutTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <GL/glut.h>

// void display(void)
// {
// 	/* clear window */
// 	glClear(GL_COLOR_BUFFER_BIT);
// 	/* draw unit square polygon */
// 	glBegin(GL_POLYGON);
// 	glVertex2f(-0.5, -0.5);
// 	glVertex2f(-0.5, 0.5);
// 	glVertex2f(0.5, 0.5);
// 	glVertex2f(0.5, -0.5);
// 	glEnd();
// 	/* flush GLbuffers */
// 	glFlush();
// }
// 
// void init()
// {
// 	/* set clear color to black */
// 	glClearColor(0.0, 0.0, 0.0, 0.0);
// 	/* set fill  color to white */
// 	glColor3f(1.0, 0.0, 0.0);
// 	/* set up standard orthogonal view with clipping */
// 	/* box as cube of side 2 centered at origin */
// 	/*This is default view and these statement could be removed */
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
// }

GLfloat x1 = 0.0f;
GLfloat y1 = 0.0f;
GLfloat rsize = 25;

GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

GLfloat windowWidth;
GLfloat windowHeight;

void TimeFunction(int value)
{
	if (x1 > windowWidth - rsize || x1 < -windowWidth)
		xstep = -xstep;

	if (y1>windowHeight || y1 < -windowHeight + rsize)
		ystep = -ystep;

	x1 += xstep;
	y1 += ystep;

	if (x1>(windowWidth - rsize + xstep))
		x1 = windowWidth - rsize - 1;
	else if (x1 < -(windowWidth + xstep))
		x1 = -windowWidth - 1;

	if (y1>(windowHeight + ystep))
		y1 = windowHeight - 1;
	else if (y1 < -(windowHeight - rsize + ystep))
		y1 = -windowHeight + rsize - 1;

	//用新坐标重新绘制场景
	glutPostRedisplay();
	glutTimerFunc(300, TimeFunction, 1);
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);

	glRectf(x1, y1, x1+rsize, y1-rsize);

	glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat aspectRatio;

	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	//重制坐标系统
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (GLfloat)w / (GLfloat)h;

	if (w <= h)
		//正投影函数
		glOrtho(-100.0, 100.0, -100 / aspectRatio, 100.0 / aspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0*aspectRatio, 100.0*aspectRatio, -100.0, 100.0, 1.0, - 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SetupRC(void)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

int main(int argc, char* argv[])
{
// 	glutInit(&argc, argv);
// 	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
// 	glutInitWindowSize(500, 500);
// 	glutInitWindowPosition(0, 0);
// 	glutCreateWindow("simple");
// 	glutDisplayFunc(display);
// 	init();
// 	glutMainLoop();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("GLRect");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(300, TimeFunction, 1);

	SetupRC();

	glutMainLoop();

	return 0;
}

