#include <iostream>
#include "Swarm.h"

Boid Swarm::getBoid(int i){
	return this->swarm[i];
}

void Swarm::addBoid(Boid b){
	int size = this->swarm.size();
	this->swarm[size] = b;
}

int Swarm::getSwarmSize(){
	return this->swarm.size(); 
}


