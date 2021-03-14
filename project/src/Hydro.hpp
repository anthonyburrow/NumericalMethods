#pragma once

#include <string>
#include <vector>

#include "io.hpp"

namespace myHydro {

    class Hydro {

        private:
            const mylib::hydroParams &params;
            const double &initRMax;

            void initVectors();

        public:
            const int &nZones;
            const int nBoundaries;
            const int &nIter;
            const double &dt;

            // Physical quantities
            std::vector<double> R;
            std::vector<double> U;
            std::vector<double> P;
            std::vector<double> V;
            std::vector<double> T;
            std::vector<double> DM;
            std::vector<double> XM;

            Hydro(const string &paramFile);
    };

}