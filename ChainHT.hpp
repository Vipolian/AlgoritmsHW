//
// Created by Vipolion on 09.12.2017.
//


#include <assert.h>
#include <iostream>
#include <utility>
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
        explicit CHashTableNode( std::pair<int,int> pair ) : data(std::move(pair)), Next( nullptr ) {}
    };

    std::vector<CHashTableNode*> table;
};



