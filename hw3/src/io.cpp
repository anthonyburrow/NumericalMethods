#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "io.hpp"

using namespace std;

namespace mylib {

    mylib::eulerParams read_params(const string &filename) {
        cout << "Reading from parameter file: " << filename << endl;

        ifstream param_file(filename);
        string line;
        mylib::eulerParams params;

        int count = 0;
        while (getline(param_file, line)) {
            if (line[0] == '#') { continue; }

            stringstream iss(line);

            switch(count) {
                case 0 :
                    double x0;
                    iss >> x0;
                    params.x0 = x0; 
                    break;
                case 1 :
                    double h;
                    iss >> h;
                    params.h = h; 
                    break;
                case 2 :
                    int n_points;
                    iss >> n_points;
                    params.n_points = n_points; 
                    break;
                default :
                    cout << "Too many lines in param file" << endl;
            }
        }
        param_file.close();

        return params;
    }

}