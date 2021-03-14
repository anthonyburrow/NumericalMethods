#define _USE_MATH_DEFINES

#include <vector>
#include <cmath>

using namespace std;

const double pi_4_3 = 4 * M_PI / 3;

namespace myHydro {

    void calcDM(vector<double> &DM, const vector<double> &R,
                const vector<double> &V) {
        double RCube = pow(R[0], 3);
        double nextRCube;

        for (int i = 0; i < DM.size(); i++) {
            nextRCube = pow(R[i + 1], 3);
            DM[i] = pi_4_3 * (nextRCube - RCube) / V[i];
            RCube = nextRCube;
        }
    }

    void calcXM(vector<double> &XM, const vector<double> &DM) {
        XM[0] = 0;

        for (int i = 1; i < XM.size(); i++) {
            XM[i + 1] = XM[i] + DM[i];
        }
    }
    
}