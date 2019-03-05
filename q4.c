#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
GLfloat vn[]={-1,-1,-1,1,-1,-1,1,1,-1,-1,1,-1,-1,-1,1,1,-1,1,1,1,1,-1,1,1};
GLfloat colors[]={0,0,0,0,0,1,0,1,0,0,1,1,1,0,0,1,0,1,1,1,0,1,1,1};
GLubyte cubeIndices[]={0,3,2,1,2,3,7,6,0,4,7,3,1,2,6,5,4,5,6,7,0,1,5,4};
static GLfloat t[]={0,0,0};
static GLint axis=2;
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(t[0],1,0,0);
	glRotatef(t[1],0,1,0);
	glRotatef(t[2],0,0,1);
	glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,CubeIndices);
	glFlush();
	glutSwapBuffers();
}
void mouse(int btn,int state,int x,int y)
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)	axis=0;
	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)	axis=1;
	if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)	axis=2;
}
void spincube()
{
	t[axis]+=2;
	if(t[axis]>360)	t[axis]-=360;
	glutPostRedisplay();
}
void myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)	glOrtho(2,2,2*h/w,2*h/w,10,10);
	else	glOrtho(-2*w/h,2*w/h,-2,2,-10,10);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutCreateWindow("Color cube");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutIdleFunc(spincube);
	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,vn);
	glColorPointer(3,GL_FLOAT,0,colors);
	glNormalPointer(GL_FLOAT,0,vn);
	glColor3f(1,1,1);
	glutMainLoop();
}
