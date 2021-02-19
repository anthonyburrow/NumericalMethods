#include <vector>
#include <functional>

using namespace std;

namespace mylib {
    vector<double> findRoot(function<vector<double> (vector<double>)> func,
                            function<vector<vector<double>> (vector<double>)> invJacobian,
                            vector<double> X0);
}