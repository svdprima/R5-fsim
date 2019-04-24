#ifndef SIMPLE_CACHE_H
#define SIMPLE_CACHE_H

#include <map>
#include <array>

template<typename value_t>
class SimpleCache
{
public:
    static constexpr uint32_t cache_size = 512;
    typedef typename std::pair<uint32_t, value_t> key_value_pair_t;
    typedef typename std::array<key_value_pair_t, cache_size>::iterator array_iterator_t;
private:
    std::array<key_value_pair_t, cache_size> items_array;
    std::map<uint32_t, array_iterator_t> items_map;
    std::array<key_value_pair_t, cache_size> direct_cache;
    unsigned int end;
    unsigned int numel;
    size_t hits;
    size_t misses;
public:
    SimpleCache() : end(0), numel(0) {}
    void put (const uint32_t& key, const value_t& value)
    {
        auto it = items_map.find(key);
        if (it == items_map.end())
        {
            if (numel != cache_size)
                numel++;
            else 
                items_map.erase((items_array.begin() + end)->first);

            *(items_array.begin() + end) = std::make_pair(key, value);
            items_map.insert(std::make_pair(key, items_array.begin() + end));
            end = (end + 1) % cache_size;
        }
    }
    
    value_t* get (const uint32_t& key)
    {
        uint32_t short_key = key & (cache_size-1);
        array_iterator_t tmp_pair = &direct_cache[short_key];
        if (key == tmp_pair->first)
        {
            hits++;
            return &(tmp_pair->second);
        }
        else
        {
            auto it = items_map.find(key);
            if (it != items_map.end())
            {
                hits++;
                *tmp_pair = *(it->second);
                return &(it->second->second);
            }
            else
            {
                misses++;
                return NULL;   
            }
        }
    }

    inline bool is_in_cache (const uint32_t& key)
    {
        return items_map.find(key) != items_map.end();
    }

    inline uint64_t GetMissCount ()
    {
        return misses;
    }

    inline uint64_t GetHitCount ()
    {
        return hits;
    }
};


#endif //SIMPLE_CACHE_H