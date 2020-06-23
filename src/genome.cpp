#include "genome.h"

#include <iostream>
#include <random>

std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0, 1.0);

size_t genome::get_input_id(size_t input)
{
    return (input + 1) << 16;
}

size_t genome::get_output_id(size_t output)
{
    return (output + 1) << 24;
}

size_t genome::from_input_id(size_t input)
{
    return (input >> 16) - 1;
}

size_t genome::from_output_id(size_t output)
{
    return (output >> 24) - 1;
}

bool genome::is_input_id(size_t input)
{
    return ((0xFF << 16) & input) > 0;
}

bool genome::is_output_id(size_t output)
{
    return ((0xFF << 24) & output) > 0;
}

genome::genome(size_t input_size, size_t output_size) : input_size(input_size), output_size(output_size)
{
    size_t inno = 1;
    for (size_t input = 0; input < input_size; input++)
    {
        for (size_t output = 0; output < output_size; output++)
        {
            this->add_connection(connection{this->get_input_id(input), this->get_output_id(output), inno, distribution(generator)});
            inno++;
        }
    }
}

void genome::add_connection(const connection &c)
{
    this->connections[c.from].push_back(c);
    this->out_in_map[c.to].push_back(c.from);
}

double genome::compute_node_result(size_t node, const std::vector<double> &inputs)
{
    if (this->is_input_id(node))
    {
        return inputs.at(this->from_input_id(node));
    }
    auto node_inputs = this->out_in_map.at(node);
    double inputs_summed = 0.0;
    for (auto n : node_inputs)
    {
        inputs_summed += this->compute_node_result(n, inputs);
    }
    return inputs_summed;
}

std::vector<double> genome::run(const std::vector<double> &inputs)
{
    if (this->input_size != inputs.size())
    {
        throw std::runtime_error("Input size doesn't match! Recieved: " + std::to_string(inputs.size()) + ", Expected: " + std::to_string(this->input_size));
    }

    std::vector<double> results(this->output_size);
    for (size_t output = 0; output < this->output_size; output++)
    {
        size_t true_output_id = this->get_output_id(output);
        results.at(output) = this->compute_node_result(true_output_id, inputs);
    }
    return results;
}

genome::~genome() {}