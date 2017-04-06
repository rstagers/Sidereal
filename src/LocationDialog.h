/*
 * LocationDialog.h
 *
 *  Created on: Apr 6, 2017
 *      Author: randy
 */

#ifndef LOCATIONDIALOG_H_
#define LOCATIONDIALOG_H_

#include <gtkmm.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

class LocationDialog: public Gtk::Dialog {
public:
	LocationDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~LocationDialog();

	void set_Data(int latDeg, int latMin, double latSec, int lonDeg, int lonMin, double lonSec) {
		LatDegrees = latDeg;
		LatMinutes = latMin;
		LatSeconds = latSec;
		LonDegrees = lonDeg;
		LonMinutes = lonMin;
		LonSeconds = lonSec;
		// Set the data in the dialog fields...
		pLonDeg->set_text(std::to_string(LonDegrees));
		pLatDeg->set_text(std::to_string(LatDegrees));
		pLonMin->set_text(std::to_string(LonMinutes));
		pLatMin->set_text(std::to_string(LatMinutes));
		pLonSec->set_text(std::to_string(LonSeconds));
		pLatSec->set_text(std::to_string(LatSeconds));
	};

	void get_Data(int* latDeg, int* latMin, double* latSec, int* lonDeg, int* lonMin, double* lonSec) {
		*latDeg = std::atoi(pLatDeg->get_text().c_str());
		*latMin = std::atoi(pLatMin->get_text().c_str());
		*latSec = std::atof(pLatSec->get_text().c_str());
		*lonDeg = std::atoi(pLonDeg->get_text().c_str());
		*lonMin = std::atoi(pLonMin->get_text().c_str());
		*lonSec = std::atof(pLonSec->get_text().c_str());
	};

protected:
	Glib::RefPtr<Gtk::Builder> builder;
    Gtk::Entry *pLonDeg, *pLonMin, *pLonSec, *pLatDeg, *pLatMin, *pLatSec;
	int LatDegrees;
	int LonDegrees;
	int LatMinutes;
	int LonMinutes;
	double LatSeconds;
	double LonSeconds;

	// Going to try to use this to validate the data?  Another idea on get_Data validate the data, the dialog
	// has returned at this point so you could make error colors or messsages on the dialog and re-run it
	// with the original data in the data with error.
    bool on_focus_outLonDeg(GdkEventFocus* ef);
};

#endif /* LOCATIONDIALOG_H_ */
