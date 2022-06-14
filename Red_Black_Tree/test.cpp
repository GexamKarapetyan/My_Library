#include <iostream>

#include "../map/map.h"


int main() {

    mylib::map<int, int> l;
   l.insert(mylib::make_pair(1, 99));
//         l.insert(mylib::make_pair(12, 7));
    l.insert(mylib::make_pair(13, 1200));
    l.insert(mylib::make_pair(37, 1200));
    l.insert(mylib::make_pair(19, 1200));
    l.insert(mylib::make_pair(23, 1200));
    l.insert(mylib::make_pair(43, 1200));
    // l.insert(mylib::make_pair(3, 1200));
    // l.insert(mylib::make_pair(11, 1200));
    // l.insert(mylib::make_pair(317, 1200));
    // l.insert(mylib::make_pair(1239, 1200));
    // l.insert(mylib::make_pair(243123, 1200));
    // l.insert(mylib::make_pair(423431243, 1200));
    // l.insert(mylib::make_pair(32314, 1200));
    // l.insert(mylib::make_pair(1321, 1200));
    l.print();
    std::cout << "\n\n";
    l.clear();

   // l.clear();
    l.print();
//  auto itr = l.begin();
//  ++itr;
//     std::cout << (*itr).first;

}