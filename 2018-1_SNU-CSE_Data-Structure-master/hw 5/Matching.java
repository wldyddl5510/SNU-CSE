import java.io.*;

public class Matching {
    public static void main(String args[]) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        HashTable hashTable = new HashTable(); //global variable
        while (true) {
            try {
                String input = br.readLine();
                if (input.compareTo("QUIT") == 0) {
                    break;
                }
                else if (input.charAt(0) == '<') { // read file
                    try {
                        hashTable = new HashTable();
                        File file = new File(input.substring(2, (input.length())));
                        BufferedReader b = new BufferedReader(new FileReader(file));
                        int cnt = 1; //line cnt
                        while (true) {
                            String input1 = b.readLine(); //reached end of file
                            if (input1 == null) //reached end of file
                                break;
                            for (int i = 0; i <= input1.length() - 6; i++) {
                                String subs = input1.substring(i, (i + 6)); //substring
                                Coord location = new Coord(cnt, i + 1); //location
                                Substring sub = new Substring(subs, location); //as substring
                                hashTable.hashing(sub);
                            }
                            cnt++; //next line
                        } //case of file read
                    }
                    catch (IOException e) {
                        System.out.println("입력이 잘못되었습니다. 오류 : " + e.toString());
                    }
                }
                else if (input.charAt(0) == '@') {
                    int indexnum = Integer.parseInt(input.substring(2, input.length())); //read index num
                    AVLTreeNode res = hashTable.search(indexnum);
                    res.PreorderPrint();
                    System.out.printf("\n");
                }
                else if (input.charAt(0) == '?') {
                    String Searchstring = input.substring(2, input.length()); //parse Pattern
                    int indicator = -1;
                    LinkedList first = hashTable.search(Searchstring.substring(0, 6)); //O(logn)
                    LinkedList actual = new LinkedList().copy(first); //O(n)
                    boolean existempty = false;
                    if (actual.isEmpty() == true) { //not found
                        indicator = -1;
                    }
                    else if (Searchstring.length() == 6) { //complete pattern
                        indicator = 1;
                    }
                    else {
                        int k = Searchstring.length() / 6;
                        for (int i = 2; i <= k ; i++) { //split substring by 6
                            Node comp = actual.first(); //compare location of first substring with later substring
                            String subs = Searchstring.substring(6 * (i - 1), 6 * i); //split substring by 6
                            LinkedList res = hashTable.search(subs);
                            if (res.isEmpty() == true) { //if later pattern not exists
                                indicator = -1; //not found
                                existempty = true;
                                break;
                            }
                            else {
                                while (comp != null) {
                                    Node curr = res.first(); // location of later pattern
                                    int indi = -1;
                                    Coord compitem = comp.getItem();
                                    while (curr != null) { // compare fitst pattern with later pattern
                                        Coord curritem = curr.getItem();
                                        if (compitem.get_i() == curritem.get_i() && (compitem.get_j() + 6 * (i - 1)) == curritem.get_j()) {
                                            indicator = 1;
                                            indi = 1;
                                            break;
                                        } //pattern valid
                                        curr = curr.getNext(); // search list
                                    }
                                    if (indi != 1) //not found
                                        actual.delete(compitem);
                                    comp = comp.getNext();
                                }
                            }
                        }
                        if(Searchstring.length() % 6 != 0 && !actual.isEmpty()) { //residuals remaining : do same with above for last remaining substring
                            String finalsub = Searchstring.substring(Searchstring.length() - 6, Searchstring.length()); //last substring
                            LinkedList resfinal = hashTable.search(finalsub);
                            int residual = Searchstring.length() % 6;
                            Node comp = actual.first();
                            if (resfinal.isEmpty() == true) {
                                indicator = -1; //not found
                                existempty = true;
                                break;
                            }
                            else {
                                while (comp != null) {
                                    Node curr = resfinal.first();
                                    int indi = -1;
                                    Coord compitem = comp.getItem();
                                    while (curr != null) {
                                        Coord curritem = curr.getItem();
                                        if (compitem.get_i() == curritem.get_i() && (compitem.get_j() + 6 * (k - 1) + residual) == curritem.get_j()) {
                                            indicator = 1;
                                            indi = 1;
                                            break;
                                        }
                                        curr = curr.getNext();
                                    }
                                    if (indi != 1)
                                        actual.delete(compitem);
                                    comp = comp.getNext();
                                }
                            }
                        }
                    }
                    if (actual.isEmpty() == false && existempty != true) { //if pattern exists
                        indicator = 1;
                        actual.printall();
                    }
                    if (indicator != 1) //pattern not exists
                        System.out.printf("%c%d, %d%c\n", '(', 0, 0, ')');
                }
            } catch (IOException e) {
                System.out.println("입력이 잘못되었습니다. 오류 : " + e.toString());
            }
        }
    }
}

