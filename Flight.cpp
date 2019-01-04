//============================================================================
// Name        : Flight.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of the Flight class
//============================================================================

#include "Flight.h"

ComparisonType Flight::comparisonType = FLIGHTNO;

int compareStr(const char* s1,const char* s2) {
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
	int firstChar = -1;
	int lastChar = -1;
	for (int i = 0; i < s.size(); ++i) {
		if (!isspace(s.at(i))) {
			lastChar = i;
			if (firstChar == -1)
				firstChar = i;
		}
	}
	if (firstChar != -1)
		s = s.substr(firstChar, lastChar - firstChar + 1);
	else
		s = "";
}

bool Flight::compareFlightNo(const Flight & F1, const Flight & F2) {
	return compareStr(F1.flightNo.c_str(), F2.flightNo.c_str()) > 0;
}

bool Flight::compareDestination(const Flight & F1, const Flight & F2) {
	return compareStr(F1.destination.c_str(), F2.destination.c_str()) > 0;
}

bool Flight::compareDeparture(const Flight & F1, const Flight & F2) {
	return compareStr(F1.departure.c_str(), F2.departure.c_str()) > 0;
}

bool Flight::compareGateNo(const Flight & F1, const Flight & F2) {
	return compareStr(F1.gateNo.c_str(), F2.gateNo.c_str()) > 0;
}

bool(*Flight::get_compare_function())(const Flight &, const Flight &){
	switch (Flight::comparisonType){
	case FLIGHTNO:
		return Flight::compareFlightNo;
		break;
	case DESTINATION:
		return Flight::compareDestination;
		break;
	case DEPARTURE:
		return Flight::compareDeparture;
		break;
	default://TODO figure out
	case GATENO:
		return Flight::compareGateNo;
		break;
	}
}

istream& operator >> (istream & in, Flight & fl){
	getline(in, fl.destination, ';');
	trim(fl.destination);
	getline(in, fl.departure, ';');
	trim(fl.departure);
	getline(in, fl.flightNo, ';');
	trim(fl.flightNo);
	getline(in, fl.gateNo, ';');
	trim(fl.gateNo);

	string trash; 
	getline(in,trash);

	return in;
}

istream& operator >> (istream & in, FlightList & fl)
{
	while (in) {
		Flight f;
		in >> f;
		fl.flights.push_back(f);
	}
	return in;
}
