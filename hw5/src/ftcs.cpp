#include <vector>

using namespace std;

namespace myLib {

    void iterFTCS(vector<double> &n, const double &r) {
        vector<double> nNew(n.size() - 2);

        for (int i = 1; i < n.size() - 1; i++) {
            nNew[i - 1] = n[i] + r * (n[i + 1] - 2 * n[i] + n[i - 1]);
        }

        for (int i = 1; i < n.size() - 1; i++) {
            n[i] = nNew[i - 1];
        }
    }

}