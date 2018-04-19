#include "Boid.h"

Boid::Boid(Vector location,Vector velocity,Vector acceleration){
	this->location = location;
	this->velocity = velocity;
	this->acceleration = acceleration;
}

Boid::Boid(Vector location,Vector velocity){
	this->location = location;
	this->velocity = velocity;
}

Vector Boid::forceCohesion(std::vector<Boid> boidsList){

}

Vector Boid::forceSeparation(std::vector<Boid> boidsList){

}

Vector Boid::forceAlignment(std::vector<Boid> boidsList){

}

Vector Boid::forceCenter(std::vector<Boid> boidsList){

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
