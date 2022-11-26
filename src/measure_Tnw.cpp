#include <iostream>
#include <vector>
#include <thread>
#include "utimer.hpp"
#include "utils.hpp"

int main(){

    int min_nw;
    int max_nw;
    int n_runs;

    std::unordered_map<std::string, int*> params;
    params["measure_Tnw_min_nw"] = &min_nw;
    params["measure_Tnw_max_nw"] = &max_nw;
    params["measure_Tnw_n_runs"] = &n_runs;
    parse_config(params);

    for (int nw = min_nw; nw <= max_nw; nw *= 2){
        std::vector<long int> times(n_runs);
        for (int n_run = 0; n_run < n_runs; n_run++){
            std::vector<std::thread> tids;
            utimer timer;
            for (int j = 0; j < nw; j++)
                tids.push_back(std::thread([] (int x) {return x;}, j));
            for(std::thread& t : tids)
                t.join();
            times[n_run] = timer.stop() / nw;
        }
        std::cout << "nw = " << nw << " -> " << mean(times) << " +- " << stdev(times) << " usecs" << std::endl;
    }

}