#include <map>
#include <array>

template<typename key_t, typename value_t>
class SimpleCache
{
private:
    static constexpr uint8_t cache_size = 32;
    std::array<std::pair<key_t, value_t>, cache_size> items_array;
    std::map<key_t, unsigned int> items_map;
    unsigned int end;
    unsigned int numel;
    size_t hits;
    size_t misses;
public:
    SimpleCache() : end(0), numel(0) {}
    void put (const key_t& key, const value_t& value) noexcept
    {
        auto ind = items_map.find(key);
        if (ind == items_map.end())
        {
            if (numel != cache_size)
            {
                items_array[end] = std::make_pair(key, value);
                items_map.insert(std::make_pair(key, end));
                numel++;
                end = (end + 1) % cache_size;
            }
            else 
            {
                items_map.erase(items_array[end].first);
                items_array[end] = std::make_pair(key, value);
                items_map.insert(std::make_pair(key, end));
                end = (end + 1) % cache_size;
            }
        }
        else
        {
            items_array[end].second = value;
        }
    }
    inline bool is_in_cache (const key_t& key) noexcept
    {
        return items_map.find(key) != items_map.end();
    }
    value_t* get (const key_t& key)
    {
        auto ind = items_map.find(key);
        if (ind == items_map.end())
        {
            misses++;
            return NULL;
        }
        else
        {
            hits++;
            return &(items_array[ind->second].second);
        }
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
