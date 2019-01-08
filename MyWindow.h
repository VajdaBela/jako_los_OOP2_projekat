//============================================================================
// Name        : Flight.h
// Author      : Vajda Bela
// Date        : 8/1/2019
// Copyright   : None
// Description : MyWindow-glavni prozor aplikacije
//				 My_manual-upustva za koriscenje
//============================================================================
#pragma once
//TODO promeniti boxeve za ?

#include "Window.h"
#include "Gui.h"
#include "Graph.h"
#include "Sort.h"
#include "Flight.h"
#include "FlightListVisual.h"
#include "Sort_drawing.h"

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Box.H>
#include <string.h>
#include <stdio.h>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.H>
#include <FL/math.h>

using namespace Graph_lib;

#define BUTTON_WIDTH 70
#define BUTTON_HEIGHT 20

class My_manual : public Window {
public:
	My_manual(Point xy, int w, int h, const string& title);
private:
	Out_box sortiraj_box;
	Out_box prikazi_box;
	Out_box ispisi_info_box;
	Out_box ispisi_sort_box;
	Out_box sledeci_box;
	Out_box prethodni_box;
	Out_box kraj_box;
	Out_box pocetak_box;
	Out_box upitnik_box;

};

/*MyWindow po zahtevu nije pisan po Strostupovoj notaciji*/
class MyWindow : public Window {
public:
	
	MyWindow(Point xy, int ww, int hh, const string& title);
	~MyWindow();

	void manual();
	void visual();
	void drawing();

	static void cb_manual(Address, Address);
	static void cb_sort(Address, Address);
	static void cb_previous(Address, Address);
	static void cb_next(Address, Address);
	static void cb_begining(Address, Address);
	static void cb_end(Address, Address);
	static void cb_write_info(Address, Address);
	static void cb_write_sorted(Address, Address);
	static void cb_drawing(Address, Address);

private:
	In_box in_file_box;
	In_box out_file_box;
	Fl_Choice* sort_type_box;
	Fl_Choice* comp_box;

	Out_box sort_iter_box;
	Out_box sort_switch_box;
	Out_box sort_comp_box;

	Button sort_button;
	Button show_sort_button;
	Button write_info_button;
	Button write_sorted_button;
	
	Button next_button;
	Button previous_button;
	Button begining_button;
	Button end_button;

	Button manual_button;

	Fl_Scroll* scroll;
	My_manual* man;
	Flight_list_visual* vi;

	Sort_drawing* sd;
};


