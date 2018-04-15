#include <iostream>
#include "Vector.h"

#ifndef BOID_H
#define BOID_H

class Boid{
private:
	Vector location;
	Vector velocity;

public:
	Boid(Vector location,Vector velocity);
	void updatePosition(std::vector<Boid> boidsList);
	void updateVelocity(std::vector<Boid> boidsList);
};

#endif