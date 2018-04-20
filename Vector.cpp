#include <iostream>
#include "Vector.h"

Vector::Vector(){
	
}

Vector::Vector(float e1,float e2,float e3){
	this->e1 = e1;
	this->e2 = e2;
	this->e3 = e3;
}

void Vector::setFirst(float e){
	this->e1 = e;
}

void Vector::setSecond(float e){
	this->e2 = e;
}

void Vector::setThird(float e){
	this->e3 = e;
}

float Vector::getFirst(){
	return this->e1;
}

float Vector::getSecond(){
	return this->e2;
}

float Vector::getThird(){
	return this->e3;
}
