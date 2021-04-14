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

    void Hydro::initVectors() {
        R.reserve(nBoundaries);
        myHydro::initR(*this);

        U.reserve(nBoundaries);
        myHydro::initU(*this);

        P.reserve(nZones);
        myHydro::initP(*this);

        V.reserve(nZones);
        Vprev.reserve(nZones);
        Vht.reserve(nZones);
        myHydro::initV(*this);

        T.reserve(nZones);
        Tht.reserve(nZones);
        myHydro::initT(*this);

        // Should not change in Lagrangian frame
        DM.reserve(nZones);
        myHydro::calcDM(*this);

        // Should not change in Lagrangian frame
        DMb.reserve(nBoundaries);
        myHydro::calcDMb(*this);

        // Should not change in Lagrangian frame
        XM.reserve(nBoundaries);
        myHydro::calcXM(*this);

        Q.reserve(nZones);
        myHydro::calcQ(*this);

    }

    void Hydro::iterate() {
        myHydro::calcU(*this);

        myHydro::calcR(*this);

        myHydro::calcV(*this);

        myHydro::calcQ(*this);
        myHydro::calcPht(*this);
        myHydro::calcET(*this);
        myHydro::calcEV(*this);

        myHydro::calcAK(*this);
        myHydro::calcAL(*this);
        myHydro::calcSdot(*this);

        myHydro::calcT(*this);
        myHydro::calcP(*this);

        iter++;
    }

}