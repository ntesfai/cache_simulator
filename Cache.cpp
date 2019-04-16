//
// Created by nubia on 4/10/2019.
//
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "Cache.h"

void Cache::queue_address(int mem_address, int index, int tag) {
    unsigned int neighboor_block;
    auto address = std::make_pair(index, tag);// Create a pair object with index and memory address as first & second
    if (associativity == 0) {
        std::swap(addresses.at((unsigned) index), address);
    } else if (associativity == 2) {
        neighboor_block = (unsigned) index + 8;
        //Both address blocks are invalid chose the index by default
        if (valid_blocks[index] == 0 && valid_blocks[neighboor_block] == 0) {
            std::swap(addresses.at((unsigned) index), address); //If all blocks invalid, use the index passed
            valid_blocks[index] = 1;
        } else if (valid_blocks[neighboor_block] == 0) {
            std::swap(addresses.at(neighboor_block),
                      address);
            valid_blocks[neighboor_block] = 1;
            lru_blocks[index] = 1;
        }
            //Both address blocks are valid, choose the LRU block
        else {
            if (lru_blocks[index] == 1) {
                std::swap(addresses.at((unsigned) index), address);
                lru_blocks[index] = 0;
                lru_blocks[neighboor_block] = 1;
            } else {
                std::swap(addresses.at(neighboor_block), address);
                lru_blocks[neighboor_block] = 0;
                lru_blocks[index] = 1;
            }
        }
    } else if (associativity == 4) {
        neighboor_block = (unsigned) index + 4;
        if (valid_blocks[index] == 0 && valid_blocks[neighboor_block] == 0 &&
            valid_blocks[neighboor_block + 4] == 0 && valid_blocks[neighboor_block + 8] == 0) {
            std::swap(addresses.at((unsigned) index), address);
            valid_blocks[index] = 1;
        } else if (valid_blocks[neighboor_block] == 0 &&
                   valid_blocks[neighboor_block + 4] == 0 && valid_blocks[neighboor_block + 8] == 0) {
            std::swap(addresses.at(neighboor_block), address);
            valid_blocks[neighboor_block] = 1;
        } else if (valid_blocks[neighboor_block + 4] == 0 && valid_blocks[neighboor_block + 8] == 0) {
            std::swap(addresses.at(neighboor_block + 4), address);
            valid_blocks[neighboor_block + 4] = 1;
        } else if (valid_blocks[neighboor_block + 8] == 0) {
            std::swap(addresses.at(neighboor_block + 8), address);
            valid_blocks[neighboor_block + 8] = 1;
            lru_blocks[index] = 1;
        }
            //All the address blocks are valid. Choose the LRU block to swap out.
        else {
            if (lru_blocks[index] == 1) {
                std::swap(addresses.at((unsigned) index), address);
                lru_blocks[index] = 0;
                lru_blocks[neighboor_block] = 1;
            } else if (lru_blocks[neighboor_block] == 1) {
                std::swap(addresses.at(neighboor_block), address);
                lru_blocks[neighboor_block] = 0;
                lru_blocks[neighboor_block + 4] = 1;
            } else if (lru_blocks[neighboor_block + 4] == 1) {
                std::swap(addresses.at(neighboor_block + 4), address);
                lru_blocks[neighboor_block + 4] = 0;
                lru_blocks[neighboor_block + 8] = 1;
            } else if (lru_blocks[neighboor_block + 8] == 1) {
                std::swap(addresses.at(neighboor_block + 8), address);
                lru_blocks[neighboor_block + 8] = 0;
                lru_blocks[index] = 1;
            }
        }
    } else if (associativity == 8) {
        neighboor_block = (unsigned) index + 2;
        //All the address blocks are invalid, swap the default index passed and set the valid bit to one
        if (valid_blocks[index] == 0 && valid_blocks[neighboor_block] == 0 &&
            valid_blocks[neighboor_block + 2] == 0 &&
            valid_blocks[neighboor_block + 4] == 0 &&
            valid_blocks[neighboor_block + 6] == 0 &&
            valid_blocks[neighboor_block + 8] == 0 &&
            valid_blocks[neighboor_block + 10] == 0 && valid_blocks[neighboor_block + 12] == 0) {
            std::swap(addresses.at((unsigned) index), address);
            valid_blocks[index] = 1;
        } else if (valid_blocks[neighboor_block] == 0 && valid_blocks[neighboor_block + 2] == 0 &&
                valid_blocks[neighboor_block + 4] == 0 &&
                 valid_blocks[neighboor_block + 6] == 0 &&
                 valid_blocks[neighboor_block + 8] == 0 &&
                 valid_blocks[neighboor_block + 10] == 0 && valid_blocks[neighboor_block + 12] == 0) {
            std::swap(addresses.at(neighboor_block), address);
            valid_blocks[neighboor_block] = 1;
        } else if (valid_blocks[neighboor_block + 2] == 0 &&
                valid_blocks[neighboor_block + 4] == 0 &&
                 valid_blocks[neighboor_block + 6] == 0 &&
                 valid_blocks[neighboor_block + 8] == 0 &&
                 valid_blocks[neighboor_block + 10] == 0 && valid_blocks[neighboor_block + 12] == 0) {
            std::swap(addresses.at(neighboor_block + 2), address);
            valid_blocks[neighboor_block + 2] = 1;
        } else if (valid_blocks[neighboor_block + 4] == 0 &&
                   valid_blocks[neighboor_block + 6] == 0 &&
                   valid_blocks[neighboor_block + 8] == 0 &&
                   valid_blocks[neighboor_block + 10] == 0 && valid_blocks[neighboor_block + 12] == 0) {
            std::swap(addresses.at(neighboor_block + 4), address);
            valid_blocks[neighboor_block + 4] = 1;
        } else if (valid_blocks[neighboor_block + 6] == 0 &&
                   valid_blocks[neighboor_block + 8] == 0 &&
                   valid_blocks[neighboor_block + 10] == 0 && valid_blocks[neighboor_block + 12] == 0) {
            std::swap(addresses.at(neighboor_block + 6), address);
            valid_blocks[neighboor_block + 6] = 1;
        } else if (valid_blocks[neighboor_block + 8] == 0 &&
                   valid_blocks[neighboor_block + 10] == 0 && valid_blocks[neighboor_block + 12] == 0) {
            std::swap(addresses.at(neighboor_block + 8), address);
            valid_blocks[neighboor_block + 8] = 1;
        } else if (valid_blocks[neighboor_block + 10] == 0 && valid_blocks[neighboor_block + 12] == 0) {
            std::swap(addresses.at(neighboor_block + 10), address);
            valid_blocks[neighboor_block + 10] = 1;
        } else if (valid_blocks[neighboor_block + 12] == 0) {
            std::swap(addresses.at(neighboor_block + 12), address);
            valid_blocks[neighboor_block + 12] = 1;
            lru_blocks[index] = 1;
        }
            //All the address blocks are valid. Select the LRU block
        else {
            if (lru_blocks[index] == 1) {
                std::swap(addresses.at((unsigned) index), address);
                lru_blocks[index] = 0;
                lru_blocks[neighboor_block] = 1;
            } else if (lru_blocks[neighboor_block] == 1) {
                std::swap(addresses.at(neighboor_block), address);
                lru_blocks[neighboor_block] = 0;
                lru_blocks[neighboor_block + 2] = 1;
            } else if (lru_blocks[neighboor_block + 2] == 1) {
                std::swap(addresses.at(neighboor_block + 2), address);
                lru_blocks[neighboor_block + 2] = 0;
                lru_blocks[neighboor_block + 4] = 1;
            } else if (lru_blocks[neighboor_block + 4] == 1) {
                std::swap(addresses.at(neighboor_block + 4), address);
                lru_blocks[neighboor_block + 4] = 0;
                lru_blocks[neighboor_block + 6] = 1;
            } else if (lru_blocks[neighboor_block + 6] == 1) {
                std::swap(addresses.at(neighboor_block + 6), address);
                lru_blocks[neighboor_block + 6] = 0;
                lru_blocks[neighboor_block + 8] = 1;
            } else if (lru_blocks[neighboor_block + 8] == 1) {
                std::swap(addresses.at(neighboor_block + 8), address);
                lru_blocks[neighboor_block + 8] = 0;
                lru_blocks[neighboor_block + 10] = 1;
            }
                //Set the LRU block address to the index
            else if (lru_blocks[neighboor_block + 10] == 1) {
                std::swap(addresses.at(neighboor_block + 10), address);
                lru_blocks[neighboor_block + 10] = 0;
                lru_blocks[neighboor_block + 12] = 1;
            } else {
                std::swap(addresses.at(neighboor_block + 12), address);
                lru_blocks[neighboor_block + 12] = 0;
                lru_blocks[index] = 1;
            }
        }
    } else if (associativity == 16) {
        static int all_blocks_valid = 0;
        static unsigned int lru_block = 0;
        //Iterate through the array of LRU block addresses, find an invalid address and swap memory. Otherwise use the LRU block
        if (all_blocks_valid == 0) {
            for (int i = 0; i < 16; i++) {
                if (valid_blocks[i] == 0) {
                    valid_blocks[i] = 1; //Mark block as valid
                    std::swap(addresses.at((unsigned) i), address);
                    if (valid_blocks[15] == 1) { //Terminate the loop since all bock addresses are valid
                        all_blocks_valid = 1;
                        lru_blocks[0] = 1;
                    }
                    break;
                }
            }
        } else {
            std::swap(addresses.at(lru_block), address);
            new_lru_address(++lru_block);
            if (lru_block == 15) // If we reach the end of the block in set associative cache, reset to 0
                lru_block = 0;
        }
    }
}


