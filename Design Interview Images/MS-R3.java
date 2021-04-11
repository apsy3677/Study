package com.codility;

// you can also use imports, for example:
import java.util.*;

class Range{
    int start,end;
    Range(int st, int en){
        start = st;
        end = en;
    }
}

public class Solution {

    public int findNxt(int[] arr, int el, int index){
        for(int i=index;i<arr.length;i++){
            if(arr[i] == el){
                return i;
            }
        }
        return -1;
    }

    public int findlast(int[] big, int[] small, int index){
        int mx = -1;

        for(int i=0;i<small.length;i++){
            int nxt= findNxt(big, small[i], index);
            if(nxt ==-1){
                return -1;
            }
            mx = Math.max(nxt, mx);
        }
        return mx;
    }

    Range shorestSeq(int[] small, int[] big){
        int bS=-1, bE =-1;
        for(int i=0;i<big.length;i++){
            int end = findlast(big, small, i);
            if(end == -1) break;
            if(bE ==-1 || end-i < bE-bS){
                bE =i;
                bE = end;
            }
        }
        
        return new Range(bS, bE);
    } 

    public static void main(String [] args) {
        // you can write to stdout for debugging purposes, e.g.
        System.out.println("This is a debug message");
    }
}


class Node{
    private Integer val;
    public Node parent, left, right;
    private boolean locked ;

    private int numOfLockedNodes =0;

    //()
    public  boolean isLocked(){
        return locked;
    }
    public boolean lock(){
        if(numOfLockedNodes >0 || locked == true){
            return false;
        }

        for(Node current = parent; current !=null;current = current.parent){
            if(current.isLocked()){
                return false;
            }
        }
        locked = true;

        for(Node curr = parent; curr!= null; curr = curr.parent){
            curr.numOfLockedNodes++;
        }
        return true;
    }

    public void unlock(){
        if(locked){
            locked = false;
            for(Node curr=parent; curr!=null;curr = curr.parent){
                curr.numOfLockedNodes--;
            }
        }
    }
}

