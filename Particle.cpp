//
// Created by sam_r on 10/10/2018.
//

#include <cstdlib>
#include "Particle.h"
using namespace std;

double myRandomPos()
//Return random double within range [0,1]
{
    double r = ((rand()/(double)RAND_MAX));
    return r;
}

Particle::Particle() {
    this->position[0] = 0;
    this->position[1] = 50;
    this->position[2] = 0;

    this->velocity[0] = 0;
    this->velocity[1] = 5;
    this->velocity[2] = 0;


    this->colour[0] = 100;
    this->colour[1] = 100;
    this->colour[2] = myRandomPos();

    this->size = myRandomPos() * 10.0f;

    this->framesLeftToLive = 240;

}

Particle::Particle(double x, double z) {
    this->position[0] = 0;
    this->position[1] = 60;
    this->position[2] = 0;

    this->velocity[0] = x;
    this->velocity[1] = 8;
    this->velocity[2] = z;


    this->colour[0] = myRandomPos();
    this->colour[1] = 40;
    this->colour[2] = 40;

    this->size = 10.0f;
    this->framesLeftToLive = 600;

}

Particle::Particle(double x, double y, double z) {
    this->position[0] = 0;
    this->position[1] = 60;
    this->position[2] = 0;

    this->velocity[0] = x;
    this->velocity[1] = y;
    this->velocity[2] = z;


    this->colour[0] = 120;
    this->colour[1] = 80;
    this->colour[2] = 80;

    this->size = 10.0f;
    this->framesLeftToLive = 600;

}

bool Particle::update(double accelerationx, double accelerationy, double accelerationz) {
    this->framesLeftToLive--;
    if (this->framesLeftToLive <= 0) {
        return false;
    }


    this->velocity[0] = this->velocity[0] + accelerationx;
    this->velocity[1] = this->velocity[1] + accelerationy;
    this->velocity[2] = this->velocity[2] + accelerationz;

    this->position[0] = this->position[0] + this->velocity[0];
    this->position[1] = this->position[1] + this->velocity[1];
    this->position[2] = this->position[2] + this->velocity[2];

    if (this->position[1] <= 0) {
        this->position[1] = -this->position[1];

        this->velocity[0] *= 0.9;
        this->velocity[1] *= -0.7;
        this->velocity[2] *= 0.9;
    }
    return true;
}
