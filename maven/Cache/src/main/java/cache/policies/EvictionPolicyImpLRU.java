package cache.policies;

import cache.dll.DoublyLinkedList;
import cache.dll.DoublyLinkedListNode;

import java.util.HashMap;
import java.util.Map;

public class EvictionPolicyImpLRU<Key> implements EvictionPolicy<Key> {

    private DoublyLinkedList<Key> dll;
    private Map<Key, DoublyLinkedListNode<Key>> mapper;

    public EvictionPolicyImpLRU() {
        DoublyLinkedList<Key> dll = new DoublyLinkedList<>();
        Map<Key, DoublyLinkedListNode<Key>> mapper = new HashMap<>();
    }

    @Override
    public Key evictKey() {
        DoublyLinkedListNode<Key> first = dll.getFirstNode();

        if(first == null){
            return null;
        }
        dll.detachNode(first);
        return first.getElement();
    }

    @Override
    public void keyAccessed(Key key) {
        // make accessed key as just used
        if(mapper.containsKey(key)){
            dll.detachNode(mapper.get(key));
            dll.addNodeAtLast(mapper.get(key));
        }else{
            DoublyLinkedListNode<Key> newNode = dll.addElementAtLast(key);
            mapper.put(key, newNode);
        }
    }

}
