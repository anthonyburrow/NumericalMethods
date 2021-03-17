#pragma once

#include <vector>

#include "Hydro.hpp"

namespace myHydro {

    void calcDM(myHydro::Hydro &hydro);

    void calcDMb(myHydro::Hydro &hydro);

    void calcXM(myHydro::Hydro &hydro);

    void calcR(myHydro::Hydro &hydro);

    void calcU(myHydro::Hydro &hydro);

    void calcV(myHydro::Hydro &hydro);
    double calcQ(myHydro::Hydro &hydro);

    void calcP(myHydro::Hydro &hydro);
    void calcET(myHydro::Hydro &hydro);
    void calcEV(myHydro::Hydro &hydro);

    void calcT(myHydro::Hydro &hydro);

}