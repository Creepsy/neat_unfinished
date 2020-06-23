#include "genome.h"

#include <iostream>
#include <random>

std::default_random_engine generator;
std::uniform_int_distribution<double> distribution(0.0, 1.0);

size_t genome::get_input_id(size_t input)
{
    return input << 16;
}

size_t genome::get_output_id(size_t output)
{
    return output << 24;
}

genome::genome(size_t input_size, size_t output_size)
{
    this->input_size = input_size;
    this->output_size = output_size;
    size_t inno = 0;
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

genome::~genome() {}