/*int Cache::has_address() {
    if(addresses.empty() || addresses.size() < 16)
        return 0;
    else
        return 1;
}*/

void Cache::cache_address(int mem_address, int index, int tag) {
    if (associativity == 0) {
        if (cache_map.find(index) == cache_map.end()) { // If there is an invalid block in a line
            ++cache_accesses;
            queue_address(mem_address, index, tag);
            cache_map[index] = tag;
            validate_block(index, associativity);
        } // Cache miss and load memory address from main memory
        else if (cache_map[index] == tag) { // Tag in a cache index is a match
            ++cache_accesses;
            ++cache_hits;
            queue_address(mem_address, index, tag);
        } // Cache hit, update address in the queue
        else if (cache_map[index] != tag) {
            ++cache_accesses;
            cache_map[index] = tag;
            queue_address(mem_address, index, tag);
        }//Cache miss, swap out the LRU memory address push the new index, address pair to the deque
    } else {
        auto it = cache_set.find(index);

        if (it == cache_set.end() || invalid_byte(index)) { //The entire cache line is invalid. Or there is an invalid byte address
            ++cache_accesses;
            queue_address(mem_address, index, tag);
            cache_set.insert(std::pair<int, int>(index, tag));
        } // Cache miss and load memory address from main memory
        else if (it->second == tag) {
            ++cache_accesses;
            ++cache_hits;
        } // Cache hit, update address in the queue and the cache multimap
        else if (it->second != tag) {
            ++cache_accesses;
            while (it != cache_set.end()) {
                if (it->second == tag && it->first == index) {
                    cache_hits++;
                    return;
                }
                else it++;
            }

            if (it == cache_set.end()) {//The cache line has no invalid byte addresses. Replace the LRU byte address
                //Update: Find the node corresponding to the lru byte address. Erase it from the cache set
                int at = lru_byte_address(index);//Code defect here.
                auto ptr = cache_set.begin();
                while(ptr != cache_set.end()) {
                    if(ptr->first == index && ptr->second == addresses.at((unsigned)at).second)
                        break;
                    else
                        ptr++;
                }
                if (ptr == cache_set.end()) {
                    std::cout << "DEBUG: Logic error in replacing lru byte address" << std::endl;
                    exit(EXIT_FAILURE);
                }
                else {
                    auto p = std::make_pair(index, tag);
                    auto p_set = std::make_pair(index, tag);
                    std::swap(addresses.at((unsigned) at), p); //Swap the contents of memory with the LRU byte address
                    cache_set.insert(p_set); //Insert the new index, tag pair to the map
                    new_lru_address(index); //Update the new LRU byte address
                    cache_set.erase(ptr);//Erase the old index, tag pair from the map
                }
            }
        }// Cache miss erase node if all byte addresses in the line are valid. Else add the address.
    }
}

