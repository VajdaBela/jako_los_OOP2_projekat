#ifndef SORT_DRAWING_H_
#define SORT_DRAWING_H_

#include <string.h>
#include <stdio.h>
#include <FL/Fl.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

#include "Sort.h"
#include "FlightListVisual.h"

#define DOT_DISTANCE 40
#define BOX_WIDTH 100
#define BOX_HEIGHT 20

extern Flight_list flight_list;
extern Sort* sort;


class Drawing : public Fl_Widget {
public:
	Drawing(int x, int y, int w, int h, const char* l, vector<vector<int>>* o) : Fl_Widget(x, y, w, h, l), order(o) {}
private:
	void draw();
	vector<vector<int>>* order;
};



class Sort_drawing : public Fl_Window {
public:

	Sort_drawing(int w, int h, const string& title);
	Drawing* d;
	Fl_Scroll* sc;
	vector<string> starting;
	vector<string> ending;
	vector<Fl_Box*> boxes;

};

#endif // !SORT_DRAWING_H_
