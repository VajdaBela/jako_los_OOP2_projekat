//============================================================================
// Name        : main.cpp
// Author      : Vajda Bela
// Date        : 8/1/2019
// Copyright   : None
// Description : the entrypoint to the program
//============================================================================

#include <string>
#include <fstream>
#include <iostream>
#include <FL/Fl.H>

#include "Flight.h"
#include "Sort.h"
#include "MyWindow.h"

using namespace std;

Sort_type sort_type;
Flight_list flight_list;
Sort* sort;

const string acceptable_sort[] = { "quick_sort", "selection_sort" };
const string acceptable_criteria[] = {"flight_no", "destination", "departure", "gate_no"};

bool check_string_valid(const string s,const string arr[], int n) {
	for (int i = 0; i < n; ++i) {
		if (s == arr[i])
			return true;
	}
	return false;
}

class Input_handle {
public:
	Input_handle(int argc, char** argv) {
		if (argc != 6) {
			correct = false;
			return;
		}
		if (!check_string_valid(argv[4], acceptable_sort, 2)) {
			correct = false;
			return;
		}
		if (!check_string_valid(argv[5], acceptable_criteria, 4)) {
			correct = false;
			return;
		}
		flight_input_file = string(argv[1]);
		flight_out_file = string(argv[2]);
		sort_result_file = string(argv[3]);
		sort_type = string(argv[4]);
		sort_by = string(argv[5]);
		correct = true;
	}

	bool correct;	
	string flight_input_file;
	string flight_out_file;
	string sort_result_file;
	string sort_type;
	string sort_by;
};

void console_work(Input_handle arguments) {
	ifstream in(arguments.flight_input_file);
	ofstream out1(arguments.flight_out_file);
	ofstream out2(arguments.sort_result_file);
	if (acceptable_sort[0] == arguments.sort_type)
		sort = new QuickSort();
	else
		sort = new SelectionSort();

	if (acceptable_criteria[0] == arguments.sort_by)
		Flight::set_comparison_type(FLIGHTNO);
	else if (acceptable_criteria[1] == arguments.sort_by)
		Flight::set_comparison_type(DESTINATION);
	else if (acceptable_criteria[2] == arguments.sort_by)
		Flight::set_comparison_type(DEPARTURE);
	else if (acceptable_criteria[3] == arguments.sort_by)
		Flight::set_comparison_type(GATENO);

	string trash;
	getline(in, trash);
	in >> flight_list;
	sort->sort(flight_list.flights);
	out1 << flight_list;
	out2 << "broj pomeranja: " << sort->getNumChanges() << endl
		<< "broj iteracija: " << sort->getNumIter() << endl
		<< "broj uporedjenja: " << sort->getNumCmps() << endl;
	out2.close();
	out1.close();
	in.close();
}

void main(int argc, char** argv) {
	Input_handle arguments(argc, argv);
	//gui
	if (argc == 1) {
		MyWindow my_window{ Point(Fl::w() / 4, Fl::h() / 4), Fl::w() / 2,Fl::h() / 2,"Flight Sorter" };
		Fl::run();
		return;
	}
	//console
	else if (arguments.correct) {
		console_work(arguments);
		return;
	}
	//bad input
	else {
		cout << "nevalidan broj argumenata, treba da ih bude 5" << endl
			<< "<input_file> <sorted_out_file> <sort_performace_file> <sort_type> <sort_criterium>" << endl;
		return;
	}
}