int Cache::parse_block_index(int address, int associativity) {
    int idx = 0;
    if (associativity == 0) {
        idx = 0b00001111 & address;
        return idx;
    }// Direct mapped 4 bit tag, 4 bit cache index
    else if (associativity == 2) {
        idx = (0b00000111 & address);
        return idx;
    }// 2 way associativity 4 bit tag 3 bit cache index 1 bit offset
    else if (associativity == 4) {
        idx = (0b00000011 & address);
        return idx;
    }// 4 way associativity 4 bit tag 2 bit cache index 2 bit offset
    else if (associativity == 8) {
        idx = (0b000000001 & address);
        return idx;
    }// 8 way associativity 4 bit tag 1 bit cache index 3 bit offset
    else if (associativity == 16) {
        return idx;
    }// Full associativity 4 bit tag 0 default cache index 4 bit offset
    else
        return -1;
}

int Cache::parse_tag(int address) {
    uint8_t tag = 0;
    if (associativity == 0)
        tag = (uint8_t) (0b11110000 & address) >> 4;
    else if (associativity == 2)
        tag = (uint8_t) (0b11111000 & address) >> 3;
    else if(associativity == 4)
        tag = (uint8_t) (0b11111100 & address) >> 2;
    else if(associativity == 8)
        tag = (uint8_t) (0b11111110 & address) >> 1;
    else
        tag = (uint8_t) (0b11111111 & address);
    return tag;
}

