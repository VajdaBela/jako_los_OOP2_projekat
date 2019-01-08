//============================================================================
// Name        : Sort.cpp
// Author      : Vajda Bela
// Date        : 8/1/2019
// Copyright   : None
// Description : Implementation of the sort classes
//============================================================================

#include "Sort.h"

using namespace std;

Sort::Sort() :
	num_cmps(0),
	num_iter(0),
	num_changes(0),
	iter(0)
{}

void Sort::step_back(std::vector<Flight>& data) {
	if (iter <= 0)
		return; //TODO vici
	vector<Flight> temp(data);
	for(int i = 0; i < data.size(); ++i) {
		data[steps[iter][i]] = temp[i];
	}
	--iter;
}

void Sort::step_forward(std::vector<Flight>& data) {
	if (iter >= steps.size() - 1)
		return;//TODO vici
	++iter;
	vector<Flight> temp(data);
	for (int i = 0; i < data.size(); ++i) {
		data[i] = temp[steps[iter][i]];
	}
}

void Sort::rewind(std::vector<Flight>& data) {
	while (iter > 0)
		step_back(data);
}

void Sort::forward(std::vector<Flight>& data) {
	while (iter < steps.size() - 1)
		step_forward(data);
}

void Sort::resetAll() {
	resetNumCmps();
	resetNumIter();
	resetNumChanges();
}

void Sort::set_steps(int n) {
	steps.clear();
	vector<int> default;
	for (int i = 0; i < n; ++i)
		default.push_back(i);
	steps.push_back(default);
}


void SelectionSort::sort(std::vector<Flight>& data) {
	//for evry index finds smallest element in the remainder of the data
	set_steps(data.size());
	auto comp_func = Flight::get_compare_function();
	
	for (int i = 0; i < data.size(); ++i) {
		vector<int> step(steps[0]);
		++num_iter;
		int smallest_idx = i;
		for (int j = i + 1; j < data.size(); ++j) {
			++num_cmps;
			if (comp_func(data[smallest_idx], data[j]))
				smallest_idx = j;
		}
		if (smallest_idx == i) {
			steps.push_back(step);
			continue;
		}
			
		int t = step[i];
		step[i] = step[smallest_idx];
		step[smallest_idx] = t;
		++num_changes;
		Flight temp = data[i];
		data[i] = data[smallest_idx];
		data[smallest_idx] = temp;
		steps.push_back(step);
	}
	iter = num_iter;
}

void QuickSort::quick_Sort(std::vector<Flight>& data, int begin, int end) {
	//takes first element az pivot
	//partitions data into smaller then the first and bigger than the first
	//puts the first in place and calls itself for the partitions
	if (begin >= end)
		return;
	vector<int> step(steps[0]);
	auto comp_func = Flight::get_compare_function();
	int pivot = begin;
	int next_begin = begin;
	int next_end = end;
	++begin;


	while (true) {
		while (begin != end && comp_func(data[pivot], data[begin])) {
			++begin;
			++num_cmps;
		}
		while (end != pivot && comp_func(data[end], data[pivot])) {
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
	quick_Sort(data, next_begin,  end - 1);
	quick_Sort(data, end + 1, next_end);
	++num_iter;
}

void QuickSort::sort(std::vector<Flight>& data) {
	set_steps(data.size());
	quick_Sort(data, 0, data.size() - 1);
	iter = num_iter;
}
