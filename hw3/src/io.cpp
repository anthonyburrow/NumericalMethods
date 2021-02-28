#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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
            if (line[0] == '#' || line[0] == NULL || line[0] == '\0') { continue; }

            stringstream iss(line);

            switch(count) {
                case 0 :
                    double x0;
                    iss >> x0;
                    params.x0 = x0;
                    cout << "x0 = " << x0 << endl;
                    break;
                case 1 :
                    double h;
                    iss >> h;
                    params.h = h;
                    cout << "h = " << h << endl;
                    break;
                default :
                    cout << "Too many lines in param file" << endl;
            }
        }
        param_file.close();

        return params;
    }

    void writePoint(const vector<double> &X, ofstream &file) {
        file << X[0] << " " << X[1] << endl;
    }

}