#include <iostream>
#include "Swarm.h"

Boid Swarm::getBoid(int i){
	return this->swarm[i];
}

void Swarm::addBoid(Boid b){
	this->swarm.push_back(b);
}

int Swarm::getSwarmSize(){
	return this->swarm.size(); 
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
}