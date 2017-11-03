#include <iostream>
#include <list>
#include <vector>
#include <cstring>
 
template <typename K>
struct HashFunction {
    virtual ~HashFunction() {}
    virtual size_t hash(const K &value) const = 0;
    virtual void setBits(size_t count) = 0;
};
 
template <typename K>
class DefaultHashFunction : public HashFunction<K> {
public:
    void setBits(size_t count);
    size_t hash(const K &value) const;
};
 
// define more intelligently
#define BITS_IN_INT 32
 
template <>
class DefaultHashFunction<int> : public HashFunction<int> {
    size_t bits;
public:
    DefaultHashFunction(size_t bits_ = BITS_IN_INT) : bits(bits_) {}
    
    void setBits(size_t count) { bits = count; }
    
    size_t hash(const int &value) const
    {
        return (size_t)(value * 0x9E370001UL) >> (BITS_IN_INT - bits);
    }
};
 
template <typename K, typename V>
class hashtable {
    size_t bucket_bits;
    size_t bucket_count;
    
    typedef std::list<std::pair<K, V> > bukkit_t;
 
    std::vector<bukkit_t*> buckets;
    HashFunction<K> *please;
    
public:
    hashtable(HashFunction<K> *func = new DefaultHashFunction<K>());
    virtual ~hashtable();
    
    bool contains(const K &key) const;
    bool add(const K &key, const V &value);
    V& get(const K &key);
    bool remove(const K &key);
    
    
    template <typename K_, typename V_>
    friend
    std::ostream& operator<<(std::ostream &stream, const hashtable<K_, V_> &table);
    
private:
    bool bucketContains(const bukkit_t* bucket, const K &key) const;
    typename bukkit_t::iterator find(const K &key, bukkit_t *bucket) const;
};
 
template <typename K, typename V>
hashtable<K, V>::hashtable(HashFunction<K> *func /*= new DefaultHashFunction<K>(bucket_bits)*/)
  : bucket_bits(8),
    bucket_count(1 << bucket_bits),
    buckets(bucket_count, NULL),
    please(func)
{
    please->setBits(bucket_bits);
}
 
template <typename K, typename V>
hashtable<K, V>::~hashtable()
{
    for (size_t i = 0; i < bucket_count; ++i) {
        delete buckets[i];
    }
    delete please;
}
 
template <typename K, typename V>
bool hashtable<K, V>::contains(const K &key) const
{
    size_t bucket = please->hash(key);
    if (!buckets[bucket]) {
        return false;
    }
    return bucketContains(buckets[bucket], key);
}
 
template <typename K, typename V>
bool hashtable<K, V>::bucketContains(const bukkit_t* bucket, const K &key) const
{
    for (typename bukkit_t::const_iterator i = bucket->begin();
         i != bucket->end();
         ++i)
    {
        if ((*i).first == key) {
            return true;
        }
    }
    return false;
}
 
template <typename K, typename V>
bool hashtable<K, V>::add(const K &key, const V &value)
{
    if (contains(key)) {
        return false;
    }
    size_t bucket = please->hash(key);
    bukkit_t *theBucket = buckets[bucket];
    if (!theBucket) {
        theBucket = buckets[bucket] = new bukkit_t();
    }
    theBucket->push_front(std::pair<K, V>(key, value));
    return true;
}
 
template <typename K, typename V>
bool hashtable<K, V>::remove(const K &key)
{
    bukkit_t *bucket = buckets[please->hash(key)];
    if (!bucket) {
        return false;
    }
    typename bukkit_t::iterator pos = find(key, bucket);
    if (pos == bucket->end()) {
        return false;
    }
    bucket->erase(pos);
    return true;
}
 
template <typename K, typename V>
typename hashtable<K, V>::bukkit_t::iterator
  hashtable<K, V>::find(const K &key, bukkit_t *bucket) const
{
    // assert !bucket
    typename bukkit_t::iterator res;
    for (res = bucket->begin(); res != bucket->end(); ++res) {
        if ((*res).first == key) {
            break;
        }
    }
    return res;
}
 
template <typename K, typename V>
V& hashtable<K, V>::get(const K &key)
{
    // assert contains(key)
    return (*find(key, buckets[please->hash(key)])).second;
}
 
template <typename K, typename V>
std::ostream& operator<<(std::ostream &stream, const hashtable<K, V> &table)
{
    stream << "[";
    bool first = true;
    for (typename std::vector<typename hashtable<K, V>::bukkit_t*>::const_iterator bucket = table.buckets.begin();
         bucket != table.buckets.end();
         ++bucket)
    {
        if (*bucket == NULL) {
            continue;
        }
        for (typename hashtable<K, V>::bukkit_t::const_iterator i = (*bucket)->begin();
             i != (*bucket)->end();
             ++i)
        {
            if (!first) {
                stream << ", ";
            }
            else {
                first = false;
            }
            stream << (*i).first << " -> " << (*i).second;
        }
    }
    stream << "]";
    return stream;
}
 
int main()
{
    hashtable<int, int> test;
    for (int i = 1; i < 10; ++i) {
        test.add(i, i * i);
    }
    std::cout << test << "\n";
    test.remove(5);
    std::cout << test << "\n";
    std::cout << "Hash does " << (test.contains(10) ? "" : "not ") << "contain key 10\n";
    std::cout << "Hash does " << (test.contains(7) ? "" : "not ") << "contain key 7\n";
}
