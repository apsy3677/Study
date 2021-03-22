package cache;

import cache.policies.EvictionPolicy;
import cache.storage.Storage;

public class Cache <Key, Value>{
    private final Storage<Key, Value> storage;
    private final EvictionPolicy<Key> evictionPolicy;

    public Cache(Storage<Key, Value> storage, EvictionPolicy<Key> evictionPolicy) {
        this.storage = storage;
        this.evictionPolicy = evictionPolicy;
    }
    public void put(Key key, Value value){

    }

    public Value get (Key key){
        return null;
    }
}
