/**
 * This file contains implementations for methods in the Page class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page/page.h"
#include <iostream>
using namespace std;


// Ensure PAGE_SIZE is initialized.
const size_t Page::PAGE_SIZE;


Page* Page::read_from_input(std::istream& in) {
    // TODO: implement me
    char x;
    int count  = 0;
	vector<char> input;
    Page temp(input);
    bool isNotEmpty = false;
    string tempString = "";
    while(in.good()) {
      count++;
      //cout << "LOOP 1" << endl;
      getline(in, tempString, '|'); 
      if(tempString.size() == 0) return nullptr; 
      isNotEmpty = true;
      bool goThrough = true;      
     
//	if(count < PAGE_SIZE && goThrough) {
	    //cout << "Count is: " << count << endl;
	    //cout << "PAGE SIZE IS: " << PAGE_SIZE << endl;
 	    //cout << "LOOP 2" << endl;
 	    //cout << x << endl;
	    int i = 0;
	    for (char &k: tempString) {
		if(i >= PAGE_SIZE) {
		       goThrough = false;
			break;
		}
	        input.push_back(k);
	//	temp.bytes.push_back(k);
	//	cout << temp.bytes.at(i) << endl;
		i++;
	    }
	    //cout << input[count - 1] << endl;
	//}
    } 
    //Page temp(input);
    //temp->size() = count;
    //temp->bytes = input;
/*
    for (int i = 0; i < input.size(); i++) {
	temp.bytes.push_back(input[i]);
    }*/

    if (isNotEmpty == false) {
	return nullptr;
   }
   else {
 	//cout << "LOOP 3" << endl;
	Page* temp1 = new Page(input);
	//temp1 = &temp;
	return temp1;	
   }
    
}


size_t Page::size() const {
    // TODO: implement me
    return bytes.size();
}


bool Page::is_valid_offset(size_t offset) const {
    // TODO: implement me
    
    if(offset < bytes.size()) {
	return true;
    }
    return false;
}


char Page::get_byte_at_offset(size_t offset) {
    // TODO: implement me

    char c;
/*
    for (int i = 0; i < bytes.size(); i++) {
	      // 	cout << "Hi" << endl;
	  	cout << bytes.at(i);
	}
*/
 
         return this->bytes.at(offset);



}
