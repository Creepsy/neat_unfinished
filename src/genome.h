#pragma once

#include <map>
#include <vector>

struct connection
{
    size_t from;
    size_t to;
    size_t inno;
    double weight = 0;
    bool enabled = true;
};

class genome
{
private:
    std::map<size_t, std::map<size_t, connection>> connections;
    std::map<size_t, std::map<size_t, connection>> reverse_connections;
    size_t input_size, output_size;

public:
    genome(size_t input_size, size_t outputs);
    ~genome();
    void add_connection(const connection &c);
    std::vector<double> run(const std::vector<double> &inputs);
    double compute_node_result(size_t node, const std::vector<double> &inputs);
    void mutate();
    void mutate_weights();
    void split_connection(const size_t& from, const size_t& to);
    void connect(const size_t& first_node, const size_t& second_node);
};
