#include "genome.h"
#include "util.h"

int main(int argc, char const *argv[])
{
    genome g = genome(2, 2);
    auto outputs = g.run({1, 2});
    print_vector(std::cout, outputs) << std::endl;

    return 0;
}
