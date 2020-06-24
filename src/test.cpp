#include <math.h>

#include "genome.h"
#include "util.h"

double sigmoid(double value);

int main(int argc, char const *argv[])
{
    innovations innos;
    genome g = genome(4, 4, sigmoid, innos);

    auto outputs = g.run({1, 2, 3, 4});
    print_vector(std::cout, outputs) << std::endl;

    return 0;
}


double sigmoid(double value) {
    return 1 / (1 + pow(M_E, -value));
}