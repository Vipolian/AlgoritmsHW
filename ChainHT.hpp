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
    bool add(const int &key);
    bool remove(const int &key);
    void print(std::ostream&);
    int Max();
    int Min();

private:

    struct CHashTableNode {
        int Key;
        CHashTableNode* Next;
        explicit CHashTableNode( const int& key ) : Key( key ), Next( nullptr ) {}
    };

    int min=0;
    int max=0;
    std::vector<CHashTableNode*> table;
};



