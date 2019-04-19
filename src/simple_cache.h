#include <map>
#include <array>

template<typename key_t, typename value_t>
class SimpleCache
{
public:
    static constexpr uint8_t cache_size = 32;
    typedef typename std::pair<key_t, value_t> key_value_pair_t;
    typedef typename std::array<key_value_pair_t, cache_size>::iterator array_iterator_t;
private:
    std::array<key_value_pair_t, cache_size> items_array;
    std::map<key_t, array_iterator_t> items_map;
    unsigned int end;
    unsigned int numel;
    size_t hits;
    size_t misses;
public:
    SimpleCache() : end(0), numel(0) {}
    void put (const key_t& key, const value_t& value)
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
    
    value_t* get (const key_t& key)
    {
        auto it = items_map.find(key);
        if (it != items_map.end())
        {
            hits++;
            return &(it->second->second);
        }
        else
        {
            misses++;
            return NULL;   
        }
    }

    inline bool is_in_cache (const key_t& key)
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
