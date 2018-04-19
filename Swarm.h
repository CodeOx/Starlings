#include <iostream>
#include <vector>
#include "Vector.h"
#include "Boid.h"

#ifndef SWARM_H
#define SWARM_H

class Swarm{
	std::vector<Boid> swarm;
	Vector centre_of_mass;

public:

	Boid getBoid(int i);
	void addBoid(Boid b);
	int getSwarmSize();
	Vector getCOM();

};


#endif