import java.io.*;
import java.util.Hashtable;
import java.util.PriorityQueue;

public class Subway {
    public static void main(String args[]) {
        String Fileinput = args[0];
        StationHashTable2<String, StationVertexHead> saving = new StationHashTable2<>();
        Hashtable<String, LinkedList<StationVertex>> namesaving = new Hashtable<>();
        readfile(Fileinput, saving, namesaving); //read file and make Graph

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        while (true) {
            try {
                String input = br.readLine();
                if (input.compareTo("QUIT") == 0)
                    break;

                command(input, saving, namesaving); // read command and work
            }
            catch (Exception e) {
                System.out.println("입력이 잘못되었습니다. 오류 : " + e.toString());
            }
        }
    }

    private static void readfile(String FileInput, StationHashTable2<String, StationVertexHead> saving, Hashtable<String, LinkedList<StationVertex>> namesaving) {
        File file = new File(FileInput);
        try {
            BufferedReader b = new BufferedReader((new FileReader(file)));
            int index = 0;
            while (true) { //read pt1
                String input1 = b.readLine();
                if (input1.compareTo("") == 0)
                    break;
                StationVertexHead newvertex = new StationVertexHead();
                String[] splitinput1 = input1.split(" ");
                newvertex.setAll(splitinput1); // make vertex
                newvertex.setIndex(index);
                saving.put(newvertex.getStationnumber(), newvertex); //save to hash table
                saving.getIndexarr()[index++] = newvertex;
                if(namesaving.isEmpty() || namesaving.get(splitinput1[1]) == null )
                    namesaving.put(splitinput1[1], new LinkedList<>());
                namesaving.get(splitinput1[1]).add(newvertex); // add to same name list
            }
            while (true) { //read pt2
                String input2 = b.readLine();
                if (input2 == null)
                    break;

                String[] splitinput2 = input2.split(" ");
                StationVertexElement end = new StationVertexElement(saving.get(splitinput2[1]), Integer.parseInt(splitinput2[2])); //adjacency vertex
                saving.get(splitinput2[0]).getList().add(end);

                if (namesaving.get(saving.get(splitinput2[0]).getStationname()) != null && namesaving.get(saving.get(splitinput2[0]).getStationname()).size() != 1) { //exists same name element -> transfer
                    Node<StationVertex> curr = namesaving.get(saving.get(splitinput2[0]).getStationname()).getHead();
                    while (curr.getNext() != null) {
                        saving.get(splitinput2[0]).getList().add(new StationVertexElement(curr.getNext().getItem(), 5)); //time spend for transfer = 5
                        curr = curr.getNext();
                    }
                }
            }
        }
        catch (Exception e) {
            System.out.println("입력이 잘못되었습니다. 오류 : " + e.toString());
        }
    }

    private static void command (String input, StationHashTable2<String, StationVertexHead> vertexdata, Hashtable<String, LinkedList<StationVertex>> namedata){ // do action
        String[] splitinput = input.split(" ");
        String start = splitinput[0];
        String end = splitinput[1];
        StationVertexHead startnode = vertexdata.get(namedata.get(start).getHead().getNext().getItem().getStationnumber());//use only name
        StationVertexHead endnode = vertexdata.get(namedata.get(end).getHead().getNext().getItem().getStationnumber());//use only name
        Path<StationVertexHead> p;
        if (input.charAt(input.length() - 1) != '!')  //minimum weight
            p = vertexdata.shortest(namedata, startnode, endnode); //actual action
        else //minimum transfer
            p = vertexdata.shortesttransfer(namedata, startnode, endnode); //actual action
        p.printpath(); //result
    }
}

class StationVertex {
    private String stationname;
    private String stationnumber;
    private String linenumber;

    public void setStationname(String s) {
        this.stationname = s;
    }
    public String getStationname() {
        return this.stationname;
    }

    public void setStationnumber(String s) {
        this.stationnumber = s;
    }
    public String getStationnumber() {
        return this.stationnumber;
    }

