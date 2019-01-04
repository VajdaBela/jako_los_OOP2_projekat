//============================================================================
// Name        : Sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of the sort classes
//============================================================================

#include "Sort.h"

using namespace std;

void Sort::resetAll() {
	resetNumCmps();
	resetNumIter();
	resetNumChanges();
}

void Sort::setSteps(int n) {
	steps.clear();
	vector<int> default;
	for (int i = 0; i < n; ++i)
		default.push_back(i);
	steps.push_back(default);
}

Sort::Sort() {
	num_cmps = 0;
	num_iter = 0;
	num_changes = 0;
}

void SelectionSort::sort(std::vector<Flight>& data){
	setSteps(data.size());
	auto compFunc = Flight::get_compare_function();
	
	for (int i = 0; i < data.size(); ++i) {
		vector<int> step(steps.back());
		++num_iter;
		int smallestIdx = i;
		for (int j = i + 1; j < data.size(); ++j) {
			++num_cmps;
			if (compFunc(data[smallestIdx], data[j]))
				smallestIdx = j;
		}
		if (smallestIdx == i)
			continue;
		int t = step[i];
		step[i] = step[smallestIdx];
		step[smallestIdx] = step[i];
		++num_changes;
		Flight temp = data[i];
		data[i] = data[smallestIdx];
		data[smallestIdx] = temp;
		steps.push_back(step);
	}
}

void QuickSort::quick_Sort(std::vector<Flight>& data, int begin, int end) {
	if (begin >= end)
		return;
	vector<int> step(steps.back());
	auto compFunc = Flight::get_compare_function();
	int pivot = begin;
	int nextBegin = begin;
	int nextEnd = end;
	++begin;


	while (true) {
		while (begin != end && compFunc(data[pivot], data[begin])) {
			++begin;
			++num_cmps;
		}
		while (end != pivot && compFunc(data[end], data[pivot])) {
			--end;
			++num_cmps;
		}
		if (begin >= end)
			break;
		++num_changes;

		int t = step[begin];
		step[begin] = step[end];
		step[end] = t;
		Flight temp = data[begin];
		data[begin] = data[end];
		data[end] = temp;
	}
	if (end != pivot) {
		++num_changes;
		int t = step[end];
		step[end] = step[pivot];
		step[pivot] = t;
		Flight temp = data[end];
		data[end] = data[pivot];
		data[pivot] = temp;
	}

	steps.push_back(step);
	quick_Sort(data, nextBegin,  end - 1);
	quick_Sort(data, end + 1, nextEnd);
	++num_iter;
}

void QuickSort::sort(std::vector<Flight>& data){
	setSteps(data.size());
	quick_Sort(data, 0, data.size() - 1);
}
