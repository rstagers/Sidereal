/*
 * mywindow.cpp
 *
 *  Created on: Aug 17, 2016
 *      Author: randy
 */

#include "mywindow.h"

CAADate date;

std::string GetEXEPath()
{
  std::string ReturnString;

  char path[PATH_MAX];
  char dest[PATH_MAX];
  memset(dest,0,sizeof(dest)); // readlink does not null terminate!
  //struct stat info;
  pid_t pid = getpid();
  sprintf(path, "/proc/%d/exe", pid);
  if (readlink(path, dest, PATH_MAX) == -1)
    perror("readlink");
  else {
	// need to strip off the exe name...
  ReturnString = dest;
  std::size_t found = ReturnString.find_last_of("/\\");
  ReturnString = ReturnString.substr(0,found);
    //printf("%s\n", dest);
  }
  return ReturnString;
}

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

std::string DecimalToDMS(double decimal, int *Degrees, int *Minutes, double *Seconds)
{
	std::ostringstream oss;

	*Degrees = static_cast<int>(decimal);

	double minutesRemainder = (decimal - *Degrees) * 60.0;
	*Minutes = static_cast<int>(minutesRemainder);
	*Seconds = (minutesRemainder - *Minutes) * 60.0;

	oss << std::setfill(' ') << std::setw(3) << *Degrees << "° " << std::setfill('0') << std::setw(2) << *Minutes << "' " <<  std::setfill('0') << std::setw(2) << std::setprecision (4) << *Seconds << "\"";

	return oss.str();
}


mywindow::mywindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) :
			Gtk::Window(cobject), builder(refGlade)
{

	ExePath = GetEXEPath();

	// dialog("Hi Randy!");

    Glib::signal_timeout().connect( sigc::mem_fun(*this, &mywindow::on_timeout), 1000 );

	MyLocation.X = 122.046425;	// Eventually pass in or use default
	MyLocation.Y = 47.985425;

	double LST = GetLocalSiderealTime(MyLocation.X);
	//std::cout << DecimalTimeToHMS(LST);

    set_default_size(400, 200);

    builder->get_widget("labelLatitude", labelLat);
    builder->get_widget("labelLongitude", labelLon);

    builder->get_widget("labelSiderealTime", labelSTime);
    builder->get_widget("labelJulianDay", labelJD);
    builder->get_widget("labelJulianDate", labelJDate);
    builder->get_widget("eventboxLocation", evbox);

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(8) << date.Julian();
    std::string Julian = oss.str();

    std::string Title;

    evbox->set_events(Gdk::BUTTON_PRESS_MASK);
    evbox->signal_button_press_event().connect(
       sigc::mem_fun(*this, &mywindow::on_eventbox_button_press) );
    evbox->set_tooltip_text("Click for new Location");

    Title = DecimalToDMS(MyLocation.Y, &LatDegrees, &LatMinutes, &LatSeconds) + "N";
    labelLat->set_text(Title.c_str());
    Title = DecimalToDMS(MyLocation.X, &LonDegrees, &LonMinutes, &LonSeconds) + "W";
    labelLon->set_text(Title.c_str());
    labelJD->set_text(Julian.c_str());
    labelJDate->set_text(PrintTime(date.Julian(), ""));
    labelSTime->set_text(DecimalTimeToHMS(LST).c_str());
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


// I think it would be better to have a class that is the dialog...
// for now just trying to see how things work...
bool mywindow::on_eventbox_button_press(GdkEventButton*)
{
	std::cout << "In event handler!" << std::endl;
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("src/Location.glade");

    LocationDialog *pDialog = 0;
    builder->get_widget_derived("Settings", pDialog);

	if(pDialog) {
		// set the parent window.
		pDialog->set_transient_for(*this);
		// Set the current data
		pDialog->set_Data(LatDegrees, LatMinutes, LatSeconds, LonDegrees, LonMinutes, LonSeconds);

		int result = pDialog->run();
		if(result == Gtk::RESPONSE_OK)  // YOU HAVE TO SET THE BUTTON ATTRIBUTES RESPONSE ID IN GLADE to -5 FOR OK -6 CANCEL
		{
		  // Update the location variables and labels from the widgets, OK was pressed.
		  // Also have to calculate the new MyLocation values from the entered values.
			std::cout << "OK pressed" << std::endl;
		}
		else
		{
		  // Do nothing, Cancel was pressed...
			std::cout << "Cancel pressed" << std::endl;
		}
		pDialog->close();
		delete pDialog;
	}
	return true;
}

// This worked but I need the dialog in a class and this signal part of that class...
//bool mywindow::on_focus_outLonDeg(GdkEventFocus* ef)
//{
//	std::cout << "Focus Out!" << std::endl;
//	// if the entry is out of range ... call this pLonDeg->grab_focus();
//	return true;
//}

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

