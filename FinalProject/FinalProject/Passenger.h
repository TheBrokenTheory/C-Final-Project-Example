#ifndef PASSENGER_H
#define PASSENGER_H
#include <iostream>
#include <string>
using namespace std;

class Passenger
{
private:
	string passengerFirstName;
	string passengerLastName;
	string flightNumber;
	string assignedSeat;


public:
	Passenger();
	Passenger(string, string, string, string);
	~Passenger();

	//Getters
	string getPassengerFirstName() { return passengerFirstName; }
	string getPassengerLastName() { return passengerLastName; }
	string getFlightNumber() { return flightNumber; }
	string getAssignedSeat() { return assignedSeat; }

};

#endif