#include <iostream>
#include <cmath>
#include <QVector3D>
#include <QMatrix4x4>
#include "Swarm.h"

#define INITIAL_SIZE 4

float magnitude1(Vector v){
    float x = v.getFirst();
    float y = v.getSecond();
    float z = v.getThird();

    float mag = std::pow((x*x)+(y*y)+(z*z),0.5);

    return mag;
}

float dotProduct1(Vector v1, Vector v2){
    return (v1.getFirst() * v2.getFirst()) + (v1.getSecond() * v2.getSecond()) + (v1.getThird() * v2.getThird());
}

int getRotationAngle1(Vector v1, Vector v2){
    if (magnitude1(v1) != 0 && magnitude1(v2)!= 0){
        std::cout<<"1 "<<magnitude1(v1)<< " "<<magnitude1(v2)<<std::endl;
        float a = (((dotProduct1(v1,v2))/((magnitude1(v1)*magnitude1(v2)))));
        std::cout<<"3 "<<a<<std::endl;
        return (int)57.296 * (std::acos(a));
    }
    return 0;
}

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
    int N = this->swarm.size();
    Vector totalForce(0.0,0.0,0.0);
    Vector location_b = b.getLocation();

    float proportionalityConstant = -1.0;
    float exponent = -1.0;
    float constant = 0.0;
    float minDistance = 10.0;
    float maxForce = 50.0;
    float force = 0.0;

    for(int i = 0; i < N; i++){
        Vector location_ib = swarm[i].getLocation();
        float delta_x = (location_ib.getFirst() - location_b.getFirst())/100.0;
        float delta_y = (location_ib.getSecond() - location_b.getSecond())/100.0;
        float delta_z = (location_ib.getThird() - location_b.getThird())/100.0;
        float dist = sqrt((delta_x*delta_x) + (delta_y*delta_y) + (delta_z*delta_z));
        force = 0.0;
        if (dist > 0){
            if (dist < minDistance){
                force = constant + proportionalityConstant*(std::pow(dist,exponent));
            }

            totalForce.setFirst(totalForce.getFirst() + force*delta_x/dist);
            totalForce.setSecond(totalForce.getSecond() + force*delta_y/dist);
            totalForce.setThird(totalForce.getThird() + force*delta_z/dist);
        }
        //std::cout<<"foorces       : "<<i<<" "<<totalForce.getSecond()<<" "<<totalForce.getThird()<<std::endl;
    }
    return totalForce;

}

Vector Swarm::forceAlignment(Boid b){
    Vector average_velocity = this->getAverageVelocity();
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    Vector velocity_b = b.getVelocity();

    x = ((average_velocity.getFirst() * swarm.size()) - velocity_b.getFirst())/(swarm.size() - 1);
    y = ((average_velocity.getSecond() * swarm.size()) - velocity_b.getSecond())/(swarm.size() - 1);
    z = ((average_velocity.getThird() * swarm.size()) - velocity_b.getThird())/(swarm.size() - 1);

    float delta_x = x - velocity_b.getFirst();
    float delta_y = y - velocity_b.getSecond();
    float delta_z = z - velocity_b.getThird();

    float proportionalityConstant = 1.0;
    float exponent = 1.0;
    float constant = 0.0;

    float force_x = constant + proportionalityConstant*(std::pow(delta_x,exponent));
    float force_y = constant + proportionalityConstant*(std::pow(delta_y,exponent));
    float force_z = constant + proportionalityConstant*(std::pow(delta_z,exponent));

    Vector force(force_x, force_y, force_z);

    return force; 
}

void Swarm::applyForceCenter(Boid &b){
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    Vector location_b = b.getLocation();
    x = location_b.getFirst();
    y = location_b.getSecond();
    z = location_b.getThird();

    Vector velocity_b = b.getVelocity();

    QVector3D position(x,y,z);
    QVector3D velocity(velocity_b.getFirst(),velocity_b.getSecond(),velocity_b.getThird());
    QVector3D normal = QVector3D::crossProduct(position,velocity);

    std::cout<<"vel here    x: "<<velocity_b.getFirst()<<" y: "<<velocity_b.getSecond()<<" z: "<<velocity_b.getThird()<<std::endl;
    std::cout<<"loc here    x: "<<location_b.getFirst()<<" y: "<<location_b.getSecond()<<" z: "<<location_b.getThird()<<std::endl;

    QMatrix4x4 m1;
    if(!(normal.x() == 0 && normal.y() == 0 && normal.z() == 0))
    {
        m1.rotate(-90, normal);
        position = position * m1;
        location_b.setFirst(position.x());
        location_b.setSecond(position.y());
        location_b.setThird(position.z());
    }

    int angle = getRotationAngle1(location_b,velocity_b);
    if (angle > 90){
        angle -= 90;
    }
    float ratio = -0.2;

    std::cout<<"angle   :   "<<angle<<std::endl;

    if(x*x + y*y + z*z > 40.0)
        b.applyRotation(angle*ratio, normal);
}

