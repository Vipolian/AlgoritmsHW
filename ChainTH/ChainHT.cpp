//
// Created by Vipolion on 20.12.2017.
//

#include "ChainHT.hpp"

int my_hash_c(const int &key, int bound)
{
    return key % bound;
}

c_hash_table::c_hash_table( int initialTableSize ) : table( initialTableSize, nullptr ) {}


c_hash_table::~c_hash_table() {

    for (auto current : table) {
        while( current != nullptr ) {
            CHashTableNode* next = current->Next;
            delete current;
            current = next;

        }
    }
}


bool c_hash_table::has( const int &key ) const {

    const int hash = my_hash_c(key, table.size());

    for( CHashTableNode* node = table[hash]; node != nullptr; node = node->Next ) {

        if( node->data.first == key ) {

            return true;

        }
    }

    return false;

}


bool c_hash_table::add( std::pair<int,int> pair ) {

    const int hash = my_hash_c( pair.first, table.size() );

    for( CHashTableNode* node = table[hash]; node != nullptr; node = node->Next ) {

        if( node->data.first == pair.first ) {

            return false;

        }
    }


    CHashTableNode* newNode = new CHashTableNode( pair );
    newNode->Next = table[hash];
    table[hash] = newNode;
    return true;

}


bool c_hash_table::remove(const int &key) {

    const int hash = my_hash_c( key, table.size() );


    if( table[hash] == nullptr ) {

        return false;
    }

    if( table[hash]->data.first == key ) {

        CHashTableNode* toDelete = table[hash];
        table[hash] = toDelete->Next;
        delete toDelete;
        return true;

    }

    for( CHashTableNode* prev = table[hash]; prev->Next != nullptr; prev = prev->Next ) {

        if( prev->Next->data.first == key ) {

            CHashTableNode* toDelete = prev->Next;
            prev->Next = toDelete->Next;
            delete toDelete;
            return true;

        }
    }

    return false;

}


void c_hash_table::print(std::ostream &outputstream) {

    for (auto current : table) {

        while( current != nullptr ) {

            CHashTableNode* next = current->Next;
            outputstream << current->data.first<< "->" << current->data.second << " ";
            current = next;

        }

        outputstream << std::endl;

    }

}

int c_hash_table::Min() {

    int min = 0;

    for (auto &i : table) {

        if (i)  min = i->data.first;
        break;

    }


    for (auto current : table) {

        while( current != nullptr ) {

            CHashTableNode* next = current->Next;

            if (current->data.first < min) { min = current->data.first; }

            current = next;

        }
    }

    return min;
}


int c_hash_table::Max() {

    int max = 0 ;

    for (auto &i : table) {

        if (i)  max = i->data.first;
        break;

    }



    for (auto current : table) {

        while( current != nullptr ) {

            CHashTableNode* next = current->Next;

            if (current->data.first > max) { max = current->data.first; }

            current = next;

        }
    }

    return max;

}
