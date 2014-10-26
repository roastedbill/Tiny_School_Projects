// CS3241Lab1.cpp : Defines the entry point for the console application.
#include <cmath>
#include <iostream>

/* header files for xcode */
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>

#define DEG2RAD 3.14159/180.0
/* header files for lab machine */
//#include "GL\glut.h"

using namespace std;

GLfloat PI = 3.14;
float alpha = 0.0, k=1;
float tx = 0.0, ty=0.0;

void drawArc(double cx, double cy, float r, int startDeg, int endDeg){
    int i;
    glColor3f(0, 0, 0);
    glLineWidth(20);
    glBegin(GL_LINE_STRIP);
    for(i=startDeg;i<=endDeg;i++){
        glVertex2f(cx+r*sin(i*DEG2RAD), cy+r*cos(i*DEG2RAD));
    }
    glEnd();
    glLineWidth(1);
}

void drawEye(double cx, double cy, float a, float b){
    int i;
    
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    for(i=0;i<360;i++)
    {
        float rad = i*DEG2RAD;
        glVertex2f(cx + cos(rad)*a,
                   cy + sin(rad)*b);
    }
    glEnd();
    
    glColor3f(0, 0, 0);
    glLineWidth(20);
    glBegin(GL_LINE_LOOP);
    for(i=0;i<360;i++)
    {
        float rad = i*DEG2RAD;
        glVertex2f(cx + sin(rad)*a,
                   cy + cos(rad)*b);
    }
    
    glEnd();
    glLineWidth(1);
}

void drawLayer(double cx, double cy, float a, float b, float startDeg, float endDeg, float R, float G, float B){
    int i;
    glColor3f(R,G,B);
    glBegin(GL_POLYGON);
    for(i=0;i<startDeg;i++)
    {
        float rad = i*DEG2RAD;
        glVertex2f(cx + sin(rad)*a,
                   cy + cos(rad)*b);
    }
    for(i=endDeg;i<360;i++)
    {
        float rad = i*DEG2RAD;
        glVertex2f(cx + sin(rad)*a,
                   cy + cos(rad)*b);
    }

    glEnd();

}

void drawBody(double cx, double cy, float a, float b){
    int i;
    
    // draw colorful 7 layers
    drawLayer(0, 2, 5, 7, 180, 180, 1, 1, 1);
    drawLayer(0, 2, 5, 7, 135, 225, 1, 1, 0);
    drawLayer(0, 2, 5, 7, 115, 245, 0, 1, 0);
    drawLayer(0, 2, 5, 7, 100, 260, 0, 0.5, 1);
    drawLayer(0, 2, 5, 7, 85, 275, 0, 1, 0.5);
    drawLayer(0, 2, 5, 7, 70, 290, 1, 0.5, 0.5);
    drawLayer(0, 2, 5, 7, 45, 315, 1, 1, 0.4);
    
    glColor3f(0, 0, 0);
    glLineWidth(20);
    glBegin(GL_LINE_LOOP);
    for(i=0;i<360;i++)
    {
        float rad = i*DEG2RAD;
        glVertex2f(cx + cos(rad)*a,
                   cy + sin(rad)*b);
    }
    
    glEnd();
    glLineWidth(1);
    
}

void drawEyeball(double cx, double cy, float r){
    int i;
    
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    for(i=0;i<360;i++)
    {
        float rad = i*DEG2RAD;
        glVertex2f(cx + cos(rad)*r,
                   cy + sin(rad)*r);
    }
    glEnd();
}

