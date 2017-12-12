//
// Created by Vipolion on 09.12.2017.
//

#ifndef HASHMAP_CHAINHM_H
#define HASHMAP_CHAINHM_H

#endif //HASHMAP_CHAINHM_H

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
using std::string;

unsigned int MyEffectiveHash( const string& key, int bound )
{
    return key.empty() ? 0 : ( static_cast<unsigned int>( key[0] ) % bound );
}

class CHashTable {
public:
    explicit CHashTable( int initialTableSize );
    ~CHashTable();

    // Проверка наличия ключа в хеш-таблице.
    bool Has( const string& key ) const;
    // Добавление ключа. Возвращает false, если ключ уже есть в хеш-таблице, повторно его не добавляет.
    bool Add( const string& key );
    // Удаление ключа. Возвращает false, если ключа нет в хеш-таблице.
    bool Remove( const string& key );

private:
    // Узел односвязного списка.
    struct CHashTableNode {
        string Key;
        CHashTableNode* Next;
        explicit CHashTableNode( const string& key ) : Key( key ), Next( nullptr ) {}
    };
    std::vector<CHashTableNode*> table;
};

CHashTable::CHashTable( int initialTableSize ) :
        table( initialTableSize, nullptr )
{
}

CHashTable::~CHashTable()
{
    // Удаляем все цепочки.
    for( int i = 0; i < static_cast<int>( table.size() ); ++i ) {
        CHashTableNode* current = table[i];
        while( current != nullptr ) {
            CHashTableNode* next = current->Next;
            delete current;
            current = next;
        }
    }
}

bool CHashTable::Has( const string& key ) const
{
    const int hash = MyEffectiveHash( key, table.size() );

    for( CHashTableNode* node = table[hash]; node != nullptr; node = node->Next ) {
        if( node->Key == key ) {
            return true;
        }
    }
    return false;
}

bool CHashTable::Add( const string& key )
{
    const int hash = MyEffectiveHash( key, table.size() );
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

bool CHashTable::Remove( const string& key )
{
    const int hash = MyEffectiveHash( key, table.size() );

    // Если пустой список.
    if( table[hash] == nullptr ) {
        return false;
    }
    // Если удаляемый ключ - первый.
    if( table[hash]->Key == key ) {
        CHashTableNode* toDelete = table[hash];
        table[hash] = toDelete->Next;
        delete toDelete;
        return true;
    }

    for( CHashTableNode* prev = table[hash]; prev->Next != nullptr; prev = prev->Next ) {
        // Если удаляемый ключ - следующий.
        if( prev->Next->Key == key ) {
            CHashTableNode* toDelete = prev->Next;
            prev->Next = toDelete->Next;
            delete toDelete;
            return true;
        }
    }

    // Предыдущий код можно заменить на следующий:
    //for( CHashTableNode** node = &table[hash]; *node != nullptr; node = &( ( *node )->Next ) ) {
    //  if( ( *node )->Key == key ) {
    //      CHashTableNode* toDelete = *node;
    //      *node = toDelete->Next;
    //      delete toDelete;
    //      return true;
    //  }
    //}
    return false;
}


