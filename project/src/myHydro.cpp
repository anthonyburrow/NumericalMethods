#include <iostream>

#include "Hydro.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    string inFilename = "./config/params";

    myHydro::Hydro hydro(inFilename);

    // Time step iteration
    // int count = 0;
    // while (count < nIter) {
    //     myHydro::iterate();
    // }

    return 0;
}