    public void setLinenumber(String s) {
        this.linenumber = s;
    }
    public String getLinenumber(){
        return this.linenumber;
    }

    public void setAll(String[] s) {
        this.stationnumber = s[0];
        this.stationname = s[1];
        this.linenumber = s[2];
    }
}

class StationVertexHead extends StationVertex {
    private LinkedList<StationVertexElement> list; //adjacency list
    private int index; //location for dijkstra algorithm

    public StationVertexHead() {
        this.setStationnumber(null);
        this.setStationname(null);
        this.setLinenumber(null);
        this.list = new LinkedList<>();
        this.index = -1;
    }

    public LinkedList getList() {
        return this.list;
    }

    public void setIndex(int index) {
        this.index = index;
    }

    public int getIndex() {
        return index;
    }
}

class StationVertexElement extends StationVertex {
    private int time; //weight from the head

    public int getTime() {
        return this.time;
    }

    public StationVertexElement(StationVertex v, int t) {
        this.setStationnumber(v.getStationnumber());
        this.setStationname(v.getStationname());
        this.setLinenumber(v.getLinenumber());
        this.time = t;
    }
}

class Node<T extends StationVertex> {
    private T item;
    private Node<T> next;

    public Node(T obj) {
        this.item = obj;
        this.next = null;
    }

    public Node(T obj, Node<T> next) {
        this.item = obj;
        this.next = next;
    }

    public final T getItem() {
        return item;
    }

    public final void setNext(Node<T> next) {
        this.next = next;
    }

    public Node<T> getNext() {
        return this.next;
    }

    public final void insertNext(T obj) {
        Node<T> NextNext = this.next;
        Node<T> Next = new Node<>(obj, NextNext);
        this.next = Next;
    }

    public Node copy() {
        if (next == null)
            return new Node(item, null);
        else
            return new Node(item, next.copy());
    }
}

class LinkedList<T extends StationVertex> { //linked list of coord
    private Node<T> head;
    private int numItems;

    public LinkedList() {
        head = new Node(null);
        numItems = 0;
    }

    public boolean isEmpty() {
        return head.getNext() == null;
    }

    public int size() {
        return numItems;
    }

    public Node<T> getHead() {
        return head;
    }

    public void add(T item) {
        Node<T> last = head;
        while (last.getNext() != null) {
            last = last.getNext();
        }
        last.insertNext(item);
        numItems++;
    }

    public LinkedList copy(LinkedList l) {
        LinkedList clone = new LinkedList();
        clone.head = l.head.copy();
        clone.numItems = l.numItems;
        return clone;
    }
}

class Path<T extends StationVertex> {
    int totaltime; //for final count
    Stack<T> pathstack; //final path

    public Path(Stack<T> s , int time) {
        this.pathstack = s;
        this.totaltime = time;
    }

    public void printpath() {
        this.pathstack.printstack();
        System.out.println(totaltime);
    }
}

class StationHashTable2<K extends String, V extends StationVertexHead> extends Hashtable<K, V> {
    private StationVertexHead[] indexarr; //save head location

    public StationHashTable2() {
        super();
        indexarr = new StationVertexHead[100000]; //big enough
    }

    public StationVertexHead searchbyindex(int i) {
        return indexarr[i];
    }

    public int searchtheindex(StationVertex v) {
        return this.get(v.getStationnumber()).getIndex();
    }

    public StationVertexHead[] getIndexarr() {
        return indexarr;
    }

