#include "innovations.h"

innovations::innovations() : next_innovation(1) { }

size_t innovations::get_innovation(size_t from_node, size_t to_node, size_t identifier) {
    innovation connection = innovation{from_node, to_node, identifier};
    auto pos = this -> existing_innovations.find(connection); 
 
    if(pos != this -> existing_innovations.end()) {
        // if the connection exists, return the innovation number of it
        return this -> existing_innovations.at(connection);
    } else {
        //otherwise create a new innovation and return the next innovation number
        this -> existing_innovations.insert(std::make_pair(connection, this -> next_innovation));
        
        return this -> next_innovation++;
    }
}

innovations::~innovations() { }