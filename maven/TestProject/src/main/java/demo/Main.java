package demo;

public class Main {
    boolean n1B = false;
    boolean n2B = false;
    Node lca = null;
    void checkIfExist(Node root, int n1, int n2){
        if(root == null){
            return;
        }
        if(n1B && n2B){
            return;
        }
        if(root.val == n1){
            n1B = true;
        }else if(root.val == n2){
            n2B = true;
        }
        checkIfExist(root.left, n1,n2);
        checkIfExist(root.right, n1, n2);

    }
    public Node lca(Node root, int n1, int n2){
//        checkIfExist(root, n1, n2)
//        if(!n1B ||  !n2B){
//            return null;
//        }
        Node lca = lcaUtils(root, n1, n2);

        checkIfExist(lca, n1, n2);
        if(n1B && n2B ){
            return lca;
        }else{
            return null;
        }

    }

    private Node lcaUtils(Node root, int n1, int n2) {
        if(root == null){
            return null;
        }
        int val = root.val;

        if(root.val > n1 && root.val >n2){
            lcaUtils(root.left, n1, n2);
        }
        else if(root.val <n1 && root.val<n2){
            lcaUtils(root.right, n1, n2);
        }else{
            return lca = root;
        }
//        lcaUtils(root.left, n1, n2);
//        lcaUtils(root.right, n1, n2);

    }

    public Node kthNodeFromLast(Node head, int k){
//        int len = 0;
//        Node curr = head;
//
//        while(curr!=null){
//            curr = curr.next;
//            len++;
//        }
//        if(len < k){
//            return null;
//        }
//
//        curr = head;
//
//        for(int i=1; i<len - k +1; i++){
//            curr = curr.next;
//        }
//        return curr;

        // Time Complexity : O(len + (len-k+1)) = O(len)

        Node curr = head;
        Node kthNode = head;
        int cnt = 0;
        if(curr ==null){
            return null;
        }
        1 2 3 4 5 k=4

            cnt =4, curr =5



        while(cnt < k){
            if(curr == null){
                return null;
            }
            curr = curr.next;
            cnt++;
        }
//        if(curr == null){
//            kthNode = kthNode.next;
//            return kthNode;
//        }
//        else{
            while(curr!=null){
                curr = curr.next;
                kthNode = kthNode.next;
            }
            return kthNode;
//        }

        // Time Complexity O(len of LL) one traversal only
    }
}
