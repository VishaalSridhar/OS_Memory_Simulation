/**
 * This file contains implementations for the methods defined in the Simulation
 * class.
 *
 * You'll probably spend a lot of your time here.
 */

#include "simulation/simulation.h"

using namespace std;

Simulation::Simulation(FlagOptions flags) {
  this->flag = flags;
}

void Simulation::outputSizes() {
//  for(auto it = mapProcess.begin(); it != mapProcess.end(); it++) {
  //  cout << "Process " << it->first << ": " << "Size: " << it->second->size() << endl;
  //}
  for(int i = 0; i < virtualAddresses.size(); i++) {
    cout << virtualAddresses.at(i) << endl;
    perform_memory_access(virtualAddresses.at(i));
    Simulation::incrementTimer();
  }
}

void Simulation::readFile() {
  ifstream file(flag.filename);
  int processID;
  string line;
  getline(file, line);
  processCount = atoi(line.data());

  for (int i = 0 ; i < processCount; i++) {
    file >> line;
    processID = atoi(line.data());

    file >> line;
    ifstream input(line.data());
    Process* newProcess = Process::read_from_input(input);
    fillMap(processID, newProcess);
    //mapProcess.emplace(processID, newProcess);
  }

  getline(file, line);
  while(file >> line) {
    if(line == "") {
      break;
    }
    processID = atoi(line.data());
    file >> line;
    fillAddress(processID, line);
    //const VirtualAddress address = VirtualAddress::from_string(pID, in);
    //virtualAddresses.push_back(address);
  }
  file.close();
}

void Simulation::fillAddress(int pID, string in) {
    const VirtualAddress address = VirtualAddress::from_string(pID, in);
    virtualAddresses.push_back(address);
}


void Simulation::fillMap(int pID, Process* process) {
	mapProcess.emplace(pID, process);
}

void Simulation::run() {
    // TODO: implement me
    readFile();
    outputSizes();
}


char Simulation::perform_memory_access(const VirtualAddress& address) {
    // TODO: implement me
    if(!mapProcess[address.process_id]->page_table.rows[address.page].present) {
	      Process* tempProcess = mapProcess[address.process_id];
        size_t tempPageSize = address.page;
	      handle_page_fault(tempProcess, tempPageSize);
    }
    else {
      if(flag.verbose) {
          printInMemory();
      }
    }
    if(mapProcess[address.process_id]->is_valid_page(address.page)) {
      if(mapProcess[address.process_id]->pages[address.page]->is_valid_offset(address.offset)) {
        PhysicalAddress tempPhysicalAddress = PhysicalAddress(mapProcess[address.process_id]->page_table.rows.at(address.page).frame, address.offset);
        cout << "    -> physical address " << tempPhysicalAddress << endl;
	if(mapProcess[address.process_id]->get_rss() < 10) {
        cout << "    -> RSS: " << mapProcess[address.process_id]->get_rss() << "     "  << endl << endl;
       }
	else {
         cout << "    -> RSS: " << mapProcess[address.process_id]->get_rss() << "    "  << endl << endl;
       }
        if (mapProcess[address.process_id]->pages[address.page]->get_byte_at_offset(address.offset) == 0) {
          cout << "SEGFAULT - INVALID PAGE" << endl;
          exit(EXIT_FAILURE);
        }
        else {
            return mapProcess[address.process_id]->pages[address.page]->get_byte_at_offset(address.offset);
        }
      }
    }
    return 0;
}


void Simulation::handle_page_fault(Process* process, size_t page) {
    // TODO: implement me
    //cout << "DONT DIE YET" << endl;
    if(flag.verbose) {
      printPageFault();
    }
    bool isFifo = false;
    if(flag.strategy == ReplacementStrategy::FIFO) {
      isFifo = true;
    }
    bool isLRU = false;
    if(flag.strategy == ReplacementStrategy::LRU) {
      isLRU = true;
    }
    size_t currRss = process->get_rss();
    int currMaxFrames = flag.max_frames;
    if(currRss >= currMaxFrames) {
      if(isFifo) {
        size_t tempFrame = process->page_table.rows.at(process->page_table.get_oldest_page()).frame;
        process->page_table.rows.at(page).frame = tempFrame;
	      process->page_table.rows.at(process->page_table.get_oldest_page()).present = false;
      }
      if(isLRU) {
        size_t tempFrame = process->page_table.rows.at(process->page_table.get_least_recently_used_page()).frame;
        process->page_table.rows.at(page).frame = tempFrame;
	      process->page_table.rows.at(process->page_table.get_least_recently_used_page()).present = false;
      }
    }
    else if (currRss < currMaxFrames) {
      process->page_table.rows.at(page).frame = Simulation::getCurrFrame();
      Simulation::incrementCurrFrame();
    }
    process->page_table.rows.at(page).last_accessed_at = Simulation::getCurrTime();
    process->page_table.rows.at(page).loaded_at = Simulation::getCurrTime();
    process->page_faults = process->page_faults + 1;
    process->memory_accesses = process->memory_accesses + 1;
    process->page_table.rows.at(page).present = true;
}

int Simulation::getCurrFrame() {
  return currFrameInMemory;
}

void Simulation::incrementCurrFrame() {
  this->currFrameInMemory = currFrameInMemory + 1;
}

int Simulation::getCurrTime() {
  return currTime;
}

void Simulation::incrementTimer() {
  this->currTime = currTime + 1;
}

void Simulation::printPageFault() {
  cout << "    -> PAGE FAULT" << endl;

}

void Simulation::printInMemory() {
  cout << "    -> IN MEMORY" << endl;
}

void Simulation::print_summary() {
     if (!flag.csv) {
         boost::format process_fmt(
             "Process %3d:  "
             "ACCESSES: %-6lu "
             "FAULTS: %-6lu "
             "FAULT RATE: %-8.2f "
             "RSS: %-6lu\n");

         for (auto entry :mapProcess) {
             cout << boost::process_fmt
                 % entry.first
                 % entry.second->memory_accesses
                 % entry.second->page_faults
                 % entry.second->get_fault_percent()
                 % entry.second->get_rss();
         }

    //     // Print statistics.
         boost::format summary_fmt(
             "\n%-25s %12lu\n"
             "%-25s %12lu\n"
             "%-25s %12lu\n");

         cout << boost::summary_fmt
             % "Total memory accesses:"
             % addresses.size()
             % "Total page faults:"
             % page_faults
             % "Free frames remaining:"
             % free_frames.size();
     }

    // if (csv) {
    //     format process_fmt(
    //         "%d,"
    //         "%lu,"
    //         "%lu,"
    //         "%.2f,"
    //         "%lu\n");

    //     for (auto entry : processes) {
    //         cout << process_fmt
    //             % entry.first
    //             % entry.second->memory_accesses
    //             % entry.second->page_faults
    //             % entry.second->get_fault_percent()
    //             % entry.second->get_rss();
    //     }

    //     // Print statistics.
    //     format summary_fmt(
    //         "%lu,,,,\n"
    //         "%lu,,,,\n"
    //         "%lu,,,,\n");

    //     cout << summary_fmt
    //         % addresses.size()
    //         % page_faults
    //         % free_frames.size();
    // }
}


