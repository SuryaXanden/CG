#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>
GLfloat v[4][3]={{0,0,1},{0,1,0},{-1,-0.5,0},{1,-0.5,0}};
int n;
void triangle(GLfloat *va,GLfloat *vb,GLfloat *vc)
{
	glVertex3fv(va);
	glVertex3fv(vb);
	glVertex3fv(vc);
}
void tetra(GLfloat *a,GLfloat *b,GLfloat *c,GLfloat *d)
{
	glColor3f(1,0,0);
	triangle(a,b,c);
	glColor3f(0,1,0);
	triangle(a,c,d);
	glColor3f(0,0,1);
	triangle(a,d,b);
	glColor3f(1,1,1);
	triangle(b,d,c);
}

void div(GLfloat *a,GLfloat *b,GLfloat *c,GLfloat *d,int m)
{
	GLfloat mid[6][3];
	int j;
	if(m>0)
	{
		for(j=0;j<3;j++)
		{
			mid[0][j]=(a[j]+b[j])/2;
			mid[1][j]=(a[j]+c[j])/2;
			mid[2][j]=(a[j]+d[j])/2;
			mid[3][j]=(b[j]+c[j])/2;
			mid[4][j]=(c[j]+d[j])/2;
			mid[5][j]=(b[j]+d[j])/2;
		}
		div(a,mid[0],mid[1],mid[2],m-1);
		div(mid[0],b,mid[3],mid[5],m-1);
		div(mid[1],mid[3],c,mid[4],m-1);
		div(mid[2],mid[5],mid[4],d,m-1);
	}
	else	tetra(a,b,c,d);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
		div(v[0],v[1],v[2],v[3],n);
	glEnd();
	glFlush();
}
void myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2,2,-2,2,-10,10);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
int main(int argc,char **argv)
{
	printf("Number of divisions? ");
	scanf("%d",&n);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutCreateWindow("3d gasket");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glClearColor(1,1,1,1);
	glutMainLoop();
	return 0;
}
