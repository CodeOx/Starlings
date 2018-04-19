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
	
}