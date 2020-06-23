#include "genome.h"
#include "util.h"

int main(int argc, char const *argv[])
{
    genome g = genome(4, 4);

    auto outputs = g.run({1, 2, 3, 4});
    print_vector(std::cout, outputs) << std::endl;

    return 0;
}
