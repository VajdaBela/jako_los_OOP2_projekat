//============================================================================
// Name        : Flight.h
// Author      : Vajda Bela
// Date        : 8/1/2019
// Copyright   : None
// Description : Flight-class representing a flight
//				 FlightList-class representing many flights
//============================================================================
#pragma once
//TODO ispraviti time comparison

#include <iostream>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

enum Comparison_type{FLIGHTNO, DESTINATION, DEPARTURE, GATENO};

class Flight{
public:
	//functions for comparing two Flight classes
	static bool compare_flight_no(const Flight& F1, const Flight& F2);
	static bool compare_destination(const Flight& F1, const Flight& F2);
	static bool compare_departure(const Flight& F1, const Flight& F2);
	static bool compare_gate_no(const Flight& F1, const Flight& F2);

	//the metric by whic to compare
	static Comparison_type get_comparison_type() { return comp_type; }
	static void set_comparison_type(Comparison_type t) { comp_type = t; }
	static bool(*get_compare_function())(const Flight&, const Flight&);

	friend istream& operator >> (istream& in, Flight& fl);
	friend ostream& operator << (ostream& out, Flight& fl);

	string get_flight_no() { return flight_no; }
	string get_destination() { return destination; }
	string get_departure() { return departure; }
	string get_gate_no() { return gate_no; }
	void set_flight_no(string s) { flight_no = s; }
	void set_destination(string s) { destination = s; }
	void set_departure(string s) { departure = s; }
	void set_gate_no(string s) { gate_no = s; }

private:
	string flight_no;
	string destination;
	string departure;
	string gate_no;

	static Comparison_type comp_type;
};


class Flight_list {
public:
	friend istream& operator >> (istream& in, Flight_list& fl);
	friend ostream& operator << (ostream& out, Flight_list& fl);
	Flight_list* operator*() { return this; }
	void pushBack(Flight fl) { flights.push_back(fl); }

	vector<Flight> flights;
};