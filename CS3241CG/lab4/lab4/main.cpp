// CS3241Lab1.cpp : Defines the entry point for the console application.
//#include <cmath>
#include "math.h"
#include <iostream>
#include <fstream>

/* header files for xcode */
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>

/* header files for lab machine */
//#include "GL\glut.h"

#define MAXPTNO 1000
#define NLINESEGMENT 32
#define NOBJECTONCURVE 8
#define DEG2RAD 3.14159/180.0

using namespace std;

// Global variables that you can use
struct Point {
    int x,y;
};

// Storage of control points
int nPt = 0;
Point ptList[MAXPTNO];

// Display options
bool displayControlPoints = true;
bool displayControlLines = true;
bool displayTangentVectors = false;
bool displayObjects = false;
bool C1Continuity = false;

GLfloat PI = 3.14;
float alpha = 0.0, k=1;
float tx = 0.0, ty=0.0;

void drawArc(double cx, double cy, float r, int startDeg, int endDeg){
    int i;
    glColor3f(0, 0, 0);
    glLineWidth(10);
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
    glLineWidth(10);
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
    glLineWidth(10);
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
    glLineWidth(10);
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
    glLineWidth(10);
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
    glLineWidth(10);
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
    glLineWidth(10);
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

void drawRightArrow()
{
    glColor3f(0,1,0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0,0);
    glVertex2f(100,0);
    glVertex2f(95,5);
    glVertex2f(100,0);
    glVertex2f(95,-5);
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    if(displayControlPoints)
    {
        
        glPointSize(5);
        glBegin(GL_POINTS);
        for(int i=0;i<nPt; i++)
        {
            glColor3f(0,0,0);
            glVertex2d(ptList[i].x,ptList[i].y);
        }
        glEnd();
        glPointSize(1);
        
    }
    
    if(displayControlLines)
    {
        glColor3f(0,1,0);
        for(int i=0;i<nPt-1; i++)
        {
            glBegin(GL_LINES);
            glVertex2d(ptList[i].x, ptList[i].y);
            glVertex2d(ptList[i+1].x, ptList[i+1].y);
            glEnd();
        }
    }
    
    
    for(int i=0; i<nPt; i++) // draw degree 3 Bezier Curves
    {
        if(i>0 && i%3==0)
        {
            if(C1Continuity && i>3){
                glColor3f(0.8,0.8,0.8);
            }else{
                glColor3f(0,0,1);
            }
            glBegin(GL_LINE_STRIP);
            for(int t=0; t<=100; t++)
            {
                glVertex2d((1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].x+
                           3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*ptList[i-2].x+
                           3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].x+
                           (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].x,
                           (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].y+
                           3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*ptList[i-2].y+
                           3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].y+
                           (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].y
                           );
            }
            glEnd();
            
            if(C1Continuity && i>3){
                glColor3f(1,0,0);
                glBegin(GL_LINE_STRIP);
                for(int t=0; t<=100; t++)
                {
                    glVertex2d(
                               (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].x+
                               3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*(2*ptList[i-3].x-ptList[i-4].x)+
                               3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].x+
                               (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].x,
                               (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].y+
                               3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*(2*ptList[i-3].y-ptList[i-4].y)+
                               3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].y+
                               (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].y
                               );
                    
                }
                glEnd();
            }
            
        }
    }
    
    if(displayTangentVectors)
    {
        for(int i=0; i<nPt; i++) // draw degree 3 Bezier Curves
        {
            if(C1Continuity)
            {
                if(i==3)
                {
                    for(int t=1; t<=100; t++){
                        if(nPt>3 && ((100*i+t)%((nPt-1)/3*100/NOBJECTONCURVE)==0))
                        {
                            // TODO: Add C1 vector
                            double a =180/3.141592653*atan2f(
                                                             (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].y+
                                                             3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*ptList[i-2].y+
                                                             3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].y+
                                                             (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].y-
                                                             (1-(t-1)/100.0)*(1-(t-1)/100.0)*(1-(t-1)/100.0)*ptList[i-3].y-
                                                             3*(1-(t-1)/100.0)*(1-(t-1)/100.0)*((t-1)/100.0)*ptList[i-2].y-
                                                             3*(1-(t-1)/100.0)*((t-1)/100.0)*((t-1)/100.0)*ptList[i-1].y-
                                                             (t-1)/100.0*(t-1)/100.0*(t-1)/100.0*ptList[i].y,
                                                             (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].x+
                                                             3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*ptList[i-2].x+
                                                             3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].x+
                                                             (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].x-
                                                             (1-(t-1)/100.0)*(1-(t-1)/100.0)*(1-(t-1)/100.0)*ptList[i-3].x-
                                                             3*(1-(t-1)/100.0)*(1-(t-1)/100.0)*((t-1)/100.0)*ptList[i-2].x-
                                                             3*(1-(t-1)/100.0)*(t-1)/100.0*(t-1)/100.0*ptList[i-1].x-
                                                             (t-1)/100.0*(t-1)/100.0*(t-1)/100.0*ptList[i].x);
                            glPushMatrix();
                            
                            
                            glTranslatef((1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].x+
                                         3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*ptList[i-2].x+
                                         3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].x+
                                         (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].x,
                                         (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].y+
                                         3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*ptList[i-2].y+
                                         3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].y+
                                         (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].y, 0);
                            
                            
                            glRotatef(a,0, 0, 1);
                            drawRightArrow();
                            glPopMatrix();
                        }
                    }
                }
                else if(i>3 && i%3==0)
                {
                    for(int t=1; t<=100; t++){
                        if(nPt>3 && ((100*i+t)%((nPt-1)/3*100/NOBJECTONCURVE)==0))
                        {
                            double a =180/3.141592653*atan2f(
                                                             (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].y+
                                                             3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*(2*ptList[i-3].y-ptList[i-4].y)+
                                                             3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].y+
                                                             (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].y-
                                                             (1-(t-1)/100.0)*(1-(t-1)/100.0)*(1-(t-1)/100.0)*ptList[i-3].y-
                                                             3*(1-(t-1)/100.0)*(1-(t-1)/100.0)*((t-1)/100.0)*(2*ptList[i-3].y-ptList[i-4].y)-
                                                             3*(1-(t-1)/100.0)*((t-1)/100.0)*((t-1)/100.0)*ptList[i-1].y-
                                                             (t-1)/100.0*(t-1)/100.0*(t-1)/100.0*ptList[i].y,
                                                             (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].x+
                                                             3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*(2*ptList[i-3].x-ptList[i-4].x)+
                                                             3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].x+
                                                             (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].x-
                                                             (1-(t-1)/100.0)*(1-(t-1)/100.0)*(1-(t-1)/100.0)*ptList[i-3].x-
                                                             3*(1-(t-1)/100.0)*(1-(t-1)/100.0)*((t-1)/100.0)*(2*ptList[i-3].x-ptList[i-4].x)-
                                                             3*(1-(t-1)/100.0)*(t-1)/100.0*(t-1)/100.0*ptList[i-1].x-
                                                             (t-1)/100.0*(t-1)/100.0*(t-1)/100.0*ptList[i].x);
                            glPushMatrix();
                            glTranslatef((1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].x+
                                         3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*(2*ptList[i-3].x-ptList[i-4].x)+
                                         3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].x+
                                         (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].x,
                                         (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].y+
                                         3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*(2*ptList[i-3].y-ptList[i-4].y)+
                                         3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].y+
                                         (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].y, 0);
                            glRotatef(a,0, 0, 1);
                            drawRightArrow();
                            glPopMatrix();
                        }
                        
                    }
                }
                
            }
            else
            {
                if(i>0 && i%3==0)
                {
                    for(int t=1; t<=100; t++){
                        if(nPt>3 && ((100*i+t)%((nPt-1)/3*100/NOBJECTONCURVE)==0))
                        {
                            // TODO: Add C1 vector
                            double a =180/3.141592653*atan2f(
                                                             (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].y+
                                                             3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*ptList[i-2].y+
                                                             3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].y+
                                                             (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].y-
                                                             (1-(t-1)/100.0)*(1-(t-1)/100.0)*(1-(t-1)/100.0)*ptList[i-3].y-
                                                             3*(1-(t-1)/100.0)*(1-(t-1)/100.0)*((t-1)/100.0)*ptList[i-2].y-
                                                             3*(1-(t-1)/100.0)*((t-1)/100.0)*((t-1)/100.0)*ptList[i-1].y-
                                                             (t-1)/100.0*(t-1)/100.0*(t-1)/100.0*ptList[i].y,
                                                             (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].x+
                                                             3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*ptList[i-2].x+
                                                             3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].x+
                                                             (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].x-
                                                             (1-(t-1)/100.0)*(1-(t-1)/100.0)*(1-(t-1)/100.0)*ptList[i-3].x-
                                                             3*(1-(t-1)/100.0)*(1-(t-1)/100.0)*((t-1)/100.0)*ptList[i-2].x-
                                                             3*(1-(t-1)/100.0)*(t-1)/100.0*(t-1)/100.0*ptList[i-1].x-
                                                             (t-1)/100.0*(t-1)/100.0*(t-1)/100.0*ptList[i].x);
                            glPushMatrix();
                            
                            
                            glTranslatef((1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].x+
                                         3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*ptList[i-2].x+
                                         3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].x+
                                         (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].x,
                                         (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].y+
                                         3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*ptList[i-2].y+
                                         3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].y+
                                         (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].y, 0);
                            
                            
                            glRotatef(a,0, 0, 1);
                            drawRightArrow();
                            glPopMatrix();
                        }
                    }
                    
                }
            }
            
        }
    }
    
    if(displayObjects)
    {
        for(int i=0; i<nPt; i++) // draw degree 3 Bezier Curves
        {
            if(C1Continuity)
            {
                if(i==3)
                {
                    for(int t=1; t<=100; t++){
                        if(nPt>3 && ((100*i+t)%((nPt-1)/3*100/NOBJECTONCURVE)==0))
                        {
                            // TODO: Add C1 vector
                            double a =180/3.141592653*atan2f(
                                                             (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].y+
                                                             3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*ptList[i-2].y+
                                                             3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].y+
                                                             (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].y-
                                                             (1-(t-1)/100.0)*(1-(t-1)/100.0)*(1-(t-1)/100.0)*ptList[i-3].y-
                                                             3*(1-(t-1)/100.0)*(1-(t-1)/100.0)*((t-1)/100.0)*ptList[i-2].y-
                                                             3*(1-(t-1)/100.0)*((t-1)/100.0)*((t-1)/100.0)*ptList[i-1].y-
                                                             (t-1)/100.0*(t-1)/100.0*(t-1)/100.0*ptList[i].y,
                                                             (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].x+
                                                             3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*ptList[i-2].x+
                                                             3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].x+
                                                             (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].x-
                                                             (1-(t-1)/100.0)*(1-(t-1)/100.0)*(1-(t-1)/100.0)*ptList[i-3].x-
                                                             3*(1-(t-1)/100.0)*(1-(t-1)/100.0)*((t-1)/100.0)*ptList[i-2].x-
                                                             3*(1-(t-1)/100.0)*(t-1)/100.0*(t-1)/100.0*ptList[i-1].x-
                                                             (t-1)/100.0*(t-1)/100.0*(t-1)/100.0*ptList[i].x);
                            glPushMatrix();
                            
                            
                            glTranslatef((1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].x+
                                         3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*ptList[i-2].x+
                                         3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].x+
                                         (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].x,
                                         (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].y+
                                         3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*ptList[i-2].y+
                                         3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].y+
                                         (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].y, 0);
                            
                            
                            glRotatef(a,0, 0, 1);
                            glScalef(10, 10, 1);
                            drawErHuLuanZi();
                            glPopMatrix();
                        }
                    }
                }
                else if(i>3 && i%3==0)
                {
                    for(int t=1; t<=100; t++){
                        if(nPt>3 && ((100*i+t)%((nPt-1)/3*100/NOBJECTONCURVE)==0))
                        {
                            double a =180/3.141592653*atan2f(
                                                             (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].y+
                                                             3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*(2*ptList[i-3].y-ptList[i-4].y)+
                                                             3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].y+
                                                             (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].y-
                                                             (1-(t-1)/100.0)*(1-(t-1)/100.0)*(1-(t-1)/100.0)*ptList[i-3].y-
                                                             3*(1-(t-1)/100.0)*(1-(t-1)/100.0)*((t-1)/100.0)*(2*ptList[i-3].y-ptList[i-4].y)-
                                                             3*(1-(t-1)/100.0)*((t-1)/100.0)*((t-1)/100.0)*ptList[i-1].y-
                                                             (t-1)/100.0*(t-1)/100.0*(t-1)/100.0*ptList[i].y,
                                                             (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].x+
                                                             3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*(2*ptList[i-3].x-ptList[i-4].x)+
                                                             3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].x+
                                                             (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].x-
                                                             (1-(t-1)/100.0)*(1-(t-1)/100.0)*(1-(t-1)/100.0)*ptList[i-3].x-
                                                             3*(1-(t-1)/100.0)*(1-(t-1)/100.0)*((t-1)/100.0)*(2*ptList[i-3].x-ptList[i-4].x)-
                                                             3*(1-(t-1)/100.0)*(t-1)/100.0*(t-1)/100.0*ptList[i-1].x-
                                                             (t-1)/100.0*(t-1)/100.0*(t-1)/100.0*ptList[i].x);
                            glPushMatrix();
                            glTranslatef((1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].x+
                                         3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*(2*ptList[i-3].x-ptList[i-4].x)+
                                         3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].x+
                                         (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].x,
                                         (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].y+
                                         3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*(2*ptList[i-3].y-ptList[i-4].y)+
                                         3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].y+
                                         (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].y, 0);
                            glRotatef(a, 0, 0, 1);
                            glScalef(10, 10, 1);
                            drawErHuLuanZi();
                            glPopMatrix();
                        }
                        
                    }
                }
                
            }
            else
            {
                if(i>0 && i%3==0)
                {
                    for(int t=1; t<=100; t++){
                        if(nPt>3 && ((100*i+t)%((nPt-1)/3*100/NOBJECTONCURVE)==0))
                        {
                            // TODO: Add C1 vector
                            double a =180/3.141592653*atan2f(
                                                             (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].y+
                                                             3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*ptList[i-2].y+
                                                             3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].y+
                                                             (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].y-
                                                             (1-(t-1)/100.0)*(1-(t-1)/100.0)*(1-(t-1)/100.0)*ptList[i-3].y-
                                                             3*(1-(t-1)/100.0)*(1-(t-1)/100.0)*((t-1)/100.0)*ptList[i-2].y-
                                                             3*(1-(t-1)/100.0)*((t-1)/100.0)*((t-1)/100.0)*ptList[i-1].y-
                                                             (t-1)/100.0*(t-1)/100.0*(t-1)/100.0*ptList[i].y,
                                                             (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].x+
                                                             3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*ptList[i-2].x+
                                                             3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].x+
                                                             (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].x-
                                                             (1-(t-1)/100.0)*(1-(t-1)/100.0)*(1-(t-1)/100.0)*ptList[i-3].x-
                                                             3*(1-(t-1)/100.0)*(1-(t-1)/100.0)*((t-1)/100.0)*ptList[i-2].x-
                                                             3*(1-(t-1)/100.0)*(t-1)/100.0*(t-1)/100.0*ptList[i-1].x-
                                                             (t-1)/100.0*(t-1)/100.0*(t-1)/100.0*ptList[i].x);
                            glPushMatrix();
                            
                            
                            glTranslatef((1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].x+
                                         3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*ptList[i-2].x+
                                         3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].x+
                                         (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].x,
                                         (1-t/100.0)*(1-t/100.0)*(1-t/100.0)*ptList[i-3].y+
                                         3*(1-t/100.0)*(1-t/100.0)*(t/100.0)*ptList[i-2].y+
                                         3*(1-t/100.0)*(t/100.0)*(t/100.0)*ptList[i-1].y+
                                         (t/100.0)*(t/100.0)*(t/100.0)*ptList[i].y, 0);
                            
                            
                            glRotatef(a,0, 0, 1);
                            glScalef(10, 10, 1);
                            drawErHuLuanZi();
                            glPopMatrix();
                        }
                    }
                    
                }
            }
            
        }
    }
    
    
    glPopMatrix();
    glutSwapBuffers ();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,w,h,0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init(void)
{
    glClearColor (1.0,1.0,1.0, 1.0);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void readFile()
{
    std::ifstream file;
    file.open("savefile.txt");
    file >> nPt;
    
    if(nPt>MAXPTNO)
    {
        cout << "Error: File contains more than the maximum number of points." << endl;
        nPt = MAXPTNO;
    }
    
    for(int i=0;i<nPt;i++)
    {
        file >> ptList[i].x;
        file >> ptList[i].y;
    }
    file.close();// is not necessary because the destructor closes the open file by default
}

void writeFile()
{
    std::ofstream file;
    file.open("savefile.txt");
    file << nPt << endl;
    
    for(int i=0;i<nPt;i++)
    {
        file << ptList[i].x << " ";
        file << ptList[i].y << endl;
    }
    file.close();// is not necessary because the destructor closes the open file by default
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
        case 'r':
        case 'R':
        readFile();
        break;
        
        case 'w':
        case 'W':
        writeFile();
        break;
        
        case 'T':
        case 't':
        displayTangentVectors = !displayTangentVectors;
        break;
        
        case 'o':
        case 'O':
        displayObjects = !displayObjects;
        break;
        
        case 'p':
        case 'P':
        displayControlPoints = !displayControlPoints;
        break;
        
        case 'L':
        case 'l':
        displayControlLines = !displayControlLines;
        break;
        
        case 'C':
        case 'c':
        C1Continuity = !C1Continuity;
        break;
        
        case 'e':
        case 'E':
        nPt = 0;
        break;
        
        case 'Q':
        case 'q':
        exit(0);
        break;
        
        default:
        break;
    }
    
    glutPostRedisplay();
}



