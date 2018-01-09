//
// Created by Vipolion on 20.12.2017.
//
#include "LineHT.hpp"


int my_hash_l(const int & key, int bound) {

    return key % bound;

}

l_hash_table::l_hash_table(int max_size) : data( max_size, std::pair<std::pair<int,int>,bool> (std::pair<int,int>(0,0),false) ), current_size(0) {}


l_hash_table::~l_hash_table() = default;


void l_hash_table::resize() {

    vector_t new_data = data;
    data.clear();
    data.resize(data.size() * 2);
    data = std::move(new_data);

}


bool l_hash_table::add( std::pair<int,int> pair ) {

    if (this->has(pair.first)) {

        return false;

    }

    if (static_cast<double>(current_size / data.size()) >= 0.75) {

        resize();
    }

    const int hash = my_hash_l(pair.first, data.size());


    if (!data[hash].second) {
        data[hash].first.first = pair.first;
        data[hash].first.second = pair.second;
        data[hash].second = true;
        current_size++;
        return true;
    }

    else {

        int i = hash;

        while (i < data.size()+hash) {

            unsigned int new_index = (i+1) % data.size();

            if (!data[new_index].second) {

                data[new_index].first.first = pair.first;
                data[new_index].first.second = pair.second;
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


bool l_hash_table::remove( const int & key ) {

    int hash = my_hash_l(key, data.size());

    if (!data[hash].second)
        return false;

    else {

        int i = 0;

        while (data[hash].first.first != key && i<data.size()) {

            hash = (hash+1)%data.size();
            ++i;
        }

        data[hash].second = false ;
        --current_size;
        return true;

    }



}


bool l_hash_table::has( const int & key ) const {

    int hash = my_hash_l(key, data.size());
    int i = 1;
    while (data[hash].first.first != key && i<data.size()) {

        hash = (hash+1)%data.size();
        ++i;
        if (i >= data.size()) break;
    }

    return data[hash].first.first == key && data[hash].second;

}


void l_hash_table::print(std::ostream &outputstream) {

    for (const auto &obj : data) {

        if (obj.second) {

            outputstream << obj.first.first<< "->" << obj.first.second<<" ";

        }
    }
}


int l_hash_table::Min() {

    int min = 0;

    for (auto &i : data) {

        if (!i.second) {

            if (i.first.first) { min = i.first.first; }
            break;

        }

    }

    for (auto &i : data) {

        if (!i.second) {

            if (i.first.first < min) { min = i.first.first; }

        }

    }

    return min;

}


int l_hash_table::Max() {

    int max = 0;

    for (auto &i : data) {

        if (!i.second) {

            if (i.first.first) { max = i.first.first; }
            break;

        }

    }

    for (auto &i : data) {

        if (!i.second) {

            if (i.first.first > max) { max = i.first.first; }

        }

    }

    return max;
}
