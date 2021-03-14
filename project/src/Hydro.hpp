#pragma once

#include <string>
#include <vector>

#include "io.hpp"

namespace myHydro {

    class Hydro {

        public:
            const int &nZones;
            const int nBoundaries;
            const int &nIter;
            const double &dt;
            const double &initRMax;

            // Physical quantities
            //   b -> bound alternative
            //   ht -> half-time alternative
            std::vector<double> R;
            std::vector<double> U;
            std::vector<double> P;
            std::vector<double> Q;
            std::vector<double> V;
            std::vector<double> Vht;
            std::vector<double> T;
            std::vector<double> DM;
            std::vector<double> DMb;
            std::vector<double> XM;

            Hydro(const string &paramFile);

            void iterate();

        private:
            const mylib::hydroParams &params;

            void initVectors();

    };

}