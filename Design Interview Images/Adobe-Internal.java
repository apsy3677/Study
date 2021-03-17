
// LinkedList

craete a linklist
return a LinkedList

class LinkedList{
	
	public Node head;

	class Node {
		int val;
		Node next;

		Node(int v){
			val = v;
			next = null;
		}
	}

	Node reverse(Node head){
		Node prev=null, curr = head, next= null;

		while(curr != null){
			next = curr.next;
			curr.next = prev;
			prev = curr;
			curr = next
		}
		head = prev;
		return head;
	}

	public static void main(String [] args){

		LinkedList linkedList  = new LinkedList();
		linkedList.head = new Node(1);
		linkedList.head.next = new Node(2);
		linkedList.head.next.next = new Node(3);

		linkedList.head.next.next.next = new Node(4);
		linklist.head = reverse(linkedList.head);
		
		1->2->3->4->null
		null<-1 <-2 <-3 4->null
		curr prev next
		1 null null
		2	1	2

		2	2	3
				4




	}
}



Road 0-100,  n = 100,
ranges []
carA 0,10 speed 20km/h
carB 3,15 speed 40km/h
carC 20-40, speed 60kmph

0,3 20km
3 -10 30km
10

color code road, 
avg speed >45kmph color it as blue
avg speed 25-45 color it orange
avg speed < 25 color red

@Getter
@ALLConstructors
class Car{
	private final string id;
	private final Double speed; // in kmph

	private final start, end;

	Car()
	{

	}
}

@Getter
@ALLConstructors
class Road{
	Double length; // in kms
	ArrayList<COLORS> road;
	Road(){
		// intitializing
	}
}

enum COLORS{
	BLUE,
	RED,
	ORANGE
}

Interval{
	int start,end,avgspeed;
}

class ColorRoad{
	Road road;
	List<Car> cars;
	findOverlappingINtervals(){
		
	}
	colorRoad(ArrayList<Intervals> list){

		Collections.sort(list, comprator);
		Interval interval = list.get(0);
		int start =  interval.start;
		int end =  interval.end;
		int avvgSpeed = 0;

		ArrayList<Intervals> ans = new ArrayList<Intervals> ;
		for(int i=1;i<list.szie();i++){
			interval= list.get(i);
			

			if(interval.start> end || intervals.end<start){

			}
			else{
				start = Math.max(start, interval.start)
				end = Math.max(end, interval.end)


			}
			avgspeed = ;
			color = ; // on the basis of 
			ans.add(new IntervalColored(start,end, color))

		}

	}


	public static void main(){

	}
}




