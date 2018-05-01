#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <map>
#include "Passenger.h"
using namespace std;

class Plane
{
private:
	string planeType;
	//If seat is booked sets bool to true
	//If empty sets bool to false
	map<string, bool> planeSeating;

	void displaySeatingTypeA();
	void displaySeatingTypeB();

public:
	Plane() {}
	Plane(string);
	~Plane();
	void addPassenger(string);
	void removePassenger(string);
	bool checkSeatBooked(string);
	bool checkPlaneBooked();
	void displaySeatingArrangement();

};

#endif