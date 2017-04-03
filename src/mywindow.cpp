/*
 * mywindow.cpp
 *
 *  Created on: Aug 17, 2016
 *      Author: randy
 */

#include "mywindow.h"

CAADate date;

double GetLocalSiderealTime(double Longitude)
{
 	struct tm *local;
  	time_t t;

  	t = time(NULL);
  	local = gmtime(&t);


  	date.Set((local->tm_year)+1900, (local->tm_mon)+1, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec, true);

  	double ST = CAASidereal::MeanGreenwichSiderealTime(date.Julian());
	double LST = ST - (Longitude / 15); // Assumes WEST so substract

 	if(LST < 0.0) LST += 24.0;
	else if(LST > 24.0) LST -= 24.0;
	return LST;
}

std::string DecimalTimeToHMS(double decimalTime)
{
	std::ostringstream oss;

	double time = decimalTime;
	int hours = time;
	double minutesRemainder = (time - hours) * 60;
	int minutes = minutesRemainder;
	double secondsRemainder = (minutesRemainder - minutes) * 60;
	int seconds = secondsRemainder;
	oss << std::setfill('0') << std::setw(2) << hours << ":" << std::setfill('0') << std::setw(2) << minutes << ":" <<  std::setfill('0') << std::setw(2) << seconds;
	return oss.str();
}

std::string PrintTime(double JD, const char* msg)
{
  std::ostringstream oss;

  CAADate date_time(JD, true);
  long year = 0;
  long month = 0;
  long day = 0;
  long hour = 0;
  long minute = 0;
  double second = 0;
  date_time.Get(year, month, day, hour, minute, second);

//  oss << msg << year << "-" << std::setfill('0') << std::setw(2) << month << "-" << std::setfill('0') << std::setw(2) << day << " " << hour << ":" << std::setfill('0') << std::setw(2) << minute << ":" << std::setfill('0') << std::setw(2) << static_cast<int>(second);
  oss << msg << year << "-" << std::setfill('0') << std::setw(2) << month << "-" << std::setfill('0') << std::setw(2) << day << "   " << hour << ":" << std::setfill('0') << std::setw(2) << minute;
  return oss.str();
}

std::string DecimalToDMS(double decimal)
{
	std::ostringstream oss;

	int Degree = decimal;
	double minutesRemainder = abs((decimal - Degree) * 60);
	int minutes = minutesRemainder;
	double secondsRemainder = abs((minutesRemainder - minutes) * 60);
	int seconds = secondsRemainder;
	oss << std::setfill(' ') << std::setw(3) << Degree << "° " << std::setfill('0') << std::setw(2) << minutes << "' " <<  std::setfill('0') << std::setw(2) << seconds << "\"";

	return oss.str();
}

mywindow::mywindow()
{

    Glib::signal_timeout().connect( sigc::mem_fun(*this, &mywindow::on_timeout), 1000 );

	MyLocation.X = 122.0464;	// Eventually pass in or use default
	MyLocation.Y = 47.98542;

	double LST = GetLocalSiderealTime(MyLocation.X);
	//std::cout << DecimalTimeToHMS(LST);

    set_default_size(400, 200);

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(8) << date.Julian();
    std::string Julian = oss.str();

    std::string Title = DecimalToDMS(MyLocation.X) + " " + DecimalToDMS(MyLocation.Y);
    set_title(Title.c_str());

    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
    add(*vbox);

    Gtk::Grid *grid = Gtk::manage(new Gtk::Grid);
    grid->set_border_width(10);
    grid->set_column_homogeneous(false);
    grid->set_column_spacing(75);
    vbox->add(*grid);


    labelTextJD = Gtk::manage(new Gtk::Label());
    labelTextJD->set_text("Julian Day: ");
    labelTextJD->set_alignment(0.0);
    grid->attach(*labelTextJD, 0, 0, 1, 1);

    labelJD = Gtk::manage(new Gtk::Label());
    labelJD->set_text(Julian.c_str());
    labelJD->set_alignment(0,0);
    grid->attach(*labelJD, 1, 0, 1, 1);


    labelTextJDate = Gtk::manage(new Gtk::Label());
    labelTextJDate->set_text("Date/Time (UTC):");
    labelTextJDate->set_alignment(0.0);
    grid->attach(*labelTextJDate, 0, 2, 1, 1);

    labelJDate = Gtk::manage(new Gtk::Label());
    labelJDate->set_text(PrintTime(date.Julian(), ""));
    labelJDate->set_alignment(0,0);
    grid->attach(*labelJDate, 1, 2, 1, 1);

    labelTextST = Gtk::manage(new Gtk::Label());
    labelTextST->set_text("Local Apparent Sidereal Time: ");
    labelTextST->set_alignment(0,0);
    grid->attach(*labelTextST, 0, 3, 1, 1);

    labelSTime = Gtk::manage(new Gtk::Label());
    labelSTime->set_text(DecimalTimeToHMS(LST).c_str());
    labelSTime->set_alignment(0,0);
    grid->attach(*labelSTime, 1, 3, 1, 1);

    vbox->show_all();
}

mywindow::~mywindow()
{
    //dtor
}

bool mywindow::on_timeout()
{
	double LST = GetLocalSiderealTime(MyLocation.X);
    labelSTime->set_text(DecimalTimeToHMS(LST).c_str());

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(8) << date.Julian();
    std::string Julian = oss.str();
    labelJD->set_text(Julian.c_str());

    labelJDate->set_text(PrintTime(date.Julian(), ""));


    return true;
}


void mywindow::on_quit_click()
{
    hide();
}

void mywindow::dialog(Glib::ustring msg)
{
    Gtk::MessageDialog dlg(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dlg.set_title("Gtkmm Tutorial 3");
    dlg.run();
}


