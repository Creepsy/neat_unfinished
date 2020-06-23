#pragma once

#include <map>
#include <vector>

struct connection
{
    size_t from;
    size_t to;
    size_t inno;
    double weight;
};

class genome
{
private:
    std::map<size_t, std::vector<connection>> connections;
    std::map<size_t, std::vector<size_t>> out_in_map;
    size_t input_size, output_size;

public:
    genome(size_t input_size, size_t outputs);
    ~genome();
    void add_connection(const connection &c);
    size_t get_input_id(size_t input);
    size_t get_output_id(size_t output);
    std::vector<double> run(const std::vector<double> &inputs);
};
