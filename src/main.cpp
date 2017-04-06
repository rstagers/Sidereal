/*
 Setting up for GTKmm was a pain in the ass!

 Had to add pkg-config to the compiler (--cflags) and linker (--libs)....
 Had to move ${FLAGS} to the end of the linker command line pattern.  (or all gtkmm is unresolved in linker)
 Had to add all the include files output from pkg-config --cflags gtkmm-3.0 to the Properties/ Paths And Symbols.  ugh!
 Had to fix the indexer so that the auto complete wouldn't show a zillion unresolved symbols...
 Notes below...


Project Property->C/C++ Build->Settings GCC C++ Compiler->Miscellaneous, add this string into other flags:
`pkg-config gtkmm-3.0 --cflags --libs`
GCC C++ Linker->Miscellaneous, add this string in linker flags:
`pkg-config gtkmm-3.0 --cflags --libs`
If you are using gtkmm 2.4, just replace "gtkmm-3.0" with "gtkmm-2.4"

Tick the GCC C++ COMPILER VERBOSE (_V) string.  (I didn't do this and all seems OK).

Edit C++ linker/Command line pattern in the way to move "${FLAGS}" at the end and KEEP SPACES as they make sense.

Autocomplete unresolved symbol errors.
If on Ubuntu, go to Window > Preferences > In Search box type "Indexer" > Select Indexer in left column. Under heading "Indexer Options" tick the following options (all but those involving the skipping of files):

Index files source files not included in project
Index unused Headers Index all header variants
Index source and header files openend in editor
Allow heuristic resolution of includes
Under heading "Indexing Strategy" tick both options which are:

Automatically update the index
Update index immediately after every file-save
Under heading "Build Configuration for the indexer" select the following option:

User active build configuration

*/

// Added library aalib (debug)

#include <gtkmm.h>

#include "mywindow.h"


int main(int argc, char** argv) {

	Gtk::Main kit(argc, argv);
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("src/MainWindow.glade");

    mywindow *window = 0;
    builder->get_widget_derived("window1", window);

    kit.run(*window);

	return 0;
}
