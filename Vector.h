#include <iostream>

#ifndef VECTOR_H
#define VECTOR_H

/*! \class Vector
A class representing a vector containing three components
*/

class Vector{
private:
	float e1; /*< first component of vector */
	float e2; /*< second component of vector */
	float e3; /*< third component of vector */

public:
	//! Accessor function to get the first component
	float getFirst();
	//! Accessor function to get the second component
	float getSecond();
	//! Accessor function to get the third component
	float getThird();
	//!Custom constructor for this class
	Vector(float e1,float e2,float e3);
	

};


#endif