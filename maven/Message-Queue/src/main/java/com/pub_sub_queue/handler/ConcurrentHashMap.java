package com.pub_sub_queue.handler;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class ConcurrentHashMap <KEY, VALUE>{
    // 0  1 2 ... 19
    // 0 1  2 3 ... 18 19


    private final int concurrencyLevel;
    private final int capacity;
    private  int load;
    private ArrayList<LinkedList > buckets;

    public ConcurrentHashMap(final int capacity, final int concurrencyLevel) {
        this.concurrencyLevel = concurrencyLevel;
        this.capacity = capacity;
    }

    public ConcurrentHashMap(){
        this.concurrencyLevel = 16;
        this.capacity = 16;
    }

    @Override
    public int hashCode() {
        return super.hashCode();
    }

    @Override
    public boolean equals(Object obj) {
        return super.equals(obj);
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    @Override
    public String toString() {
        return super.toString();
    }

    public VALUE get(KEY k){

        int hashCode = hashCode(k);
        // search for linked

        LinkedList linkedList = buckets[hashCode];

        // traverse linklist

    }

    public void put (KEY k, VALUE val){
        int hashCode = hashCode(k);
        // search for linked
        int segment = hashCode/concurrencyLevel;
        int offset = ;

        while(true){
            if (Locks[segmnetNO].isFree()){
                // writye in bucket
                break;
            }else{
                wait();
            }
        }


    }
}
