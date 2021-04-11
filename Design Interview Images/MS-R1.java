package com.codility;

// you can also use imports, for example:
import java.util.*;

class Node{
    int val;
    Node prev;
    Node next;
    Node()// constructor
}

public class Solution {

    // n , s, a, b
 public static Set<Integer> uniqueStairs(int n, int s, int a, int b){
 // List<Integer> ans = new ArrayList<> ();
 Set<Integer> present = new HashSet<> ();
 
 Queue<Integer> qu = new LinkedList<> ();
 
 if(n<1){
 return present;
 }
 
 if(a >= n && b >=n){
 return present;
 }
 
 int[] moves = {a, -a, b, -b};
 qu.add(s);
 present.add(s);
 
 while(!qu.isEmpty()){
 int st = qu.peek();
 
 qu.remove();
 
 for(int i=0;i<4;i++){
 int nxtState = st + moves[i];
 
 if(nxtState >= s && nxtState <= n && (!present.contains(nxtState))){
 qu.add(nxtState);
 
 present.add(nxtState);
 }
 }
 
 }
 
 return present;
 }
    
    public static int maxGuests(int[] entry, int[] exit){
        int n = entry.length;
        int m = entry.length;

        Arrays.sort(entry);
        Arrays.sort(exit);

        int i =0, j =0;
        int maxGuestPresent = 0;
        int guests =0;
        while(i<n && j<m){
            if(entry[i] <= exit[j]){
                guests++;
                maxGuestPresent = Math.max(maxGuestPresent, guests);
                i++;
            }else{
                guests --;
                j++;
            }
            
        }

        return maxGuestPresent;
    }

    public static void main(String [] args) {
        // you can write to stdout for debugging purposes, e.g.

        //Set<Integer> present = uniqueStairs(10, 2, 5, 7);
        int[] entry = {1, 2, 9, 5, 5};
        int[] exit = {4, 5, 12, 9, 12};



        System.out.println(maxGuests(entry, exit));
    }
}