void Cache::print_state(int associativity) {
    unsigned int index = 0;
    std::deque<std::pair<int, int>> address_copy = this->addresses;
    //std::sort(address_copy.begin(), address_copy.end()); //Sorts the queue copy based on the first element in each pair

    if (associativity == 0) {
        int i = 0;
        //Direct mapped output
        auto p = address_copy.begin();
        while (p != address_copy.end()) {
            if (p->first != -1 && p->second != -1) {
                std::cout << "Set " << i++ << ": " << p->second << std::endl;
            } else {
                std::cout << "Set " << i++ << ": " << "INVL"
                          << std::endl; //If the valid block is 0 then the block is invalid.
            }
            p++;
        }
        std::cout << std::endl;
        return;
    } else if (associativity == 2) {
        unsigned int neighboor_block = 8;
        //2 way set associativity
        while (index < 8) {
            if (addresses.at(index).first ==
                -1) //If the first cache address is invalid the neighbooring ones are as well
                std::cout << "Set " << index << ": " << "INVL" << " INVL" << std::endl;
            else if (addresses.at(neighboor_block).first == -1)
                std::cout << "Set" << index << ": " << addresses.at(index).second << " INVL" << std::endl;
            else
                std::cout << "Set" << index << ": " << addresses.at(index).second << " "
                          << addresses.at(neighboor_block).second << std::endl;

            index++;
            neighboor_block++;
        }

        std::cout << std::endl;
        return;
    } else if (associativity == 4) {
        unsigned int neighboor_block = 4;
        //4 way set associativity
        while (index < 4) {
            //If the first index is invalid, the neighboring ones are as well
            if (addresses.at(index).first == -1)
                std::cout << "Set " << index << ": " << "INVL" << " INVL" << "INVL" << "INVL" << std::endl;
            else if (addresses.at(neighboor_block).first == -1)
                std::cout << "Set " << index << ": " << addresses.at(index).second << " " <<" INVL " << " INVL " << " INVL"
                          << std::endl;
            else if (addresses.at(neighboor_block + 4).first == -1)
                std::cout << "Set " << index << ": " << addresses.at(index).second << " " <<
                          addresses.at(neighboor_block).second << " " << " INVL " << " INVL" << std::endl;
            else if (addresses.at(neighboor_block + 8).first == -1)
                std::cout << "Set " << index + 1 << ": " << addresses.at(index).second << " " <<
                          addresses.at(neighboor_block).second <<  " " <<addresses.at(neighboor_block + 4).second << " " << "INVL"
                          << std::endl;
            else
                std::cout << "Set " << index << ": " << addresses.at(index).second << " " <<
                          addresses.at(neighboor_block).second << " " << addresses.at(neighboor_block + 4).second << " " <<
                          addresses.at(neighboor_block + 8).second << std::endl;
            index++;
            neighboor_block++;

        }

        std::cout << std::endl;
        return;
    } else if (associativity == 8) {
        unsigned neighboor_block = index + 2;
        while (index < 2) {
            if (addresses.at(index).first == -1)
                std::cout << "Set " << index << ": " << "INVL " << "INVL " << "INVL " << "INVL " << "INVL " << "INVL "
                          << "INVL " << "INVL " << std::endl;
            else if (addresses.at(neighboor_block).first == -1)
                std::cout << "Set " << index << ": " << addresses.at(index).second << " INVL " << "INVL " << "INVL "
                          << "INVL " << "INVL " << "INVL " << "INVL " << std::endl;
            else if (addresses.at(neighboor_block + 2).first == -1)
                std::cout << "Set " << index << ": " << addresses.at(index).second
                          << " " << addresses.at(neighboor_block).second
                          << " INVL " << "INVL " << "INVL " << "INVL " << "INVL " << "INVL " << std::endl;
            else if (addresses.at(neighboor_block + 4).first == -1)
                std::cout << "Set " << index << ": " << addresses.at(index).second
                          << " " << addresses.at(neighboor_block).second
                          << " " << addresses.at(neighboor_block + 2).second  << " INVL " << "INVL " << "INVL " << "INVL "
                          << "INVL "
                          << std::endl;
            else if (addresses.at(neighboor_block + 6).first == -1)
                std::cout << "Set " << index << ": " << " " << addresses.at(index).second
                          << " " << addresses.at(neighboor_block).second
                          << " " <<  addresses.at(neighboor_block + 2).second << " " <<addresses.at(neighboor_block + 4).second
                          << " INVL " << "INVL " << "INVL " << "INVL "
                          << std::endl;
            else if (addresses.at(neighboor_block + 8).first == -1)
                std::cout << "Set " << index << ": " << addresses.at(index).second
                          << " " << addresses.at(neighboor_block).second
                          << " " << addresses.at(neighboor_block + 2).second << " " << addresses.at(neighboor_block + 4).second
                          << " " << addresses.at(neighboor_block + 6).second
                          << " " << "INVL " << "INVL " << "INVL "
                          << std::endl;
            else if (addresses.at(neighboor_block + 10).first == -1)
                std::cout << "Set " << index << ": " << addresses.at(index).second
                          << " " << addresses.at(neighboor_block).second << " " <<
                          addresses.at(neighboor_block + 2).second
                          << " " << addresses.at(neighboor_block + 4).second << " " << addresses.at(neighboor_block + 6).second
                          << " " << addresses.at(neighboor_block + 8).second << " INVL "
                          << "INVL " << std::endl;
            else if (addresses.at(neighboor_block + 12).first == -1)
                std::cout << "Set " << index << ": " << addresses.at(index).second
                          << " " << addresses.at(neighboor_block).second
                          << " " << addresses.at(neighboor_block + 2).second << " " << addresses.at(neighboor_block + 4).second
                          << " " << addresses.at(neighboor_block + 6).second << " " <<
                          addresses.at(neighboor_block + 8).second
                          << " " <<addresses.at(neighboor_block + 10).second  << " INVL"
                          << std::endl;
            else
                std::cout << "Set " << index << ": " << addresses.at(index).second
                          << " " << addresses.at(neighboor_block).second
                          << " " << addresses.at(neighboor_block + 2).second << " " << addresses.at(neighboor_block + 4).second
                          << " " << addresses.at(neighboor_block + 6).second << " " <<
                          addresses.at(neighboor_block + 8).second
                          << " " << addresses.at(neighboor_block + 10).second << " " << addresses.at(neighboor_block + 12).second
                          << std::endl;
            index++;
            neighboor_block++;

        }
        //8 way set associativity

        std::cout << std::endl;
        return;
    } else if (associativity == 16) {
        //full set associativity
        std::cout << "Set 0: ";
        for (; index < 16; index++) {
            if (addresses.at(index).first == -1)
                std::cout << "INVL ";

            else
                std::cout << addresses.at(index).second << " ";
        }

        std::cout << std::endl;
        return;
    }
}