class Coord { //location of substring
    private int i;
    private int j;

    public int get_i() {
        return this.i;
    }

    public void set_i(int i) {
        this.i = i;
    }

    public int get_j() {
        return this.j;
    }

    public void set_j(int j) {
        this.j = j;
    }

    public Coord(int i, int j) {
        this.set_i(i);
        this.set_j(j);
    }

    public void print_coordi() {
        System.out.printf("%c%d, %d%c", '(', this.get_i(), this.get_j(), ')');
    }
}

class Node { //node for coord
    private Coord item;
    private Node Next;

    public Node copy() {
        if (Next == null) {
            return new Node(item, null);
        } else {
            return new Node(item, Next.copy());
        }
    }

    public void setItem(Coord newitem) {
        this.item = newitem;
    }

    public Coord getItem() {
        return this.item;
    }

    public void setNext(Node newNext) {
        this.Next = newNext;
    }

    public Node getNext() {
        return this.Next;
    }

    public Node(Coord item) {
        this.setItem(item);
        this.setNext(null);
    }

    public Node(Coord item, Node next) {
        this.setItem(item);
        this.setNext(next);
    }

    public void insertNext(Coord item) {
        Node nextnext = this.getNext();
        Node next = new Node(item, nextnext);
        this.setNext(next);
    }

    public void removeNext() {
        this.setNext(this.getNext().getNext());
    }

    public void print_Node() {
        Coord loca = this.getItem();
        loca.print_coordi();
    }
}

class LinkedList { //linked list of coord
    Node head;
    int numItems;

    public LinkedList() {
        head = new Node(null);
    }

    public boolean isEmpty() {
        return head.getNext() == null;
    }

    public int size() {
        return numItems;
    }

    public Node first() {
        return head.getNext();
    }

    public void add(Coord item) {
        Node last = head;
        while (last.getNext() != null) {
            last = last.getNext();
        }
        last.insertNext(item);
        numItems++;
    }

    public void add(Node node) {
        Node last = head;
        while (last.getNext() != null) {
            last = last.getNext();
        }
        last.setNext(node);
        numItems++;
    }

    public void removeAll() {
        head.setNext(null);
    }

    public void delete(Coord c) {
        Node curr = head;
        while (true) {
            if (curr.getNext() == null)
                break;
            if (curr.getNext().getItem() == c) {
                curr.setNext(curr.getNext().getNext());
                this.numItems--;
            } else
                curr = curr.getNext();
        }
    }

    public LinkedList copy(LinkedList l) {
        LinkedList clone = new LinkedList();
        clone.head = l.head.copy();
        clone.numItems = l.numItems;
        return clone;
    }

    public void printall() {
        Node curr = head.getNext();
        while (curr != null) {
            curr.print_Node();
            curr = curr.getNext();
            if (curr != null)
                System.out.printf(" ");
            else
                System.out.printf("\n");
        }
        return;
    }
}

