// CS3241Lab1.cpp : Defines the entry point for the console application.
//#include <cmath>
#include "math.h"
#include <iostream>
#include <fstream>
//gl headers for xcode
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>

// global variable
// pi value can be accessed using the built-in M_PI
bool m_Smooth = false;
bool m_Highlight = false;
GLfloat angle = 0;   /* in degrees */
GLfloat angle2 = 0;   /* in degrees */
GLfloat zoom = 1.0;
int mouseButton = 0;
int moving, startx, starty;

#define NO_OBJECT 4;
int current_object = 0;

using namespace std;

void setupLighting()
{
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    
    // Lights, material properties
    GLfloat	ambientProperties[]  = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat	diffuseProperties[]  = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat	specularProperties[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightPosition[] = {-100.0f,100.0f,100.0f,1.0f};
    
    glClearDepth( 1.0 );
    
    glLightfv( GL_LIGHT0, GL_POSITION, lightPosition);
    
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientProperties);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseProperties);
    glLightfv( GL_LIGHT0, GL_SPECULAR, specularProperties);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
    
    // Default : lighting
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    
}

void drawSphere(double r)
{
    
    float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    float mat_diffuse[] = {0.8f, 0.1f, 0.1f, 1.0f};
    float mat_specular[] =  {0.8, 0.8, 0.8, 0.8};
    float no_shininess = 0.0f;
    float shininess = 80.0f;
    //float mat_emission[] = {0.2f, 0.2f, 0.2f, 0.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    if(m_Highlight)
    {
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    } else {
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
    }
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    
    int i,j;
    int n = 20;
    for(i=0;i<n;i++)
        for(j=0;j<2*n;j++)
            if(m_Smooth)
            {
                glBegin(GL_POLYGON);
                
                // the normal of each vertex is actaully its own coordinates normalized for a sphere
                
                // your normal here
                glNormal3f(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
                glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
                // your normal here
                glNormal3f(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
                glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
                // your normal here
                glNormal3f(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
                glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
                // your normal here
                glNormal3f(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
                glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
                glEnd();
            } else	{
                glBegin(GL_POLYGON);
                // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
                glNormal3d(sin((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),cos((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),sin((j+0.5)*M_PI/n));
                glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
                glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
                glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
                glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
                glEnd();
            }
    
}

void drawSoccer(double r)
{
    
    float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    float mat_diffuse[] = {0.2f, 0.2f, 0.2f, 1.0f};
    float mat_specular[] =  {0.9, 0.9, 0.9, 1.0f};
    float no_shininess = 0.0f;
    float shininess = 60.0f;
    //float mat_emission[] = {0.2f, 0.2f, 0.2f, 0.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    if(m_Highlight)
    {
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    } else {
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
    }
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    
    int i,j;
    int n = 20;
    for(i=0;i<n;i++)
        for(j=0;j<2*n;j++)
            if(m_Smooth)
            {
                glBegin(GL_POLYGON);
                
                // the normal of each vertex is actaully its own coordinates normalized for a sphere
                
                // your normal here
                glNormal3f(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
                glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
                // your normal here
                glNormal3f(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
                glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
                // your normal here
                glNormal3f(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
                glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
                // your normal here
                glNormal3f(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
                glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
                glEnd();
            } else	{
                glBegin(GL_POLYGON);
                // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
                glNormal3d(sin((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),cos((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),sin((j+0.5)*M_PI/n));
                glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
                glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
                glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
                glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
                glEnd();
            }
    
}


void drawBox(float a, float b, float c)
{
    float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient[] = {0.0f, 0.4f, 0.4f, 1.0f};
    float mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
    float mat_specular[] =  {0.8, 0.8, 0.8, 0.8};
    float no_shininess = 0.0f;
    float shininess = 80.0f;
    //float mat_emission[] = {0.2f, 0.2f, 0.2f, 0.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    if(m_Highlight)
    {
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    } else {
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
    }
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    
    int i;
    
    if(m_Smooth)
    {
        glBegin(GL_POLYGON);
        glNormal3f(-1,-1,-1);
        glVertex3f(-a/2,-b/2,-c/2);
        glNormal3f(1,-1,-1);
        glVertex3f(a/2,-b/2,-c/2);
        glNormal3f(1,1,-1);
        glVertex3f(a/2,b/2,-c/2);
        glNormal3f(-1,1,-1);
        glVertex3f(-a/2,b/2,-c/2);
        glEnd();
        
        glBegin(GL_POLYGON);
        glNormal3f(1,-1,-1);
        glVertex3f(a/2,-b/2,-c/2);
        glNormal3f(1,-1,1);
        glVertex3f(a/2,-b/2,c/2);
        glNormal3f(1,1,1);
        glVertex3f(a/2,b/2,c/2);
        glNormal3f(1,1,-1);
        glVertex3f(a/2,b/2,-c/2);
        glEnd();
        
        glBegin(GL_POLYGON);
        glNormal3f(-1,-1,-1);
        glVertex3f(-a/2,-b/2,-c/2);
        glNormal3f(-1,-1,1);
        glVertex3f(-a/2,-b/2,c/2);
        glNormal3f(1,-1,1);
        glVertex3f(a/2,-b/2,c/2);
        glNormal3f(1,-1,-1);
        glVertex3f(a/2,-b/2,-c/2);
        glEnd();
        
        glBegin(GL_POLYGON);
        glNormal3f(-1,-1,-1);
        glVertex3f(-a/2,-b/2,-c/2);
        glNormal3f(-1,1,-1);
        glVertex3f(-a/2,b/2,-c/2);
        glNormal3f(-1,1,1);
        glVertex3f(-a/2,b/2,c/2);
        glNormal3f(-1,-1,1);
        glVertex3f(-a/2,-b/2,c/2);
        glEnd();
        
        glBegin(GL_POLYGON);
        glNormal3f(-1,1,-1);
        glVertex3f(-a/2,b/2,-c/2);
        glNormal3f(1,1,-1);
        glVertex3f(a/2,b/2,-c/2);
        glNormal3f(1,1,1);
        glVertex3f(a/2,b/2,c/2);
        glNormal3f(-1,1,1);
        glVertex3f(-a/2,b/2,c/2);
        glEnd();
        
        glBegin(GL_POLYGON);
        glNormal3f(-1,-1,1);
        glVertex3f(-a/2,-b/2,c/2);
        glNormal3f(-1,1,1);
        glVertex3f(-a/2,b/2,c/2);
        glNormal3f(1,1,1);
        glVertex3f(a/2,b/2,c/2);
        glNormal3f(1,-1,1);
        glVertex3f(a/2,-b/2,c/2);
        glEnd();
    } else	{
        glBegin(GL_POLYGON);
        glNormal3f(0,0,-1);
        glVertex3f(-a/2,-b/2,-c/2);
        glVertex3f(a/2,-b/2,-c/2);
        glVertex3f(a/2,b/2,-c/2);
        glVertex3f(-a/2,b/2,-c/2);
        glEnd();
        
        glBegin(GL_POLYGON);
        glNormal3f(1,0,0);
        glVertex3f(a/2,-b/2,-c/2);
        glVertex3f(a/2,-b/2,c/2);
        glVertex3f(a/2,b/2,c/2);
        glVertex3f(a/2,b/2,-c/2);
        glEnd();
        
        glBegin(GL_POLYGON);
        glNormal3f(0,-1,0);
        glVertex3f(-a/2,-b/2,-c/2);
        glVertex3f(-a/2,-b/2,c/2);
        glVertex3f(a/2,-b/2,c/2);
        glVertex3f(a/2,-b/2,-c/2);
        glEnd();
        
        glBegin(GL_POLYGON);
        glNormal3f(-1,0,0);
        glVertex3f(-a/2,-b/2,-c/2);
        glVertex3f(-a/2,b/2,-c/2);
        glVertex3f(-a/2,b/2,c/2);
        glVertex3f(-a/2,-b/2,c/2);
        glEnd();
        
        glBegin(GL_POLYGON);
        glNormal3f(0,1,0);
        glVertex3f(-a/2,b/2,-c/2);
        glVertex3f(a/2,b/2,-c/2);
        glVertex3f(a/2,b/2,c/2);
        glVertex3f(-a/2,b/2,c/2);
        glEnd();
        
        glBegin(GL_POLYGON);
        glNormal3f(0,0,1);
        glVertex3f(-a/2,-b/2,c/2);
        glVertex3f(-a/2,b/2,c/2);
        glVertex3f(a/2,b/2,c/2);
        glVertex3f(a/2,-b/2,c/2);
        glEnd();
    }
    
}

void drawMan(){
    // head
    glPushMatrix();
    glTranslatef(0, 1, 0);
    drawSphere(0.6);
    glPopMatrix();
    
    // body
    glPushMatrix();
    glRotatef(35, 0, 1, 0);
    drawBox(1, 0.8, 1);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glTranslatef(0, 0.8, 0);
    drawBox(0.3, 1, 0.3);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(0, 0.8, 0);
    drawBox(0.3, 1, 0.3);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(-170, 1, 0, 0);
    glTranslatef(0, 1, 0);
    drawBox(0.4, 1.3, 0.4);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(170, 1, 0, 0);
    glTranslatef(0, 1, 0);
    drawBox(0.4, 1.3, 0.4);
    glPopMatrix();
    
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(0, 0, -6);
    
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    
    glScalef(zoom,zoom,zoom);
    
    switch (current_object) {
        case 0:
            drawSphere(1);
            break;
        case 1:
            glPushMatrix();
            glRotatef(25, 1.0, 0.0, 0.0);
            glRotatef(25, 0.0, 1.0, 0.0);
            drawBox(1, 1, 1);
            glPopMatrix();
            break;
        case 2:
            glPushMatrix();
            glScalef(0.6, 0.6, 0.6);
            
            for (int i=0; i<20; i++) {
                glPushMatrix();
                glRotated(360/20*i, 0.2, 0.2, 0.2);
                
                drawSphere(0.8);
                glPushMatrix();
                drawBox(0.1, 5, 0.1);
                glTranslatef(0, 0, 2.5);
                drawSphere(0.3);
                glTranslatef(0, 0, -5);
                drawSphere(0.3);
                glPopMatrix();
                
                glPopMatrix();
            }
            glPopMatrix();
            break;
        case 3:
            
            for(int i=0; i<10;i++){
                
                glPushMatrix();
                glTranslatef(0, -0.5, 0);
                drawSoccer(0.3);
                glPopMatrix();
                
                glPushMatrix();
                glRotatef(360/10*i, 0, 1, 0);
                glTranslatef(0, 0, 2);
                glScalef(0.5, 0.5, 0.5);
                glRotatef(90, 0, 1, 0);
                drawMan();
                glPopMatrix();
                
            }
            break;
        default:
            break;
    };
    glPopMatrix();
    glutSwapBuffers ();
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
        case 'p':
        case 'P':
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            break;
        case 'w':
        case 'W':
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            break;
        case 'v':
        case 'V':
            glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
            break;
        case 's':
        case 'S':
            m_Smooth = !m_Smooth;
            break;
        case 'h':
        case 'H':
            m_Highlight = !m_Highlight;
            break;
            
        case '1':
        case '2':
        case '3':
        case '4':
            current_object = key - '1';
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
    if (state == GLUT_DOWN) {
        mouseButton = button;
        moving = 1;
        startx = x;
        starty = y;
    }
    if (state == GLUT_UP) {
        mouseButton = button;
        moving = 0;
    }
}

void motion(int x, int y)
{
    if (moving) {
        if(mouseButton==GLUT_LEFT_BUTTON)
        {
            angle = angle + (x - startx);
            angle2 = angle2 + (y - starty);
        }
        else zoom += ((y-starty)*0.001);
        startx = x;
        starty = y;
        glutPostRedisplay();
    }
    
}

int main(int argc, char **argv)
{
    cout<<"CS3241 Lab 3"<< endl<< endl;
    
    cout << "1-4: Draw different objects"<<endl;
    cout << "S: Toggle Smooth Shading"<<endl;
    cout << "H: Toggle Highlight"<<endl;
    cout << "W: Draw Wireframe"<<endl;
    cout << "P: Draw Polygon"<<endl;
    cout << "V: Draw Vertices"<<endl;
    cout << "Q: Quit" <<endl<< endl;
    
    cout << "Left mouse click and drag: rotate the object"<<endl;
    cout << "Right mouse click and drag: zooming"<<endl;
    
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (600, 600);
    glutInitWindowPosition (50, 50);
    glutCreateWindow ("CS3241 Assignment 3");
    glClearColor (1.0,1.0,1.0, 1.0);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    setupLighting();
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    
    glMatrixMode(GL_PROJECTION);
    gluPerspective( /* field of view in degree */ 40.0,
                   /* aspect ratio */ 1.0,
                   /* Z near */ 1.0, /* Z far */ 80.0);
    glMatrixMode(GL_MODELVIEW);
    glutMainLoop();
    
    return 0;
}