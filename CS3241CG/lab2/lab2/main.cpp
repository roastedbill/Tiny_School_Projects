// CS3241Lab1.cpp : Defines the entry point for the console application.
#include <cmath>
#include <iostream>

/* header files for xcode */
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>

/* header files for lab machine */
//#include "GL/glut.h"

using namespace std;

#define numStars 100
#define numPlanets 9
#define DEG2RAD 3.14159/180.0
#define g 0.01

class planet
{
public:
	float distFromRef;
    float distFromRef2;
	float angularSpeed;
	GLfloat color[4];
	float size;
	float angle;
    float pos, speed; // for jumping
    
	planet()
	{
		distFromRef = 0;
        distFromRef2 = 0;
		angularSpeed = 0;;
        speed = 0;
        pos = 0;
		color[0] = color[1] = color[2] = 0;
        color[3] = 1.0;
		size = 0;
		angle = 0;
	}
    
    void setPlanet(float dis, float angv, float color0, float color1, float color2, float r)
	{
		distFromRef = dis;
        pos = dis;
		angularSpeed = angv;
		color[0] = color0;
        color[1] = color1;
        color[2] = color2;
		size = r;
		angle += angv;
        if(angle>360)
            angle -= 360;
	}
    
    void setDis2(float b){
        distFromRef2 = b;
    }
    
    void setAlpha(float af){
        color[3] = af;
    }
    
};

GLfloat PI = 3.14;
float alpha = 0.0, k=1;
float alphaRest = 1.0;
float tx = 0.0, ty=0.0;
planet planetList[numPlanets];
int starRand[numStars][3];

void drawPlanet(planet Planet){
    int i;
    glColor4f(Planet.color[0], Planet.color[1], Planet.color[2], Planet.color[3]);
    glBegin(GL_POLYGON);
    for(i=0;i<=360;i++){
        glVertex2f(Planet.size*sin(i*DEG2RAD), Planet.size*cos(i*DEG2RAD));
    }
    glEnd();
}

void drawStar(double cx, double cy, float a, float af){
    glColor4f(1, 1, 1, af);
    glBegin(GL_POLYGON);
    glVertex2f(cx+a/2,cy+a/2);
    glVertex2f(cx+a/2,cy-a/2);
    glVertex2f(cx-a/2,cy-a/2);
    glVertex2f(cx-a/2,cy+a/2);
    glEnd();
    //printf("%lf %lf %f %f\n",cx,cy,a,alpha);				

}

void drawStars(){
    for(int i=0; i<numStars; i++){
        drawStar(starRand[i][0]%2000/100.0-10, starRand[i][1]%2000/100.0-10, starRand[i][2]%100/1000.0, (rand()%100)/100.0);
        //printf("drawing star %d: ",i);
    }
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

void initPlanets(){
    for(int i=0; i<numPlanets; i++)
        planetList[i] = planet();
    
    planetList[8].setPlanet(0, 0, 0.2, 0.2, 0.4, 1.2);
    
    planetList[0].setPlanet(2, 0, 1, 0.65, 0, 0.5);
    planetList[1].setPlanet(3, 0, 0.3, 0.65, 1, 0.4);
    planetList[2].setPlanet(4, 0, 0.6, 0, 0.9, 0.3);
    planetList[3].setPlanet(0, 0, 0.1, 0.1, 1, 1.3);
    planetList[4].setPlanet(4.5, 1, 0.9, 0.1, 0.2, 0.5);
    planetList[4].setDis2(2.5);
    planetList[5].setPlanet(0.8, 2, 0.4, 0.1, 0.9, 0.25);
    planetList[6].setPlanet(10, 0, 0.9, 0.3, 0.1, 2);
    planetList[6].setDis2(35);
    
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.3, 1.0);
	glShadeModel (GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_LINE_SMOOTH );
	glEnable( GL_POLYGON_SMOOTH );
    for(int i=0;i<numStars;i++){
        starRand[i][0] = rand();
        starRand[i][1] = rand();
        starRand[i][2] = rand();
    }
    initPlanets();
}

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

