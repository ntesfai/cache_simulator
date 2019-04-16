//
// Created by nubia on 4/10/2019.
/**Author: Nubian Tesfai
 * Organization: Arizona State University
 * Date: 4/10/2019
 *
 * This program will simulate cache memory accesses given an input file of memory addresses. Uses LRU replacement
 * algorithm.
    */
#ifndef NTESFAI_PROJECT_4_CACHE_H
#define NTESFAI_PROJECT_4_CACHE_H

#include <deque>
#include <utility>
#include <stdint.h>
#include <unordered_map>
#include <map>

class Cache {

private:

    int associativity;
    int valid_blocks[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int lru_blocks[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    unsigned int cache_accesses;
    unsigned int cache_hits;
    /*Queue data structure queues and tracks the LRU memory address. If a memory access matches the address at the front
     * of the queue, it is dequeued
     * */
    std::deque<std::pair<int , int>> addresses; //Index key address value
    //Hashmap that stores the address using uint_t8 index, tag. Helps to quickly determine a hit or miss.
    std::multimap<int, int> cache_set;
    std::map<int , int> cache_map;

public:

    /**Cache constructor
     * accepts the associativity as a parameter. Initializes a queue that contains memory addresses as 8 bit values*/
    Cache(int associativity) {
        this->cache_accesses = 0;
        this->cache_hits = 0;
        this->associativity = associativity;
        for(int i = 0; i < 16; i++) {
            auto address = std::make_pair(-1, -1);
            addresses.push_front(address);
        }
    }

    /**Cache destructor*/
    ~Cache() {
        this->associativity = 0;
    }

    /**Name: queue_address
     * Parameter: uint8_t
     * pushes a memory address into the addresses queue.*/
    void queue_address(int, int, int);

    /**Name: cache_address
     * Parameter: uint8_t, uint8_t
     * Inserts the index key tag value into the cache map. If the tags match, increment cache hits by one.
     * */
     void cache_address(int, int, int);

    /**Name: has_address
     * Returns 0 if the queue has no addresses contained within it or if there are less than 16 in cache,
     * else returns 1*/
    int has_address();

    /**Name: print_state
     * Parameters: none
     * Method sends the state of the cache to the standard output.*/
    void print_state(int);

    /**Name: parse_tag
     * Parameters: uint8_t
     * Method parses the word and returns correct cache tag.*/
    int parse_tag(int);

    /**Name: parse_block_index
     * Parameter: uint8_t
     * Method parses the word and returns the correct block index*/
    int parse_block_index(int, int);

    /**Name: validate_block
     * Parameter: uint8_t
     * Increments the integer value in the corresponding cache block. The valid bit in an invalid block must be flipped
     * on a cache miss.*/
     int validate_block(int, int);

     /**Name: get_associativity
      * Returns the value of the associativity of the cache object*/
      int get_associativity();

      /**Name: get_cache_hits
       * Returns the number of cache hits*/
      int get_cache_hits();

      /**Name: get_cache_accesses
       * Returns the number of cache accesses*/
      int get_cache_accesses();

      /**Name: invalid_byte
       * Parameter: int
       * Returns true if there exists a byte address that is still invalid in the cache line, false otherwise.*/
      bool invalid_byte(int index);

      /**Name: lru_byte_address
       * Parameter: int
       * Returns the index value for the LRU byte address in the deque.*/
       int lru_byte_address(int index);

       /**Name: new_lru_address
        * Parameter: int
        * Sets the new location of the LRU byte address in a cache line*/
        void new_lru_address(int index);

};
#endif //NTESFAI_PROJECT_4_CACHE_H