Vector Swarm::forceDrag(Boid b){
    Vector v = b.getVelocity();

    float v_x = v.getFirst();
    float v_y = v.getSecond();
    float v_z = v.getThird();

    float proportionalityConstant = 0.02;
    float exponent = 2.0;

    float force_x = proportionalityConstant*(std::pow((v_x),exponent));
    float force_y = proportionalityConstant*(std::pow((v_y),exponent));
    float force_z = proportionalityConstant*(std::pow((v_z),exponent));

    if (v_x > 0){
        force_x = -1 * force_x;
    }
    if (v_y > 0){
        force_y = -1 * force_y;
    }
    if (v_z > 0){
        force_z = -1 * force_z;
    }
    Vector force(force_x, force_y, force_z);

    return force;
}

Vector Swarm::forceCenter(Boid b){
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    Vector location_b = b.getLocation();
    x = location_b.getFirst();
    y = location_b.getSecond();
    z = location_b.getThird();

    float proportionalityConstant = 0.0;

    Vector velocity_b = b.getVelocity();
    float mag_v = (velocity_b.getFirst()*velocity_b.getFirst()) + (velocity_b.getSecond()*velocity_b.getSecond()) + (velocity_b.getThird()*velocity_b.getThird());
    if (mag_v <1000 && mag_v > 0){
        proportionalityConstant = 1000/mag_v;
    }

    float exponent = 1.0;

    float force_x = proportionalityConstant*(-x/magnitude1(location_b));
    float force_y = proportionalityConstant*(-y/magnitude1(location_b));
    float force_z = proportionalityConstant*(-z/magnitude1(location_b));

    Vector force(force_x, force_y, force_z);

    return force;
}

void* updateBoid(void* threadarg){
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;
    float time;
    Boid b;
    Swarm s;
    time = my_data->time;
    b = my_data->b;
    s = my_data->s;
    b.update(time);
    Vector force1 = s.forceCohesion(b);
    Vector force2 = s.forceCenter(b);
    Vector force3 = s.forceDrag(b);
    Vector force4 = s.forceSeparation(b);
    Vector force5 = s.forceAlignment(b);
    Vector force;
    force.setFirst(force1.getFirst() + force2.getFirst() + force3.getFirst() + force4.getFirst() + force5.getFirst());
    force.setSecond(force1.getSecond() + force2.getSecond() + force3.getSecond() + force4.getSecond() + force5.getSecond());
    force.setThird(force1.getThird() + force2.getThird() + force3.getThird() + force4.getThird() + force5.getThird());
    applyForceCenter(b);
    b.applyForce(force);

    std::cout<< "cohesion   "<<force1.getFirst()<<" "<<force1.getSecond()<<" "<<force1.getThird()<<std::endl;
    std::cout<< "center   "<<force2.getFirst()<<" "<<force2.getSecond()<<" "<<force2.getThird()<<std::endl;
    std::cout<< "drag   "<<force3.getFirst()<<" "<<force3.getSecond()<<" "<<force3.getThird()<<std::endl;
    std::cout<< "seperation   "<<force4.getFirst()<<" "<<force4.getSecond()<<" "<<force4.getThird()<<std::endl;
    std::cout<< "align   "<<force5.getFirst()<<" "<<force5.getSecond()<<" "<<force5.getThird()<<std::endl;

}

void Swarm::update(float t){
    int NUM_THREADS = swarm.size();

    pthread_t threads[NUM_THREADS];
    struct thread_data td[NUM_THREADS];
    int rc;
    Swarm sw;
    
	for (int i = 0; i < NUM_THREADS; i++){
        td[i].time = t;
        td[i].b = swarm[i];
        td[i].s = sw;
        rc = pthread_create(&threads[i], NULL, updateBoid, (void *)&td[i]);
        if (rc) {
          std::cout << "Error:unable to create thread," << rc << std::endl;
          exit(-1);
        }
	}
    //Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
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

Vector Swarm::getAverageVelocity(){
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    int N = swarm.size();

    for(int i = 0; i < N; i++){
        Vector velocity_i = swarm[i].getVelocity();
        x = x + velocity_i.getFirst();
        y = y + velocity_i.getSecond();
        z = z + velocity_i.getThird();
    }

    x = x/N;
    y = y/N;
    z = z/N;

    Vector v(x,y,z);

    return v;
}
