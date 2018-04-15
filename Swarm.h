#include <iostream>
#include <vector>
#include "Vector.h"
#include "Boid.h"

#ifndef SWARM_H
#define SWARM_H

class Swarm{
	std::vector<Boid> swarm;

public:

	Boid getBoid(int i);
	void addBoid(Boid b);
	int getSwarmSize();

};


#endif