#include <chrono>
#include "utimer.hpp"

utimer::utimer(){
	start = std::chrono::high_resolution_clock::now();
}

long int utimer::stop(){
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long int usec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	return usec;
}