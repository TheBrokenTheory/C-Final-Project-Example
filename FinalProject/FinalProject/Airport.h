#ifndef AIRPORT_H
#define AIRPORT_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include<vector>
#include "Flight.h"
#include "Passenger.h"

using namespace std;

class Airport
{
private:
	ifstream flightSchedule;
	vector<Flight*> allFlights;

	void readFlightSchedule();
	void bookNewReservation();
	void cancelReservation();
	void displayBoardingPass();
	void displayFlightSchedule();
	void displayAvailableCities();
	void listPassengersOnFlight();
	bool checkFlightBooked(string);
	void showAlternativeFlights(string);
	void displaySeatingArrangement(string);
	bool checkIfSeatBooked(string, string);
	void addNewPassenger(string, Passenger*);
	bool validateSeatNumber(string);
	bool validateFlightNumber(string);
	bool validteName(string);

public:
	Airport();
	~Airport();
	void controlMenu();

	//Exception for file
	class FileNotFound
	{
	public:
		void getMessage() { cout << "ERROR: File Not Found"; }
	};

};

#endif