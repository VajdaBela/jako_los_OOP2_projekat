//============================================================================
// Name        : Flight.h
// Author      : Vajda Bela
// Date        : 8/1/2019
// Copyright   : None
// Description : Implementacija MyWindow i My_manual
//============================================================================
#include "MyWindow.h"
//TODO vreme lose uporedjuje
#define X_POSITION 110
#define X_POSITION2 30
#define X_POSITION3 140
#define WIDTH 120
#define WIDTH2 90
#define HEIGHT 20

extern Sort_type sort_type;
extern Flight_list flight_list;
extern Sort* sort;
extern string file_name;

/*items and callbacks for choice buttons*/
void cb_comp_type(Fl_Widget*, void* t) {
	Flight::set_comparison_type( static_cast<Comparison_type>((fl_intptr_t)t));
}

Fl_Menu_Item comp_menu[] = {
	{ "broj leta", 0, cb_comp_type, (void*)FLIGHTNO },
	{ "destinacija", 0, cb_comp_type, (void*)DESTINATION },
	{ "vreme poleta", 0, cb_comp_type, (void*)DEPARTURE },
	{ "kapija", 0, cb_comp_type, (void*)GATENO },
	{ 0 }
};

void cb_sort_type(Fl_Widget*, void* t) {
	sort_type = static_cast<Sort_type>((fl_intptr_t)t);
}

Fl_Menu_Item sort_menu[] = {
	{ "selection sort", 0, cb_sort_type, (void*)SELECTION_SORT},
	{ "quick sort", 0, cb_sort_type, (void*)QUICK_SORT },
	{0}
};



My_manual::My_manual(Point xy, int w, int h, const string& title) :
	Window(xy, w, h, title),
	sortiraj_box(Point(0, 0), w, HEIGHT, ""),
	prikazi_box(Point(0,20), w, HEIGHT, ""),
	ispisi_info_box(Point(0,40), w, HEIGHT, ""),
	ispisi_sort_box(Point(0, 60), w, HEIGHT, ""),
	sledeci_box(Point(0, 80), w, HEIGHT, ""),
	prethodni_box(Point(0, 100), w, HEIGHT, ""),
	kraj_box(Point(0, 120), w, HEIGHT, ""),
	pocetak_box(Point(0, 140), w, HEIGHT, ""),
	upitnik_box(Point(0, 160), w, HEIGHT, "")
{
	attach(sortiraj_box);
	attach(prikazi_box);
	attach(ispisi_info_box);
	attach(ispisi_sort_box);
	attach(sledeci_box);
	attach(prethodni_box);
	attach(kraj_box);
	attach(pocetak_box);
	attach(upitnik_box);

	sortiraj_box.put("sortiraj - sortira i prikaze rezultat");
	prikazi_box.put("prikazi - prikaze grafik sortiranja");
	ispisi_info_box.put("ispisi info - ispisuje u zadati file informacije o sortiranju");
	ispisi_sort_box.put("ispisi sort - ispisuje u zadati file rezultat sortiranja");
	sledeci_box.put("sledeci - prikaze sledece stanje u sortiranju");
	prethodni_box.put("prethodni - prikaze prethodno stanje u sortiranju");
	kraj_box.put("kraj - prikazuje krajnje stanje sortiranja");
	pocetak_box.put("pocetak - prikazuje pocetno stanje sortiranja");
	upitnik_box.put("? - ovaj manual");
	
}

