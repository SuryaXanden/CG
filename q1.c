#include<GL/glut.h>
#include<stdio.h>
int x1,y1,x2,y2;
void pix(int x,int y)
{
	glPointSize(2);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
}
void line(int x1,int x2,int y1,int y2)
{
	glColor3f(1,1,1);
	int dx,dy,i,e,incx,incy,inc1,inc2,x,y;
	dx=x2-x1;
	dy=y2-y1;
	if(dx<0) dx=-dx;
	if(dy<0) dy=-dy;
	incx=1;
	if(x2<x1)
		incx=-1;
	incy=1;
	if(y2<y1)
		incy=-1;
	x=x1; y=y1;
	if(dx>dy)
	{
		pix(x,y);
		e=2*dy-dx;
		inc1=2*(dy-dx);
		inc2=2*dy;
		for(i=0;i<dx;i++)
		{
			if(e>0)
			{
				y+=incy;
				e+=inc1;
			}
			else
				e+=inc2;
			x+=incx;
			pix(x,y);
		}
	}
	else
	{
		pix(x,y);
		e=2*dx-dy;
		inc1=2*(dx-dy);
		inc2=2*dx;
		for(i=0;i<dy;i++)
		{
			if(e>0)
			{
				x+=incx;
				e+=inc1;
			}
			else
				e+=inc2;
			y+=incy;
			pix(x,y);
		}
	}
}
void disp()
{
	line(x1,x2,y1,y2);
	glFlush();
}
int main(int argc,char **argv)
{
	printf("Enter (x1,y1,x2,y2): ");
	scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(800,600);
	glutCreateWindow("Bresenham LDA");
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,1);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,500,0,500);
	glutDisplayFunc(disp);
	glutMainLoop();
}
