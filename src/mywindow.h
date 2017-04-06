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

#define _USE_MATH_DEFINES
#include "AA+.h"			// Added /home/randy/Astronomy/AA+_Meeus_Debug for the header files needed.

class mywindow : public Gtk::Window
{
    public:
        mywindow();
        virtual ~mywindow();
    protected:
        std::string ExePath;

        Gtk::Label *labelTextLocation;

        Gtk::Label *labelTextLat;
        Gtk::Label *labelLat;
        Gtk::Label *labelTextLon;
        Gtk::Label *labelLon;

        Gtk::Label *labelTextJD;
        Gtk::Label *labelJD;

        Gtk::Label *labelTextJDate;
        Gtk::Label *labelJDate;

        Gtk::Label *labelTextST;
        Gtk::Label *labelSTime;

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
    private:
};
#endif // MYWINDOW_H


