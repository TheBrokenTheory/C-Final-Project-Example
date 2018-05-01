#include "Airport.h"

//Default constructor, pulls flight data from file
Airport::Airport()
{
	readFlightSchedule();
}

//Reads flight schedules from file
//Creates flight objects with that info
void Airport::readFlightSchedule()
{
	try
	{
		flightSchedule.open("Flights.txt", ios::in);
		if (flightSchedule.fail())
		{
			throw FileNotFound();
		}
	}
	catch (FileNotFound e)
	{
		e.getMessage();
	}

	while (!flightSchedule.eof())
	{
		string departureCity;
		string arrivalCity;
		string departureTime;
		string arrivalTime;
		string flightNumber;
		string aircraftType;
		string s;
		int frequentFlyerPoints;
		
		//Pulling flights from file
		getline(flightSchedule, departureCity, ' ');
		getline(flightSchedule, arrivalCity, ' ');
		getline(flightSchedule, departureTime, ' ');
		getline(flightSchedule, arrivalTime, ' ');
		getline(flightSchedule, flightNumber, ' ');
		getline(flightSchedule, aircraftType, ' ');
		getline(flightSchedule, s, '\n');
		frequentFlyerPoints = atoi(s.c_str());	//Converting string to int

		//Add new flight to allFlights vector
		allFlights.push_back(new Flight(departureCity, arrivalCity, departureTime, arrivalTime, flightNumber, aircraftType, frequentFlyerPoints));
	}

	//Close file
	flightSchedule.close();
}

//Main control menu for all user operations
void Airport::controlMenu()
{
	int menuChoice = 0;

	while (menuChoice != 7)
	{
		cout << "\tNew York City Airport" << endl;
		cout << "------------------------------------------" << endl;
		cout << "1.) Book a new reservation" << endl;
		cout << "2.) Cancel a reservation" << endl;
		cout << "3.) Display boarding pass for a passenger" << endl;
		cout << "4.) Display flight schedule" << endl;
		cout << "5.) Display available cities" << endl;
		cout << "6.) List passengers on a flight" << endl;
		cout << "7.) Quit" << endl;

		cin >> menuChoice;
		while (menuChoice < 0 || menuChoice > 7)
		{
			cout << "Enter a valid choice: ";
			cin >> menuChoice;
		}

		switch (menuChoice)
		{
		case 1:
			bookNewReservation();
			break;
		case 2:
			cancelReservation();
			break;
		case 3:
			displayBoardingPass();
			break;
		case 4:
			displayFlightSchedule();
			break;
		case 5:
			displayAvailableCities();
			break;
		case 6:
			listPassengersOnFlight();
			break;
		case 7:
			break;
		}
	}
}

//Books a new reservation
//Asks user for passenger info
//Shows available flights and seats
//If flight is booked, it will show other flights
//to the same destination
void Airport::bookNewReservation()
{
	string flightNum;
	string firstName;
	string lastName;
	string seatNum;

	system("cls");	//Clears screen
	displayFlightSchedule();

	cout << "Enter the flight number: ";
	cin >> flightNum;
	while (!validateFlightNumber(flightNum))
	{
		cout << "Enter a valid flight Number: ";
		cin >> flightNum;
	}
	
	if (checkFlightBooked(flightNum))
	{
		cout << "Sorry, this flight is already booked. Here are some alternative flights: " << endl;
		showAlternativeFlights(flightNum);
	}
	else
	{
		//Display seating arrangement
		displaySeatingArrangement(flightNum);

		cout << "Enter seat number: ";
		cin >> seatNum;
		
		while (!validateSeatNumber(seatNum))
		{
			cout << "Enter a valid seat number: ";
			cin >> seatNum;
		}

		//Checks if seat is already booked
		while (checkIfSeatBooked(flightNum, seatNum))
		{
			cout << "That seat is already booked" << endl;
			cout << "Enter seat number: ";
			cin >> seatNum;
			while (!validateSeatNumber(seatNum))
			{
				cout << "Enter a valid seat number: ";
				cin >> seatNum;
			}
		}

		cout << "Enter passenger first name: ";
		cin >> firstName;
		while (!validteName(firstName))
		{
			cout << "Enter valid passenger first name: ";
			cin >> firstName;
		}

		cout << "Enter passenger last name: ";
		cin >> lastName;
		while (!validteName(lastName))
		{
			cout << "Enter valid passenger last name: ";
			cin >> lastName;
		}

		//Creates new passenger and adds it to the flight
		Passenger *passenger = new Passenger(flightNum, seatNum, firstName, lastName);
		addNewPassenger(flightNum, passenger);
	}
}