class AVLTreeNode {
    private LinkedList list;
    private String searchKey;
    private AVLTreeNode leftChild;
    private AVLTreeNode rightChild;
    private int height;

    public void setKey(String s) {
        this.searchKey = s;
    }

    public String getKey() {
        return this.searchKey;
    }

    public void setList(LinkedList l) {
        this.list = l;
    }

    public LinkedList getList() {
        return this.list;
    }

    public void setLeftChild(AVLTreeNode leftc) {
        this.leftChild = leftc;
    }

    public AVLTreeNode getLeftChild() {
        return this.leftChild;
    }

    public void setRightChild(AVLTreeNode rightc) {
        this.rightChild = rightc;
    }

    public AVLTreeNode getRightChild() {
        return this.rightChild;
    }

    public int getHeight() {
        return this.height;
    }

    public void setHeight(int h) {
        this.height = h;
    }

    public static int height(AVLTreeNode n) { //for calculating height of null tree
        if (n == null)
            return 0;
        else
            return n.getHeight();
    }

    public AVLTreeNode() {
        this.setLeftChild(null);
        this.setRightChild(null);
        this.setKey(null);
        this.setList(new LinkedList());
        this.setHeight(0);
    }

    public AVLTreeNode Insert(AVLTreeNode root, Substring s) {
        if (root == null || root.getKey() == null) { //new insertion
            root = new AVLTreeNode();
            root.setKey(s.getS());
            root.getList().add(s.getLocation());
            root.setHeight(1);
            return root; //new root
        }
        int indicator = s.getS().compareTo(root.getKey());
        if (indicator == 0) { //already exists
            root.getList().add(s.getLocation()); //just add location
        }
        else if (indicator < 0) {
            AVLTreeNode newLeftChild = Insert(root.getLeftChild(), s); //Insert to left
            root.setLeftChild(newLeftChild);
        }
        else {
            AVLTreeNode newRightChild = Insert(root.getRightChild(), s); //insert to right
            root.setRightChild(newRightChild);
        }
        root.setHeight(Math.max(height(root.getRightChild()), height(root.getLeftChild())) + 1); //adjust height
        AVLTreeNode fixedresult = fixToAVL(root); // fix to avl Tree
        return fixedresult;
    }

    public boolean isAVLTree() {
        if (Math.abs(height(this.getLeftChild()) - height(this.getRightChild())) <= 1)
            return true;
        else
            return false;
    }

    public int getheightdiff(AVLTreeNode root) { // left - right height
        return (height(root.getLeftChild()) - height(root.getRightChild()));
    }

    public AVLTreeNode fixToAVL(AVLTreeNode root) {
        int hd = getheightdiff(root);
        if (hd > 1) { // left larger
            if (getheightdiff(root.getLeftChild()) < 0) { // "<" shape
                root.setLeftChild(leftRotate(root.getLeftChild())); // "/"shape
                root.setHeight(Math.max(height(root.getRightChild()), height(root.getLeftChild())) + 1);
            }
            root = rightRotate(root);// [/ to ^]
        } else if (hd < -1) { // right larger
            if (getheightdiff(root.getRightChild()) > 0) { // > shape
                root.setRightChild(rightRotate(root.getRightChild()));// "\ shape"
                root.setHeight(Math.max(height(root.getRightChild()), height(root.getLeftChild())) + 1);
            }
            root = leftRotate(root); // [\ to ^]
        }
        root.height = 1 + Math.max(height(root.getLeftChild()), height(root.getRightChild())); //adjust height
        return root;
    }

    public AVLTreeNode rightRotate(AVLTreeNode root) {
        if (root.getLeftChild() != null) {
            AVLTreeNode leftc = root.getLeftChild();
            AVLTreeNode T2 = leftc.getRightChild();

            int T1h = height(leftc.getLeftChild());
            int T2h = height(leftc.getRightChild());
            int T3h = height(root.getRightChild());

            leftc.setRightChild(root);
            root.setLeftChild(T2);

            //adjust height
            root.setHeight(Math.max(T2h, T3h) + 1);
            leftc.setHeight(Math.max(height(root), T1h) + 1);
            return leftc;
        }
        else //no need to rotate
            return root;
    }

