/*
 * LocationDialog.cpp
 *
 *  Created on: Apr 6, 2017
 *      Author: randy
 */

#include "LocationDialog.h"
#include <cmath>

LocationDialog::LocationDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) :
Gtk::Dialog(cobject), builder(refGlade) {
	// TODO Auto-generated constructor stub


	// My dialog box needs to have N/S E/W for the location and the
	// Input has to be validated, if I can once the user exits a field if the field is not
	// valid... pop up a box and make them correct it...  Could use a spin maybe for the int
	// Hours and Minutes don't know about the double Seconds?

	// Here we need to get the widgets we need to populate and populate them...

	builder->get_widget("entryLonDegrees", pLonDeg);
	builder->get_widget("entryLatDegrees", pLatDeg);
	builder->get_widget("entryLonMinutes", pLonMin);
	builder->get_widget("entryLatMinutes", pLatMin);
	builder->get_widget("entryLonSeconds", pLonSec);
	builder->get_widget("entryLatSeconds", pLatSec);
	builder->get_widget("comboboxtext1", pComboLat);
	builder->get_widget("comboboxtext2", pComboLon);

	// If we got them populate them...
	if(pLonDeg) {

		pLonDeg->signal_focus_out_event().connect(sigc::mem_fun(*this, &LocationDialog::on_focus_outLonDeg));
	}
	if(pLatDeg){

	}

	if(pLonMin) {

	}
	if(pLatMin){

	}

	if(pLonSec) {

	}
	if(pLatSec){

	}

}

LocationDialog::~LocationDialog() {
	// TODO Auto-generated destructor stub
}

bool LocationDialog::on_focus_outLonDeg(GdkEventFocus* ef)
{
	std::cout << "Focus Out!" << std::endl;
	// if the entry is out of range ... call this pLonDeg->grab_focus();
	return true;
}
