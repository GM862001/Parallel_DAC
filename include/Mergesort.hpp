#ifndef MERGESORT
#define MERGESORT

#include <vector>

struct T {
    int *array;
    int left;
    int right;
};

typedef struct T Tin;
typedef struct T Tout;

std::vector<Tin> split(Tin to_split);
Tout merge(std::vector<Tout> to_merge);
bool basecase(Tin to_check);
bool stop(Tin to_check);
Tout solve(Tin to_sort);

long int run(int N, int B, int S, int random_seed);

#endif