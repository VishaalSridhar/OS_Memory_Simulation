/**
 * This file contains implementations for methods in the PhysicalAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "physical_address/physical_address.h"
#include <iostream>

using namespace std;

string PhysicalAddress::to_string() const {
    // TODO: implement me
    /* string frame_address;
    int temp = frame;

    while (temp != 0) {
	frame_address = (temp % 2 == 0 ? "0":"1") + frame_address;
	temp /= 2;
    }
    cout << "frame is: " << frame_address << endl;

    string offset_address;
    int temp2 = offset;

    while (temp2 != 0) {
	offset_address = (offset % 2 == 0 ? "0":"1") + offset_address;
	temp2 /= 2;
    }
    cout << "Offset is: " << offset_address << endl;

    string physical_address = frame_address + offset_address;
    cout << "IT IS: " << physical_address << endl;
    
    return physical_address;
    */

     //Final String to output
     string physical_address;

     // Converting frame to unsigned long for bitset
     unsigned long frame_address = frame;
     bitset<FRAME_BITS> fbits(frame_address);
     physical_address = fbits.to_string();
     unsigned long offset_address = offset;
     bitset<OFFSET_BITS> obits(offset_address);
     physical_address += obits.to_string();


     return physical_address;

}


ostream& operator <<(ostream& out, const PhysicalAddress& address) {
    // TODO: implement me
    out << address.to_string();
    out << " [frame: " << address.frame << "; offset: " << address.offset << "]";
    return out;
}
