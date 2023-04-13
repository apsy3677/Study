
Q) Design an in-memory key values store

Cache 
TTL
Cache<

API supported

get(key)
set(key,value, TTL)

Value{
String key
String val;
LL start;
LL end;
}

cache{
Typedef pair<string, pair<string, long long>> record;

Private int maxSize;
//Private EvictionPolicy evictionPolicy; 
Private list< record > dq; 
unordered_map<string, list<record>::iterator> lru_map;
Public:
cache(int maxSize){
	this->maxSize = maxSize;
}
Value get(string key){
	if(lru_map.find(key) != lru_map.end()){
 Auto it = lru_map[key];
String val = (it->second).first
Long long int ttl= (it->second).second;

dq.erase(it);
dp.push_front( {key, {val,  min(ttl, LongLong_MAX))}};
// key, value{key, val, start, end}
// currentTime >= end 
lru_map.erase(key);
Lru_map[key] = dq.begin();

Return val;
		}
Return “NotFound”
}
Void set(key, Value  value, long long ttl = LongLong_MAX){
// we will also check if size of cache is full we we evict some record
	if(lru_map.find(key) != lru_map.end()){
 Auto it = lru_map[key];
String val = (it->second).first
Long long int ttl= (it->second).second;
min(ttl, LongLong_MAX)
dq.erase(it);
dp.push_front( {key, {value,  ttl)}};
lru_map.erase(key);
Lru_map[key] = dq.begin();

Return val;
		}
Else{
if(lrU_map.size() >= maxSize()){
Auto it = dq.back();
dq.pop_back();
lru_map.erase(it.first);
	}
dq.push_front({key, {value,  ttl}})
Lru_map[key] = dq.begin();
}
}
}

TTL 
If ttl expiring this 
{start, end} end time our TTL

Solution:
typedef tuple <int,int,int> tiii;
typedef list<tiii>::iterator olink;
typedef list<int>::iterator tlink;

class LRUCacheTTL
{
private:
    list <tiii> order;
    map <time_t, list <int>> buckets;
    unordered_map <int, pair <olink, tlink>> links;
    int capacity;

public:
    LRUCacheTTL (int capacity)
    {
        this->capacity = capacity;
    }
    
    int get_val (int k)
    {
        // lazy evict on ttl.
        evictExpired ();
        
        // not found.
        if (links.count (k) == 0)
            throw "key not found";
        
        // found.
        auto [ol, tl] = links [k];
        auto kvt = *ol;
        
        // change order.
        order.erase (ol);
        order.push_back (kvt);
        
        // create link.
        links [k] = {prev (order.end ()), tl};
        
        // get out.
        return get <1> (kvt);
    }
    
    void put (int k, int v, time_t ttl)
    {
        // lazy evict on ttl.
        evictExpired ();
        
        // bad capacity.
        if (capacity == 0)
            throw "capacity is 0";
        
        // bad ttl.
        if (time (NULL) >= ttl)
            return;
        
        // key already present, update.
        if (links.count (k))
        {
            // links.
            auto [ol, tl] = links [k];
            auto kvt = *ol;
            
            // change order.
            order.erase (ol);
            order.emplace_back (k, v, ttl);
            
            // change time bucket.
            buckets [get<2> (kvt)].erase (tl);
            if (buckets [get<2> (kvt)].empty ())
                buckets.erase (get <2> (kvt));
            buckets [ttl].push_back (k);
            
            // create link.
            links [k] = {prev (order.end ()), prev (buckets [ttl].end ())};
            
            // done.
            return;
        }
        
        // evict if at capacity.
        if (links.size () == capacity)
        {
            // eviction candidate.
            auto [ol, tl] = links [get <0> (*order.begin ())];
            
            // remove from time bucket.
            buckets [get <2> (*ol)].erase (tl);
            if (buckets [get <2> (*ol)].empty ())
                buckets.erase (get<2> (*ol));
        
            // remove order.
            order.erase (ol);
            
            // remove link.
            links.erase (get<0> (*ol));
        }
        
        // insert.
        order.emplace_back (k, v, ttl);
        buckets [ttl].push_back (k);
        links [k] = {prev (order.end ()), prev (buckets [ttl].end ())};
    }
    
    void evictExpired ()
    {
        auto now = time (NULL);
        auto it = buckets.begin ();
        
        while (it != buckets.end ())
        {
            auto& [ttl, keys] = *it;
                
            if (ttl > now)
                break;
            
            for (auto k : keys)
            {
                auto [ol, tl] = links [k];
                order.erase (ol);
                links.erase (k);
            }
            
            buckets.erase (it++);
        }
    }
    
    int size ()
    {
        evictExpired ();
        return links.size ();
    }
};

int main() 
{
    LRUCacheTTL cache (1);
    
    cache.put (1, 2, time (NULL)+10);
    std::this_thread::sleep_for (chrono::milliseconds (1000));
    cout << cache.size () << endl;
    cache.put (1, 2, time (NULL)+1);
    std::this_thread::sleep_for (chrono::milliseconds (1000));
    cout << cache.size () << endl;
}