/**Author: Nubian Tesfai
 * Organization: Arizona State University
 * Date: 4/10/2019
 *
 * This program will simulate cache memory accesses given an input file of memory addresses. The output will show the
 * state of the cache and a visual representation of the associativity.*/

/**Name: main
 * Parameters: .txt file
 * Method for the start of the program execution. Calls methods needed to simulate cache hardware. A text file with
 * listed addresses are read line by line and cache hits/misses are calculated. The associativity is specified as a
 * program input after the text file name.*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <system_error>
#include "Cache.h"

int main(int argc, char*argv[]) {

    Cache *cache = new Cache((uint8_t)std::stoi(argv[2]));

    std::string file_name = argv[1];
    std::ifstream source(file_name.c_str());
    std::string line;
    int address;
    int index;

    //Open source file check
    if(!source.is_open()) {
       std::cout << "Error in opening txt file." << std::endl;
       return -1;
    }

    std::cout << "Nubian Tesfai" << std::endl;
    std::cout<< std::setbase(16);
    std::cout << std::setw(10) << std::setfill('0');
    //While loop reads each line in the .txt file, converts the string in line to an uint8_t.
    while(std::getline(source, line)) {
       address = stoi(line, nullptr, 16);
       int temp = cache->parse_block_index(address, cache->get_associativity());
        //If the index is calculated correctly it will be positive. Otherwise exit the program.
       if(temp != -1)
           index = temp;
       else {
           std::cout << "Error in parsing cache index" << std::endl;
           return -1;
       }
       int tag = cache->parse_tag(address);
       cache->cache_address(address, index, tag);
       cache->print_state(cache->get_associativity());
    }
    std::cout<< std::setbase(10);
    std::cout << "Hits: " << cache->get_cache_hits() << std::endl;
    std::cout << "Misses: " << cache->get_cache_accesses() - cache->get_cache_hits() << std::endl;

    delete cache;
    return 0;
}