int Cache::validate_block(int index, int associativity) {
    valid_blocks[index]++;
    if (associativity == 0 && valid_blocks[index] > 1) {
        std::cout << "DEBUG: More than one valid bit in one way associativity" << std::endl;
        exit(EXIT_FAILURE);
    } else if (associativity == 2 && valid_blocks[index] > 2) {
        std::cout << "DEBUG: More than two valid bits in two way associativity" << std::endl;
        exit(EXIT_FAILURE);
    } else if (associativity == 4 && valid_blocks[index] > 4) {
        std::cout << "DEBUG: More than four valid bits in two way associativity" << std::endl;
        exit(EXIT_FAILURE);
    } else if (associativity == 8 && valid_blocks[index] > 8) {
        std::cout << "DEBUG: More than eight valid bits in eight way associativity" << std::endl;
        exit(EXIT_FAILURE);
    } else if (associativity == 16 && valid_blocks[index] > 16) {
        std::cout << "DEBUG: More than 16 valid bits in full associativity" << std::endl;
        exit(EXIT_FAILURE);
    } else return 0;
}

int Cache::get_associativity() {
    return this->associativity;
}

int Cache::get_cache_hits() {
    return this->cache_hits;
}

int Cache::get_cache_accesses() {
    return this->cache_accesses;
}

