/**
 * This file contains implementations for methods in the Frame class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "frame/frame.h"
#include <iostream>

using namespace std;


void Frame::set_page(Process* process, size_t page_number) {
    // TODO: implement me
    //cout << "Page NUMBER IS: " << page_number << endl;
    this->page_number = page_number;
    this->process = process;
    //set page contents
    if(process->is_valid_page(page_number)) {
	this->contents = process->pages.at(page_number); 
    }

    
}
