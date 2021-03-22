package cache.policies;

public interface EvictionPolicy<Key> {

    Key evictKey();

    void keyAccessed(Key key);
}