void drawErHuLuanZi(){
    drawBody(0, 2, 5, 7);
    drawEye(-3, 4.5, 2.2, 2);
    drawEye(3, 4.3, 3.0, 2.6);
    drawEyeball(-4, 5.5, 0.4);
    drawEyeball(5, 5.6, 0.5);
    drawMouth(0, 3);
    drawLeg(5.5,0,1,3);
    drawArm(6,1,1.2);
    
    glPushMatrix();
    
    if(planetList[6].pos<=planetList[6].distFromRef){
        planetList[6].speed = 0.2;
    }
    
    planetList[6].pos+=planetList[6].speed;
    glTranslatef(0, planetList[6].pos, 0);
    planetList[6].speed -= g;
    planetList[6].setAlpha(alphaRest);
    drawPlanet(planetList[6]);
    glPopMatrix();
}

void drawClock(){
    time_t timeNow = time (NULL);
    struct tm * timeinfo = localtime(&timeNow);

    drawPlanet(planetList[8]);
    
    glPushMatrix();
    int hour = timeinfo->tm_hour;
    if(hour>12)
        hour-=12;
    glRotatef( 360 - (float)hour/12*360  - (360/60.0) * (float)(timeinfo->tm_min+1)/60.0, 0.0, 0.0, 1.0);
    glTranslatef(0, planetList[0].distFromRef, 0);
    drawPlanet(planetList[0]);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef( 360-(float)timeinfo->tm_min/60*360, 0.0, 0.0, 1.0);
    glTranslatef(0, planetList[1].distFromRef, 0);
    drawPlanet(planetList[1]);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef( 360-(float)timeinfo->tm_sec/60*360, 0.0, 0.0, 1.0);
    glTranslatef(0, planetList[2].distFromRef, 0);
    drawPlanet(planetList[2]);
    glPopMatrix();
    
}

void drawSystem2(){

    planetList[3].setAlpha(alphaRest);
    drawPlanet(planetList[3]);
    
    glPushMatrix();
    
    float a = planetList[4].distFromRef;
    float b = planetList[4].distFromRef2;
    float angR = planetList[4].angle*DEG2RAD;
    
    glRotatef(planetList[4].angle, 0.0, 0.0, 1.0);
    glTranslatef(0,sqrt( a*a*b*b/(a*a*sin(angR)*sin(angR) + b*b*cos(angR)*cos(angR))), 0);
    planetList[4].angle += planetList[4].angularSpeed;
    planetList[4].setAlpha(alphaRest);
    drawPlanet(planetList[4]);
    
    glPushMatrix();
    
    glRotatef(planetList[5].angle, 0.0, 0.0, 1.0);
    glTranslatef(0,planetList[5].distFromRef, 0);
    planetList[5].angle += planetList[5].angularSpeed;
    planetList[5].setAlpha(alphaRest);
    drawPlanet(planetList[5]);
    glPopMatrix();
    
    glPopMatrix();


}

void drawAll(){
    
    glPushMatrix();
    
    glPushMatrix();
    glTranslatef(5, 5, 0);
    drawClock();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4, 4, 0);
    drawSystem2();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(2, -7, 0);
    glScalef(0.6, 0.6, 1);
    drawErHuLuanZi();
    glPopMatrix();
    
    glPopMatrix();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawStars();
    
	glPushMatrix();
    
	//controls transformation
	glScalef(k, k, k);	
	glTranslatef(tx, ty, 0);	
	glRotatef(alpha, 0, 0, 1);
    
	//draw stuff here!
    drawAll();
    
    
	glPopMatrix();
	glFlush ();
}

void idle()
{
	//update animation here
    
	
	glutPostRedisplay();	//after updating, draw the screen again
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
            
        case 't':
            alphaRest=1-alphaRest;
            if(alphaRest<0.5){
                tx-=5;
                ty-=5;
            }else{
                tx+=5;
                ty+=5;
            }
            glutPostRedisplay();
            break;
            
		default:
            break;
	}
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 2\n\n";
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
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);	
	//glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
    
	return 0;
}
