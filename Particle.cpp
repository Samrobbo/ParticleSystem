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


    this->colour[0] = myRandomPos();
    this->colour[1] = myRandomPos();
    this->colour[2] = myRandomPos();

    this->size = myRandomPos() * 10.0f;

    this->framesLeftToLive = 240;

}

Particle::Particle(double x, double z) {
    this->position[0] = 0;
    this->position[1] = 50;
    this->position[2] = 0;

    this->velocity[0] = x;
    this->velocity[1] = 5;
    this->velocity[2] = z;


    this->colour[0] = myRandomPos();
    this->colour[1] = myRandomPos();
    this->colour[2] = myRandomPos();

    this->size = 10.0f;
    this->framesLeftToLive = 240;

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
    return true;
}
