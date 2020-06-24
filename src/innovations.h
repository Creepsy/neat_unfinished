#pragma once

#include <map>

struct innovation
{
    size_t from;
    size_t to;
    size_t identifier;
};

inline bool operator<(const innovation first, const innovation second)
{
    return first.identifier < second.identifier;
}

class innovations
{
private:
    size_t next_innovation;

    std::map<innovation, size_t> existing_innovations;

public:
    innovations();
    size_t get_innovation(size_t from_node, size_t to_node, size_t identifier);
    ~innovations();
};