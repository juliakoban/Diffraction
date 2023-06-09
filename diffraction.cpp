#include <iostream>
#include <fstream>
#include <math.h>

// variables to modify

const double a = 10.;  // width of the slit
const double dA = 3.; // dostance between slits in the double slit variant

const double screenSize = 100.;

const double lambda = 1.0;         // wavelength
const double amplitude = 30.;      // amplitude of the wave source
const double screenDistance = 90.; // distance from screen to the slit

const int n = 2000;       // number of points on the screen (more meaning more precise graph)
const int nSimpson = 100; // number of simpson's method subintervals

// constant formulas
const double k = (2 * M_PI) / lambda; // wavenumber
const double h = screenSize / n;      // step on the screen

// functions
double Simpson(double xMin, double xMax, int n, double y, double (*Function)(double, double)); // approximating the integral of a function between xMin and xMax
double R(double x, double y);                                                                  // r-distance between the source and the observation point(screen), where x-coordinate on the slit, y-coordinate on the screen
double RealPart(double x, double y);                                                           // real part of the diffraction integral
double ImaginaryPart(double x, double y);                                                      // imaginary part of the diffraction integral
double getLargest();                                                                           // for intensity normalization


int main()
{
    std::fstream file;
    file.open("intensity.data", std::ios::out);

    double y[n];                   // observation points on the screen
    double intensity[n];           // intensity that forms an image of single-slit diffraction
    double doubleSlitIntensity[n]; // intensity that forms an image of double-slit diffraction

    // filling arrays
    for (int i = 0; i < n; i++)
    {
        y[i] = i * h - (screenSize / 2.);
        intensity[i] = pow(Simpson(-(a / 2), (a / 2), nSimpson, y[i], RealPart), 2) + pow(Simpson(-(a / 2), (a / 2), nSimpson, y[i], ImaginaryPart), 2);
        doubleSlitIntensity[i] = 4 * intensity[i] * pow(cos((M_PI * dA * y[i]) / (lambda * screenDistance)), 2);
    }

    // writing to file - intensity(y), doubleSlitIntensity(y)
    for (int i = 0; i < n; i++)
    {
        file << y[i] << "   " << intensity[i] / intensity[n / 2] << "   " << doubleSlitIntensity[i] / doubleSlitIntensity[n / 2] << std::endl;
    }

    file.close();
    return 0;
}

double Simpson(double xMin, double xMax, int n, double y, double (*Function)(double, double))
{
    double simpson = 0.;
    double h = (xMax - xMin) / n; // step size
    double x = xMin + h;

    for (int i = 0; i < (n / 2); i++)
    {
        simpson += (h / 3.) * (Function(x - h, y) + 4 * Function(x, y) + Function(x + h, y)); // formula based based upon a quadratic interpolation
        x += 2. * h;
    }

    return simpson;
}

double R(double x, double y)
{
    return sqrt(pow(y - x, 2) + pow(screenDistance, 2));
}

double RealPart(double x, double y)
{
    return amplitude * cos(k * R(x, y)) / sqrt(R(x, y));
}

double ImaginaryPart(double x, double y)
{
    return amplitude * sin(k * R(x, y)) / sqrt(R(x, y));
}