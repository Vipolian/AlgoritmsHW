//
// Created by Vipolion on 13.12.2017.
//

#ifndef HASHMAPS_LINEHM_H
#define HASHMAPS_LINEHM_H

#endif //HASHMAPS_LINEHM_H

#include <assert.h>
#include <iostream>
#include <vector>
#include <cmath>


using vector_t = std::vector<std::pair<std::pair<int,int>,bool>>;


class l_hash_table {

public:

    explicit l_hash_table(int max_size);
    ~l_hash_table();
    bool has( const int & key ) const;
    bool add( std::pair<int,int> pair );
    bool remove( const int & key );
    void print( std::ostream& );
    void resize();
    int Max();
    int Min();

private:

    int max=0;
    int min=0;
    vector_t data;
    unsigned int current_size;

};



