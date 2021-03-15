#define _USE_MATH_DEFINES

#include <vector>
#include <cmath>

#include "Hydro.hpp"

using namespace std;

const double pi4 = 4 * M_PI;
const double pi4_sq = pi4 * pi4;
const double pi4_3 = pi4 / 3;
const double G = 132709742648;   // km^3 Msol^-1 s^-2

namespace myHydro {

    void calcDM(myHydro::Hydro &hydro) {
        double RCube = 0;
        double nextRCube;

        for (int i = 0; i < hydro.nBoundaries; i++) {
            nextRCube = pow(hydro.R[i + 1], 3);
            hydro.DM[i] = pi4_3 * (nextRCube - RCube) / hydro.V[i];
            RCube = nextRCube;
        }
    }

    void calcDMb(myHydro::Hydro &hydro) {
        hydro.DMb[0] = hydro.DM[0];

        for (int i = 1; i < hydro.nZones; i++) {
            hydro.DMb[i] = 0.5 * (hydro.DM[i] + hydro.DM[i - 1]);
        }

        hydro.DMb[hydro.nZones] = hydro.DM[hydro.nZones - 1];
    }

    void calcXM(myHydro::Hydro &hydro) {
        hydro.XM[0] = 0;

        for (int i = 1; i < hydro.nBoundaries; i++) {
            hydro.XM[i + 1] = hydro.XM[i] + hydro.DM[i];
        }
    }

    void calcR(myHydro::Hydro &hydro) {
        for (int i = 1; i < hydro.nBoundaries; i++) {
            hydro.R[i] = hydro.R[i] + hydro.U[i] * hydro.dt;
        }
    }

    void calcU(myHydro::Hydro &hydro) {
        double R_sq;
        double dP;
        double dQ;
        const int &nZones = hydro.nZones;
        
        for (int i = 1; i < nZones; i++) {
            R_sq = pow(hydro.R[i], 2);
            dP = hydro.P[i] - hydro.P[i - 1];
            dQ = hydro.Q[i] - hydro.Q[i - 1];

            hydro.U[i] = hydro.U[i] +
                         hydro.dt * (pi4_sq * R_sq * (dP - dQ) /
                                         hydro.DMb[i] -
                                     G * hydro.XM[i] / R_sq);
        }

        // Outer boundary with P = Q = 0
        R_sq = pow(hydro.R[nZones], 2);
        dP = -hydro.P[nZones - 1];
        dQ = -hydro.Q[nZones - 1];
        hydro.U[nZones] = hydro.U[nZones] +
                          hydro.dt * (pi4_sq * R_sq * (dP - dQ) /
                                          hydro.DMb[nZones] -
                                      G * hydro.XM[nZones] / R_sq);
    }

    void calcV(myHydro::Hydro &hydro) {
        double RCube = 0;
        double nextRCube;
        double nextV;

        for (int i = 0; i < hydro.nZones; i++) {
            nextRCube = pow(hydro.R[i + 1], 3);
            nextV = pi4_3 * (nextRCube - RCube) / hydro.DM[i];
            RCube = nextRCube;

            hydro.Vht[i] = 0.5 * (V + hydro.V[i]);

            if (nextV < V[i]) {
                hydroQ[i] = calcQ(U[i + 1], U[i], Vht[i]);
            }
            else { hydro.Q[i] = 0; }

            hydro.V[i] = nextV;
        }
    }

    void calcQ(double U1, double U0, double Vht) {
        const double dU = U1 - U0;
        if (dU < 0) {
            return 2 * pow(dU, 2) / Vht;
        }
        else { return 0; }
    }

    void calcP(myHydro::Hydro &hydro) {
        // Pht as a function of Tht, Vht

        // Get P?
    }

    void calcET(myHydro::Hydro &hydro) {
        // ETht as a function of Tht, Vht
    }

    void calcEV(myHydro::Hydro &hydro) {
        // EVht as a function of Tht, Vht
    }

    void calcT(myHydro::Hydro &hydro) {
        double prevT;

        for (int i = 0; i < hydro.nZones; i++) {
            // Calc T
            prevT = hydro.T[i];

            

            // Calc Tht
            // When dt is not constant, this equation needs
            // to be slightly different
            hydro.Tht[i] = 1.5 * hydro.T[i] - 0.5 * prevT;
        }
    }

}