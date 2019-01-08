//============================================================================
// Name        : Sort.h
// Author      : Vajda Bela
// Date        : 8/1/2019
// Copyright   : None
// Description : Widget for showing a Flight_list
//============================================================================
#ifndef FLIGHTLISTVISUAL_H_
#define FLIGHTLISTVISUAL_H_



#include <vector>
#include <string.h>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>

#include "Flight.h"

using namespace std;

class Flight_list_visual : public Fl_Group {
public:
	Flight_list_visual(int x, int y, int w, Flight_list& fl);
	~Flight_list_visual();

private:
	vector<Fl_Box*> boxes;
	vector<char*> lables;

	void add_flight(Flight& fl, int x, int y);
	void make_box(int x, int y, string l);
};

#endif // !FLIGHTLISTVISUAL_H_
