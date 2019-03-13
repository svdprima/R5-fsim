#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <list>
#include <unordered_map>
#include <stdexcept>

template<typename key_t, typename value_t>
class LRUCache
{
public:
	typedef typename std::pair<key_t, value_t> key_value_pair_t;
	typedef typename std::list<key_value_pair_t>::iterator list_iterator_t;

private:
	std::list<key_value_pair_t> _cache_items_list;
	std::unordered_map<key_t, list_iterator_t> _cache_items_map;
	size_t _max_size;
    uint64_t hits;
    uint64_t misses;

public:
    LRUCache(size_t max_size) : _max_size(max_size), hits(0), misses(0) {}

    void put(const key_t& key, const value_t& value)
    {
		auto it = _cache_items_map.find(key);
		_cache_items_list.push_front(key_value_pair_t(key, value));
		if (it != _cache_items_map.end())
		{
			_cache_items_list.erase(it->second);
			_cache_items_map.erase(it);
		}
		_cache_items_map[key] = _cache_items_list.begin();
		
		if (_cache_items_map.size() > _max_size)
		{
			auto last = _cache_items_list.end();
			last--;
			_cache_items_map.erase(last->first);
			_cache_items_list.pop_back();
		}
	}

    bool is_in_cache (const key_t& key)
    {
        return !(_cache_items_map.find(key) == _cache_items_map.end()); 
    }
	
	value_t* get(const key_t& key)
	{
		auto it = _cache_items_map.find(key);
		if (it == _cache_items_map.end())
		{
			misses++;
			return NULL;
		}
		else
		{
			_cache_items_list.splice(_cache_items_list.begin(), _cache_items_list, it->second);
			hits++;
			return &(it->second->second);
		}
	}

    inline uint32_t GetMissCount ()
    {
        return misses;
    }
    inline uint32_t GetHitCount ()
    {
        return hits;
    }
};

#endif
