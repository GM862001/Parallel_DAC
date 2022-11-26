#include <cmath>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

bool is_sorted(int *a, int size){

    for (int i = 0; i < size - 1; i++)
        if (a[i] > a[i + 1])
            return false;

    return true;

}

float mean(std::vector<long int> v){

    float sum = 0.0;
    for (auto& elem : v)
        sum += elem;
    return sum / v.size();

}

float stdev(std::vector<long int> v){

    float sum = 0.0;
    float mu = mean(v);
    for (auto& elem : v)
        sum += pow(elem - mu, 2);
    return sqrt(sum / v.size());

}

void active_delay(int msecs){

    auto start = std::chrono::high_resolution_clock::now();
    bool end = false;
    while (!end) {
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        if (duration >= msecs)
            end = true;
    }
    return;

}

void parse_config(std::unordered_map<std::string, int*> params){

    std::string config_filepath = "config.cfg";
    std::ifstream config_file(config_filepath);
    std::string line;
    while (getline(config_file, line)){
        line.erase(std::remove_if(line.begin(), line.end(), isspace),line.end());
        if (line[0] == '#' || line.empty()) continue;

        auto delimiter = line.find("=");
        auto name = line.substr(0, delimiter);
        auto value = line.substr(delimiter + 1);

        if (params.find(name) != params.end()){
            *params[name] = std::stoi(value);
        }
    }

}