void fillMouth(double cx, double cy){
    int i;
    
    // Fill main part
    glColor3f(0.75,0,0);
    glBegin(GL_POLYGON);
    
    for(i=140;i<=230;i++)
    {
        float rad = i*DEG2RAD;
        glVertex2f(cx + sin(rad)*(cy-0.5),
                   cy + cos(rad)*(cy-0.5));
    }
	glVertex2f(cx + sin(230*DEG2RAD)*(cy-1.5),
               cy + cos(230*DEG2RAD)*(cy-1.5));
	glVertex2f(cx + sin(140*DEG2RAD)*(cy-1.5),
               cy + cos(140*DEG2RAD)*(cy-1.5));
    glEnd();
	
	glColor3f(0, 0.5, 1);
	glBegin(GL_POLYGON);
    
    for(i=140;i<=230;i++)
    {
        float rad = i*DEG2RAD;
        glVertex2f(cx + sin(rad)*(cy-1.5),
                   cy + cos(rad)*(cy-1.5));
    }
    
    glEnd();
    
	// Fill two semicircles
    glColor3f(0.75,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(cx-(cy-1)*sin(50*DEG2RAD),
               cy-(cy-1)*cos(50*DEG2RAD));
    for(i=0;i<=50;i++)
    {
        float rad = i*DEG2RAD;
        glVertex2f(cx-(cy-1)*sin(50*DEG2RAD) + sin(rad)*0.5,
                   cy-(cy-1)*cos(50*DEG2RAD) + cos(rad)*0.5);
    }
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2f(cx-(cy-1)*sin(50*DEG2RAD),
               cy-(cy-1)*cos(50*DEG2RAD));
    for(i=230;i<=360;i++)
    {
        float rad = i*DEG2RAD;
        glVertex2f(cx-(cy-1)*sin(50*DEG2RAD) + sin(rad)*0.5,
                   cy-(cy-1)*cos(50*DEG2RAD) + cos(rad)*0.5);
    }
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2f(cx+(cy-1)*sin(40*DEG2RAD),
               cy-(cy-1)*cos(40*DEG2RAD));
    for(i=0;i<=140;i++)
    {
        float rad = i*DEG2RAD;
        glVertex2f(cx+(cy-1)*sin(40*DEG2RAD) + sin(rad)*0.5,
                   cy-(cy-1)*cos(40*DEG2RAD) + cos(rad)*0.5);
    }
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2f(cx+(cy-1)*sin(40*DEG2RAD),
               cy-(cy-1)*cos(40*DEG2RAD));
    for(i=320;i<=360;i++)
    {
        float rad = i*DEG2RAD;
        glVertex2f(cx+(cy-1)*sin(40*DEG2RAD) + sin(rad)*0.5,
                   cy-(cy-1)*cos(40*DEG2RAD) + cos(rad)*0.5);
    }
    glEnd();
    
}

void drawMouth(double cx, double cy){
    fillMouth(cx, cy);
    drawArc(cx, cy, cy-1.5, 140, 230);
    drawArc(cx, cy, cy-0.5, 140, 230);
    drawArc(cx-(cy-1)*sin(50*DEG2RAD), cy-(cy-1)*cos(50*DEG2RAD), 0.5, 230, 360);
    drawArc(cx-(cy-1)*sin(50*DEG2RAD), cy-(cy-1)*cos(50*DEG2RAD), 0.5, 0, 50);
    drawArc(cx+(cy-1)*sin(40*DEG2RAD), cy-(cy-1)*cos(40*DEG2RAD), 0.5, 320, 360);
    drawArc(cx+(cy-1)*sin(40*DEG2RAD), cy-(cy-1)*cos(40*DEG2RAD), 0.5, 0, 140);
    
}

void drawLeg(double cx, double cy, double a, double b){
    glPushMatrix();
	glRotatef(-40, 0, 0, 1);
    glTranslatef(cx, cy, 0);
    drawLayer(0, 0, a, b, 140, 220, 0, 0, 1);
    drawLayer(0, 0, a, b, 110, 250, 1, 0.5, 0.5);
    drawLayer(0, 0, a, b, 80, 280, 0, 1, 0.5);
    glColor3f(0, 0, 0);
    glLineWidth(20);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<=140;i++)
    {
        float rad = i*DEG2RAD;
        glVertex2f(sin(rad)*a,
                   cos(rad)*b);
    }
    for(int i=220;i<=360;i++)
    {
        float rad = i*DEG2RAD;
        glVertex2f(sin(rad)*a,
                   cos(rad)*b);
    }
    
    glEnd();
    glLineWidth(1);
    glPopMatrix();

    glPushMatrix();
	glRotatef(40, 0, 0, 1);
    glTranslatef(-cx, cy, 0);
    drawLayer(0, 0, a, b, 140, 220, 0, 1, 0.5);
    drawLayer(0, 0, a, b, 110, 250, 0, 0, 1);
    drawLayer(0, 0, a, b, 80, 280, 1, 0.5, 0.5);
    glColor3f(0, 0, 0);
    glLineWidth(20);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<=140;i++)
    {
        float rad = i*DEG2RAD;
        glVertex2f(sin(rad)*a,
                   cos(rad)*b);
    }
    for(int i=220;i<=360;i++)
    {
        float rad = i*DEG2RAD;
        glVertex2f(sin(rad)*a,
                   cos(rad)*b);
    }
    
    glEnd();
    glLineWidth(1);
    glPopMatrix();

}

