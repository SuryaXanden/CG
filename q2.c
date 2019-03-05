#include<GL/glut.h>
#include<stdio.h>
int x,y,rFlag=0;
float th=0,trX=0,trY=0;
void draw_pixel(float x1,float y1)
{
	glColor3f(0,0,1);
	glPointSize(5);
	glBegin(GL_POINTS);
		glVertex2f(x1,y1);
	glEnd();
}
void triangle()
{
	glColor3f(1,0,0);
	glBegin(GL_POLYGON);
		glVertex2f(100,100);
		glVertex2f(250,400);
		glVertex2f(400,100);
	glEnd();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	if(rFlag==1)
	{
		trX=trY=0;
		th+=0.1;
		draw_pixel(0,0);
	}
	if(rFlag==2)
	{
		trX=x;
		trY=y;
		th+=0.1;
		draw_pixel(x,y);
	}
	glTranslatef(trX,trY,0);
	glRotatef(th,0,0,1);
	glTranslatef(-trX,-trY,0);
	triangle();
	glutPostRedisplay();
	glutSwapBuffers();
}
void menu(int option)
{
	if(option==1)	rFlag=1;
	if(option==2)	rFlag=2;
	if(option==3)	rFlag=3;
}
int main(int argc,char **argv)
{
	printf("Enter Fixed Points (x,y) for Roration: ");
	scanf("%d%d",&x,&y);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(800,600);
	glutCreateWindow("Create and Rotate Triangle");
	glClearColor(0,0,0,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500,500,-500,500);
	glMatrixMode(GL_MODELVIEW);
	glutDisplayFunc(display);
	glutCreateMenu(menu);
	glutAddMenuEntry("Rotate around ORIGIN",1);
	glutAddMenuEntry("Rotate around FIXED POINT",2);
	glutAddMenuEntry("Stop Rotation",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}
