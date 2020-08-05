import java.io.*;

class Node<T> { //class for node : used to define Stack
    private T item;
    private Node<T> next;

    public T getItem() {
        return this.item;
    }

    public void setItem(T item) {
        this.item = item;
    }

    public Node<T> getNext() {
        return this.next;
    }

    public void setNext(Node<T> next) {
        this.next = next;
    }

    public Node() {
        this.setNext(null);
        this.setItem(null);
    }

    public Node(T item) {
        this.setItem(item);
        this.setNext(null);
    }

    public Node(T item, Node<T> next) {
        this.setItem(item);
        this.setNext(next);
    }

    public void insertNext(T item) {
        Node<T> NextNext = this.getNext();
        Node<T> Next = new Node<>(item, NextNext);
        this.setNext(Next);
    }

    public void removeNext() {
        this.setNext(this.getNext().getNext());
    }
}

class Stack<T> { //class for stack : used for both operator and numbers -> define as generics
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
}

class Operator { // class for operator : save operation and its priority, association
    private char operator;
    private int priority; //priority for operations : (0 < +;-1 < *;/;%2 < ~3 < ^4 < )5
    private boolean rightAsso; //unary - and ^ are right asso

    public char getOperator() {
        return this.operator;
    }
    public void setOperator(char c) {
        this.operator = c;
    }
    public int getPriority() {
        return this.priority;
    }
    public void setPriority(int i) {
        this.priority = i;
    }
    public boolean getRightAsso() {
        return this.rightAsso;
    }
    public void setRightAsso(boolean a) {
        this.rightAsso = a;
    }

    public Operator(char c) {
        this.setOperator(c);
        //below is for setting up priority
        if(c == '(')
            this.setPriority(0);
        else if(c == '+' || c == '-')
            this.setPriority(1);
        else if(c == '*' || c == '/' || c == '%')
            this.setPriority(2);
        else if(c == '~')
            this.setPriority(3);
        else if(c == '^')
            this.setPriority(4);
        else if(c == ')')
            this.setPriority(5);

        if(c == '^' || c == '~')
            this.setRightAsso(true);
        else
            this.setRightAsso(false);
    }
}

