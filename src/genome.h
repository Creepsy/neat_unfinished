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

public:
    genome();
    ~genome();
    void add_connection(size_t from, size_t to);
};
