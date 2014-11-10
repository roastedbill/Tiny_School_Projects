#include "drawHouses.h"
#define GL_PI 3.141592653


void A0105649House(GLuint texSet[])
{
	//plot dimension
	//x: -4:4
	//y: 0:12
	//z: -4:4
	
	//bounding volume
	glPushMatrix();
	glTranslatef(0, 6, 0);
	glScalef(8, 12, 8);	
	glColor3f(1.0, 1.0, 1.0);
	glutWireCube(1);
    glPopMatrix();
    
    glEnable(GL_TEXTURE_2D);
    
    // draw base
    glBindTexture( GL_TEXTURE_2D, texSet[19] );
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(-3.5, 1, 2);
    glTexCoord2d(1.0,0.0);glVertex3f(-3.5, 1, -3);
    glTexCoord2d(1.0,1.0);glVertex3f(3.5, 1, -3);
    glTexCoord2d(0.0,1.0);glVertex3f(3.5, 1, 2);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(-3.5, 1, -3);
    glTexCoord2d(1.0,0.0);glVertex3f(-3.5, 0, -3);
    glTexCoord2d(1.0,1.0);glVertex3f(3.5, 0, -3);
    glTexCoord2d(0.0,1.0);glVertex3f(3.5, 1, -3);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(-3.5, 1, 2);
    glTexCoord2d(1.0,0.0);glVertex3f(-3.5, 0, 2);
    glTexCoord2d(1.0,1.0);glVertex3f(3.5, 0, 2);
    glTexCoord2d(0.0,1.0);glVertex3f(3.5, 1, 2);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(-3.5, 1, -3);
    glTexCoord2d(1.0,0.0);glVertex3f(-3.5, 0, -3);
    glTexCoord2d(1.0,1.0);glVertex3f(-3.5, 0, 2);
    glTexCoord2d(0.0,1.0);glVertex3f(-3.5, 1, 2);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(3.5, 1, -3);
    glTexCoord2d(1.0,0.0);glVertex3f(3.5, 0, -3);
    glTexCoord2d(1.0,1.0);glVertex3f(3.5, 0, 2);
    glTexCoord2d(0.0,1.0);glVertex3f(3.5, 1, 2);
    glEnd();
    
    glColor4f(1, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // stairs
    glBindTexture( GL_TEXTURE_2D, texSet[19] );
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(1.5, 0.8, 2);
    glTexCoord2d(1.0,0.0);glVertex3f(1.5, 0.8, 2.5);
    glTexCoord2d(1.0,1.0);glVertex3f(3, 0.8, 2.5);
    glTexCoord2d(0.0,1.0);glVertex3f(3, 0.8, 2);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(1.5, 0.8, 2.5);
    glTexCoord2d(1.0,0.0);glVertex3f(1.5, 0, 2.5);
    glTexCoord2d(1.0,1.0);glVertex3f(3, 0, 2.5);
    glTexCoord2d(0.0,1.0);glVertex3f(3, 0.8, 2.5);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(1.5, 0.8, 2.5);
    glTexCoord2d(1.0,0.0);glVertex3f(1.5, 0, 2.5);
    glTexCoord2d(1.0,1.0);glVertex3f(1.5, 0, 2);
    glTexCoord2d(0.0,1.0);glVertex3f(1.5, 0.8, 2);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(3, 0.8, 2.5);
    glTexCoord2d(1.0,0.0);glVertex3f(3, 0, 2.5);
    glTexCoord2d(1.0,1.0);glVertex3f(3, 0, 2);
    glTexCoord2d(0.0,1.0);glVertex3f(3, 0.8, 2);
    glEnd();
    
    glColor4f(1, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glBindTexture( GL_TEXTURE_2D, texSet[19] );
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(1.5, 0.6, 2.5);
    glTexCoord2d(1.0,0.0);glVertex3f(1.5, 0.6, 3);
    glTexCoord2d(1.0,1.0);glVertex3f(3, 0.6, 3);
    glTexCoord2d(0.0,1.0);glVertex3f(3, 0.6, 2.5);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(1.5, 0.6, 3);
    glTexCoord2d(1.0,0.0);glVertex3f(1.5, 0, 3);
    glTexCoord2d(1.0,1.0);glVertex3f(3, 0, 3);
    glTexCoord2d(0.0,1.0);glVertex3f(3, 0.6, 3);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(1.5, 0.6, 3);
    glTexCoord2d(1.0,0.0);glVertex3f(1.5, 0, 3);
    glTexCoord2d(1.0,1.0);glVertex3f(1.5, 0, 2.5);
    glTexCoord2d(0.0,1.0);glVertex3f(1.5, 0.6, 2.5);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(3, 0.6, 3);
    glTexCoord2d(1.0,0.0);glVertex3f(3, 0, 3);
    glTexCoord2d(1.0,1.0);glVertex3f(3, 0, 2.5);
    glTexCoord2d(0.0,1.0);glVertex3f(3, 0.6, 2.5);
    glEnd();
    
    glColor4f(1, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glBindTexture( GL_TEXTURE_2D, texSet[19] );
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(1.5, 0.4, 3);
    glTexCoord2d(1.0,0.0);glVertex3f(1.5, 0.4, 3.5);
    glTexCoord2d(1.0,1.0);glVertex3f(3, 0.4, 3.5);
    glTexCoord2d(0.0,1.0);glVertex3f(3, 0.4, 3);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(1.5, 0.4, 3.5);
    glTexCoord2d(1.0,0.0);glVertex3f(1.5, 0, 3.5);
    glTexCoord2d(1.0,1.0);glVertex3f(3, 0, 3.5);
    glTexCoord2d(0.0,1.0);glVertex3f(3, 0.4, 3.5);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(1.5, 0.4, 3.5);
    glTexCoord2d(1.0,0.0);glVertex3f(1.5, 0, 3.5);
    glTexCoord2d(1.0,1.0);glVertex3f(1.5, 0, 3);
    glTexCoord2d(0.0,1.0);glVertex3f(1.5, 0.4, 3);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(3, 0.4, 3.5);
    glTexCoord2d(1.0,0.0);glVertex3f(3, 0, 3.5);
    glTexCoord2d(1.0,1.0);glVertex3f(3, 0, 3);
    glTexCoord2d(0.0,1.0);glVertex3f(3, 0.4, 3);
    glEnd();
    
    glColor4f(1, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glBindTexture( GL_TEXTURE_2D, texSet[19] );
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(1.5, 0.2, 3.5);
    glTexCoord2d(1.0,0.0);glVertex3f(1.5, 0.2, 4);
    glTexCoord2d(1.0,1.0);glVertex3f(3, 0.2, 4);
    glTexCoord2d(0.0,1.0);glVertex3f(3, 0.2, 3.5);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(1.5, 0.2, 4);
    glTexCoord2d(1.0,0.0);glVertex3f(1.5, 0, 4);
    glTexCoord2d(1.0,1.0);glVertex3f(3, 0, 4);
    glTexCoord2d(0.0,1.0);glVertex3f(3, 0.2, 4);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(1.5, 0.2, 4);
    glTexCoord2d(1.0,0.0);glVertex3f(1.5, 0, 4);
    glTexCoord2d(1.0,1.0);glVertex3f(1.5, 0, 3.5);
    glTexCoord2d(0.0,1.0);glVertex3f(1.5, 0.2, 3.5);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(3, 0.2, 4);
    glTexCoord2d(1.0,0.0);glVertex3f(3, 0, 4);
    glTexCoord2d(1.0,1.0);glVertex3f(3, 0, 3.5);
    glTexCoord2d(0.0,1.0);glVertex3f(3, 0.2, 3.5);
    glEnd();
    
    glColor4f(1, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // cylinder building
    float s, t, r=1.5, h=4.0;
    glPushMatrix();
    glTranslatef(2, 1, -0.5);
    glBindTexture(GL_TEXTURE_2D, texSet[14] );
    for (t=0.0;t<1.0;t+=0.05)
        for(s=0.0;s<1.0;s+=0.05) {
            glBegin(GL_POLYGON);
            glTexCoord2f(s,t);glVertex3f(r*cos(2*GL_PI*s), t*h, r*sin(2*GL_PI*s));
            glTexCoord2f(s+0.05,t); glVertex3f(r*cos(2*GL_PI*(s+0.05)), t*h, r*sin(2*GL_PI*(s+0.05)));
            glTexCoord2f(s+0.05,t+0.05); glVertex3f(r*cos(2*GL_PI*(s+0.05)), (t+0.05)*h, r*sin(2*GL_PI*(s+0.05)));
            glTexCoord2f(s,t+0.05); glVertex3f(r*cos(2*GL_PI*s), (t+0.05)*h, r*sin(2*GL_PI*s));
            glEnd();
        }
    glColor4f(1, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
    
    // --roof
    glBindTexture( GL_TEXTURE_2D, texSet[2] );
    
    glBegin(GL_POLYGON);
    glTexCoord2d(0.5,1.0);glVertex3f(2, 7, -0.5);
    glTexCoord2d(0.0,0.0);glVertex3f(0.5, 5, 1);
    glTexCoord2d(1.0,1.0);glVertex3f(3.5, 5, 1);
    glEnd();
    
    glBegin(GL_POLYGON);
    glTexCoord2d(0.5,1.0);glVertex3f(2, 7, -0.5);
    glTexCoord2d(0.0,0.0);glVertex3f(3.5, 5, 1);
    glTexCoord2d(1.0,1.0);glVertex3f(3.5, 5, -2);
    glEnd();
    
    glBegin(GL_POLYGON);
    glTexCoord2d(0.5,1.0);glVertex3f(2, 7, -0.5);
    glTexCoord2d(0.0,0.0);glVertex3f(0.5, 5, -2);
    glTexCoord2d(1.0,1.0);glVertex3f(3.5, 5, -2);
    glEnd();
    
    glBegin(GL_POLYGON);
    glTexCoord2d(0.5,1.0);glVertex3f(2, 7, -0.5);
    glTexCoord2d(0.0,0.0);glVertex3f(0.5, 5, -2);
    glTexCoord2d(1.0,1.0);glVertex3f(0.5, 5, 1);
    glEnd();
    
    glColor4f(1, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, 0);

    
    // cube building
    glBindTexture( GL_TEXTURE_2D, texSet[2] );
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(-2.5, 3, -2);
    glTexCoord2d(1.0,0.0);glVertex3f(-2.5, 0, -2);
    glTexCoord2d(1.0,1.0);glVertex3f(1, 0, -2);
    glTexCoord2d(0.0,1.0);glVertex3f(1, 3, -2);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(-2.5, 3, 1);
    glTexCoord2d(1.0,0.0);glVertex3f(-2.5, 0, 1);
    glTexCoord2d(1.0,1.0);glVertex3f(1, 0, 1);
    glTexCoord2d(0.0,1.0);glVertex3f(1, 3, 1);
    glEnd();
    
    glBegin(GL_POLYGON);
    glTexCoord2d(0.0,0.0);glVertex3f(-2.5, 3, -2);
    glTexCoord2d(1.0,0.0);glVertex3f(-2.5, 0, -2);
    glTexCoord2d(1.0,0.8);glVertex3f(-2.5, 0, 1);
    glTexCoord2d(0.0,0.8);glVertex3f(-2.5, 3, 1);
    glTexCoord2d(0.5,1.0);glVertex3f(-2.5, 3.5, -0.5);
    glEnd();
    
    glBegin(GL_POLYGON);
    glTexCoord2d(0.0,0.0);glVertex3f(1, 3, -2);
    glTexCoord2d(1.0,0.0);glVertex3f(1, 0, -2);
    glTexCoord2d(1.0,0.8);glVertex3f(1, 0, 1);
    glTexCoord2d(0.0,0.8);glVertex3f(1, 3, 1);
    glTexCoord2d(0.5,1.0);glVertex3f(1, 3.5, -0.5);
    glEnd();
    
    glColor4f(1, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, 0);
    
        // --- roof
    glBindTexture( GL_TEXTURE_2D, texSet[14] );
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(-2.5, 3.5, -0.5);
    glTexCoord2d(1.0,0.0);glVertex3f(-2.5, 3, 1);
    glTexCoord2d(1.0,1.0);glVertex3f(1, 3, 1);
    glTexCoord2d(0.0,1.0);glVertex3f(1, 3.5, -0.5);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(-2.5, 3, -2);
    glTexCoord2d(1.0,0.0);glVertex3f(-2.5, 3.5, -0.5);
    glTexCoord2d(1.0,1.0);glVertex3f(1, 3.5, -0.5);
    glTexCoord2d(0.0,1.0);glVertex3f(1, 3, -2);
    glEnd();
    
    glColor4f(1, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, 0);
    
        // --- windows
    glBindTexture( GL_TEXTURE_2D, texSet[28] );
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(-2, 1.5, 1);
    glTexCoord2d(1.0,0.0);glVertex3f(-1, 1.5, 1);
    glTexCoord2d(1.0,1.0);glVertex3f(-1, 2.5, 1);
    glTexCoord2d(0.0,1.0);glVertex3f(-2, 2.5, 1);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(-0.5, 1.5, 1);
    glTexCoord2d(1.0,0.0);glVertex3f(0.5, 1.5, 1);
    glTexCoord2d(1.0,1.0);glVertex3f(0.5, 2.5, 1);
    glTexCoord2d(0.0,1.0);glVertex3f(-0.5, 2.5, 1);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(-2, 1.5, -2);
    glTexCoord2d(1.0,0.0);glVertex3f(-1, 1.5, -2);
    glTexCoord2d(1.0,1.0);glVertex3f(-1, 2.5, -2);
    glTexCoord2d(0.0,1.0);glVertex3f(-2, 2.5, -2);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(-0.5, 1.5, -2);
    glTexCoord2d(1.0,0.0);glVertex3f(0.5, 1.5, -2);
    glTexCoord2d(1.0,1.0);glVertex3f(0.5, 2.5, -2);
    glTexCoord2d(0.0,1.0);glVertex3f(-0.5, 2.5, -2);
    glEnd();
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);glVertex3f(-2.5, 1.5, 0);
    glTexCoord2d(1.0,0.0);glVertex3f(-2.5, 1.5, -1);
    glTexCoord2d(1.0,1.0);glVertex3f(-2.5, 2.5, -1);
    glTexCoord2d(0.0,1.0);glVertex3f(-2.5, 2.5, 0);
    glEnd();
    
    glColor4f(1, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, 0);
}