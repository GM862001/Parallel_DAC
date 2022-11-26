#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <thread>
#include <unordered_map>
#include "Mergesort.hpp"
#include "utils.hpp"
#include "utimer.hpp"
#include "DAC.hpp"

int BASECASE_MAX_LENGTH;
int STOP_MAX_LENGTH;
int Td, Tc, Ts;

std::vector<Tin> split(Tin to_split){

    int mid = (to_split.left + to_split.right) / 2;	
    Tin first = {
        to_split.array,
        to_split.left,
        mid
    };
    Tin second = {
        to_split.array,
        mid + 1,
        to_split.right
    };
    std::vector<Tin> result{first, second};
    active_delay(Td);
    return result;

}

Tout merge(std::vector<Tout> to_merge){

    int *a = to_merge[0].array;
    int left = to_merge[0].left;
    int mid = to_merge[0].right;
    int right = to_merge[1].right;

    int size = right - left + 1;
    int *temp = new int[size];
    for (int i = left, j = mid + 1, k = 0; k < size; k++)
	    if (i <= mid && (j > right || a[i] <= a[j])){
		    temp[k] = a[i];
		    i++;
		} else { // i > mid || (j <= right && a[i] > a[j])
		    temp[k] = a[j];
		    j++;
		}

    memcpy(a + left, temp, sizeof(int) * size);
    delete[] temp;
    
    Tout result{a, left, right};
    active_delay(Tc);
    return result;

}

bool basecase(Tin to_check){
    return (to_check.right - to_check.left + 1 <= BASECASE_MAX_LENGTH);
}

bool stop(Tin to_check){
    return (to_check.right - to_check.left + 1 <= STOP_MAX_LENGTH);
}

Tout solve(Tin to_sort){
    std::sort(&(to_sort.array[to_sort.left]), &(to_sort.array[to_sort.right + 1]));
    active_delay(Ts);
    return to_sort;
}

long int run(int N, int B, int S, int random_seed){

    srand(random_seed);

    Tin a = {
        new int[N],
        0,
        N - 1
    };
    for (int i = 0; i < N; i++)
        a.array[i] = rand();

    std::unordered_map<std::string, int*> time_constants;
    time_constants["Td"] = &Td;
    time_constants["Tc"] = &Tc;
    time_constants["Ts"] = &Ts;
    parse_config(time_constants);

    BASECASE_MAX_LENGTH = B;
    STOP_MAX_LENGTH = S;

    utimer timer;
    parallel_DAC(a, split, merge, basecase, stop, solve);
    long int time = timer.stop();

    if (not is_sorted(a.array, N)){
        std::cerr << "An error occured: array not sorted";
        exit(-1);
    }
    delete[] a.array;
    
    return time;

}
