#pragma once

#include <vector>

namespace myHydro {

    void calcDM(std::vector<double> &DM,
                const std::vector<double> &R,
                const std::vector<double> &V);

    void calcXM(std::vector<double> &XM,
                const std::vector<double> &DM);

    void tIterR(std::vector<double> &XM,
                const std::vector<double> &DM);

}