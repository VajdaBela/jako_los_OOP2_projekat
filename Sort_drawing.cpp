#include "Sort_drawing.h"

void Drawing::draw() {
	//draws the graphic represantation of the sort
	fl_push_matrix();
	fl_translate(x(), y());
	fl_color(FL_BLACK);
	int y = BOX_HEIGHT / 2;
	//draws circles
	for (int j = 0; j < (*order)[0].size(); ++j) {
		int x = BOX_WIDTH + DOT_DISTANCE;
		for (int i = 0; i < order->size(); i++) {
			fl_circle(x, y, 5);
			x += DOT_DISTANCE;
		}
		y += BOX_HEIGHT;
	}

	int x = BOX_WIDTH + DOT_DISTANCE;
	y = BOX_HEIGHT / 2;
	//draws lines
	for (int i = 0; i < order->size() - 1; ++i) {
		for (int j = 0; j < (*order)[i].size(); ++j) {
			fl_begin_line();
			fl_vertex(x, j * BOX_HEIGHT + y);
			int k = 0;
			for (k = 0; k < (*order)[i + 1].size(); ++k)
				if ((*order)[i + 1][k] == j)
					break;
			fl_vertex(x + DOT_DISTANCE, k * BOX_HEIGHT + y);
			fl_end_line();
		}
		x += DOT_DISTANCE;
	}

	fl_pop_matrix();
}

Sort_drawing::Sort_drawing(int w, int h, const string& title) :
	Fl_Window{ w,h,title.c_str() }
{
	sort->rewind(flight_list.flights);
	for (Flight flight : flight_list.flights) {
		starting.push_back(flight.get_flight_no());
	}
	sort->forward(flight_list.flights);
	for (Flight flight : flight_list.flights) {
		ending.push_back(flight.get_flight_no());
	}

	begin();
	sc = new Fl_Scroll{ 0,0,w,h };
	this->resizable(sc);

	vector<int> lastPositions = sort->steps[sort->steps.size() - 1];
	int final_box_y = BOX_WIDTH + DOT_DISTANCE * (sort->steps.size() + 1);
	//the boxes on either side
	for (int i = 0; i < flight_list.flights.size(); ++i) {
		boxes.push_back(new Fl_Box{ FL_UP_BOX, 0, BOX_HEIGHT*lastPositions[i], BOX_WIDTH, BOX_HEIGHT, starting[i].c_str() });
		boxes.push_back(new Fl_Box{ FL_UP_BOX, final_box_y, BOX_HEIGHT*i, BOX_WIDTH, BOX_HEIGHT, ending[i].c_str() });
	}
	int i = (int)BOX_HEIGHT*lastPositions.size();
	//the drawing in-between
	d = new Drawing{ 0,0, final_box_y + BOX_WIDTH, i,0, &sort->steps };
	sc->end();
	end();
	show();
}