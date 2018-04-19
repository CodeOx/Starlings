#include "Boid.h"

#define LOCATION_FACTOR 10.0
#define VELOCITY_FACTOR 10.0

Boid::Boid(){
	Vector l(((rand() % 100) + 1)/LOCATION_FACTOR,((rand() % 100) + 1)/LOCATION_FACTOR,((rand() % 100) + 1)/LOCATION_FACTOR);
	Vector v(((rand() % 100) + 1)/LOCATION_FACTOR,((rand() % 100) + 1)/LOCATION_FACTOR,((rand() % 100) + 1)/LOCATION_FACTOR);
	Vector a(0.0,0.0,0.0);

	this->location = l;
	this->velocity = v;
	this->acceleration = a;
}

Boid::Boid(Vector location,Vector velocity,Vector acceleration){
	this->location = location;
	this->velocity = velocity;
	this->acceleration = acceleration;
}

Boid::Boid(Vector location,Vector velocity){
	this->location = location;
	this->velocity = velocity;
}

void Boid::applyForce(Vector force){

}

void Boid::updateDirection(){

}

void Boid::updateLocation(){

}

Vector Boid::getLocation(){
	return this->location;
}
