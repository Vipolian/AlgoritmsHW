//
// Created by Vipolion on 20.12.2017.
//
#include "DoubleHT.hpp"


int my_hash_d(const int & key, int bound) {

    return key % bound;

}


int my_second_hash(const int & key, int bound) {


    int hash_d = (int)pow(key, 2.0);
    hash_d %= bound;
    if (hash_d == 0) ++hash_d;
    return hash_d;
}

d_hash_table::d_hash_table(int max_size) : data( max_size, std::pair<std::pair<int,int>,bool> (std::pair<int,int>(0,0),false) ), current_size(0) {}


d_hash_table::~d_hash_table() {}


void d_hash_table::resize() {

    vector_t new_data = data;
    data.clear();
    data.resize(data.size() * 2);

    data = std::move(new_data);

}


bool d_hash_table::add( std::pair<int,int> pair ) {

    if (this->has(pair.first)){
        return false;
    }

    if (static_cast<double>(current_size / data.size()) >= 0.75) {

        resize();

    }

    const int hash = my_hash_d(pair.first, data.size());



    if (!data[hash].second) {

        data[hash].first.first = pair.first;
        data[hash].first.second = pair.second;
        data[hash].second = true;
        current_size++;
        return true;

    }

    else {

        int i = 1;
        while (i <= data.size()) {

            unsigned int new_index = (my_hash_d(pair.first, data.size()) + i * my_second_hash(pair.first, data.size())) % data.size();

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


bool d_hash_table::remove(const int & key) {

    int hash = my_hash_d(key, data.size());

    if (!data[hash].second) {

        return false;

    }

    else {

        int i = 1;

        while (data[hash].first.first != key) {

            hash = (my_hash_d(key, data.size()) + i * my_second_hash(key, data.size())) % data.size();
            ++i;

        }

        data[hash].second = false ;
        --current_size;
        return true;

    }
}


bool d_hash_table::has( const int & key ) const {

    int hash = my_hash_d( key, data.size() );
    int i = 1;
    while (data[hash].first.first != key) {

        hash = (my_hash_d(key, data.size()) + i * my_second_hash(key, data.size())) % data.size();
        ++i;
        if (i>=data.size()) break;

    }

    return data[hash].first.first == key && data[hash].second;

}


void d_hash_table::print(std::ostream &outputstream) {

    for (const auto &obj : data) {

        if (obj.second) {

            outputstream << obj.first.first<< "->" << obj.first.second<<" ";

        }
    }
}


int d_hash_table::Min() {

    int min = 0;

    for (auto &i : data) {

        if (i.second) {

            if (i.first.first) { min = i.first.first; }

        }

    }


    for (auto &i : data) {

        if (i.second) {

            if (i.first.first < min) { min = i.first.first; }

        }

    }
    return min;
}


int d_hash_table::Max() {

    int max = 0;

    for (auto &i : data) {

        if (i.second) {

            if (i.first.first) { max = i.first.first; }
            break;

        }
    }


    for (auto &i : data) {

        if (i.second) {

            if (i.first.first > max) { max = i.first.first; }

        }
    }

    return max;

}