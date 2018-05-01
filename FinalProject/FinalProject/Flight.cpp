#include "Flight.h"

//Default no arg constructor
Flight::Flight()
{
}

//Initialize all members and reads passenger data to obj
Flight::Flight(string departCity, string arriveCity, string departTime, string arriveTime, string flightNum, string planeType, int flyerPoints)
{
	departureCity = departCity;
	arrivalCity = arriveCity;
	departureTime = departTime;
	arrivalTime = arriveTime;
	flightNumber = flightNum;
	aircraftType = planeType;
	frequentFlyerPoints = flyerPoints;

	//Creates the proper plane type object
	initializePlane();

	//Pulls passenger data from file for this flight
	readPassengerData();
}

//Reads passenger data for this flight
void Flight::readPassengerData()
{
	try
	{
		passengerDataFile.open("PassengerList.txt", ios::in);
		if (passengerDataFile.fail())
		{
			throw FileNotFound();
		}
	}
	catch (FileNotFound e)
	{
		e.getMessage();
	}

	//Only pulls passengers fro this flight
	while (!passengerDataFile.eof())
	{
		string flightNum;
		string seat;
		string firstName;
		string lastName;

		getline(passengerDataFile, flightNum, ' ');
		getline(passengerDataFile, seat, ' ');
		getline(passengerDataFile, firstName, ' ');
		getline(passengerDataFile, lastName, '\n');

		if (flightNum == flightNumber)
		{
			Passenger *newPassenger = new Passenger(flightNum, seat, firstName, lastName);
			aircraft->addPassenger(seat);	//Adds passenger to plane
			passengersOnFlight.push_back(newPassenger);	//Adds passenger to passenger list
		}
	}

	passengerDataFile.close();
}

//Returns list of passengers from this flight
void Flight::getPassengersFromFlight()
{
	cout << "\n\nPassengers on flight" << endl;
	cout << "--------------------" << endl;

	int size = passengersOnFlight.size();
	for (int i = 0; i < size; i++)
	{
		cout << passengersOnFlight[i]->getPassengerFirstName() << " " << passengersOnFlight[i]->getPassengerLastName()
			<< " " << passengersOnFlight[i]->getAssignedSeat() << endl;
	}
}

//Displays boarding pass if the name is on flight
void Flight::displayBoardingPass(string name)
{
	int size = passengersOnFlight.size();
	for (int i = 0; i < size; i++)
	{
		if (passengersOnFlight[i]->getPassengerFirstName() == name || passengersOnFlight[i]->getPassengerLastName() == name)
		{
			cout << "\n\nBOARDING PASS:" << endl;
			cout << "--------------" << endl;

			cout << passengersOnFlight[i]->getPassengerFirstName() << " " << passengersOnFlight[i]->getPassengerLastName() << endl;
			cout << "Seat: " << passengersOnFlight[i]->getAssignedSeat() << endl; 
			cout << "Flight #: " << flightNumber << endl;
			cout << "Flyer Miles: " << frequentFlyerPoints << endl;

		}
	}
}

//Creates the right aircraft type for this flight
void Flight::initializePlane()
{
	if (aircraftType == "A")
	{
		aircraft = new Plane("A");
	}
	else if (aircraftType == "B")
	{
		aircraft = new Plane("B");
	}
}

//Checks if flight is already booked, true if booked, false if there is room
bool Flight::checkFlightBooked()
{
	bool bookedFlight;

	bookedFlight = aircraft->checkPlaneBooked();

	return bookedFlight;
}

//Checks if seat is already booked, true if booked, false if open
bool Flight::checkIfSeatBooked(string seatNum)
{
	bool seatBooked = false;

	seatBooked = aircraft->checkSeatBooked(seatNum);

	return seatBooked;
}

//Displays seating chart
void Flight::displaySeatingArrangement()
{
	aircraft->displaySeatingArrangement();
}

//Adds a new passenger to the plane
void Flight::addNewPassenger(Passenger* pass)
{
	string seat = pass->getAssignedSeat();
	passengersOnFlight.push_back(pass);
	
	aircraft->addPassenger(seat);
}

//Removes a passenger from the flight and opens their seat back up
void Flight::removePassenger(string name)
{
	int size = passengersOnFlight.size();
	for (int i = 0; i < size; i++)
	{
		if (passengersOnFlight[i]->getPassengerFirstName() == name || passengersOnFlight[i]->getPassengerLastName() == name)
		{
			string seat = passengersOnFlight[i]->getAssignedSeat();
			aircraft->addPassenger(seat);

			passengersOnFlight.erase(passengersOnFlight.begin() + i);
		}
	}
}

//Writes all passenger data back to the file when the program 
//is closing. Appends to end
void Flight::writePassengerData()
{
	try
	{
		passengerDataFile.open("PassengerList.txt", ios::app);
		if (passengerDataFile.fail())
		{
			throw FileNotFound();
		}
	}
	catch (FileNotFound e)
	{
		e.getMessage();
	}

	int size = passengersOnFlight.size();
	for (int i = 0; i < size; i++)
	{
		passengerDataFile << flightNumber << " ";
		passengerDataFile << passengersOnFlight[i]->getAssignedSeat() << " ";
		passengerDataFile << passengersOnFlight[i]->getPassengerFirstName() << " ";
		passengerDataFile << passengersOnFlight[i]->getPassengerLastName() << "\n";
	}

	passengerDataFile.close();
}

Flight::~Flight()
{

}
