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
#include "utility.h"

using namespace std;

// Global Properties
double particleSize = 10.0f;
int lifetime = 1000;
Triple colour = Triple(1, 0, 0);
double initialPower = 1;
double gravity = -0.13;
int particlesInSystem = 0;

list <Particle> particles;

void drawPoint(Particle p) {
    glPointSize(p.size);
    glBegin(GL_POINTS);
    glColor4f(p.colour.first, p.colour.second, p.colour.third, p.alpha);
    glVertex3f(p.position.first, p.position.second, p.position.third);
    glEnd();
}

void display() {
    glLoadIdentity();
    gluLookAt(400.0, 1200.0, 2000.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    else if (key == 32) {
        particles.clear();
    }
    else if (key == 'r') {
        colour = Triple(myRandomPos(), myRandomPos(), myRandomPos());
    }
    else if (key == 'e') {
        for (double a = 0; a < 2*M_PI; a+= (2*M_PI/100)){
            particles.emplace_back(Particle(Triple(4*sin(a), 8, 4*cos(a)), colour, particleSize, lifetime));
        }
    }
    else if (key == 's') {
        for (double a = -2; a <= 2; a+= 1){
            for (double b = -2; b <= 2; b += 1) {
                particles.emplace_back(Particle(Triple(a, 8, b), colour, particleSize, lifetime));
            }
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

//list<int> framerates = {60,60,60};
//int frameCount = 0;

void tick(int x) {
    list<Particle>::iterator it;
    for(it = particles.begin(); it != particles.end();) {
        if (!(it->update(Triple(0, gravity, 0)))) {
            it = particles.erase(it);
        }
        else {
            ++it;
        }
    }
    glutPostRedisplay();


//    frameCount++;
//    long t = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count();
//    t = t / 1000000;
//    if (t != previousTime) {
//        int average = 0;
//
//        cout << average << "FPS (average)" << endl;
//        framerates.erase(framerates.begin());
//        framerates.emplace_back(frameCount);
//        frameCount = 0;
//        previousTime = t;
//    }

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

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    initGraphics(argc, argv);
    glEnable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutMainLoop();
}