#include <vector>
#include <functional>

using namespace std;

namespace {
    vector<double> newtonIteration (const vector<double> X0,
                                    function<vector<double> (vector<double>)> func,
                                    function<vector<vector<double>> (vector<double>)> invJacobian) {
        vector<double> X1;
        vector<double> funcValue = func(X0);
        vector<vector<double>> invJacValue = invJacobian(X0);

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
        vector<double> X_prev = X0;
        vector<double> X;

        int max_iter = 100;
        int count = 0;
        while (count < max_iter) {
            X = newtonIteration(X_prev, func, invJacobian);

            // convergence check / print?

            X_prev = X;
            count++;
        }

        return X;
    }
}