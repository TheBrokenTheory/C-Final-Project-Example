#ifndef FLIGHT_H
#define FLIGHT_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Passenger.h"
#include "Plane.h"



using namespace std;

class Flight
{
private:
	string departureCity;
	string arrivalCity;
	string departureTime;
	string arrivalTime;
	string flightNumber;
	string aircraftType;
	int frequentFlyerPoints;
	vector<Passenger*> passengersOnFlight;
	Plane *aircraft = nullptr;

	fstream passengerDataFile;

public:
	Flight();
	//Copy constructor
	Flight(const Flight&) {}
	Flight(string, string, string, string, string, string, int);
	~Flight();

	void readPassengerData();
	void getPassengersFromFlight();
	void initializePlane();
	void displayBoardingPass(string);
	void writePassengerData();
	bool checkFlightBooked();
	void displaySeatingArrangement();
	bool checkIfSeatBooked(string);
	void addNewPassenger(Passenger*);
	void removePassenger(string);

	//Getters
	string getDepartureCity() { return departureCity; }
	string getArrivalCity() { return arrivalCity; }
	string getDepartureTime() { return departureTime; }
	string getArrivalTime() { return arrivalTime; }
	string getFlightNumber() { return flightNumber; }
	string getAircraftType() { return aircraftType; }
	int getFrequentFlyerPoints() { return frequentFlyerPoints; }


	//Exception for file
	class FileNotFound
	{
	public:
		void getMessage() { cout << "ERROR: File Not Found"; }
	};
};

#endif