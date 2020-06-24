#pragma once

#include <map>
#include <vector>

#include "innovations.h"

struct connection
{
    size_t from;
    size_t to;
    size_t inno;
    double weight = 0;
    bool enabled = true;
};

typedef double (*activation_t)(double);

class genome
{
private:
    std::map<size_t, std::map<size_t, connection>> connections;
    std::map<size_t, std::map<size_t, connection>> reverse_connections;
    size_t input_size, output_size, hidden_size;
    activation_t activation;

public:
    genome(size_t input_size, size_t outputs, activation_t activation, innovations &innos);
    ~genome();
    void add_connection(const connection &c);
    void add_connection(size_t from, size_t to, double weight, innovations &innos);
    void disable_connection(size_t from, size_t to);
    std::vector<double> run(const std::vector<double> &inputs);
    double compute_node_result(size_t node, const std::vector<double> &inputs);
    void mutate();
    void mutate_weights();
    void split_connection(size_t from, size_t to, innovations &innos);
    size_t compute_identifier();
};
