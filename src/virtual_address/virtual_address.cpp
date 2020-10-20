/**
 * This file contains implementations for methods in the VirtualAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "virtual_address/virtual_address.h"
#include <string>
#include <iostream>
using namespace std;


VirtualAddress VirtualAddress::from_string(int process_id, string address) {
  // TODO: implement me
  string page_string = address.substr(0, PAGE_BITS);
  string offset_string = address.substr(PAGE_BITS, OFFSET_BITS);

  size_t page_address = std::stoull(page_string, 0, 2);
  size_t offset_address = std::stoull(offset_string, 0, 2);

  return VirtualAddress(process_id, page_address, offset_address);
}


string VirtualAddress::to_string() const {
  // TODO: implement me
  return bitset<10>(page).to_string() + bitset<6>(offset).to_string();
}


ostream& operator <<(ostream& out, const VirtualAddress& address) {
  // TODO: implement me
  out << "PID " << address.process_id << " @ " << address.to_string();
  out << " [page: " << address.page << "; offset: " << address.offset << "]";
  return out;
}
