#ifndef COUNTDOWN_BOX_H
#define COUNTDOWN_BOX_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>

#include <chrono>
#include <string>
#include <thread>
#include <memory>

/**
* Extends Fl_Box for internal countdown timer
* that on initiation runs a seperate thread for
* the countdown and update of the box
*/
class Countdown_Box : public Fl_Box {
	typedef std::common_type_t<std::chrono::system_clock::duration, std::chrono::system_clock::duration> common_type_duration;
	std::unique_ptr<std::thread> myThread;
	int _time = 0;
private:
	void startThread() {
		myThread = std::make_unique<std::thread>([&]() {this->startTimer(); });
	}

	template<typename T, class = typename std::enable_if<std::is_same<T, common_type_duration>::value>::type>
	long long to_long(T time) {
		using namespace std::chrono;
		return duration_cast<seconds>(time).count();
	}

	template<class T, class = typename std::enable_if<std::is_floating_point<T>::value || std::is_integral<T>::value>::type>
	const char * to_char(T number) {
		std::string * str = new std::string(std::to_string(number));
		return str->data();
	}

protected:
	void draw() override {
		Fl_Box::draw();
	};

public:
	Countdown_Box(int time) :Fl_Box{ 20, 20, 300, 100, "Hello, World!" }, _time{time} {
		startThread();
	}

	void startTimer() {
		using namespace std::chrono;
		auto duration = system_clock::now() + seconds{ _time };
		auto current = to_long(duration - system_clock::now());
		this->label(to_char(current));
		Fl::check();
		while (duration > system_clock::now()) {
			auto diff = duration - system_clock::now();
			auto time = to_long(diff);
			if (current > time) {
				current = time;
				this->label(to_char(current));
				Fl::check();
			}
		}
		this->label("Finished!");
		Fl::check();
	}
};
#endif // !COUNTDOWN_BOX_H
