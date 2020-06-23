#include "genome.h"

#include <iostream>

genome::genome()
{
}

void genome::add_connection(const connection &c)
{
    this->connections[c.from].push_back(c);
}

genome::~genome()
{
}