//============================================================================
// Name        : Flight.h
// Author      : Vajda Bela
// Date        : 8/1/2019
// Copyright   : None
// Description : Implementation of the Flight class
//				 Implementation of the FlightList class
//============================================================================

#include "Flight.h"

Comparison_type Flight::comp_type = FLIGHTNO;

int compare_str(const char* s1,const char* s2) {
	//case insensitive comparison of c style strings
	while (*s1 != '\0' && *s2 != '\0') {
		int rez = tolower(*s1) - tolower(*s2);
		if (rez != 0)
			return rez;
		++s1;
		++s2;
	}
	if (*s1 == '\0' && *s2 == '\0')
		return 0;
	else if (*s1 == '\0')
		return -1;
	else
		return 1;
}

void trim(string& s) {
	//removes all white spaces from the begining and end
	int first_char = -1;
	int last_char = -1;
	for (int i = 0; i < s.size(); ++i) {
		if (!isspace(s.at(i))) {
			last_char = i;
			if (first_char == -1)
				first_char = i;
		}
	}
	if (first_char != -1)
		s = s.substr(first_char, last_char - first_char + 1);
	else
		s = "";
}

bool Flight::compare_flight_no(const Flight & F1, const Flight & F2) {
	return compare_str(F1.flight_no.c_str(), F2.flight_no.c_str()) > 0;
}

bool Flight::compare_destination(const Flight & F1, const Flight & F2) {
	return compare_str(F1.destination.c_str(), F2.destination.c_str()) > 0;
}

bool Flight::compare_departure(const Flight & F1, const Flight & F2) {
	return compare_str(F1.departure.c_str(), F2.departure.c_str()) > 0;
}

bool Flight::compare_gate_no(const Flight & F1, const Flight & F2) {
	return compare_str(F1.gate_no.c_str(), F2.gate_no.c_str()) > 0;
}

bool(*Flight::get_compare_function())(const Flight &, const Flight &) {
	switch (Flight::comp_type) {
	default:
	case FLIGHTNO:
		return Flight::compare_flight_no;
		break;
	case DESTINATION:
		return Flight::compare_destination;
		break;
	case DEPARTURE:
		return Flight::compare_departure;
		break;
	case GATENO:
		return Flight::compare_gate_no;
		break;
	}
}

istream& operator >> (istream & in, Flight & fl) {
	getline(in, fl.destination, ';');
	trim(fl.destination);
	getline(in, fl.departure, ';');
	trim(fl.departure);
	getline(in, fl.flight_no, ';');
	trim(fl.flight_no);
	getline(in, fl.gate_no, ';');
	trim(fl.gate_no);

	string trash; 
	getline(in,trash);

	return in;
}

ostream & operator << (ostream & out, Flight & fl) {
	return out << fl.destination << ";" << fl.departure << ";"
		<< fl.flight_no << ";" << fl.gate_no;
}

istream& operator >> (istream & in, Flight_list & fl) {
	while (in) {
		Flight f;
		in >> f;
		fl.flights.push_back(f);
	}
	return in;
}

ostream & operator << (ostream & out, Flight_list & fl) {
	for (Flight flight : fl.flights) {
		out << flight << endl;
	}
	return out;
}
