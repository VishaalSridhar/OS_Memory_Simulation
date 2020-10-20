/**
 * This file contains the main() function that drives the simulation. You'll
 * need to add logic to this file to create a Simulation instance and invoke its
 * run() method.
 */

#include <cstdlib>
#include "simulation/simulation.h"
#include "flag_parser/flag_parser.h"
#include <fstream>
#include <iostream>
using namespace std;

/**
* The main entry point to the simulation.
*/

int main(int argc, char** argv) {
    // TODO: implement me
    int processCount = 0;
    //int process_id;
    FlagOptions flags;
    if(!parse_flags(argc, argv, flags)) {
      cout << "Error parsing flags" << endl;
      return EXIT_FAILURE;
    }

    Simulation simulation(flags);
    simulation.run();



    //fstream input()
    return EXIT_SUCCESS;
}
