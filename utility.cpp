//
// Created by sam_r on 29/11/2018.
//

#include "utility.h"


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

double myRandomNeg()
//Return random double within range [-1, 0]
{
    return -myRandomPos();
}

void writeToFile(std::string filename, std::list<std::string> data) {


    std::ofstream currentFile("C:\\Users\\sam_r\\University\\Graphics\\ParticleSystem\\" + filename + ".txt");
    for (auto line : data) {
        currentFile << line << std::endl;
    }
    currentFile.close();
}
