#include <iostream>
#include <vector>
#include <unordered_map>
#include "Mergesort.hpp"
#include "utils.hpp"

int main(){

    int N;
    int B;
    int min_nw;
    int max_nw;
    int n_runs;

    std::unordered_map<std::string, int*> params;
    params["exp2_N"] = &N;
    params["exp2_B"] = &B;
    params["exp2_min_nw"] = &min_nw;
    params["exp2_max_nw"] = &max_nw;
    params["exp2_n_runs"] = &n_runs;
    parse_config(params);

    std::vector<long int> times(n_runs);
    for (int nw = min_nw; nw <= max_nw; nw *= 2){
        int S = N / nw;
        for (int n_run = 0; n_run < n_runs; n_run++)
            times[n_run] = run(N, B, S, n_run);
        std::cout << "nw = " << nw << " -> " << mean(times) << " +- " << stdev(times) << " usecs" << std::endl;
    }

    return 0;

}
