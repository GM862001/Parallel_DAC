#include <iostream>
#include "Mergesort.hpp"

int main(int argc, char *argv[]){

    if (argc < 5){
        std::cout << "Usage: " << argv[0] << " <N> <B> <nw> <random_seed>" << std::endl;
    }

    int N = atoi(argv[1]);
    int B = atoi(argv[2]);
    int nw = atoi(argv[3]);
    int random_seed = atoi(argv[4]);
    int S = N / nw;
    long int time = run(N, B, S, random_seed);
    std::cout << "Time: " << time << " usecs" << std::endl;

    return 0;

}
