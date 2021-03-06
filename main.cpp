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
double wind = 0.0;
enum Shape{FILLED_SQUARE, CIRCLE, SQUARE, SINGLE};
Shape emissionShape = CIRCLE;
bool renderAsLine = false;
int shapeDensity = 50;
int framesPerEmission = 10;
int emissionFrameCount = 0;

double zoomFactor = 1.0;
long previousTime = 0;
long previousSecondTime = 0;
int FPSCounter = 0;

list<string> fpsData;
list<string> frameData;

list <Particle> particles;

int targetFPS = 60.0;

void drawLine(Particle p) {
    glLineWidth(p.size / 2);
    glBegin(GL_LINES);
    glColor4f(p.colour.first, p.colour.second, p.colour.third, p.alpha);
    glVertex3f(p.oldPosition.first, p.oldPosition.second, p.oldPosition.third);
    glVertex3f(p.position.first, p.position.second, p.position.third);
    glEnd();
}

void drawPoint(Particle p) {
    glPointSize(p.size);
    glBegin(GL_POINTS);
    glColor4f(p.colour.first, p.colour.second, p.colour.third, p.alpha);
    glVertex3f(p.position.first, p.position.second, p.position.third);
    glEnd();
}

void drawParticle(Particle p) {
    if (renderAsLine) {
        drawLine(p);
    } else {
        drawPoint(p);
    }
}

void display() {
    glLoadIdentity();
    gluLookAt(400.0 * zoomFactor, 1200.0 * zoomFactor, 2000.0 * zoomFactor,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    list<Particle>::iterator it;
    for(it = particles.begin(); it != particles.end(); ++it) {
        drawParticle(*it);
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
        case '3':
            emissionShape = SQUARE;
            break;
        case '4':
            emissionShape = SINGLE;
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
            shapeDensity -= 5;
            if (shapeDensity < 10)
                shapeDensity = 10;
            break;
        case 'D':
            shapeDensity += 5;
            break;
        case 'g':
            gravity += 0.05;
            break;
        case 'G':
            gravity -= 0.05;
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
        case 'E':
            framesPerEmission -= 1;
            if (framesPerEmission < 1) {
                framesPerEmission = 1;
            }
            break;
        case 'e':
            framesPerEmission += 1;
            if (framesPerEmission > 100) {
                framesPerEmission = 100;
            }
            break;
        case 't':
        case 'T':
            renderAsLine = !renderAsLine;
            break;
        case 'r':
        case 'R':
            particleSize = 5.0f;
            lifetime = 600;
            colour = Triple(1, 0, 0);
            initialPower = 1;
            gravity = -0.13;
            emissionShape = CIRCLE;
            renderAsLine = false;
            shapeDensity = 50;
            framesPerEmission = 10;
            wind = 0.0;
            particles.clear();
            break;
        case 'w':
            wind -= 0.004;
            break;
        case 'W':
            wind += 0.004;
            break;
        case 'z':
            zoomFactor-= 0.1;
            if (zoomFactor < 0.3) {
                zoomFactor = 0.3;
            }
            break;
        case 'Z':
            zoomFactor+= 0.1;
            if (zoomFactor > 2.5) {
                zoomFactor = 2.5;
            }
            break;
        case 'k':
        case 'K':
            if (targetFPS < 100) {
                targetFPS = 1000;
            } else {
                targetFPS = 60;
            }
            break;
        case 'x':
            targetFPS = 5;
            break;
        case 'X':
            targetFPS = 60;
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

void emitShape() {
    emissionFrameCount++;

    if (emissionFrameCount >= framesPerEmission) {
        emissionFrameCount = 0;
        double increment = 0;
        switch (emissionShape) {
            case CIRCLE:
                for (double a = 0; a < 2 * M_PI; a += (2 * M_PI / shapeDensity)) {
                    particles.emplace_back(
                            Particle(Triple(4 * sin(a), 8, 4 * cos(a)) * initialPower, colour, particleSize, lifetime));
                }
                break;
            case SQUARE:
                increment = 9.0 / sqrt(shapeDensity);
                for (double a = -4; a <= 4; a += increment) {
                    particles.emplace_back(Particle(Triple(a, 8, -4) * initialPower, colour, particleSize, lifetime));
                    particles.emplace_back(Particle(Triple(a, 8, 4) * initialPower, colour, particleSize, lifetime));
                }
                for (double a = -4; a <= 4; a += increment) {
                    particles.emplace_back(Particle(Triple(-4, 8, a) * initialPower, colour, particleSize, lifetime));
                    particles.emplace_back(Particle(Triple(4, 8, a) * initialPower, colour, particleSize, lifetime));
                }
                break;
            case FILLED_SQUARE:
                increment = 9.0 / sqrt(shapeDensity);
                for (double a = -4; a <= 4; a += increment) {
                    for (double b = -4; b <= 4; b += increment) {
                        particles.emplace_back(Particle(Triple(a, 8, b) * initialPower, colour, particleSize, lifetime));
                    }
                }
                break;
            case SINGLE:
                if (particles.size() < 2) {
                    particles.emplace_back(Particle(Triple(4, 8, 0) * initialPower, colour, particleSize, lifetime));
                }
                break;
        }
    }
}

void dataTracker() {
    FPSCounter++;
    long t = chrono::duration_cast<chrono::milliseconds >(chrono::system_clock::now().time_since_epoch()).count();
    long seconds = t / 1000;
    long changeInTime = t - previousTime;
    // Time per frame vs particles data
    frameData.emplace_back(to_string(changeInTime) + "," + to_string(particles.size()));

    previousTime = t;
    if (seconds >= previousSecondTime) {
        // Frames per second vs particles data
        fpsData.emplace_back(to_string(FPSCounter) + "," + to_string(particles.size()));

        FPSCounter = 0;
        previousSecondTime = seconds;

    }

}

void tick(int x) {
    list<Particle>::iterator it;
    for (it = particles.begin(); it != particles.end();) {
        if (!(it->update(Triple(wind, gravity, 0)))) {
            it = particles.erase(it);
        } else {
            ++it;
        }
    }

    emitShape();

    glutPostRedisplay();


    glutTimerFunc(1000.0/targetFPS, tick, 0);
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
    glutTimerFunc(1000.0/targetFPS, tick, 0);
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