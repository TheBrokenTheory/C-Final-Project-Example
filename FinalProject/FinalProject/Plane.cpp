#include "Plane.h"

Plane::Plane(string type)
{
	string planeTypeA[20] = { "1A", "1B", "1C", "1D", "2A", "2B", "2C", "2D",
		"3A", "3B", "3C", "3D", "4A", "4B", "4C", "4D", "5A", "5B", "5C", "5D" };

	string planeTypeB[15] = { "1A", "1B", "1C", "2A", "2B", "2C", "3A", "3B", "3C",
		"4A", "4B", "4C", "5A", "5B", "5C" };

	//Initialze each seat with empty(false)
	if (type == "A")
	{
		planeType = "A";
		for (int i = 0; i < 20; i++)
		{
			planeSeating[planeTypeA[i]] = false;
		}
	}
	else if (type == "B")
	{
		planeType = "B";
		for (int i = 0; i < 15; i++)
		{
			planeSeating[planeTypeB[i]] = false;
		}
	}
}

//Adds passenger to their seat
void Plane::addPassenger(string seat)
{
	planeSeating[seat] = true;
}

//Removes passenger
void Plane::removePassenger(string seat)
{
	planeSeating[seat] = false;
}
//Returns true if seat is empty, false if its booked
bool Plane::checkSeatBooked(string seat)
{
	bool seatBooked = false;

	if (planeSeating[seat] == true)
	{
		seatBooked = true;
	}

	return seatBooked;
}

//Returns true if plane if booked, false if there is room
bool Plane::checkPlaneBooked()
{
	bool seatStatus = true;

	for (map<string, bool>::iterator it = planeSeating.begin(); it != planeSeating.end(); it++)
	{
		if (it->second == false)
		{
			seatStatus = false;
		}
	}

	return seatStatus;
}

//Calls functions for the right plane type
void Plane::displaySeatingArrangement()
{
	if (planeType == "A")
	{
		displaySeatingTypeA();
	}
	else if (planeType == "B")
	{
		displaySeatingTypeB();
	}
}

//Displays seating chart for type A planes
void Plane::displaySeatingTypeA()
{
	int isleCounter = 0;
	int rowCounter = 2;

	cout << "\n  Seating Chart" << endl;
	cout << "   A  B  X  C  D" << endl;
	cout << "-----------------" << endl;
	cout << "1:";

	for (map<string, bool>::iterator it = planeSeating.begin(); it != planeSeating.end(); it++)
	{
		//Shows x to indicate the isle
		if (isleCounter == 2)
		{
			cout << " X ";
			isleCounter = 0;
		}

		if (it->second == true)
		{
			//Displays B if seat is already booked
			cout << " B";

			//Starts a new line if it gets to the end of the row
			if (it->first == "1D" || it->first == "2D" || it->first == "3D" || it->first == "4D")
			{
				cout << endl;
				cout << rowCounter << ":";
				isleCounter = 0;
				rowCounter++;
			}
			else
			{
				//puts spaces between each icon
				cout <<  " ";
				++isleCounter;
			}
		}
		else
		{
			//Displays a O if seat is open
			cout << " O";

			//Starts a new line if it gets to the end of the row
			if (it->first == "1D" || it->first == "2D" || it->first == "3D" || it->first == "4D")
			{
				cout << endl;
				cout << rowCounter << ":";
				isleCounter = 0;
				rowCounter++;
			}
			else
			{
				//puts spaces between each icon
				cout << " ";
				++isleCounter;
			}
		}
	}
	cout << "\n\n";
}

//Displays seating chart for type B planes
void Plane::displaySeatingTypeB()
{
	int isleCounter = 0;
	int rowCounter = 2;

	cout << "\n  Seating Chart" << endl;
	cout << "   A  X  B  C" << endl;
	cout << "---------------" << endl;
	cout << "1:";

	for (map<string, bool>::iterator it = planeSeating.begin(); it != planeSeating.end(); it++)
	{
		//Shows x to indicate the isle
		if (isleCounter == 1)
		{
			cout << " X ";
			//isleCounter = 0;
		}

		if (it->second == true)
		{
			//Displays B if seat is already booked
			cout << " B";

			//Starts a new line if it gets to the end of the row
			if (it->first == "1C" || it->first == "2C" || it->first == "3C" || it->first == "4C")
			{
				cout << endl;
				cout << rowCounter << ":";
				isleCounter = 0;
				rowCounter++;
			}
			else
			{
				//puts spaces between each icon
				cout << " ";
				++isleCounter;
			}
		}
		else
		{
			//Displays a O if seat is open
			cout << " O";

			//Starts a new line if it gets to the end of the row
			if (it->first == "1C" || it->first == "2C" || it->first == "3C" || it->first == "4C")
			{
				cout << endl;
				cout << rowCounter << ":";
				isleCounter = 0;
				rowCounter++;
			}
			else
			{
				//puts spaces between each icon
				cout << " ";
				++isleCounter;
			}
		}
	}
	cout << "\n\n";
}


Plane::~Plane()
{
}
