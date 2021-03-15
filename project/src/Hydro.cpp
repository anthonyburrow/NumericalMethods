#include <string>

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
        iter = 0;

        initVectors();
    }

    void Hydro::iterate() {
        myHydro::calcU(*this);

        myHydro::calcR(*this);

        myHydro::calcV(*this);

        myHydro::calcP(*this);
        myHydro::calcET(*this);
        myHydro::calcEV(*this);

        myHydro::calcT(*this);

        iter++;
    }

    void Hydro::initVectors() {
        R.reserve(nBoundaries);
        myHydro::initR(*this);

        U.reserve(nBoundaries);
        myHydro::initU(*this);

        P.reserve(nZones);
        myHydro::initP(*this);

        V.reserve(nZones);
        Vht.reserve(nZones);
        myHydro::initV(*this);

        T.reserve(nZones);
        Tht.reserve(nZones);
        myHydro::initT(*this);

        DM.reserve(nZones);
        myHydro::calcDM(*this);

        DMb.reserve(nBoundaries);
        myHydro::calcDMb(*this);

        XM.reserve(nBoundaries);
        myHydro::calcXM(*this);

        Q.reserve(nZones);
        myHydro::initQ(*this);
    }

}