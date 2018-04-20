#include <iostream>
#include <cmath>
#include "Swarm.h"

#define INITIAL_SIZE 4

Swarm::Swarm(){
	for(int i = 0; i < INITIAL_SIZE; i++){
		Boid b;
		this->swarm.push_back(b);
	}
}

Boid Swarm::getBoid(int i){
	return this->swarm[i];
}

void Swarm::addBoid(Boid b){
	this->swarm.push_back(b);
}

int Swarm::getSwarmSize(){
	return this->swarm.size(); 
}

Vector Swarm::forceCohesion(Boid b){
	Vector centre_of_mass = this->getCOM();
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;

	Vector location_b = b.getLocation();

	x = ((centre_of_mass.getFirst() * swarm.size()) - location_b.getFirst())/(swarm.size() - 1);
	y = ((centre_of_mass.getSecond() * swarm.size()) - location_b.getSecond())/(swarm.size() - 1);
	z = ((centre_of_mass.getThird() * swarm.size()) - location_b.getThird())/(swarm.size() - 1);

	float delta_x = x - location_b.getFirst();
	float delta_y = y - location_b.getSecond();
	float delta_z = z - location_b.getThird();

    float proportionalityConstant = 1.0;
    float exponent = 1.0;
    float constant = 0.0;

    float force_x = constant + proportionalityConstant*(std::pow(delta_x,exponent));
    float force_y = constant + proportionalityConstant*(std::pow(delta_y,exponent));
    float force_z = constant + proportionalityConstant*(std::pow(delta_z,exponent));

	Vector force(force_x, force_y, force_z);

	return force; 
}

Vector Swarm::forceSeparation(Boid b){

}

Vector Swarm::forceAlignment(Boid b){

}

Vector Swarm::forceCenter(Boid b){
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    Vector location_b = b.getLocation();
    x = location_b.getFirst();
    y = location_b.getSecond();
    z = location_b.getThird();

    float proportionalityConstant = 1.0;
    float exponent = 1.0;

    float force_x = proportionalityConstant*(std::pow((-1*x),exponent));
    float force_y = proportionalityConstant*(std::pow((-1*y),exponent));
    float force_z = proportionalityConstant*(std::pow((-1*z),exponent));

    Vector force(force_x, force_y, force_z);

    return force;
}

void Swarm::update(float time){
	for (int i = 0; i < swarm.size(); i++){
		swarm[i].update(time);
        Vector force1 = forceCohesion(swarm[i]);
        Vector force2 = forceCenter(swarm[i]);
        Vector force;
        force.setFirst(force1.getFirst() + force2.getFirst());
        force.setSecond(force1.getSecond() + force2.getSecond());
        force.setThird(force1.getThird() + force2.getThird());
        swarm[i].applyForce(force);
	}
}

Vector Swarm::getCOM(){
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;

	int N = swarm.size();

	for(int i = 0; i < N; i++){
		Vector location_i = swarm[i].getLocation();
		x = x + location_i.getFirst();
		y = y + location_i.getSecond();
		z = z + location_i.getThird();
	}

	x = x/N;
	y = y/N;
	z = z/N;

	Vector v(x,y,z);

	return v;
}
