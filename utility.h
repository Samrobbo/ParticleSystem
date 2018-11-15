//
// Created by sam_r on 15/11/2018.
//

#ifndef PARTICLESYSTEM_UTILITY_H
#define PARTICLESYSTEM_UTILITY_H

#include <cstdlib>

double myRandomPosOrNeg()
//Return random double within range [-1,1]
{
    double r = ((rand()/(double)RAND_MAX) * 2) - 1;
    return r;
}

double myRandomPos()
//Return random double within range [0,1]
{
    double r = ((rand()/(double)RAND_MAX));
    return r;
}

double myRandomNeg() {
    return -myRandomPos();
}

#endif //PARTICLESYSTEM_UTILITY_H
