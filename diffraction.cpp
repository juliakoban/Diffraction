#include <iostream>
#include <fstream>
#include <math.h>

// variables to modify
const double yMin = -5.;
const double yMax = -5.;

const double lambda = 1.0;


// functions
double Simpson(double xMin, double xMax, int n, double y, double (*Function)(double, double));

double Parabola(double x, double y)
{
    return x * x;
}

int main()
{
    std::cout << Simpson(2, 4, 4, 1, Parabola) << std::endl;
    return 0;
}

double Simpson(double xMin, double xMax, int n, double y, double (*Function)(double, double))
{
    double simpson = 0.;
    double h = (xMax - xMin) / n;
    double x = xMin + h;

    for(int i = 0; i < (n / 2); i++)
    {
        simpson += (h / 3.) * (Function(x - h, y) + 4 * Function(x, y) + Function(x + h, y));
        x += 2. * h;
    }

    return simpson;
}