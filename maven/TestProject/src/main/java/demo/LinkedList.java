package demo;

public class LinkedList {

    public Node head;

    class Node{
        int val;
        Node next;

        Node (int  val){
            this.val = val;
            this.next = null;
        }

    }

    Node reverse(Node head, int k){
        if(head == null){
            return null;
        }

        Node current = head;
        Node next = null;
        Node prev = null;

        int count = 0;

        while(count <k && (current !=null)){
            next = current.next;
            current.next = prev;
            prev = current;
            current = next;
            count++;
        }

        if(next != null){
            head.next = reverse(next, k);
        }

        return prev;
    }

    void printLL(Node head){

        Node curr = head;

        while(curr!= null){
            System.out.print(curr.val + "->");
            curr= curr.next;
        }
        System.out.println();

    }
    public static void main(String[] args) {
        LinkedList list = new LinkedList();

        list.push(1);
        list.push(2);
        list.push(3);
        list.push(4);
        list.push(5);
        list.push(6);
        list.push(7);

        list.printLL(list.head);

        list.head = list.reverse(list.head, 3);

        list.printLL(list.head);

    }

    private void push(int val) {
        Node node = new Node (val);
        node.next = head;
        head = node;
    }
}
