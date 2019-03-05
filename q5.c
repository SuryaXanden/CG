#include<stdio.h>
#include<GL/glut.h>
double xmax=100,xmin=50,ymax=100,ymin=50,xvmin=200,xvmax=300,yvmin=200,yvmax=300;
int RIGHT=8,TOP=4,LEFT=2,BOTTOM=1,code=0;
int comp(double x,double y)
{
	code=0;
	if(y>ymax)	code |=TOP;
	else if(y<ymin)	code |=BOTTOM;
	if(x>xmax)	code |=RIGHT;
	else if(x<xmin)	code |=LEFT;
	return code;
}
void cd(double x0,double y0,double x1,double y1)
{
	int o0,o1,oOut;
	int accept=0,done=0;
	o0=comp(x0,y0);
	o1=comp(x1,y1);
	do
	{
		if(!(o0|o1))	accept=done=1;
		else if(o0 & o1)	done=1;
		else
		{
			double x,y;
			oOut=o0? o0:o1;
			if(oOut & TOP)
			{
				x=x0+(x1-x0)*(ymax-y0)/(y1-y0);
				y=ymax;
			}
			else if(oOut & BOTTOM)
			{
				x=x0+(x1-x0)*(ymin-y0)/(y1-y0);
	            		y=ymin;
			}
			else if(oOut & RIGHT)
			{
				y=y0+(y1-y0)*(xmax-x0)/(x1-x0);
				x=xmax;
			}
			else
			{
				y=y0+(y1-y0)*(xmin-x0)/(x1-x0);
				x=xmin;
			}
			if(oOut==o0)
			{
				x0=x;
				y0=y;
				o0=comp(x0,y0);
			}
			else
			{
				x1=x;
				y1=y;
				o1=comp(x1,y1);
			}
		}
	}while(!done);
	if(accept)
	{
		double sx=(xvmax-xvmin)/(xmax-xmin);
		double sy=(yvmax-yvmin)/(ymax-ymin);
		double vx0=xvmin+(x0-xmin)*sx;
		double vy0=yvmin+(y0-ymin)*sy;
		double vx1=xvmin+(x1-xmin)*sx;
		double vy1=yvmin+(y1-ymin)*sy;
		glColor3f(1,0,0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(xvmin,yvmin);
			glVertex2f(xvmax,yvmin);
			glVertex2f(xvmax,yvmax);
			glVertex2f(xvmin,yvmax);
		glEnd();
		glColor3f(0,0,1);
		glBegin(GL_LINES);
			glVertex2d(vx0,vy0);
			glVertex2d(vx1,vy1);
		glEnd();
	}
}
void display()
{
	double x0=120,y0=10,x1=40,y1=130;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	glBegin(GL_LINES);
		glVertex2d(x0,y0);
		glVertex2d(x1,y1);
		glVertex2d(60,20);
		glVertex2d(80,120);
	glEnd();
	glColor3f(0,0,1);
	glBegin(GL_LINE_LOOP);
		glVertex2f(xmin,ymin);
		glVertex2f(xmax,ymin);
		glVertex2f(xmax,ymax);
		glVertex2f(xmin,ymax);
	glEnd();
	cd(x0,y0,x1,y1);
	cd(60,20,80,120);
	glFlush();
}
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(800,600);
	glutCreateWindow("Cohen Suterland Line Clipping Algorithm");
	glutDisplayFunc(display);
	glClearColor(1,1,1,1);
	glColor3f(1,0,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,499,0,499);
	glutMainLoop();
}
