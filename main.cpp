#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib,"glaux.lib")
#include <windows.h>
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glaux.h>
#include <stdlib.h> 
#include <time.h>
#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>
#include <ctime>
float cc=0.4;
GLfloat pt[4][3]={{0.0,0.0,1.0},{0.0,1.0,0.0},{-1.0,-0.5,0.0}, {1.0,-0.5,0.0}};
GLfloat colors[5][3]={{0.3+cc/5,cc/3,0.1+cc/2}, {cc/10,0.3+cc/10,cc/10-0.1}, {0.5+cc/8,0.6+cc/7,cc/9+0.7}, {1-cc/10,cc/15,0.5+cc/20}, {0.3+cc/5,cc/3-0.2,0.1+cc/2}};
int n=3;
int alpha = 0, beta = 0;
void CALLBACK mouse(AUX_EVENTREC *event)
{
	static int x0, y0 = -12345;
	if (y0 != -12345)
	{
		alpha += event->data[AUX_MOUSEX] - x0;
		beta += event->data[AUX_MOUSEY] - y0;
	}
	x0 = event->data[AUX_MOUSEX];
	y0 = event->data[AUX_MOUSEY];
}

void triangle(GLfloat *va,GLfloat *vb,GLfloat *vc)
{
	glVertex3fv(va);
	glVertex3fv(vb);
	glVertex3fv(vc);
}

void pyramid(GLfloat *a,GLfloat *b,GLfloat *c,GLfloat *d)
{
    glColor3fv(colors[rand() % 5]);
    triangle(a,b,c);
    glColor3fv(colors[rand() % 5]);
    triangle(a,c,d);
    glColor3fv(colors[rand() % 5]);
    triangle(a,d,b);
    glColor3fv(colors[rand() % 5]);
    triangle(b,d,c);
}

void divide_pyramid(GLfloat *a,GLfloat *b,GLfloat *c,GLfloat *d,int m)
{
    GLfloat division[6][3];
    int j;
    if(m>0)
    {   
        for(j=0;j<3;j++) 
			division[0][j]=(2*a[j]+b[j])/3;
        for(j=0;j<3;j++) 
			division[1][j]=(a[j]+c[j])/2;
        for(j=0;j<3;j++) 
			division[2][j]=(a[j]+2*d[j])/3;
        for(j=0;j<3;j++) 
			division[3][j]=(b[j]+c[j])/2;
        for(j=0;j<3;j++) 
			division[4][j]=(2*c[j]+d[j])/3;
        for(j=0;j<3;j++) 
			division[5][j]=(b[j]+d[j])/2;
        divide_pyramid(a,division[0],division[1],division[2],m-1);
        divide_pyramid(division[0],b,division[3],division[5],m-1);
        divide_pyramid(division[1],division[3],c,division[4],m-1);
        divide_pyramid(division[2],division[5],division[4],d,m-1);
    }
    else
        pyramid(a,b,c,d);     
}

void display(void)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess = 100.0;
	GLfloat light_ambient[] = { 5.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { -1.0, 0.0, 0.7, 0.0 };
	GLfloat white_light[] = { 1.0,1.0,1.0,1.0 };
	GLfloat blue_light[] = { 0.0, 1.0, 1.0,1.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, blue_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glBegin(GL_TRIANGLES);      
    divide_pyramid(pt[0],pt[1],pt[2],pt[3],n); 
    glEnd();               
	glDisable(GL_LIGHT0);
    glFlush();                                                                                             
}

void myReshape(int w,int h)
{
    glViewport(0,0,w,h);                
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();                       
    glOrtho(-20.0,20.0,-20.0,20.0 ,-10.0,10.0);                         
	glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();     
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);                                  
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(500,500);      
	glutCreateWindow("---");  
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);       
	glEnable(GL_DEPTH_TEST);
	auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSELOC, mouse);                        
	glClearColor(1.0,1.0,1.0,1.0);        
	glutMainLoop();     
	return 0;
}