void drawArm(double cx, double cy, double r){
    glPushMatrix();
    glTranslatef(cx, cy, 0);
    drawLayer(0, 0, r, r, 180, 180, 0, 1, 0.5);
    
    glColor3f(0, 0, 0);
    glLineWidth(20);
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<360; i++){
        float rad = i*DEG2RAD;
        glVertex2f(sin(rad)*r,
                   cos(rad)*r);
    }
    glEnd();
    glLineWidth(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-cx, cy+2, 0);
    drawLayer(0, 0, r, r, 180, 180, 0, 1, 0.5);
    
    glColor3f(0, 0, 0);
    glLineWidth(20);
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<360; i++){
        float rad = i*DEG2RAD;
        glVertex2f(sin(rad)*r,
                   cos(rad)*r);
    }
    glEnd();
    glLineWidth(1);
    glPopMatrix();

}

void drowErHuLuanZi(){
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ZERO);
    drawBody(0, 2, 5, 7);
    drawEye(-3, 4.5, 2.2, 2);
    drawEye(3, 4.3, 3.0, 2.6);
    drawEyeball(-4, 5.5, 0.4);
    drawEyeball(5, 5.6, 0.5);
    drawMouth(0, 3);
    drawLeg(5.5,0,1,3);
    drawArm(6,1,1.2);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
    
	//controls transformation
	glScalef(k, k, k);	
	glTranslatef(tx, ty, 0);	
	glRotatef(alpha, 0, 0, 1);
	
	//draw your stuff here
    
    drowErHuLuanZi();
    
	glPopMatrix();
	glFlush ();
}

void runEyeball(){

}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
    
	glOrtho(-10, 10, -10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glShadeModel (GL_SMOOTH);
    glEnable( GL_LINE_SMOOTH );
	glEnable( GL_POLYGON_SMOOTH );
}


void keyboard (unsigned char key, int x, int y)
{
	//keys to control scaling - k
	//keys to control rotation - alpha
	//keys to control translation - tx, ty
	switch (key) {
            
		case 'a':
			alpha+=10;
			glutPostRedisplay();
            break;
            
		case 'd':
			alpha-=10;
			glutPostRedisplay();
            break;
            
		case 'q':
			k+=0.1;
			glutPostRedisplay();
            break;
            
		case 'e':
			if(k>0.1)
				k-=0.1;
			glutPostRedisplay();
            break;
            
		case 'z':
			tx-=0.1;
			glutPostRedisplay();
            break;
            
		case 'c':
			tx+=0.1;
			glutPostRedisplay();
            break;
            
		case 's':
			ty-=0.1;
			glutPostRedisplay();
            break;
            
		case 'w':
			ty+=0.1;
			glutPostRedisplay();
            break;
            
		default:
            break;
	}
}

void mouse(int button, int state, int x, int y)
{
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(runEyeball);
            break;
        case GLUT_MIDDLE_BUTTON:
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(NULL);
            break;
        default:
            break;
    }
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 1\n\n";
	cout<<"+++++CONTROL BUTTONS+++++++\n\n";
	cout<<"Scale Up/Down: Q/E\n";
	cout<<"Rotate Clockwise/Counter-clockwise: A/D\n";
	cout<<"Move Up/Down: W/S\n";
	cout<<"Move Left/Right: Z/C\n";
    
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
    
	return 0;
}
