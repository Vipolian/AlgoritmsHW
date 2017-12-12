#include <iostream>
#include <vector>



unsigned int my_hash(const std::string & key, int bound) {

    
}

unsigned int my_second_hash(const std::string & key, int bound) {

    return key.empty() ? 0 : (static_cast<unsigned int>(key[0]) % (bound - 1) + 1);
}



using vector_t = std::vector<std::string>;


class hash_table {

public:

    explicit hash_table(int max_size);
    ~hash_table();

    // Проверка наличия ключа в хеш-таблице.
    bool has( const std::string & key ) const;
    // Добавление ключа. Возвращает false, если ключ уже есть в хеш-таблице, повторно его не добавляет.
    bool add( const std::string & key );
    // Удаление ключа. Возвращает false, если ключа нет в хеш-таблице.
    bool remove( const std::string & key );

    void resize();


private:

    vector_t data;
    unsigned int current_size;
};



hash_table::hash_table(int max_size) : data(max_size, ""), current_size(0) {}

hash_table::~hash_table() {}


void hash_table::resize() {

    vector_t new_data = data;
    data.clear();
    data.resize(data.size() * 2);

    for (const auto & obj: new_data) {
        add(obj);
    }

}


bool hash_table::add(const std::string & key) {

    if (this->has(key))
        return false;

    if (static_cast<double>(current_size / data.size()) >= 0.75) {
        resize();
    }

    const int hash = my_hash(key, data.size());


    if (data[hash] == "") {
        data[hash] = key;
        current_size++;
        return true;
    }
    else {
        int i = 1;
        while (i <= data.size()) {
            unsigned int new_index = (my_hash(key, data.size()) + i * my_second_hash(key, data.size())) % data.size();
            if (data[new_index] == "") {
                data[new_index] = key;
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


bool hash_table::remove(const std::string & key) {

    const int hash = my_hash(key, data.size());

    if (data[hash] == "")
        return false;

    else
        data[hash] = "";

    return true;

}

bool hash_table::has(const std::string & key) const {

    const int hash = my_hash(key, data.size());

    for (int i = hash; i < data.size(); ++i) {
        if(data[i] == key)
            return true;
    }

    return false;
}



