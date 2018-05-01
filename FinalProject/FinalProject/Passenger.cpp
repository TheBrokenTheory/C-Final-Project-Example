#include "Passenger.h"



Passenger::Passenger()
{
}

//Initialize passenger with all data
Passenger::Passenger(string flightNum, string seat, string fName, string lName)
{
	flightNumber = flightNum;
	assignedSeat = seat;
	passengerFirstName = fName;
	passengerLastName = lName;
}


Passenger::~Passenger()
{
}
