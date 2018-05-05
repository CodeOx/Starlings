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
	//! construcor
	Vector();
	//!Custom constructor for this class
	Vector(float e1,float e2,float e3);
	//! Function to set the first component
	void setFirst(float e);
	//! Function to set the second component
	void setSecond(float e);
	//! Function to set the third component
	void setThird(float e);
	//! Accessor function to get the first component
	float getFirst();
	//! Accessor function to get the second component
	float getSecond();
	//! Accessor function to get the third component
	float getThird();

};


#endif