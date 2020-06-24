#include <iostream>
#include <vector>

template <typename T>
std::ostream &print_vector(std::ostream &os, const std::vector<T> &vector)
{
    std::cout << "[";
    for (size_t i = 0; i < vector.size(); i++)
    {
        std::cout << vector.at(i);
        if (i + 1 < vector.size())
        {
            std::cout << ", ";
        }
    }
    std::cout << "]";
    return os;
}