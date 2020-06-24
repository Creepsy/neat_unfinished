#include "genome.h"

#include <iostream>
#include <random>

std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0, 1.0);

genome::genome(size_t input_size, size_t output_size, activation_t activation, innovations &innos) : input_size(input_size), output_size(output_size), hidden_size(0), activation(activation)
{
    // connect every input with every output and assign a unique innovation-number to each
    for (size_t input = 0; input < input_size; input++)
    {
        for (size_t output = 0; output < output_size; output++)
        {
            this->add_connection(input, output + input_size, innos);
        }
    }
}

void genome::add_connection(const connection &c)
{
    // add a connection (and a reverse connection for recursively evaluating the network value later on)
    this->connections[c.from][c.to] = c;
    this->reverse_connections[c.to][c.from] = c;
}

void genome::add_connection(size_t from, size_t to, innovations &innos)
{
    // TODO: add unique nnovation number
    size_t innovation_num = innos.get_innovation(from, to, this->compute_identifier());
    this->add_connection(connection{from, to, innovation_num, distribution(generator)});
}

void genome::disable_connection(size_t from, size_t to)
{
    this->connections.at(from).at(to).enabled = false;
    this->reverse_connections.at(to).at(from).enabled = false;
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
        return this->activation(inputs_summed);
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
    // change the weights 80% of the time
    if(distribution(generator) <= 0.8) {
        for(auto& from_pair : this -> connections) {
            for(auto& to_pair : from_pair.second) {
                // 90% to change the weight slightly, otherwise assign a completly new value
                if(distribution(generator) <= 0.9) {
                    to_pair.second.weight += (distribution(generator) - 0.5) / 10;
                } else {
                    to_pair.second.weight = distribution(generator);
                }
            }
        }
    }
}

void genome::split_connection(size_t from, size_t to, innovations &innos)
{
    // disable an existing connection and create a connected node at it's place
    size_t hidden_id = this->input_size + this->output_size + this->hidden_size;
    this->hidden_size++;
    this->disable_connection(from, to);
    this->add_connection(from, hidden_id, innos);
    this->add_connection(hidden_id, to, innos);
}

genome::~genome() {}

inline size_t hash(size_t h, size_t x)
{
    for (size_t i = 0; i < sizeof(size_t); i++)
    {
        h ^= x & 255;
        x >>= 8;
        h = (h << 24) + h * 0x193;
    }
    return h;
}

size_t genome::compute_identifier()
{
    // compute a value uniquely representing the connections of the genome
    size_t result = -1;
    for (auto &from_pair : this->connections)
    {
        for (auto &to_pair : from_pair.second)
        {
            result = hash(result, to_pair.second.inno);
        }
    }
    return result;
}