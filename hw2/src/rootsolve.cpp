#include <iostream>
#include <vector>
#include <functional>
#include <limits>
#include <cmath>

using namespace std;

namespace {
    vector<double> newtonIteration (const vector<double> X0,
                                    function<vector<double> (vector<double>)> func,
                                    function<vector<vector<double>> (vector<double>)> invJacobian) {
        vector<double> X1(2);

        vector<double> funcValue(2);
        funcValue = func(X0);

        vector<vector<double>> invJacValue(2, vector<double>(2));
        invJacValue = invJacobian(X0);

        for (int i=0; i < X0.size(); i++) {
            X1[i] = X0[i];

            for (int j=0; j < invJacValue[i].size(); j++) {
                X1[i] += invJacValue[i][j] * funcValue[j];
            }
        }

        return X1;
    }
}

namespace mylib {
    vector<double> findRoot(function<vector<double> (vector<double>)> func,
                            function<vector<vector<double>> (vector<double>)> invJacobian,
                            const vector<double> &X0) {
        vector<double> X_prev(2);
        X_prev = X0;

        vector<double> X(2);

        cout << "Solving for the root..." << endl;

        const int max_iter = 100;
        int count = 0;
        const double eps = std::numeric_limits<double>::epsilon();
        while (count < max_iter) {
            X = newtonIteration(X_prev, func, invJacobian);

            const int n_digits = numeric_limits<double>::max_digits10;
            cout.precision(n_digits);
            cout << X[0] << ", " << X[1] << endl;

            if (abs(X[0] - X_prev[0]) < eps && abs(X[0] - X_prev[0]) < eps) {
                count++;
                break;
            }

            X_prev = X;
            count++;
        }

        cout << "Found root with " << count << " iterations" << endl;

        return X;
    }
}