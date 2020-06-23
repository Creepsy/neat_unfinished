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
    size_t input_size, output_size;

public:
    genome(size_t input_size, size_t outputs);
    ~genome();
    void add_connection(const connection &c);
    std::vector<double> run(std::vector<double> &inputs);
};