bool Cache::invalid_byte(const int index) {
    unsigned int jump = 0;
    if (associativity == 2) {
        if (addresses.at(index).first == -1 || addresses.at(index + 8).first == -1)
            return true;
        else return false;
    } else if (associativity == 4) {
        for (int i = 0; i < 4; i++) {
            if (addresses.at(index + jump).first == -1)
                return true;
            else jump += 4;
        }
        return false;
    } else if (associativity == 8) {
        for (int i = 0; i < 8; i++) {
            if (addresses.at(index + jump).first == -1)
                return true;
            else jump += 2;
        }
        return false;
    } else if (associativity == 16) {
        for (int i = 0; i < 16; i++) {
            if (addresses.at((unsigned)i).first == -1)
                return true;
        }
        return false;
    }
    return false;
}

int Cache::lru_byte_address(int index) {
    int jump = 0;
    if (associativity == 2) {
        for (int i = 0; i < 2; i++) {
            if (lru_blocks[index + jump] == 1)
                return index + jump;
            else
                jump += 8;
        }
    } else if (associativity == 4) {
        for (int i = 0; i < 4; i++) {
            if (lru_blocks[index + jump] == 1)
                return index + jump;
            else
                jump += 4;
        }
    } else if (associativity == 8) {
        for (int i = 0; i < 8; i++) {
            if (lru_blocks[index + jump] == 1)
                return index + jump;
            else
                jump += 2;
        }
    } else {
        for (int i = 0; i < 16; i++) {
            if (lru_blocks[i] == 1)
                return i;
        }
    }
    exit(EXIT_FAILURE);
}

void Cache::new_lru_address(int index) {
    // Update the lru byte address for 2 way associativity
    if (associativity == 2) {
        // Check if this is the last byte address in the cache line. Sets the first byte address in cache line to LRU
        if (lru_blocks[index + 8] == 1) {
            lru_blocks[index + 8] = 0;
            lru_blocks[index] = 1;
        } else {
            lru_blocks[index] = 0;
            lru_blocks[index + 8] = 1;
        }
        return;
    } else if (associativity == 4) {
        // Check if this is the last byte address in the cache line. Sets the first byte address in cache line to LRU
        if (lru_blocks[index + 12] == 1) {
            lru_blocks[index + 12] = 0;
            lru_blocks[index] = 1;
        } else {
            for (int i = 0; i <= 8; i += 4) {
                if (lru_blocks[index + i] == 1) {
                    lru_blocks[index + i] = 0;
                    lru_blocks[index + i + 4] = 1;
                    return;
                }
            }
        } // Go through the cache line and find the byte address marked as LRU
    } else if (associativity == 8) {
        // Check if this is the last byte address in the cache line. Sets the first byte address in cache line to LRU
        if (lru_blocks[index + 14] == 1) {
            lru_blocks[index + 14] = 0;
            lru_blocks[index] = 1;
        } else {
            for (int i = 0; i <= 12; i++) {
                if (lru_blocks[index + i] == 1) {
                    lru_blocks[index + i] = 0;
                    lru_blocks[index + i + 2] = 1;
                    return;
                }
            }
        }
    } else //Associativity must be fully mapped
    {
        if (lru_blocks[15] == 1) {
            lru_blocks[15] = 0;
            lru_blocks[0] = 1;
        } else {
            for (int i = 0; i <= 14; i++) {
                if (lru_blocks[index + i] == 1) {
                    lru_blocks[index + i] = 0;
                    lru_blocks[index + i + 1] = 1;
                    return;
                }
            }
        }
    }
}

