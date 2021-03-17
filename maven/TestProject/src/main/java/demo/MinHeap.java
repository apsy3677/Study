package demo;

import java.util.PriorityQueue;
import java.util.Scanner;

public class MinHeap {
    final PriorityQueue<Integer> pq;
    final int k; // Heap of Size n

    public MinHeap( int k) {
        this.pq = new PriorityQueue<>(k);
        this.k = k;
    }

    public int add(int n){
        // if pq size is <k , then push to pq
        if(pq.size()<k){
            pq.add(n);
        }
        // if curr element is greater then the smallest element in min heap
        //remove the smallest element from heap
        //push current element
        else if(pq.peek() < n){
            pq.poll();
            pq.add(n);
        }
        if(pq.size() == k){
            return pq.peek();
        }else{
            return Integer.MIN_VALUE;
        }
    }
}

class Main{
    public static void main(String[] args) {
        int k =3;
        findKthLargest(k);
    }

    public static void findKthLargest(int k) {
        MinHeap pq = new MinHeap(k);
        Scanner in = new Scanner(System.in);

        while(true){
            try{
                int x = pq.add(in.nextInt());
                if(x!= Integer.MIN_VALUE){
                    System.out.println("Kth Largest Element "+ x);
                }
            }catch (Exception exception){
                break;
            }
        }
    }
}