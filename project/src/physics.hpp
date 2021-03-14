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

    void calcTht(myHydro::Hydro &hydro);

}