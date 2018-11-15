//
// Created by sam_r on 15/11/2018.
//

#ifndef PARTICLESYSTEM_TRIPLE_H
#define PARTICLESYSTEM_TRIPLE_H
class Triple {
public:
    double first;
    double second;
    double third;

    Triple();
    Triple(double, double, double);
    Triple operator+ (const Triple&) const;
    Triple operator* (const int) const;
    };
#endif //PARTICLESYSTEM_TRIPLE_H