    public AVLTreeNode leftRotate(AVLTreeNode root) {
        if (root.getRightChild() != null) {
            AVLTreeNode rightc = root.getRightChild();
            AVLTreeNode T2 = rightc.getLeftChild();

            int T1h = height(root.getLeftChild());
            int T2h = height(rightc.getLeftChild());
            int T3h = height(rightc.getRightChild());

            rightc.setLeftChild(root);
            root.setRightChild(T2);

            //adjust height
            root.setHeight(Math.max(T1h, T2h) + 1);
            rightc.setHeight(Math.max(height(root), T3h) + 1);
            return rightc;
        }
        else //no need to rotate
            return root;
    }

    public AVLTreeNode Search(AVLTreeNode Node, String s) {
        AVLTreeNode searchfail = new AVLTreeNode();
        if (Node != null && Node.getKey() != null) {
            int indicator = s.compareTo(Node.getKey());
            if (indicator == 0) { //search finished
                return Node;
            } else if (indicator < 0) {
                if (Node.getLeftChild() != null)
                    return Search(Node.getLeftChild(), s);
                else
                    return searchfail;
            } else {
                if (Node.getRightChild() != null)
                    return Search(Node.getRightChild(), s);
                else
                    return searchfail;
            }
        }
        else
            return searchfail;
    }

    public void PreorderPrint() {
        if (this.getKey() != null) {
            System.out.printf("%s", this.getKey());
            if (this.getLeftChild() != null) {
                System.out.printf(" ");
                this.getLeftChild().PreorderPrint();
            }
            if (this.getRightChild() != null) {
                System.out.printf(" ");
                this.getRightChild().PreorderPrint();
            }
        }
        else {
            System.out.printf("EMPTY");
        }
    }
/*
    public void prettyPrint() {
        System.out.print("(");
        if (this.leftChild != null) {
            this.leftChild.prettyPrint();
            System.out.print(", ");
        }
        System.out.print(this.searchKey);
        if (this.rightChild != null) {
            System.out.print(", ");
            this.rightChild.prettyPrint();
        }
        System.out.print(")");
    }*/
}

class HashTable {
    private AVLTreeNode[] arr = new AVLTreeNode[100];

    public HashTable() {
        for (int i = 0; i < 100; i++) {
            arr[i] = new AVLTreeNode();
        }
    }

    public AVLTreeNode get(int i) {
        return arr[i];
    }

    public void hashing(Substring s) {
        AVLTreeNode a = new AVLTreeNode().Insert(arr[s.getKey()], s);
        arr[s.getKey()] = a;
    }

    public LinkedList search(String Pattern) {
        int sum = 0;
        for (int i = 0; i < Pattern.length(); i++) {
            sum = sum + (int) Pattern.charAt(i);
        }
        int key;
        if(sum < 100)
            key = sum;
        else
            key = sum % 100;

        LinkedList result = arr[key].Search(arr[key], Pattern).getList();

        return result;
    }

    public AVLTreeNode search(int index) {
        return arr[index];
    }
}

class Substring { //location, hash key, String value : all-in-one
    private String s;
    private int key;
    private Coord location;

    public Substring(String s, Coord location) {
        this.s = s;
        int sum = 0;
        for (int i = 0; i < s.length(); i++) {
            sum = sum + (int) s.charAt(i);
        }

        if(sum < 100)
            this.key = sum;
        else
            this.key = sum % 100;
        this.location = location;
    }

    public String getS() {
        return this.s;
    }

    public int getKey() {
        return this.key;
    }

    public Coord getLocation() {
        return this.location;
    }
}