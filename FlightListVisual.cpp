//============================================================================
// Name        : Sort.h
// Author      : Vajda Bela
// Date        : 8/1/2019
// Copyright   : None
// Description : implementation of class Flight_list_visual
//============================================================================
#include "FlightListVisual.h"

#define X 200

Flight_list_visual::Flight_list_visual(int x, int y, int w, Flight_list& fl) :
	Fl_Group(x,y,w, fl.flights.size()*25 + 40)
{
	boxes.push_back(new Fl_Box(x + 1, y, 50, 50, "broj leta:")); //width and height is irelevant
	boxes.push_back(new Fl_Box(x + X, y, 50, 50, "destinacija:"));
	boxes.push_back(new Fl_Box(x + X*2, y, 50, 50, "vreme poleta:"));
	boxes.push_back(new Fl_Box(x + X*3, y, 50, 50, "broj kapijhe:"));
	y = 50;
	for(Flight flight:fl.flights) {
		add_flight(flight, x, y);
		y += 25;
	}
	end();
}

Flight_list_visual::~Flight_list_visual() {
	for (int i = 0; i < boxes.size(); ++i)
		delete boxes[i];
	boxes.clear();
	for (int i = 0; i < lables.size(); ++i)
		delete[] lables[i];
	lables.clear();
}

void Flight_list_visual::add_flight(Flight& fl, int x, int y) {
	make_box(x, y, fl.get_flight_no());
	make_box(x + X, y, fl.get_destination());
	make_box(x + X * 2, y, fl.get_departure());
	make_box(x + X * 3, y, fl.get_gate_no());
}

void Flight_list_visual::make_box(int x, int y, string l) {
	char* temp = new char[l.size() + 1];
	strcpy(temp, l.c_str());
	lables.push_back(temp);
	boxes.push_back(new Fl_Box(x, y, 50, 50, temp));
}
