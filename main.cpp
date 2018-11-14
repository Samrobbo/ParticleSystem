//////////////////////////////////////////
// School of Computer Science
// The University of Manchester
//
// This code is licensed under the terms of the Creative Commons
// Attribution 2.0 Generic (CC BY 3.0) License.
//
// Skeleton code for COMP37111 coursework, 2012-13
//
// Authors: Arturs Bekasovs and Toby Howard
//
//////////////////////////////////////////

#define _USE_MATH_DEFINES

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <chrono>
#include <list>
#include <iterator>

#include <math.h>
#include <GL/glut.h>
#include "Particle.h"

using namespace std;

// Display list for coordinate axis
GLuint axisList;

int AXIS_SIZE= 200;
int axisEnabled= 1;
list <Particle> particles;

double myRandom()
//Return random double within range [-1,1]
{
    double r = ((rand()/(double)RAND_MAX) * 2) - 1;
    return r;
}

long previousFrameDrawnTime = 0;

long fps() {
    long frameDrawnTime = chrono::duration_cast<chrono::microseconds >(chrono::system_clock::now().time_since_epoch()).count();
    long timeElapsed =  frameDrawnTime - previousFrameDrawnTime;
    previousFrameDrawnTime = frameDrawnTime;
    return (long)(1.0f / (timeElapsed / 1000000.0f));
}

void drawPoint(Particle p) {
    glPointSize(p.size);
    glBegin(GL_POINTS);
    glColor3f(p.colour[0], p.colour[1], p.colour[2]);
    glVertex3f(p.position[0], p.position[1], p.position[2]);
    glEnd();
}

void display()
{
    glLoadIdentity();
    gluLookAt(100.0, 300.0, 1000.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // If enabled, draw coordinate axis
    if(axisEnabled) {
        glCallList(axisList);
    }

    list<Particle>::iterator it;
    for(it = particles.begin(); it != particles.end(); ++it) {
        drawPoint(*it);
    }
    glutSwapBuffers();

}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        cout << particles.size();
        exit(0);
    }
    if (key == 32) {
        particles.clear();
        particles.emplace_back(Particle());
    }
    if (key == 'e') {
        for (double a = 0; a <= 2*M_PI; a+= (2*M_PI/200)){
            particles.emplace_back(Particle(4*sin(a), 4*cos(a)));
            particles.emplace_back(Particle(4*sin(a), 12 ,4*cos(a)));
        }
    }
    glutPostRedisplay();
}

void reshape(int width, int height) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 10000.0);
    glMatrixMode(GL_MODELVIEW);
}

void tick(int x) {
    list<Particle>::iterator it;
    for(it = particles.begin(); it != particles.end();) {
        //it->update(myRandom() / 10.0f, -0.025, 0);
        if (!(it->update(0, -0.16,0))){
            it = particles.erase(it);
        }
        else {
            ++it;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(1000.0/60.0, tick, 0);
}


void initGraphics(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutCreateWindow("Sam's Particle System");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutTimerFunc(1000.0/60.0, tick, 0);
}

//



int main(int argc, char *argv[])
{
    srand(time(nullptr));
    initGraphics(argc, argv);
    glEnable(GL_POINT_SMOOTH);
    glutMainLoop();
}