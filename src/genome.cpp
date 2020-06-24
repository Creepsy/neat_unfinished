#include "genome.h"

#include <iostream>
#include <random>

std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0, 1.0);

genome::genome(size_t input_size, size_t output_size, activation_t activation) : 
    input_size(input_size), output_size(output_size), activation(activation)
{
    // connect every input with every output and assign a unique innovation-number to each
    size_t inno = 1;
    for (size_t input = 0; input < input_size; input++)
    {
        for (size_t output = 0; output < output_size; output++)
        {
            this->add_connection(connection{input, output + input_size, inno, distribution(generator)});
            inno++;
        }
    }
}

void genome::add_connection(const connection &c)
{
    // add a connection (and a reverse connection for recursively evaluating the network value later on)
    this->connections[c.from][c.to] = c;
    this->reverse_connections[c.to][c.from] = c;
}

void genome::add_connection(size_t from, size_t to)
{
    // TODO: add unique nnovation number
    this -> add_connection(connection{from, to, -1, distribution(generator)});
}

double genome::compute_node_result(size_t node, const std::vector<double> &inputs)
{
    if (node < this->input_size)
    {
        // return value directly from input array when "computing" the value of an input node
        return inputs.at(node);
    }
    else
    {
        // get all the incoming connections, multiply the source node values with the connection weight and sum them up (activation function missing)
        auto node_connections = this->reverse_connections.at(node);
        double inputs_summed = 0.0;
        for (auto n : node_connections)
        {
            if (n.second.enabled)
            {
                inputs_summed += n.second.weight * this->compute_node_result(n.second.from, inputs);
            }
        }
        return this -> activation(inputs_summed);
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
        size_t true_output_id = this->input_size + output;
        results.at(output) = this->compute_node_result(true_output_id, inputs);
    }
    return results;
}

void genome::mutate()
{
}

void genome::mutate_weights()
{
}

void genome::split_connection(size_t from, size_t to)
{
}

genome::~genome() {}