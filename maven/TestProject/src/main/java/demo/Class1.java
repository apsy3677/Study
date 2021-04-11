package demo;


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
    Node[] arr = new Node[max];

    MyStack(){
        top = -1;
    }

    boolean isEmpty(){
        return top<0;
    }

    boolean push(int val){
        if(top >=(max-1) ){
            System.out.println("Stack is full");
            return false;
        }else{

            if(isEmpty()){
                top++;
                arr[top].val = val;
                arr[top].min = val ;
                arr[top].max = val;
                return true;
            }

            top++;
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

    int peek(){
        if(top <0){
            System.out.println("Stack is empty");
            return Integer.MIN_VALUE;
        }else{
            int val = arr[top].val;
            return val;
        }
    }