public class CalculatorTest {
    public static void main(String args[]) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        while (true) {
            try {
                String input = br.readLine();
                if (input.compareTo("q") == 0)
                    break;

                command(input);
            } catch (Exception e) {
                System.out.println("입력이 잘못되었습니다. 오류 : " + e.toString());
            }
        }
    }

    private static void command(String input) {
        int l = input.length();
        int j = 0;
        int operloca = 0;
        int numbercount = 0;

        //1. infix to postfix
        Stack<Operator> operStack = new Stack<>(); //stack for keeping operator
        //Caution: for Operation Stack, NumofItem will only count "actually calculating operators", meaning that unary ~ and (,) will not be counted numofItems
        StringBuilder postfix = new StringBuilder(); //saving postfix expression

        boolean indicate = true; //determine whether input is proper

        while (j < l) {
            if (input.charAt(j) == ' ' || input.charAt(j) =='\t') { // if blank is input
                j++;
            } else if ('0' <= input.charAt(j) && input.charAt(j) <= '9') { // if number is input
                operloca = j; //save this location : for later determination of unary operator and excluding prefix
                postfix.append(input.charAt(j++)); // add operator to expression directly
                if (j == l || (input.charAt(j) < '0' || input.charAt(j) > '9')) {//break for end of the string
                    postfix.append(' ');
                    if (numbercount != operStack.getNumItems()) { // # of number before previous number must be equals to # of operator : as this is an infix expression
                        indicate = false;
                        break;
                    }
                    numbercount++;
                    if (j == l) //if end of String
                        break;
                }
            } else if (input.charAt(j) == '+' || input.charAt(j) == '-' || input.charAt(j) == '*' || input.charAt(j) == '/' || input.charAt(j) == '%' || input.charAt(j) == '^' || input.charAt(j) == '(' || input.charAt(j) == ')') { //operator is input
                Operator currentOper = new Operator(input.charAt(j)); //convert to operator
                //case1 : bracelet
                if (input.charAt(j) == '(') {
                    operStack.push(currentOper);
                    operStack.setNumItems(operStack.getNumItems() - 1); //bracelet will not be considered as meaningful number of operator
                } else if (input.charAt(j) == ')') {
                    if (operStack.isempty() == true || ((input.charAt(operloca) > '9' || input.charAt(operloca) < '0') && operloca != 0 && input.charAt(operloca) != ')')) { // no '(' for ')'
                        indicate = false;
                        break;
                    }
                    while (operStack.isempty() == false && operStack.peek().getOperator() != '(') { // run operator in bracelet
                        postfix.append(operStack.pop().getOperator());
                        numbercount--; //result of the calculation -> 2 numbers become 1 number
                        postfix.append(' ');
                        if (operStack.isempty() == true) { // '(' is lesser
                            indicate = false;
                            break;
                        }
                    }
                    if (indicate == true) {
                        operStack.pop(); //remove '('
                        operStack.setNumItems(operStack.getNumItems() + 1); //bracelet will not be considered as meaningful number of operator
                    }
                } else {
                    String temporal = postfix.toString();
                    if (temporal.length() == 0 || ((input.charAt(operloca) > '9' || input.charAt(operloca) < '0') && operloca != 0 && input.charAt(operloca) != ')')) { //not between the numbers
                        if (input.charAt(j) == '-') {
                            currentOper = new Operator('~'); //convert to unary operator
                        } else {
                            indicate = false; //wrong input
                            break;
                        }
                    }
                    if (operStack.isempty() == false) {
                        while (true) {
                            if (currentOper.getRightAsso() == false) { //case of left asso
                                if (operStack.peek().getPriority() < currentOper.getPriority())
                                    break;
                            } else { //case of right asso
                                if (operStack.peek().getPriority() <= currentOper.getPriority())
                                    break;
                            }
                            char op = operStack.pop().getOperator();
                            postfix.append(op); //addto postfix expression
                            if (op == '~') {
                                operStack.setNumItems(operStack.getNumItems() + 1); //unary will not be considered as meaningful number of operator
                            } else {
                                numbercount--; //result of calculation -> 2 numbers to 1 number
                            }
                            postfix.append(' ');
                            if (operStack.isempty() == true)
                                break;
                        }
                    }
                    operStack.push(currentOper);
                    if (currentOper.getOperator() == '~') {
                        operStack.setNumItems(operStack.getNumItems() - 1);
                    }
                }
                operloca = j++;
            } else { //undefined operators as input
                indicate = false;
                break;
            }
        }
        while (operStack.isempty() == false) { // clear remaining operators
            if (operStack.peek().getOperator() != '(') { //no bracelet should be left for proper input
                char op = operStack.pop().getOperator();
                postfix.append(op);
                if (op == '~') {
                    operStack.setNumItems(operStack.getNumItems() + 1);
                }
            } else { //bracelet should be all removed previous step if input is proper
                indicate = false;
                break;
            }
            if (operStack.isempty() == false) // not boundary operator
                postfix.append(' '); // add blank
        }

        String postfixExpression = postfix.toString(); //final

        //2. postfix calculator
        Stack<Long> NumStack = new Stack<>();

        int l2 = postfixExpression.length();
        int k = 0;

        StringBuilder temp = new StringBuilder(); //this string will determine whether current input is continuing number, or number has been end

        while (k < l2) {
            char current = postfixExpression.charAt(k);

            if (current == ' ') {
                String temp2 = temp.toString();
                temp = new StringBuilder();
                if (temp2.equals("not a number") == false) { //one number ends!
                    Long i = Long.parseLong(temp2); //change one number into Long type
                    NumStack.push(i);
                }
                k++;
            } else if ('0' <= current && current <= '9') { //if input is continuing number
                temp.append(current);
                k++;
            } else if (current == '~') { //unary operator deals with only one numbers : exceptional case
                if (NumStack.isempty() == false) { //proper input
                    Long signedNum = NumStack.pop();
                    NumStack.push(-signedNum);
                    k++;
                    temp.append("not a number"); //check that previous input was not a number
                } else { // only unary exists
                    indicate = false;
                    break;
                }
            } else { //operation
                if (NumStack.getNumItems() >= 2) { //proper input has 2 number for 1 operator
                    Long later = NumStack.pop();
                    Long prior = NumStack.pop();

                    if (current == '+') {
                        prior = prior + later;
                    } else if (current == '-') {
                        prior = prior - later;
                    } else if (current == '*') {
                        prior = prior * later;
                    } else if (current == '/') {
                        if (later != 0) {
                            prior = prior / later;
                        } else { //exceptional case
                            indicate = false;
                            break;
                        }
                    } else if (current == '%') {
                        if (later != 0) {
                            prior = prior % later;
                        } else { //exceptioanl case
                            indicate = false;
                            break;
                        }
                    } else if (current == '^') {
                        if (prior == 0 && later < 0) { //exceptional case
                            indicate = false;
                            break;
                        } else {
                            prior = (long) Math.pow((double) prior, (double) later);
                        }
                    }
                    NumStack.push(prior); //save the result
                    k++;
                    temp.append("not a number"); //check previous input
                } else { //too many operator in expression : need implement case of 2++3
                    indicate = false;
                    break;
                }
            }
        }
        Long res = new Long(-10000); //assign any number : would change by the way.
        /*if(NumStack.isempty() == true) {
            indicate = false;
        }
        else {
            res = NumStack.pop();
        }
        if(NumStack.isempty() == false) //if only one number is not left
            indicate = false;
        */
        if (NumStack.getNumItems() != 1)
            indicate = false;
        else
            res = NumStack.pop();

        if (indicate == true) {
            System.out.println(postfixExpression); // print expression
            System.out.println(res);
        } else
            System.out.println("ERROR");
    }
}

