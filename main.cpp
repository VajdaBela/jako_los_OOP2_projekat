//============================================================================
// Name        : main.cpp
// Author      :
// Date        :
// Copyright   :
// Description :
//============================================================================

//TODO dvorecne identifikatore odvojiti dolnjom crtom

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <ctype.h>
#include <string.h>

#include "Flight.h"
#include "Sort.h"

using namespace std;





void main()
{
	ifstream in("inputFileExample.txt");
	string trash;
	getline(in, trash);
	FlightList fl;
	in >> fl;
	
	QuickSort sc;
	//sc.resetAll();
	sc.sort(fl.flights);

	cout << "abc";

}
