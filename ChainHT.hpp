//
// Created by Vipolion on 09.12.2017.
//

#ifndef HASHMAP_CHAINHM_H
#define HASHMAP_CHAINHM_H

#include <assert.h>
#include <iostream>
#include <vector>



class c_hash_table {
public:

    explicit c_hash_table( int initialTableSize );
    ~c_hash_table();
    bool has(const int &key) const;
    bool add( std::pair<int,int> pair );
    bool remove(const int &key);
    void print(std::ostream&);
    int Max();
    int Min();

private:

    struct CHashTableNode {
        std::pair<int,int> data;
        CHashTableNode* Next;
        explicit CHashTableNode( std::pair<int,int> pair ) : data(pair), Next( nullptr ) {}
    };

    int min=0;
    int max=0;
    std::vector<CHashTableNode*> table;
};



