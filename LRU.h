//Least Recently Used (LRU) cache

class solution {
public:
	LRUCache(int capacity) {
		this->capacity = capacity;
	}
	int get(int key) {
		if(cacheMap.find(key) == cacheMap.end()) return -1;

		//Transfers elements from x into the container, inserting them at position.
		cacheList.splice(cacheList.begin(), cacheList,cacheMap[key]);
		cacheMap[key] = cacheList.begin();
		return cacheMap[key]->value;
	}
	void set(int key, int value) {
		if(cacheMap.find(key) == cacheMap.end()) {
			if(cacheList.size() == capacity)  {
				cacheMap.erase(cacheList.back().key);
				cacheList.pop_back();
			}

			cacheList.push_front(CacheNode(key, value));
			cacheMap[key] = cacheList.begin();
		}
		else {
			cacheMap[key]->value = value;
			cacheList.splice(cacheList.begin(), cacheList,cacheMap[key]);
			cacheMap[key] = cacheList.begin();
		}
	}
private:
	struct CacheNode {
		int key;
		int value;
		CacheNode(int k, int value) : key(k), value(value){}
	}

private:
	std::list<CacheNode> cacheList;
	std::unordered_map<int, std::list<CacheNode>::iterator> cacheMap;
	int capacity;
}
