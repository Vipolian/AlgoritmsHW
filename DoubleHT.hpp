//
// Created by Vipolion on 13.12.2017.
//

#ifndef HASHMAPS_DOUBLEHM_H
#define HASHMAPS_DOUBLEHM_H

#endif //HASHMAPS_DOUBLEHM_H

#include <assert.h>
#include <iostream>
#include <vector>
#include <cmath>




using vector_t = std::vector<std::pair<int,bool>>;


class d_hash_table {

public:

    explicit d_hash_table(int max_size);
    ~d_hash_table();
    bool has( const int & key ) const;
    bool add( const int & key );
    bool remove( const int & key );
    void print(std::ostream&);
    void resize();
    int Max();
    int Min();
    
private:
    
    int max=0;
    int min=0;
    vector_t data;
    unsigned int current_size;
    
};



