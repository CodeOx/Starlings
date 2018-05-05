#include <iostream>
#include <vector>
#include <QVector3D>
#include <QMatrix4x4>
#include <cstdlib>
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
	Vector acceleration; /*< accelaration is current accelaration of boid */

public:
	//! Custom constructors
	Boid();
	Boid(Vector location,Vector velocity,Vector accelaration);
	Boid(Vector location,Vector velocity);
	//! This function applies the force on boid
	void applyForce(Vector force);
    void applyRotation(float angle, QVector3D v);
    //! function to update velocity
	void updateVelocity(float time);
	//! function to update location
	void updateLocation(float time);
	//! function to update the boid after elapsed time
	void update(float time);
	//! function to get location
	Vector getLocation();
    //! function to get velocity
    Vector getVelocity();
    //! function to set velocity
    void setVelocity(Vector v);

};

#endif