void mouse(int button, int state, int x, int y)
{
    /*button: GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON */
    /*state: GLUT_UP or GLUT_DOWN */
    enum
    {
        MOUSE_LEFT_BUTTON = 0,
        MOUSE_MIDDLE_BUTTON = 1,
        MOUSE_RIGHT_BUTTON = 2,
        MOUSE_SCROLL_UP = 3,
        MOUSE_SCROLL_DOWN = 4
    };
    if((button == MOUSE_LEFT_BUTTON)&&(state == GLUT_UP))
    {
        if(nPt==MAXPTNO)
        {
            cout << "Error: Exceeded the maximum number of points." << endl;
            return;
        }
        ptList[nPt].x=x;
        ptList[nPt].y=y;
        nPt++;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    cout<<"CS3241 Lab 4"<< endl<< endl;
    cout << "Left mouse click: Add a control point"<<endl;
    cout << "Q: Quit" <<endl;
    cout << "P: Toggle displaying control points" <<endl;
    cout << "L: Toggle displaying control lines" <<endl;
    cout << "E: Erase all points (Clear)" << endl;
    cout << "C: Toggle C1 continuity" <<endl;
    cout << "T: Toggle displaying tangent vectors" <<endl;
    cout << "O: Toggle displaying objects" <<endl;
    cout << "R: Read in control points from \"savefile.txt\"" <<endl;
    cout << "W: Write control points to \"savefile.txt\"" <<endl;
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (600, 600);
    glutInitWindowPosition (50, 50);
    glutCreateWindow ("CS3241 Assignment 4");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    
    return 0;
}
