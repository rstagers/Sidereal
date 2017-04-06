/*
 * mywindow.h
 *
 *  Created on: Aug 17, 2016
 *      Author: randy
 */

#ifndef MYWINDOW_H_
#define MYWINDOW_H_

#include <gtkmm-3.0/gtkmm.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "LocationDialog.h"

#define _USE_MATH_DEFINES
#include "AA+.h"			// Added /home/randy/Astronomy/AA+_Meeus_Debug for the header files needed.

class mywindow : public Gtk::Window
{
    public:
        mywindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);//constructor);
        virtual ~mywindow();
    protected:
        Glib::RefPtr<Gtk::Builder> builder;

        std::string ExePath;

        Gtk::EventBox *evbox;
        Gtk::Label *labelLat;
        Gtk::Label *labelLon;
        Gtk::Label *labelJD;
        Gtk::Label *labelJDate;
        Gtk::Label *labelSTime;

        Gtk::Entry *pLonDeg, *pLonMin, *pLonSec, *pLatDeg, *pLatMin, *pLatSec;


        void on_quit_click();
        bool on_timeout();
        void dialog(Glib::ustring msg);
    	CAA2DCoordinate MyLocation;
    	int LatDegrees;
    	int LonDegrees;
    	int LatMinutes;
    	int LonMinutes;
    	double LatSeconds;
    	double LonSeconds;

    	bool on_eventbox_button_press(GdkEventButton* button_event);
    	bool on_focus_outLonDeg(GdkEventFocus* ef);

    private:
};
#endif // MYWINDOW_H


