//============================================================================
// Name        : Sort.h
// Author      : Vajda Bela
// Date        : 8/1/2019
// Copyright   : None
// Description : Sort interface class and various sorting algorithms in C++
//============================================================================
#pragma once

#include "Flight.h"
#include <vector>

enum Sort_type { SELECTION_SORT, QUICK_SORT};


// Sort class
class Sort {
protected:
	// number of comparisons performed in sort function
	unsigned long num_cmps;
	unsigned long num_iter;
	unsigned long num_changes;
	long long iter;
	
public:
	Sort();
	// main entry point
	virtual void sort(std::vector<Flight>& data) = 0;
	//makes a step back in the sorting
	void step_back(std::vector<Flight>& data);
	//makes a step forward in the sorting
	void step_forward(std::vector<Flight>& data);
	//resets the data to the begining state
	void rewind(std::vector<Flight>& data);
	//puts data into sorted state
	void forward(std::vector<Flight>& data);

	/*sledece funkcije ne prate strostrupovu notaciju
	jer prva nametnuta funkcija getNumCmps ne prati tu notaciju
	radi konsistentnosti ni ja nisam
	takodje ";" je nepotreban i ona je Nametnuta*/
	// returns number of comparisons
	unsigned long getNumCmps() const { return num_cmps; };
	unsigned long getNumIter() const { return num_iter; }
	unsigned long getNumChanges() const { return num_changes; }
	long long getIter() const { return iter; }
	void setIter(long long i) { iter = i; }



	// functions for resetting counters
	void resetNumCmps() { num_cmps = 0; };
	void resetNumIter() { num_iter = 0; };
	void resetNumChanges() { num_changes = 0; };
	void resetAll();
	void set_steps(int n);

	//record of the sorting process
	std::vector<std::vector<int>> steps;
};

// SelectionSort class
class SelectionSort : public Sort {
public:
	// main entry point
	void sort(std::vector<Flight>& data);
};

//QuickSort class
class QuickSort : public Sort {
private:
	//recursive function for sorting 
	//separated from "sort" because cant change signiature from that functino 
	void quick_Sort(std::vector<Flight>& data, int begin, int end);
public:
	//main entry point
	void sort(std::vector<Flight>& data);
};