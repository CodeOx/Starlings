#include <iostream>
#include "Vector.h"

#ifndef BOID_H
#define BOID_H

/*! \class Boid
A class representing a Boid 
*/
class Boid{
private:
	Vector location; /*< location is current position of boid */
	Vector velocity; /*< velocity is current velocity of boid */
	Vector accelaration; /*< accelaration is current accelaration of boid */

public:
	//! Custom constructors
	Boid(Vector location,Vector velocity,Vector direction);
	Boid(Vector location,Vector velocity);
	//! This function gives the force vector that boid experiences due to cohesion rule
	Vector forceCohesion(std::vector<Boid> boidsList);
	//! This function gives the force vector that boid experiences due to separation rule
	Vector forceSeparation(std::vector<Boid> boidsList);
	//! This function gives the force vector that boid experiences due to alignment rule
	Vector forceAlignment(std::vector<Boid> boidsList);
	//! This function gives the force vector that boid experiences due to centeringrule
	Vector forceCenter(std::vector<Boid> boidsList);
	//! This function applies the force on boid
	void applyForce(Vector force);
	//! function to update direction
	void updateDirection();
	//! function to update location
	void updateLocation();

};

#endif