
#ifndef HASHMAP_CHAINHM_H
#define HASHMAP_CHAINHM_H

#endif //HASHMAP_CHAINHM_H

#include <assert.h>
#include <iostream>
#include <vector>

 int my_hash_c(const int &key, int bound)
{
    return key % bound;
}

class c_hash_table {
public:
    
    explicit c_hash_table( int initialTableSize );
    ~c_hash_table();
    bool Has( const int& key ) const;
    bool Add( const int& key );
    bool Remove( const int& key );
    void print();
    int Max();
    int Min();

private:
  
    struct CHashTableNode {
        int Key;
        CHashTableNode* Next;
        explicit CHashTableNode( const int& key ) : Key( key ), Next( nullptr ) {}
    };
    
    std::vector<CHashTableNode*> table;
};


c_hash_table::c_hash_table( int initialTableSize ) : table( initialTableSize, nullptr ) {}


c_hash_table::~c_hash_table() {
    
    for( int i = 0 ; i <  table.size() ; ++i ) {
        CHashTableNode* current = table[i];
        while( current != nullptr ) {
            CHashTableNode* next = current->Next;
            delete current;
            current = next;
            
        }
    }
}


bool c_hash_table::Has( const int& key ) const {
    
    const int hash = my_hash_c(key, table.size());

    for( CHashTableNode* node = table[hash]; node != nullptr; node = node->Next ) {
        
        if( node->Key == key ) {
            
            return true;
            
        }
    }
    
    return false;
    
}


bool c_hash_table::Add( const int& key ) {
    
    const int hash = my_hash_c(key, table.size());
    
    for( CHashTableNode* node = table[hash]; node != nullptr; node = node->Next ) {
       
        if( node->Key == key ) {
            
            return false;
        
        }
    }
    
    CHashTableNode* newNode = new CHashTableNode( key );
    newNode->Next = table[hash];
    table[hash] = newNode;
    return true;
    
}


bool c_hash_table::Remove( const int& key ) {
    
    const int hash = my_hash_c(key, table.size());

    
    if( table[hash] == nullptr ) {
       
        return false;
    }
    
    if( table[hash]->Key == key ) {
        CHashTableNode* toDelete = table[hash];
        table[hash] = toDelete->Next;
        delete toDelete;
        return true;
        
    }

    for( CHashTableNode* prev = table[hash]; prev->Next != nullptr; prev = prev->Next ) {
        
        if( prev->Next->Key == key ) {
            CHashTableNode* toDelete = prev->Next;
            prev->Next = toDelete->Next;
            delete toDelete;
            return true;
            
        }
    }
    
    return false;
    
}


void c_hash_table::print() {
    
    for( int i = 0; i < static_cast<int>( table.size() ); ++i ) {
       
        CHashTableNode* current = table[i];
        while( current != nullptr ) {
            CHashTableNode* next = current->Next;
            std::cout << current->Key << std::endl;
            current = next;

        }
    }
    
}
