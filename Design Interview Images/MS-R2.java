package com.codility;

// you can also use imports, for example:
import java.util.*;

public class Solution {
    
    public static void main(String [] args) {
        // you can write to stdout for debugging purposes, e.g.
        MyStack st = new MyStack();
        st.push(3); System.out.println(st.peek() + " "+ st.peekMax() + " " + st.peekMin());
        st.push(5); System.out.println(st.peek() + " "+ st.peekMax() + " " + st.peekMin());
        st.push(1); System.out.println(st.peek() + " "+ st.peekMax() + " " + st.peekMin());
        st.push(7); System.out.println(st.peek() + " "+ st.peekMax() + " " + st.peekMin());
        st.push(4); System.out.println(st.peek() + " "+ st.peekMax() + " " + st.peekMin());
        System.out.println("Popping..........  ");

        System.out.println(st.pop() + " "+ st.peekMax() + " " + st.peekMin());
        System.out.println(st.pop() + " "+ st.peekMax() + " " + st.peekMin());
        System.out.println(st.pop() + " "+ st.peekMax() + " " + st.peekMin());
        System.out.println(st.pop() + " "+ st.peekMax() + " " + st.peekMin());
        System.out.println(st.pop() + " "+ st.peekMax() + " " + st.peekMin());

        System.out.println("This is a debug message");
    }
}

class Node{
    public int val;
    public int min;
    public int max;

    Node(){
        val = 0;
        min = Integer.MIN_VALUE;
        max = Integer.MAX_VALUE;
    }
}

class MyStack{
    static final int max = 10000;
    int top;
    Node[] arr;

    MyStack(){
        top = -1;
        arr = new Node[max];
    }

    boolean isEmpty(){
        return top<0;
    }

    boolean push(int val){
        if(top >= (max-1) ){
            System.out.println("Stack is full");
            return false;
        }else{
            
            if(top<0){
                top++;
                arr[top] = new Node();
                arr[top].val = val;
                arr[top].min = val ;
                arr[top].max = val;
                return true;
            }

            top++;
            arr[top] = new Node();
            arr[top].val = val;
            arr[top].min = Math.min(arr[top-1].min, val);
            arr[top].max = Math.max(arr[top-1].max, val);
            return true;
        }
    }

    int pop(){
        if(top < 0){
            System.out.println("Stack is empty");
            return Integer.MIN_VALUE;
        }else{
            int val = arr[top].val;
            top--;
            return val;
        }
    }

    int peekMax() {
            if (top < 0) {
                System.out.println("Stack is empty");
                return Integer.MAX_VALUE;
            } else {
                int val = arr[top].max;
                return val;
            }

            
    }

    int peek(){
        if(top <0){
            System.out.println("Stack is empty");
            return Integer.MIN_VALUE;
        }else{
            int val = arr[top].val;
            return val;
        }
    }

    int peekMin () {
        if (top < 0) {
            System.out.println("Stack is empty");
            return Integer.MIN_VALUE;
        } else {
            int val = arr[top].min;
            return val;
        }
    }

}




