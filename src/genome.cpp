#include "genome.h"

#include <iostream>
#include <random>

std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0, 1.0);

size_t genome::get_input_id(size_t input)
{
    // map an index into the input value array to the input node ID
    return (input + 1) << 16;
}

size_t genome::get_output_id(size_t output)
{
    // map an index into the output value array to the output node ID
    return (output + 1) << 24;
}

size_t genome::from_input_id(size_t input)
{
    // reverse of get_input_id
    return (input >> 16) - 1;
}

size_t genome::from_output_id(size_t output)
{
    // reverse of get_output_id
    return (output >> 24) - 1;
}

bool genome::is_input_id(size_t input)
{
    // check if an ID is the node ID of an input node
    return ((0xFF << 16) & input) > 0;
}

bool genome::is_output_id(size_t output)
{
    // check if an ID is the node ID of an output node
    return ((0xFF << 24) & output) > 0;
}

genome::genome(size_t input_size, size_t output_size) : input_size(input_size), output_size(output_size)
{
    // connect every input with every output and assign a unique innovation-number to each
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
    // add a connection (and a reverse connection for recursively evaluating the network value later on)
    this->connections[c.from].push_back(c);
    this->reverse_connections[c.to].push_back(c);
}

double genome::compute_node_result(size_t node, const std::vector<double> &inputs)
{
    if (this->is_input_id(node))
    {
        // return value directly from input array when "computing" the value of an input node
        return inputs.at(this->from_input_id(node));
    }
    else
    {
        // get all the incoming connections, multiply the source node values with the connection weight and sum them up (activation function missing)
        auto node_connections = this->reverse_connections.at(node);
        double inputs_summed = 0.0;
        for (auto n : node_connections)
        {
            inputs_summed += n.weight * this->compute_node_result(n.from, inputs);
        }
        return inputs_summed;
    }
}

std::vector<double> genome::run(const std::vector<double> &inputs)
{
    if (this->input_size != inputs.size())
    {
        throw std::runtime_error("Input size doesn't match! Recieved: " + std::to_string(inputs.size()) + ", Expected: " + std::to_string(this->input_size));
    }

    // for each output node, traverse the nodes backwards (this is where reverse_connections is used) and compute the final results recursively
    std::vector<double> results(this->output_size);
    for (size_t output = 0; output < this->output_size; output++)
    {
        size_t true_output_id = this->get_output_id(output);
        results.at(output) = this->compute_node_result(true_output_id, inputs);
    }
    return results;
}

genome::~genome() {}