    public Path<StationVertexHead> shortest(Hashtable<K, LinkedList<StationVertex>> namesaving, StationVertexHead start, StationVertexHead end) {
        int n = this.size();
        int[] dist = new int[n];
        boolean[] visited = new boolean[n];
        int[] prev = new int[n];
        PriorityQueue<pair> p = new PriorityQueue<>(n);
        for(int i = 0 ; i < n ; i++) {
            dist[i] = 2147483647;
            visited[i] = false;
            prev[i] = -1;
        } //initial condition : all vertex are inf dist from start vertex

        dist[start.getIndex()] = 0;
        visited[start.getIndex()] = true; //start vertex to set S
        p.offer(new pair(start.getIndex(),0));

        Node<StationVertexElement> curr = start.getList().getHead();
        int k;
        while(curr.getNext() != null) {
            k = searchtheindex(curr.getNext().getItem());
            if(curr.getNext().getItem().getStationname().compareTo(start.getStationname()) == 0) {
                dist[k] = 0;
                p.offer(new pair(k,0));
            }
            else {
                dist[k] = curr.getNext().getItem().getTime();
                p.offer(new pair(k,dist[k]));
            }
            curr = curr.getNext();
        } //if exists transfer in start node : transfer immediately

        LinkedList<StationVertex> endpossible = namesaving.get(end.getStationname());//possible end stations
        Stack<StationVertexHead> res = new Stack<>();
        LinkedList<StationVertexHead> result = new LinkedList<>();
        int endlocation = -1;
        while(!p.isEmpty()) {

            int min = (int)p.peek().getDistance();
            int minindex = p.peek().getIndex();
            p.poll();
            if(min > dist[minindex])
                continue;
            dist[minindex] = min;

            visited[minindex] = true;
            Node<StationVertex> curr2 = endpossible.getHead(); //one of end list
            boolean ended = false;
            while(curr2.getNext() != null) { //loop end list
                StationVertexHead matchedhead = this.get(curr2.getNext().getItem().getStationnumber());
                if(visited[matchedhead.getIndex()]) {//if arrived one of them
                    ended = true;
                    endlocation = minindex;
                    break;
                }
                curr2 = curr2.getNext();
            }
            if(ended)
                break;

            StationVertexHead relaxationHead = this.searchbyindex(minindex);
            curr = relaxationHead.getList().getHead();
            while(curr.getNext() != null) {
                StationVertexElement e = curr.getNext().getItem();
                k = searchtheindex(e);
                if(!visited[k] && dist[minindex] + e.getTime() < dist[k]) {
                    dist[k] = dist[minindex] + e.getTime();
                    prev[k] = minindex;
                    p.offer(new pair(k, (long)dist[k]));
                }
                curr = curr.getNext();
            }
        }

        if(endlocation != -1) {
            int temp = endlocation;
            while (true) { //backtracking
                StationVertexHead v = this.searchbyindex(temp);
                res.push(v);
                if(prev[temp] == -1) { //break condition
                    if(res.peek().getStationname().compareTo(start.getStationname()) != 0)
                        res.push(start);
                    break;
                }
                temp = prev[temp]; //backtracking
            }
        }
        else {
            return null;
        }
        return (new Path(res, dist[endlocation]));
    }

