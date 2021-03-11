package demonstartion;

import java.util.Stack;

public class QueueUsingStacks {

    private Stack<Integer> s1 = new Stack<Integer>();
    private Stack<Integer> s2 = new Stack<Integer>();

    void push(int x){
        while(!s1.isEmpty()){
            s2.push(s1.pop());
        }
        s1.push(x);
        while(!s2.isEmpty()){
            s1.push(s2.pop());
        }
    }

    int pop(){
        if(s1.isEmpty()){
            System.out.println("Queue is empty");
            return -1;
        }
        int x = s1.peek();
        s1.pop();
        return x;
    }

    public static void main(String[] args) {

        QueueUsingStacks q = new QueueUsingStacks();

        q.push(1);
        q.push(10);
        q.push(20);

        System.out.println(q.pop());
        System.out.println(q.pop());
        System.out.println(q.pop());        System.out.println(q.pop());
    }
}
