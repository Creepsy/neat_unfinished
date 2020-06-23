#include "genome.h"

#include <iostream>

genome::genome() {
}

void genome::add_connection(const connection& c) {
    this -> connections[c.from].push_back(c);
}

genome::~genome() {
    for(std::pair<const size_t, std::vector<connection>>& c : this -> connections) {
        std::cout << c.first << ": ";
        for(connection& conn : c.second) {
            std::cout << conn.inno << ", ";
        }
        std::cout << std::endl;
    }
}