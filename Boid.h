#include <iostream>
#include "Vector.h"

#ifndef BOID_H
#define BOID_H

class Boid{
private:
	Vector location;
	Vector velocity; //respresents direction of velocity
	float speed;

public:
	Boid(Vector location,Vector velocity, float speed);
	void updatePosition(std::vector<Boid> boidsList);
	void updateVelocity(std::vector<Boid> boidsList);
	void updateSpeed(std::vector<Boid> boidsList);

	Vector getPosition();
	Vector getVelocity();
	float getSpeed();
};

#endif