#include <vector>

using namespace std;

namespace myHydro {

    void initR(vector<double> &R, const double &initRMax) {
        // Start with uniform spacial boundaries
        const int nZones = R.size() - 1;
        const double dR = initRMax / nZones;

        R[0] = 0;

        for (int i = 1; i < nZones + 1; i++) {
            R[i] = R[i - 1] + dR;
        }
    }

    void initU(vector<double> &U) {
        // Start with zero velocities
        for (int i = 0; i < U.size(); i++) {
            U[i] = 0;
        }
    }

    void initP(vector<double> &P) {

    }

    void initV(vector<double> &V) {

    }

    void initT(vector<double> &T) {

    }

}