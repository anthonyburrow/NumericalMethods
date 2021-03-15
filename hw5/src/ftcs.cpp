#include <vector>

using namespace std;

namespace myLib {

    void iterFTCS(vector<double> &n, const double &r) {
        for (int i = 1; i < n.size() - 1; i++) {
            n[i] = n[i] + r * (n[i + 1] - 2 * n[i] + n[i - 1]);
        }
    }

}