#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <iomanip>

#include "io.hpp"

using namespace std;

const int n_digits = numeric_limits<double>::max_digits10;

namespace myLib {

    myLib::params readParams(const string &filename) {
        cout << "Reading from parameter file: " << filename << endl;

        ifstream param_file(filename);
        string line;
        myLib::params params;

        int count = 0;
        while (getline(param_file, line)) {
            if (line[0] == '#' || line[0] == '\0') { continue; }

            stringstream iss(line);

            switch(count) {
                case 0 :
                    double D;
                    iss >> D;
                    params.D = D;
                    cout << "  D: " << D << endl;
                    count++;
                    break;
                case 1 :
                    double dt;
                    iss >> dt;
                    params.dt = dt;
                    cout << "  dt: " << dt << endl;
                    count++;
                    break;
                case 2 :
                    double dx;
                    iss >> dx;
                    params.dx = dx;
                    cout << "  dx: " << dx << endl;
                    count++;
                    break;
                case 3 :
                    double xmin;
                    iss >> xmin;
                    params.xmin = xmin;
                    cout << "  x min: " << xmin << endl;
                    count++;
                    break;
                case 4 :
                    double xmax;
                    iss >> xmax;
                    params.xmax = xmax;
                    cout << "  x max: " << xmax << endl;
                    count++;
                    break;
                case 5 :
                    double NL;
                    iss >> NL;
                    params.NL = NL;
                    cout << "  Left bound: " << NL << endl;
                    count++;
                    break;
                case 6 :
                    double NR;
                    iss >> NR;
                    params.NR = NR;
                    cout << "  Right bound: " << NR << endl;
                    count++;
                    break;
                case 7 :
                    double tmax;
                    iss >> tmax;
                    params.tmax = tmax;
                    cout << "  Evolution time: " << tmax << endl;
                    count++;
                    break;
                default :
                    cout << "Too many lines in param file" << endl;
            }
        }
        param_file.close();

        return params;
    }

    void writePoint(const vector<double> &n, ofstream &file) {
        file << setprecision(n_digits);

        for (double const &x : n) {
            file << x << " ";
        }

        file << endl;
    }

    void writePoint(const double *n, const int &nPoints, ofstream &file) {
        file << setprecision(n_digits);

        for (int i = 0; i < nPoints; i++) {
            file << n[i] << " ";
        }

        file << endl;
    }

}