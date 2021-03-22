package cache.storage;

import java.util.HashMap;
import java.util.Map;

public class HashMapBasedStorage<Key, Value> implements Storage<Key, Value> {

    private Map<Key, Value> storage;
    private final Integer capacity;

    public HashMapBasedStorage(Integer capacity) {
        this.capacity = capacity;
        storage = new HashMap<>();
    }

    @Override
    public void add(Key key, Value value) {
        if(isStorageFull()){
            // storage full
            System.out.println("Storage is full");
            return;
        }
        storage.put(key, value);
    }

    private boolean isStorageFull() {
        return storage.size() == capacity;
    }

    @Override
    public void remove(Key key) {
        if(!storage.containsKey(key)){
            System.out.println("key doesn't exist in cache");
        }
        storage.remove(key);
    }

    @Override
    public Value get(Key key) {
        (if(!storage.containsKey(key))){
            System.out.println("key doesnt exist in cache");
            return null;
        }
        return storage.get(key);
    }
}
