//
// Created by sam_r on 10/10/2018.
//

#ifndef PARTICLESYSTEM_PARTICLE_H
#define PARTICLESYSTEM_PARTICLE_H

class Particle {
public:
    double velocity[3];
    double position[3];
    double colour[3];
    double size;
    double alpha;
    int framesLeftToLive;

    Particle();
    Particle(double, double);
    Particle(double, double, double);
    bool update(double, double, double);

};


#endif //PARTICLESYSTEM_PARTICLE_H
