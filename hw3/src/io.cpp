#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <iomanip>

#include "io.hpp"

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
                    double h;
                    iss >> h;
                    params.h = h;
                    cout << "h = " << h << endl;
                    count++;
                    break;
                default :
                    cout << "Too many lines in param file" << endl;
            }
        }
        param_file.close();

        return params;
    }

    const int n_digits = numeric_limits<double>::max_digits10;

    void writePoint(const vector<double> &X, ofstream &file) {
        file << fixed << setprecision(n_digits)
             << X[0] << " " << X[1] << endl;
    }

}