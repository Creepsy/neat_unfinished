#include <math.h>

#include "genome.h"
#include "util.h"

double sigmoid(double value);

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 100; i++)
    {
        innovations innos;
        genome g = genome(4, 4, sigmoid, innos);
        genome g2 = genome(4, 4, sigmoid, innos);
        g2.split_connection(3, 6, innos);
        g.split_connection(3, 6, innos);
        g.split_connection(1, 6, innos);

        for (int i = 0; i < 100000; i++)
        {
            auto outputs = g.run({1.0, 2.0, 3.0, 4.0});
            auto outputs2 = g2.run({1.0, 2.0, 3.0, 4.0});
        }
    }

    return 0;
}

double sigmoid(double value)
{
    return 1.0 / (1.0 + exp(-value));
}