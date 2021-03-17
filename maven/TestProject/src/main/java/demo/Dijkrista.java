package demo;

import lombok.Getter;

import java.util.*;

class Edge{
    int source, dest, weight;

    public Edge(int source, int dest, int weight) {
        this.source = source;
        this.dest = dest;
        this.weight = weight;
    }
}

@Getter
class Node{
    int vertex, weight;

    public Node(int vertex, int weight) {
        this.vertex = vertex;
        this.weight = weight;
    }
}
class Graph{
    List<List<Edge>> adjList = null;

    public Graph(List<List<Edge>> adjList) {
        this.adjList = adjList;
    }

    public Graph(List<Edge> edges, int n) {
        this.adjList = new ArrayList<>();
        for(int i=0;i<n;i++){
            adjList.add(new ArrayList<>());
        }
        for(Edge edge: edges){
            adjList.get(edge.source).add(edge);
        }
    }
}

class MyComparator implements Comparator<Node>{
    @Override
    public int compare(Node n1, Node n2){
        return n1.weight - n2.weight;
    }
}

public class Dijkrista {
    public static void findShortestPaths(Graph graph, int source, int n){
        PriorityQueue<Node> minHeap;
//        minHeap = new PriorityQueue<>(new Comparator<Node>(){
//            @Override
//            public int compare(Node n1, Node n2){
//                return n1.weight - n2.weight;
//            }
//        });

//        minHeap = new PriorityQueue<Node> (Comparator.comparing(Node::getWeight));

        minHeap = new PriorityQueue<Node> ((n1, n2) ->{
            return n1.weight - n2.weight;
        });

        minHeap.add(new Node(source, 0));

        List<Integer> dist;
        dist = new ArrayList<>(Collections.nCopies(n, Integer.MAX_VALUE));
        dist.set(source, 0);

        Boolean [] done = new Boolean[n];
        done[source] = true;
        int [] prev = new int[n];
        prev[source] = -1;

        while(!minHeap.isEmpty()){
            Node node = minHeap.poll(); // gets and remove from PQ
            int u = node.getVertex();

            // for each neighboour
            for(Edge edge: graph.adjList.get(u)){
                int v = edge.dest;
                int weight = edge.weight;

                if(!done[v] && (dist.get(u) + weight) < dist.get(v) ){
                    dist.set(v, dist.get(u) + weight);
                    prev[v] = u;
                    minHeap.add(new Node(v, dist.get(v)));
                }
            }
            done[u] = true;
        }
        // dist[i] contains distance from source to dest

    }
}