    public Path<StationVertexHead> shortesttransfer(Hashtable<K, LinkedList<StationVertex>> namesaving, StationVertexHead start, StationVertexHead end) {
        int n = this.size();
        long[] dist = new long[n];
        boolean[] visited = new boolean[n];
        int[] prev = new int[n];
        PriorityQueue<pair> p = new PriorityQueue<>(n);
        for(int i = 0 ; i < n ; i++) {
            dist[i] = 922337203685L;
            visited[i] = false;
            prev[i] = -1;
        }
        dist[start.getIndex()] = 0;
        visited[start.getIndex()] = true;
        p.offer(new pair(start.getIndex(),0));

        Node<StationVertexElement> curr = start.getList().getHead();
        int k;
        while(curr.getNext() != null) {
            k = searchtheindex(curr.getNext().getItem());
            if(curr.getNext().getItem().getStationname().compareTo(start.getStationname()) == 0) {
                dist[k] = 0;
                p.offer(new pair(k, 0));
            }
            else {
                dist[k] = curr.getNext().getItem().getTime();
                p.offer(new pair(k, dist[k]));
            }
            curr = curr.getNext();
        }

        LinkedList<StationVertex> endpossible = namesaving.get(end.getStationname());//possible end stations
        Stack<StationVertexHead> res = new Stack();
        LinkedList<StationVertexHead> result = new LinkedList<>();
        int endlocation = -1;
        while(!p.isEmpty()) {
            long min = p.peek().getDistance();
            int minindex = p.peek().getIndex();
            p.poll();
            if(min > dist[minindex])
                continue;
            dist[minindex] = min;
            visited[minindex] = true;

            Node<StationVertex> curr2 = endpossible.getHead();
            boolean ended = false;
            while(curr2.getNext() != null) {
                StationVertexHead matchedhead = this.get(curr2.getNext().getItem().getStationnumber());
                if(visited[matchedhead.getIndex()]) {
                    ended = true;
                    endlocation = minindex;
                    break;
                }
                curr2 = curr2.getNext();
            }
            if(ended)
                break;

            StationVertexHead relaxationHead = this.searchbyindex(minindex);
            curr = relaxationHead.getList().getHead();
            while(curr.getNext() != null) {
                StationVertexElement e = curr.getNext().getItem();
                k = searchtheindex(e);
                if(e.getStationname().compareTo(relaxationHead.getStationname()) != 0) {//not transfer station -> same logic
                    if (!visited[k] && dist[minindex] + (long)e.getTime() < dist[k]) {
                        dist[k] = dist[minindex] + (long)e.getTime();
                        prev[k] = minindex;
                        p.offer(new pair(k, dist[k]));
                    }
                }
                else {
                    if (!visited[k] && dist[minindex] + (long)e.getTime() + 2147483647L < dist[k]) { //transfer station : give excess time for transfer -> min transfer
                        dist[k] = dist[minindex] + (long)e.getTime() + 2147483647L;
                        prev[k] = minindex;
                        p.offer(new pair(k, dist[k]));
                    }
                }
                curr = curr.getNext();
            }
        }

        if(endlocation != -1) { //successful search
            int temp = endlocation;
            while (true) { //backtracking the route
                StationVertexHead v = this.searchbyindex(temp);
                res.push(v);
                if (prev[temp] == -1) { //break condition
                    if (res.peek().getStationname().compareTo(start.getStationname()) != 0) //if transfer from start
                        res.push(start);
                    break;
                }
                temp = prev[temp];//backtracking the route
            }
        }
        else {
            return null;
        }
        return (new Path<>(res, (int)(dist[endlocation] % 2147483647)));
    }
}

class Stack<T extends StationVertex> { //class for stack : used for both operator and numbers -> define as generics
    private Node<T> top;
    private int numItems;

    public int getNumItems() {
        return this.numItems;
    }

    public void setNumItems(int i) {
        this.numItems = i;
    }

    public boolean isempty() {
        if(this.top == null)
            return true;
        else
            return false;
    }

    public Stack() {
        this.top = null;
        this.setNumItems(0);
    }

    public T pop() {
        T res = top.getItem();
        this.top = top.getNext();
        this.setNumItems(this.getNumItems() - 1);
        return res;
    }

    public void push(T item) {
        this.top = new Node<>(item, top);
        this.setNumItems(this.getNumItems() + 1);
    }

    public T peek() {
        return top.getItem();
    }

    public void printstack() {
        while(!this.isempty()) {
            T curr = this.pop();
            if(!this.isempty() && this.peek().getStationname().compareTo(curr.getStationname()) == 0) {
                this.pop();
                System.out.printf("[%s]", curr.getStationname());
            }
            else {
                System.out.printf("%s", curr.getStationname());
            }
            if(isempty())
                System.out.printf("\n");
            else
                System.out.printf(" ");
        }
    }
}

class pair implements Comparable<pair> { //for priority queue
    private int index;
    private long distance;

    public int getIndex() {
        return index;
    }

    public long getDistance() {
        return distance;
    }


    public pair(int index, long distance) {
        this.index = index;
        this.distance = distance;
    }

    @Override
    public int compareTo(pair p) {
        if(this.distance > p.getDistance())
            return 1;
        else
            return -1;
    }
}