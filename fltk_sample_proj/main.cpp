#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Box.H>
#include "Countdown_Box.h"

int main(int argc, char **argv) {
	Fl_Window *window = new Fl_Window(340, 140);
	Countdown_Box *box = new Countdown_Box(60);
	box->box(FL_UP_BOX);
	box->labelfont(FL_BOLD + FL_ITALIC);
	box->labelsize(36);
	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->label("Counter");
	window->show(argc, argv);
	return Fl::run();
}