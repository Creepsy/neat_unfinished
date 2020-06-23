#include "genome.h"

int main(int argc, char const *argv[])
{
    genome g = genome{};
    g.add_connection(connection{1, 2, 0, 0.4});
    g.add_connection(connection{1, 3, 1, 0.4});
    g.add_connection(connection{2, 2, 2, 0.4});

    return 0;
}