//Cancels a flight reservation
//Removes passenger from flight and plane
//Opens their seat up to be book by another passenger
void Airport::cancelReservation()
{
	system("cls");	//Clears screen

	string name;
	string flightNum;

	cout << "Enter the flight number: ";
	cin >> flightNum;
	while (!validateFlightNumber(flightNum))
	{
		cout << "Enter a valid flight Number: ";
		cin >> flightNum;
	}

	cout << "Enter the first or last name attached to the boarding pass: ";
	cin >> name;
	while (!validteName(name))
	{
		cout << "Enter valid passenger name: ";
		cin >> name;
	}

	int size = allFlights.size();
	for (int i = 0; i < size; i++)
	{
		if(allFlights[i]->getFlightNumber() == flightNum)
		{
			allFlights[i]->removePassenger(name);
		}
	}

	cout << "Reservation has been canceled." << endl;
	cout << "\n\n";
}

//Displays boarding pass info for a passenger
//Asks the user to enter the first or last name
void Airport::displayBoardingPass()
{
	system("cls");	//Clears screen

	string name;
	cout << "Enter the first or last name attached to the boarding pass: ";
	cin >> name;
	while (!validteName(name))
	{
		cout << "Enter valid passenger name: ";
		cin >> name;
	}

	int size = allFlights.size();
	for (int i = 0; i < size; i++)
	{
		allFlights[i]->displayBoardingPass(name);
	}
	cout << "\n\n";
}

//Displays flight schedule
//Allows user to sort by arrival city or departure city
void Airport::displayFlightSchedule()
{
	system("cls");	//Clears screen

	cout << "\t\t\tFlight Schedule" << endl;
	cout << "From | To | Depart | Arrival | Flight # | Aircraft Type | Flyer Points" << endl;
	cout << "-----------------------------------------------------------------------" << endl;

	int size = allFlights.size();
	for (int i = 0; i < size; i++)
	{
		cout << left << setw(3) << allFlights[i]->getDepartureCity() << "    ";
		cout << left << setw(3) << allFlights[i]->getArrivalCity() << "   ";
		cout << left << setw(5) << allFlights[i]->getDepartureTime() << "    ";
		cout << left << setw(5) << allFlights[i]->getArrivalTime() << "      ";
		cout << left << setw(4) << allFlights[i]->getFlightNumber() << "          ";
		cout << left << setw(1) << allFlights[i]->getAircraftType() << "            ";
		cout << left << setw(4) << allFlights[i]->getFrequentFlyerPoints()<< "\n\n";
	}
}

//Displays a list of all available cities
void Airport::displayAvailableCities()
{
	system("cls");	//Clears screen

	cout << "Available Cities" << endl;
	cout << "----------------" << endl;
	cout << "ATL Atlanta" << endl;
	cout << "ORL Orlando" << endl;
	cout << "DFW Dallas/Fort Worth" << endl;
	cout << "NYC New York City" << endl;
	cout << "HAW Hawaii" << endl;
	cout << "CHI Chicago" << endl;
	cout << "LAX LosAngeles" << endl;
	cout << "\n\n";
}

//Asks the user to enter a flight number,
//Then displays all the passengers on that flight
void Airport::listPassengersOnFlight()
{
	system("cls");	//Clears screen

	string selectedFlight;

	cout << "Enter the flight number to view all the passengers: ";
	cin >> selectedFlight;
	while (!validateFlightNumber(selectedFlight))
	{
		cout << "Enter a valid flight Number: ";
		cin >> selectedFlight;
	}

	int size = allFlights.size();
	for (int i = 0; i <size; i++)
	{
		
		if (!selectedFlight.compare(allFlights[i]->getFlightNumber()))
		{
			allFlights[i]->getPassengersFromFlight();
		}
	}
	cout << "\n\n";
}

//Checks if flight is already booked, true if booked, false if there is room
bool Airport::checkFlightBooked(string flightNum)
{
	bool bookedFlight;

	int size = allFlights.size();
	for (int i = 0; i < size; i++)
	{
		if (!flightNum.compare(allFlights[i]->getFlightNumber()))
		{
			bookedFlight = allFlights[i]->checkFlightBooked();
		}
	}

	return bookedFlight;
}

