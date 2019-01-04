//============================================================================
// Name        : Sort.h
// Author      : 
// Date        :
// Copyright   : 
// Description : Sort interface class and various sorting algorithms in C++
//============================================================================
#pragma once

#include "Flight.h"
#include <vector>


// Sort class
class Sort
{
protected:
	// number of comparisons performed in sort function
	unsigned long num_cmps;
	unsigned long num_iter;
	unsigned long num_changes;
	std::vector<std::vector<int>> steps;
public:
	Sort();
	// main entry point
	virtual void sort(std::vector<Flight>& data) = 0;
	// returns number of comparisons
	unsigned long getNumCmps() const { return num_cmps; };
	// resets the number of comparisons
	void resetNumCmps() { num_cmps = 0; };
	void resetNumIter() { num_iter = 0; };
	void resetNumChanges() { num_changes = 0; };
	void resetAll();
	void setSteps(int n);
};

// SelectionSort class
class SelectionSort : public Sort
{
public:
	// main entry point
	void sort(std::vector<Flight>& data);
};

class QuickSort : public Sort {
private:
	void quick_Sort(std::vector<Flight>& data, int begin, int end);
public:
	void sort(std::vector<Flight>& data);
};