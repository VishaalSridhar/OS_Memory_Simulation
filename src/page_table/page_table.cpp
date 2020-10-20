/**
 * This file contains implementations for methods in the PageTable class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page_table/page_table.h"
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;


size_t PageTable::get_present_page_count() const {
    // TODO: implement me
    size_t count = 0;
    for(int i = 0; i < rows.size(); i++) {
        if(rows.at(i).present == 1) {
	    count++;
	}
    }
    return count;
}

size_t PageTable::get_oldest_page() const {
    // TODO: implement me
   int minIndex = 0;
   int maxLoadTime = INT_MAX;

   for(int i = 0; i < rows.size(); i++) {
     if(rows.at(i).present == 1) {
       if(rows.at(i).loaded_at < maxLoadTime) {
	        maxLoadTime = rows.at(i).loaded_at;
	        minIndex = i;
       }
     }
    }



  return minIndex;
}


size_t PageTable::get_least_recently_used_page() const {
    // TODO: implement me
   int minIndex = 0;
   int leastAccessedAt = INT_MAX;

   for(int i = 0; i < rows.size(); i++) {
     if(rows.at(i).present == 1) {
       if(rows.at(i).last_accessed_at < leastAccessedAt) {
	  leastAccessedAt = rows.at(i).last_accessed_at;
	  minIndex = i;
       }
     }
    }

  return minIndex;
}
