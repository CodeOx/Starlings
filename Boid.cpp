#include "Boid.h"

#define LOCATION_FACTOR 5.0
#define VELOCITY_FACTOR 10.0
#define mass 1.0

Boid::Boid(){
	Vector l(((rand() % 100) -50)/LOCATION_FACTOR,((rand() % 100) -50)/LOCATION_FACTOR,((rand() % 100) -50)/LOCATION_FACTOR);
	Vector v(((rand() % 100) -50)/LOCATION_FACTOR,((rand() % 100) -50)/LOCATION_FACTOR,((rand() % 100) -50)/LOCATION_FACTOR);
	Vector a(0.0,0.0,0.0);

	this->location = l;
	this->velocity = v;
	this->acceleration = a;

	//std::cout<<location.getFirst();
	//std::cout<<velocity.getFirst();
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

	//std::cout<<force.getFirst() << "heterf";

	acceleration.setFirst(force.getFirst()/mass);
	acceleration.setSecond(force.getSecond()/mass);
	acceleration.setThird(force.getThird()/mass);
}

void Boid::updateLocation(float time){
	location.setFirst(location.getFirst() + (velocity.getFirst() * time));
    location.setSecond(location.getSecond() + (velocity.getSecond() * time));
    location.setThird(location.getThird() + (velocity.getThird() * time));
}

void Boid::updateVelocity(float time){
	velocity.setFirst(velocity.getFirst() + (acceleration.getFirst() * time));
    velocity.setSecond(velocity.getSecond() + (acceleration.getSecond() * time));
    velocity.setThird(velocity.getThird() + (acceleration.getThird() * time));
}

void Boid::update(float time){
	updateLocation(time);
	updateVelocity(time);
}

Vector Boid::getLocation(){
	return this->location;
}
