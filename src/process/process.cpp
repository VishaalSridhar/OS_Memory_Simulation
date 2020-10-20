/**
 * This file contains implementations for methods in the Process class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "process/process.h"
#include <sstream>
#include <iostream>

using namespace std;


Process* Process::read_from_input(std::istream& in) {
    // TODO: implement me
	string input, tempString = "";
	int max_count = 64;
	int i=0;
	size_t bytes = 0;
	vector<Page*> tempPages;
	while(!in.eof()) {
	    getline(in, input, '|');
	    for(char &k: input) {
		tempString = tempString + k;
		i++;
		bytes++;
		if (i == max_count) {
		    Page* newPage;
		    istringstream currPageContents(tempString);
		    newPage = newPage->read_from_input(currPageContents);
		    tempPages.push_back(newPage);
		    //cout << "TEMPSTRING IS: " << tempString << endl;
		    tempString = "";
		    i = 0;
		}
	    }
	}

	bool greaterZero = false;
	if(tempString.size() > 0) {
	    greaterZero = true;
	}
	if(greaterZero) {
	    Page* newPage;
	    istringstream currPageContents(tempString);
	    newPage = newPage->read_from_input(currPageContents);
	    tempPages.push_back(newPage);
	    tempString = "";
	    i = 0;
	}
	Process* newProcess = new Process(bytes, tempPages);

	//cout << "BYTES SIZE is: " << bytes << endl;
	//cout << "PAGE VECTOR SIZE IS: " << tempPages.size() << endl;
	return newProcess;

}


size_t Process::size() const {
    // TODO: implement me
    return num_bytes;
}


bool Process::is_valid_page(size_t index) const {
    // TODO: implement me
    if (index < 0) return false;
    if(index < pages.size()) return true;
    return false;
}


size_t Process::get_rss() const {
    // TODO: implement me
    size_t count = 0;
    for(int k = 0; k < pages.size(); k++) {
	if(page_table.rows.at(k).present == true) {
	    count++;
	}
    }
    return count;
}


double Process::get_fault_percent() const {
    // TODO: implement me
    if(this->memory_accesses == 0) return 0.0;
    return ((double)this->page_faults /(double) this->memory_accesses) * 100;
}