//Displays alternative flights to the same destination from the same departure city
void Airport::showAlternativeFlights(string flightNum)
{
	string departureCity;
	string arrivalCity;
	int size = allFlights.size();

	//get the arrival and departure city
	for (int i = 0; i < size; i++)
	{
		if (!flightNum.compare(allFlights[i]->getFlightNumber()))
		{
			departureCity = allFlights[i]->getDepartureCity();
			arrivalCity = allFlights[i]->getArrivalCity();
		}
	}

	cout << "\n\t\t\tFlight Schedule" << endl;
	cout << "From | To | Depart | Arrival | Flight # | Aircraft Type | Flyer Points" << endl;
	cout << "-----------------------------------------------------------------------" << endl;

	//Display alternative flights
	for (int i = 0; i < size; i++)
	{
		if (!flightNum.compare(allFlights[i]->getFlightNumber()))
		{
			continue;
		}
		else if (!departureCity.compare(allFlights[i]->getDepartureCity()) && !arrivalCity.compare(allFlights[i]->getArrivalCity()))
		{
			cout << left << setw(3) << allFlights[i]->getDepartureCity() << "    ";
			cout << left << setw(3) << allFlights[i]->getArrivalCity() << "   ";
			cout << left << setw(5) << allFlights[i]->getDepartureTime() << "    ";
			cout << left << setw(5) << allFlights[i]->getArrivalTime() << "      ";
			cout << left << setw(4) << allFlights[i]->getFlightNumber() << "          ";
			cout << left << setw(1) << allFlights[i]->getAircraftType() << "            ";
			cout << left << setw(4) << allFlights[i]->getFrequentFlyerPoints() << "\n\n";
		}
	}
}

//Displays seating chart for flight (Shows which seats have already been booked)
void Airport::displaySeatingArrangement(string flightNum)
{
	int size = allFlights.size();
	for (int i = 0; i < size; i++)
	{
		if (!flightNum.compare(allFlights[i]->getFlightNumber()))
		{
			allFlights[i]->displaySeatingArrangement();
		}
	}
}

//Checks if seat is already booked, true if booked, false if open
bool Airport::checkIfSeatBooked(string flightNum, string seatNum)
{
	bool seatBooked = false;
	int size = allFlights.size();
	for (int i = 0; i < size; i++)
	{
		if (!flightNum.compare(allFlights[i]->getFlightNumber()))
		{
			seatBooked = allFlights[i]->checkIfSeatBooked(seatNum);
		}
	}

	return seatBooked;
}

//Adds a new passenger to the flight
void Airport::addNewPassenger(string flightNum, Passenger* pass)
{
	int size = allFlights.size();
	for (int i = 0; i < size; i++)
	{
		if (!flightNum.compare(allFlights[i]->getFlightNumber()))
		{
			allFlights[i]->addNewPassenger(pass);
		}
	}
}

//Returns true if the flightNum is good, false if its not
bool Airport::validateSeatNumber(string seatNumber)
{
	bool seatNumValidates = true;

	//Getting the first char
	string seatNumString = seatNumber.substr(0, 1);
	const char *seatNum = seatNumString.c_str();

	//Converting char to int
	int seat = *seatNum - 48;

	//Getting second char
	string seatLetterString = seatNumber.substr(1, 1);
	const char *seatLetter = seatLetterString.c_str();
	
	//Testing seat number
	if (!isdigit(*seatNum))
	{
		seatNumValidates = false;
	}
	else if (seat <= 0 || seat >= 6)
	{
		seatNumValidates = false;
	}

	//Testing seat Letter
	if (!isalpha(*seatLetter))
	{
		seatNumValidates = false;
	}
	else
	{
		for (int i = 0; i < seatNumString.size(); i++)
		{
			//Convert char to upper case
			int uppercaseChar = toupper(seatNumber[1]);
			if (uppercaseChar < 'A' || uppercaseChar >= 'D')
			{
				seatNumValidates = false;
			}
		}
	}
	
	return seatNumValidates;
}

//Validates that the user entered a correct flight number
//Returns true if valid, false if not
bool Airport::validateFlightNumber(string flightNum)
{
	bool flightNumValidates = false;

	int size = allFlights.size();
	for (int i = 0; i < size; i++)
	{
		//If it matches a flight number it returns true, else it returns false
		if (!flightNum.compare(allFlights[i]->getFlightNumber()))
		{
			flightNumValidates = true;
		}
	}

	return flightNumValidates;
}

//Validates the user entered a name only containing characters
//returns true if it is valid, false if not
bool Airport::validteName(string name)
{
	bool nameValidates = true;

	//Cycles through every character in name to make sure its a letter
	int size = name.size();
	for (int i = 0; i < size; i++)
	{
		//Convert char to upper case
		int uppercaseChar = toupper(name[i]);
		if (uppercaseChar < 'A' || uppercaseChar > 'Z')
		{
			nameValidates = false;
		}
	}

	return nameValidates;
}

//TODO Delete any dynamic mem
Airport::~Airport()
{
	//Clear passenger file
	fstream passengerDataFile; 
	passengerDataFile.open("PassengerList.txt", ios::out);
	passengerDataFile.close();

	//Write all passenger data to file
	int size = allFlights.size();
	for (int i = 0; i <size; i++)
	{
		allFlights[i]->writePassengerData();
	}
}
