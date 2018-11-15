//
// Created by sam_r on 10/10/2018.
//

#include <cstdlib>
#include <iostream>
#include "Particle.h"
using namespace std;

Particle::Particle(Triple startingVelocity, Triple colour, double size, int lifetime) {
    this->position = Triple(0,60,0);
    this->velocity = startingVelocity;
    this->colour = colour;
    this->size = size;
    this->startingLifetime = lifetime;
    this->framesLeftToLive = lifetime;
    this->alpha = 1.0;
}

Particle::Particle(Triple startingPosition, Triple startingVelocity, Triple colour, double size, int lifetime) {
    this->position = startingPosition;
    this->velocity = startingVelocity;
    this->colour = colour;
    this->size = size;
    this->startingLifetime = lifetime;
    this->framesLeftToLive = lifetime;
    this->alpha = 1.0;
}

bool Particle::update(Triple acceleration) {
    this->framesLeftToLive--;
    if (this->framesLeftToLive <= 0) {
        return false;
    }

    this->alpha = double(this->framesLeftToLive) / this->startingLifetime;

    this->velocity = this->velocity + acceleration;

    this->position = this->position + velocity;

    if (this->position.second <= 0) {
        this->position.second = -this->position.second;

        this->velocity = this->velocity * 0.9;
        this->velocity.second = -this->velocity.second;
    }
    return true;
}
