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
    void applyForceCenter(Boid &b);
    //! This function gives the force vector that boid experiences due to drag
    Vector forceDrag(Boid b);
	//! This function is used to update the swarm after elapsed time
	void update(float time);
	//! This function gives the centre of mass of the swarm	
    Vector getCOM(Boid b);
	//! This function gives the average velocity of the swarm	
    Vector getAverageVelocity(Boid b);

	Boid getBoid(int i);
	void addBoid(Boid b);
	int getSwarmSize();
    float getDistance(Vector v1, Vector v2);
    Vector forceCenter(Boid b);
    Vector forceCenter1(Boid b);
};


#endif
