#include <iostream>
#include <vector>
#include <unordered_map>
#include "Mergesort.hpp"
#include "utils.hpp"

int main(){

    int min_N;
    int max_N;
    int B;
    int nw;
    int n_runs;

    std::unordered_map<std::string, int*> params;
    params["exp1_min_N"] = &min_N;
    params["exp1_max_N"] = &max_N;
    params["exp1_B"] = &B;
    params["exp1_nw"] = &nw;
    params["exp1_n_runs"] = &n_runs;
    parse_config(params);

    std::vector<long int> times(n_runs);
    for (int N = min_N; N <= max_N; N *= 2){
        std::cout << "N = " << N << std::endl;
        for (int par_degree = 1; par_degree <= nw; par_degree *= nw){
            for (int n_run = 0; n_run < n_runs; n_run++)
                times[n_run] = run(N, B, N / par_degree, n_run);
            std::cout << "nw = " << par_degree << " -> " << mean(times) << " +- " << stdev(times) << " usecs" << std::endl;
        }
    }

    return 0;

}
