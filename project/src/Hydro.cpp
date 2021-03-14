#include <string>
#include <vector>

#include "Hydro.hpp"

#include "io.hpp"
#include "initialize.hpp"
#include "physics.hpp"

using namespace std;

namespace myHydro {

    Hydro::Hydro(const string &paramFile)
      : params(mylib::readParams(paramFile)),
        nZones(params.nZones),
        nBoundaries(nZones + 1),
        nIter(params.nIter),
        dt(params.duration / nIter),
        initRMax(params.initRMax)
    {
        initVectors();
    }

    void Hydro::initVectors() {
        R.reserve(nBoundaries);
        myHydro::initR(R, initRMax);

        U.reserve(nBoundaries);
        myHydro::initU(U);

        P.reserve(nZones);
        myHydro::initP(P);

        V.reserve(nZones);
        myHydro::initV(V);

        T.reserve(nZones);
        myHydro::initT(T);

        DM.reserve(nZones);
        myHydro::calcDM(DM, R, V);

        DM.reserve(nBoundaries);
        myHydro::calcXM(XM, DM);
    }

}