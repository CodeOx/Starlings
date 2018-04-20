#include <iostream>
#include <vector>
#include "Vector.h"
#include "Boid.h"

#ifndef SWARM_H
#define SWARM_H

class Swarm{
	std::vector<Boid> swarm;

public:
	//! Constructor	
	Swarm();
	//! This function gives the force vector that boid experiences due to cohesion rule
	Vector forceCohesion(Boid b);
	//! This function gives the force vector that boid experiences due to separation rule
	Vector forceSeparation(Boid b);
	//! This function gives the force vector that boid experiences due to alignment rule
	Vector forceAlignment(Boid b);
	//! This function gives the force vector that boid experiences due to centeringrule
	Vector forceCenter(Boid b);
	//! This function is used to update the swarm after elapsed time
	void update(float time);
	//! This function gives the centre of mass of the swarm	
	Vector getCOM();

	Boid getBoid(int i);
	void addBoid(Boid b);
	int getSwarmSize();

};


#endif