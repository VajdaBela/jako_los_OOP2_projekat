//============================================================================
// Name        : Flight.h
// Author      : Vajda Bela
// Date        : 2/1/2019
// Copyright   : None
// Description : 
//============================================================================
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

enum ComparisonType{FLIGHTNO, DESTINATION, DEPARTURE, GATENO};

class Flight{
public:
	static bool compareFlightNo(const Flight& F1, const Flight& F2);
	static bool compareDestination(const Flight& F1, const Flight& F2);
	static bool compareDeparture(const Flight& F1, const Flight& F2);
	static bool compareGateNo(const Flight& F1, const Flight& F2);

	friend istream& operator >> (istream& in, Flight& fl);

	string flightNo;
	string destination;
	string departure;
	string gateNo;

	static ComparisonType comparisonType;
	static void setComparisonType(ComparisonType t) { comparisonType = t; }
	static bool(*get_compare_function())(const Flight&, const Flight&);
};


class FlightList {
public:
	friend istream& operator >> (istream& in, FlightList& fl);
	void pushBack(Flight fl) { flights.push_back(fl); }
	vector<Flight> flights;
};