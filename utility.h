//
// Created by sam_r on 15/11/2018.
//

#ifndef PARTICLESYSTEM_UTILITY_H
#define PARTICLESYSTEM_UTILITY_H

#include <cstdlib>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <iostream>

double myRandomPosOrNeg();
double myRandomPos();
double myRandomNeg();

void writeToFile(std::string filename, std::list<std::string> data);


#endif //PARTICLESYSTEM_UTILITY_H
