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
double particleSize = 5.0f;
int lifetime = 600;
Triple colour = Triple(1, 0, 0);
double initialPower = 1;
double gravity = -0.13;
enum Shape{FILLED_SQUARE, CIRCLE, SQUARE};
Shape emissionShape = CIRCLE;
list <Particle> particles;
int shapeDensity = 50;

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
    switch (key) {
        case '1':
            emissionShape = CIRCLE;
            break;
        case '2':
            emissionShape = FILLED_SQUARE;
            break;
        case 'c':
            colour = Triple(myRandomPos(), myRandomPos(), myRandomPos());
            break;
        case 'l':
            lifetime -= 30;
            if (lifetime < 30)
                lifetime = 30;
            break;
        case 'L':
            lifetime += 30;
            break;
        case 'd':
            shapeDensity -= 10;
            if (shapeDensity < 10)
                shapeDensity = 10;
            break;
        case 'D':
            shapeDensity += 5;
            break;
        case 'g':
            gravity += 0.1;
            break;
        case 'G':
            gravity -= 0.1;
            break;
        case 's':
            particleSize -= 1;
            if (particleSize < 1)
                particleSize = 1;
            break;
        case 'S':
            particleSize += 1;
            break;
        case 'p':
            initialPower -= 0.1;
            break;
        case 'P':
            initialPower += 0.1;
            break;
        case 32:
            particles.clear();
            break;
        case 27:
            cout << particles.size();
            exit(0);
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

    switch(emissionShape){
        case CIRCLE:
            for (double a = 0; a < 2*M_PI; a+= (2*M_PI/shapeDensity)){
                particles.emplace_back(Particle(Triple(4*sin(a), 8, 4*cos(a)) * initialPower, colour, particleSize, lifetime));
            }
            break;
        case SQUARE:
        case FILLED_SQUARE:
            double increment = sqrt(shapeDensity) / 9.0;
            for (double a = -4; a <= 4; a+= increment){
                for (double b = -4; b <= 4; b += increment) {
                    particles.emplace_back(Particle(Triple(a, 8, b) * initialPower, colour, particleSize, lifetime));
                }
            }
            break;
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

    glutTimerFunc(1000.0/30.0, tick, 0);
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
    glutTimerFunc(1000.0/30.0, tick, 0);
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