MyWindow::MyWindow(Point xy, int ww, int hh, const string& title) :
	Window(xy,ww,hh,title),
	in_file_box(Point(X_POSITION,0), WIDTH, HEIGHT, "input file:"),
	out_file_box(Point(X_POSITION, 20), WIDTH, HEIGHT, "output file:"),
	sort_type_box(NULL),
	comp_box(NULL),
	sort_button(Point(X_POSITION2, 80), WIDTH2, HEIGHT, "sortiraj", cb_sort),
	show_sort_button(Point(X_POSITION3, 80), WIDTH2, HEIGHT, "prikazi", cb_drawing),
	write_info_button(Point(X_POSITION2,100), WIDTH2, HEIGHT, "ispisi info", cb_write_info),
	write_sorted_button(Point(X_POSITION3, 100), WIDTH2, HEIGHT, "ispisi sort", cb_write_sorted),
	next_button(Point(X_POSITION2, 140), WIDTH2, HEIGHT, "sledeci", cb_next),
	previous_button(Point(X_POSITION3, 140), WIDTH2, HEIGHT, "prethodni", cb_previous),
	begining_button(Point(X_POSITION2, 160), WIDTH2, HEIGHT, "kraj", cb_end),
	end_button(Point(X_POSITION3, 160), WIDTH2, HEIGHT, "pocetak", cb_begining),
	sort_iter_box(Point(X_POSITION, 180), WIDTH, HEIGHT, "broj iteracija:"),
	sort_switch_box(Point(X_POSITION, 200), WIDTH, HEIGHT, "broj pomeranja:"),
	sort_comp_box(Point(X_POSITION, 220), WIDTH, HEIGHT, "broj poredjenja:"),
	manual_button(Point(20, hh-30), 20, 20,"?",cb_manual),
	scroll(NULL),
	man(NULL),
	vi(NULL),
	sd(NULL)
{

	
	attach(in_file_box);
	attach(out_file_box);
	begin();
	sort_type_box = new Fl_Choice(X_POSITION, 40, WIDTH, HEIGHT, "tip sorta:");
	sort_type_box->menu(sort_menu);
	sort_type_box->value(0);
	comp_box = new Fl_Choice(X_POSITION, 60, WIDTH, HEIGHT, "po cemu:");
	comp_box->menu(comp_menu);
	comp_box->value(0);
	end();
	attach(sort_button);
	attach(show_sort_button);
	attach(write_info_button);
	attach(write_sorted_button);
	attach(next_button);
	attach(previous_button);
	attach(begining_button);
	attach(end_button);
	attach(sort_iter_box);
	attach(sort_switch_box);
	attach(sort_comp_box);
	attach(manual_button);
	begin();
	scroll = new Fl_Scroll(250, 0, ww - 250, hh);
	scroll->type(Fl_Scroll::BOTH_ALWAYS);
	end();
	
}

MyWindow::~MyWindow() {
	delete man;
	delete scroll;
	delete sort_type_box;
	delete comp_box;
}

void MyWindow::manual() {
	delete man;
	man = new My_manual{ Point(0,0),500,200,"manual" };
}

void MyWindow::visual()
{
	//show the flight_list
	delete vi;
	sort_iter_box.put(sort->getNumIter());
	sort_switch_box.put(sort->getNumChanges());
	sort_comp_box.put(sort->getNumCmps());
	scroll->begin();

	vi = new Flight_list_visual(scroll->x(), scroll->y(), scroll->w() - 30, flight_list);
	scroll->end();
	scroll->redraw();
}

void MyWindow::drawing() {
	if (sort == NULL)
		return; //TODO vici
	delete sd;
	sd = new Sort_drawing{ x_max(), y_max(), string("Sortiranje graf") };
}

void MyWindow::cb_manual(Address, Address pw){
	reference_to<MyWindow>(pw).manual();
}

void MyWindow::cb_sort(Address, Address pw) {
	string file_name = reference_to<MyWindow>(pw).in_file_box.get_string();
	ifstream in(file_name);
	if (!in)
		return;//TODO vici da nije dobro
	string trash;
	getline(in, trash);
	flight_list.flights.clear();
	in >> flight_list;
	delete sort;
	if (sort_type == SELECTION_SORT)
		sort = new SelectionSort();
	else
		sort = new QuickSort();
	sort->sort(flight_list.flights);
	reference_to<MyWindow>(pw).visual();
}

void MyWindow::cb_previous(Address, Address pw) {
	if (sort == NULL)
		return; //TODO vici
	sort->step_back(flight_list.flights);
	reference_to<MyWindow>(pw).visual();
}

void MyWindow::cb_next(Address, Address pw) {
	if (sort == NULL)
		return;//TODO vici
	sort->step_forward(flight_list.flights);
	reference_to<MyWindow>(pw).visual();
}

void MyWindow::cb_begining(Address, Address pw){
	if (sort == NULL)
		return;//TODO vici
	sort->rewind(flight_list.flights);
	reference_to<MyWindow>(pw).visual();
}

void MyWindow::cb_end(Address, Address pw) {
	if (sort == NULL)
		return;//TODO vici
	sort->forward(flight_list.flights);
	reference_to<MyWindow>(pw).visual();
}

void MyWindow::cb_write_info(Address, Address pw) {
	string file_name = reference_to<MyWindow>(pw).out_file_box.get_string();
	ofstream out(file_name);
	if (!out || sort == NULL) {
		return; //TODO vici

	}
	out << "broj pomeranja: " << sort->getNumChanges() << endl;
	out << "broj iteracija: " << sort->getNumIter() << endl;
	out << "broj uporedjenja: " << sort->getNumCmps() << endl;
}

void MyWindow::cb_write_sorted(Address, Address pw) {
	string file_name = reference_to<MyWindow>(pw).out_file_box.get_string();
	ofstream out(file_name);
	if (!out || sort == NULL) {
		return; //TODO vici

	}
	out << flight_list;
}

void MyWindow::cb_drawing(Address, Address pw) {
	reference_to<MyWindow>(pw).drawing();
}
