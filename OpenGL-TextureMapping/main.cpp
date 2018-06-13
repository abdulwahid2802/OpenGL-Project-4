//
//  main.cpp
//  OpenGL-TextureMapping
//
//  Created by mac on 6/13/18.
//  Copyright © 2018 mac. All rights reserved.
//

// For Windows
/*
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
*/

#include <GLUT/glut.h>
#include <OPENGL/gl.h>
#include <OPENGL/glu.h>


#include <iostream>
#include <stdlib.h>
#include <stdio.h>

/*  Create checkerboard texture  */

// specify the texture height and width
#define checkImageWidth 64
#define checkImageHeight 64

// texture object[height][width][rgba];
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

static GLuint texName;
static int angle=0;

void makeCheckImage(void)
{
    int i, j, c;
    
    for (i = 0; i < checkImageHeight; i++) {
        for (j = 0; j < checkImageWidth; j++) {
            c = ((((i&0x8)==0)^((j&0x8)==0)))*255;
            checkImage[i][j][0] = (GLubyte) c;
            checkImage[i][j][1] = (GLubyte) c;
            checkImage[i][j][2] = (GLubyte) c;
            checkImage[i][j][3] = (GLubyte) 255;
        }
    }
}

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    
    makeCheckImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
                 checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 checkImage);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texName);
    
    glPushMatrix();
    
    glRotatef(angle, 0, 0, 1);

    
    // front
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0.0); // bottom left
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 0.0); // bottom right
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 0.0); // top left
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 0.0); // top right
    glEnd();
    

    
    // right
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 0.0); // bottom left
    glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, 0.0); // top left
    glTexCoord2f(1.0, 1.0); glVertex3f(2.0, 1.0-1, -1.5); // top right
    glTexCoord2f(1.0, 0.0); glVertex3f(2.0, -1.0-1, -1.5); // bottom right
    glEnd();
    

    // back
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0+1.0, -1.0-1, -1.5); // bottom left
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0+1.0, 1.0-1, -1.5); // bottom right
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0+1.0, 1.0-1, -1.5); // top left
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0+1.0, -1.0-1, -1.5); // top right
    glEnd();
    
    
    // left
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(1.0-2, -1.0, 0.0); // bottom left
    glTexCoord2f(0.0, 1.0); glVertex3f(1.0-2, 1.0, 0.0); // top left
    glTexCoord2f(1.0, 1.0); glVertex3f(2.0-2, 1.0-1, -1.5); // top right
    glTexCoord2f(1.0, 0.0); glVertex3f(2.0-2, -1.0-1, -1.5); // bottom right
    glEnd();
    
    
    // bottom
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0.0); // bottom left
    glTexCoord2f(0.0, 1.0); glVertex3f(1.0, -1.0, 0.0); // bottom right
    glTexCoord2f(1.0, 1.0); glVertex3f(2.0, -2.0, -1.5); // top left
    glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -2.0, -1.5); // top right
    glEnd();
    
    // top
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0+2, 0.0); //
    glTexCoord2f(0.0, 1.0); glVertex3f(1.0, -1.0+2, 0.0); //
    glTexCoord2f(1.0, 1.0); glVertex3f(2.0, -2.0+2, -1.5); //
    glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -2.0+2, -1.5); //
    glEnd();
    
    glPopMatrix();
    
    
    
    glFlush();
    glDisable(GL_TEXTURE_2D);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.6);
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
            break;
            
        case 'l':
            angle = angle % 360;
            angle+=10;
            glutPostRedisplay();
            break;
            
        case 'r':
            angle = angle % 360;
            angle-=10;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

