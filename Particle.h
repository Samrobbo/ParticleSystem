//
// Created by sam_r on 10/10/2018.
//

#ifndef PARTICLESYSTEM_PARTICLE_H
#define PARTICLESYSTEM_PARTICLE_H

#include "Triple.h"

class Particle {
public:
    Triple velocity;
    Triple position;
    Triple oldPosition;
    Triple colour;

    double size;
    double alpha;
    int framesLeftToLive;
    int startingLifetime;

    Particle(Triple, Triple, double, int);
    Particle(Triple, Triple, Triple, double, int);
    bool update(Triple);

};


#endif //PARTICLESYSTEM_PARTICLE_H
