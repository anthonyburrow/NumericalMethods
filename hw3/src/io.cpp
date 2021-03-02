#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <iomanip>

#include "io.hpp"
#include "nr.h"

using namespace std;

namespace mylib {

    mylib::eulerParams readParams(const string &filename) {
        cout << "Reading from parameter file: " << filename << endl;

        ifstream param_file(filename);
        string line;
        mylib::eulerParams params;

        int count = 0;
        while (getline(param_file, line)) {
            if (line[0] == '#' || line[0] == '\0') { continue; }

            stringstream iss(line);

            switch(count) {
                case 0 :
                    double x0;
                    iss >> x0;
                    params.x0 = x0;
                    cout << "x0 = " << x0 << endl;
                    count++;
                    break;
                case 1 :
                    double nPoints;
                    iss >> nPoints;
                    params.nPoints = nPoints;
                    cout << "No. points = " << nPoints << endl;
                    count++;
                    break;
                case 2 :
                    double tol;
                    iss >> tol;
                    params.tol = tol;
                    cout << "Relative accuracy = " << tol << endl;
                    count++;
                    break;
                case 3 :
                    double hMinRatio;
                    iss >> hMinRatio;
                    params.hMinRatio = hMinRatio;
                    cout << "Minimum h = " << hMinRatio << " * h" << endl;
                    count++;
                    break;
                default :
                    cout << "Too many lines in param file" << endl;
            }
        }
        param_file.close();

        cout << "..." << endl;

        return params;
    }

    const int n_digits = numeric_limits<double>::max_digits10;

    void writePoint(const vector<double> &X, ofstream &file) {
        file << fixed << setprecision(n_digits)
             << X[0] << " " << X[1] << endl;
    }

    void writePoint(const double &x, const double &y, ofstream &file) {
        file << fixed << setprecision(n_digits)
             << x << " " << y << endl;
    }

    // void writeAll(const vector<double> &X, const Vec_IO_DP &y,
    //               ofstream &file) {
    //     for (int i=0; i < X.size(); i++) {
    //         file << fixed << setprecision(n_digits)
    //             << X[i] << " " << y[i] << endl;
    //     }
    // }

}