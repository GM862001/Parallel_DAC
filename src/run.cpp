#include <iostream>
#include <unordered_map>
#include "Mergesort.hpp"
#include "utils.hpp"

int main(int argc, char *argv[]){

    if (argc < 3){
        std::cout << "Usage: " << argv[0] << " <N> <nw>" << std::endl;
    }

    int N = atoi(argv[1]);
    int nw = atoi(argv[2]);
    int B;
    int random_seed;

    std::unordered_map<std::string, int*> params;
    params["run_B"] = &B;
    params["run_random_seed"] = &random_seed;
    parse_config(params);

    int S = N / nw;
    long int time = run(N, B, S, random_seed);
    std::cout << "Time: " << time << " usecs" << std::endl;

    return 0;

}
