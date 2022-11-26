#ifndef UTIMER
#define UTIMER

#include <chrono>

class utimer {

    std::chrono::time_point<std::chrono::high_resolution_clock> start;

public:
    utimer();
    long int stop();

};

#endif