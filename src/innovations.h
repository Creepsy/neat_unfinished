#pragma once

#include <map>
#include <vector>
#include <functional>

struct innovation {
    size_t identifier;
    size_t inno;
};

class innovations
{
private:
    size_t next_innovation;

    std::map<std::pair<size_t, size_t>, innovation> existing_innovations;
public:
    innovations();
    size_t get_innovation(size_t from_node, size_t to_node, size_t identifier);
    ~innovations();
};