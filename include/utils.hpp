#ifndef UTILS
#define UTILS

#include <unordered_map>

bool is_sorted(int *a, int size);
float mean(std::vector<long int> v);
float stdev(std::vector<long int> v);
void active_delay(int msecs);
void parse_config(std::unordered_map<std::string, int*> params);

#endif