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


int my_hash_d(const int & key, int bound) {

    return key % bound;

}

 int my_second_hash(const int & key, int bound) {


     int hash_d = (int)pow(key, 2.0);
     hash_d %= bound;
     if (hash_d == 0) ++hash_d;
     return hash_d;
}



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
    
    int max;
    int min;
    vector_t data;
    unsigned int current_size;
    
};



d_hash_table::d_hash_table(int max_size) : data(max_size,std::pair<int,bool>(0,false)), current_size(0) {}


d_hash_table::~d_hash_table() {}


void d_hash_table::resize() {

    vector_t new_data = data;
    data.clear();
    data.resize(data.size() * 2);

    data = std::move(new_data);

}


bool d_hash_table::add(const int & key) {

    if (this->has(key))
        return false;

    if (static_cast<double>(current_size / data.size()) >= 0.75) {
       
        resize();
        
    }

    const int hash = my_hash_d(key, data.size());

    if (!data[hash].second) {
        
        data[hash].first = key;
        data[hash].second = true;
        current_size++;
        return true;
        
    }
   
    else {
        
        int i = 1;
        while (i <= data.size()) {
            
            unsigned int new_index = (my_hash_d(key, data.size()) + i * my_second_hash(key, data.size())) % data.size();
           
            if (!data[new_index].second) {
                
                data[new_index].first = key;
                data[new_index].second = true;
                current_size++;
                return true;
                
            }
            
            else {
                
                i += 1;
                
            }
        }
        
        return false;
        
    }
}


bool d_hash_table::remove(const int & key) {

    int hash = my_hash_d(key, data.size());

    if (!data[hash].second) {

        return false;

    }

    else {
        
        int i = 1;

        while (data[hash].first != key) {
            
        hash = (my_hash_d(key, data.size()) + i * my_second_hash(key, data.size())) % data.size();
        ++i;
            
    }

        data[hash].second = false ;
        --current_size;
        return true;

    }
}


bool d_hash_table::has(const int & key) const {

    int hash = my_hash_d(key, data.size());
    int i = 1;
    while (data[hash].first != key) {
        
        hash = (my_hash_d(key, data.size()) + i * my_second_hash(key, data.size())) % data.size();
        ++i;
        if (i>=data.size()) break;
        
    }

    if(data[hash].first == key && data[hash].second == true){

        return true;

    }

    return false;
}


void d_hash_table::print(std::ostream &outputstream) {

    for (const auto &obj : data) {

        if (obj.second) {

            outputstream << obj.first<<" ";

        }
    }
}
