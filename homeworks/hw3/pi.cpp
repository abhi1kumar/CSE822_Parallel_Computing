#include <algorithm>
#include <iostream>
#include <random>

using std::cout; using std::endl;
using std::atoi;

int getCounts(int Npoints, int seed) {
    /*
    Function to randomly sample points from a square of side length 1,
    and count number on points that lie within the unit circle
    */

    std::mt19937_64 dre(seed);
    std::uniform_real_distribution<double> dist(0, 1);

    int N_in = 0;
    double x;
    double y;
    
    for (int i=0; i<Npoints; ++i) {
        x = dist(dre);
        y = dist(dre);

        if (x * x + y * y <= 1.0) {
            ++N_in;
        }
    }

    return N_in;
}

int main(int argc, char* argv[]) {

    cout.precision(15);

    if (argc == 1) {
        cout << "Please input a number of points!" << endl;
    } else {

        int Npoints = atoi(argv[1]);

        int N_in = getCounts(Npoints, 0);

        long double pi;

        pi = 4 * (long double)N_in/(long double)Npoints;

        cout << "After " << Npoints << " iterations, calculated value of pi = " << pi << endl;

    }

    return 0;

}