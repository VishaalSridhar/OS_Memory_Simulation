/**
 * This file contains the definition of the Simulation class.
 *
 * You're free to modify this class however you see fit. Add new methods to help
 * keep your code modular.
 */

#pragma once
#include "process/process.h"
#include "flag_parser/flag_parser.h"
#include "virtual_address/virtual_address.h"
#include "physical_address/physical_address.h"
#include <map>
#include <list>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <ostream>
#include <boost/format.hpp>

using namespace std;

/**
    * Class responsible for running the memory simulation.
*/

class Simulation {
    // PUBLIC CONSTANTS
    public:

    /**PhysicalAddress
        * The maximum number of frames in the simulated system (512).
    */
    static const size_t NUM_FRAMES = 1 << 9;

    // PUBLIC API METHODS
    public:

    /**
        * Runs the simulation.
    */
    void run();

    //Constructor
    Simulation(FlagOptions flags);

    void outputSizes();

    void readFile();

    void fillMap(int pID, Process* process);

    void fillAddress(int pID, string in);

    void printPageFault();

    void printInMemory();

    void incrementTimer();

    int getCurrTime();

    void incrementCurrFrame();

    int getCurrFrame();

    // PRIVATE METHODS
    private:

    /**
        * Performs a memory access for the given virtual address, translating it to
        * a physical address and loading the page into memory if needed. Returns the
        * byte at the given address.
    */
    char perform_memory_access(const VirtualAddress& address);

    /**
        * Handles a page fault, attempting to load the given page for the given
        * process into memory.
    */
    void handle_page_fault(Process* process, size_t page);

    /**
        * Print the summary statistics in the required format.
    */
    void print_summary();

    // INSTANCE VARIABLES
    private:
    int currTime = 0;
    int currFrameInMemory = 0;
    FlagOptions flag;
    int processCount = 0;
    map<int, Process*> mapProcess;
    vector<VirtualAddress> virtualAddresses;
};
