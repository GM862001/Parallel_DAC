#ifndef DAC
#define DAC

#include <thread>
#include <vector>
#include <algorithm>

// Uncomment the lines below if you want to measure the syncing overhead

// #include <iostream>
// #include <mutex>
// #include "utimer.hpp"

// std::mutex log_mutex;

template<typename Tin, typename Tout>
Tout sequential_DAC(
    Tin input,
    std::vector<Tin> (*divide)(Tin),
    Tout (*conquer)(std::vector<Tout>),
    bool (*basecase)(Tin),
    Tout (*solve)(Tin)
){

    if(basecase(input))
        return(solve(input));
    else {
        std::vector<Tin> subproblems = divide(input);
        std::vector<Tout> subresults(subproblems.size());
        for(unsigned long i = 0; i < subproblems.size(); i++)
            subresults[i] = sequential_DAC(subproblems[i], divide, conquer, basecase, solve);
        return conquer(subresults);
    }

}

template<typename Tin, typename Tout>
Tout parallel_DAC(
    Tin input,
    std::vector<Tin> (*divide)(Tin),
    Tout (*conquer)(std::vector<Tout>),
    bool (*basecase)(Tin),
    bool (*stop)(Tin),
    Tout (*solve)(Tin)
){

    if(basecase(input))
        return(solve(input));
    else if (stop(input))
        return sequential_DAC(input, divide, conquer, basecase, solve);
    else {
        std::vector<Tin> subproblems = divide(input);
        std::vector<Tout> subresults(subproblems.size());

        std::vector<std::thread> tids;
        auto subsolver = [&](int i){ subresults[i] = parallel_DAC(subproblems[i], divide, conquer, basecase, stop, solve); };
        for(unsigned long i = 1; i < subproblems.size(); i++)
            tids.push_back(std::thread(subsolver, i));
        subsolver(0);
        // utimer timer;
        for(std::thread& t : tids)
            t.join();
        // long int T = timer.stop();
        // {
        //    std::lock_guard<std::mutex> guard(log_mutex);
        //    std::cout << "Overhead: " << T << " usecs (input size of the node: " << input.right - input.left + 1 << ")" << std::endl;
        //}
        return conquer(subresults);
    }

}

#endif
