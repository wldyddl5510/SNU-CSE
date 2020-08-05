import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class BigInteger
{
    public static final String QUIT_COMMAND = "quit";
    public static final String MSG_INVALID_INPUT = "占쌉뤄옙占쏙옙 占쌩몌옙占실억옙占쏙옙占싹댐옙.";

    // implement this
    private int[] num;
    private char sign;

    public int getNum(int i) {
        return this.num[i];
    }

    public char getSign() {
        return this.sign;
    }

    public void setNum(int i, int change) {
        this.num[i] = change;
    }

    public void setSign(char sign) {
        this.sign = sign;
    }

    public int length() {
        return this.num.length;
    }

    public void printBig(){
        for(int i = 0 ; i < this.length() ; i++) {
            System.out.printf("%d ", this.num[i]);
        }
    }
    public static final Pattern EXPRESSION_PATTERN = Pattern.compile("");

    public BigInteger(int i) {
        int[] result = new int[200];
        int j = 199;
        int numb;

        if(i < 0) { //if negative
            this.setSign('-');
            numb = -i;
        }
        else { //if 0
            this.setSign('+');
            numb = i;
        }

        while(true) {
            if(numb < 10 && numb >= 0) { // only 1 bit
                result[j] = numb;
                break;
            }
            else { //more than 1 bit
                result[j] = numb % 10;
                numb = numb / 10;
                j--;
            }
        }

        int[] last = new int[199 - j + 1];

        for(int k = 0 ; k < 199 - j + 1 ; k++) { //move result to original
            last[k] = result[k + j];
            //this.setNum(k, result[k + j]);
        }
        this.num = last;
    }

    public BigInteger(int[] num1) {
        int x = num1[0];

        this.num = num1;

        if(x < 0) {
            this.setSign('-');
            this.setNum(0, -x);
        }
        else {
            this.setSign('+');
            this.setNum(0, x);
        }
    }

    public BigInteger(String s) {
        int l = s.length();
        this.setSign(s.charAt(0)); //assumption : input is clean. i.e. without NA

        for(int j = 1 ; j < l ; j++) {
            this.setNum(j-1, (Character.getNumericValue(s.charAt(j))));
        }
    }

    public int absLarge(BigInteger big) {
        int l_1 = this.length();
        int l_2 = big.length();

        if(l_1 > l_2)
            return 1; //this is large
        else if(l_1 < l_2)
            return -1; //  big is large
        else {
            int i = 0;
            while(i < this.length()) {
                if(this.getNum(i) > big.getNum(i))
                    return 1; //this is large
                else if(this.getNum(i) < big.getNum(i))
                    return -1; // big is large
                else
                    i++;
            }
            return 0; // same
        }
    }

    public int LongLength(BigInteger big) {
        int l_1 = this.length();
        int l_2 = big.length();

        if(l_1 >= l_2)
            return l_1;
        else
            return l_2;
    }
    public int ShortLength(BigInteger big) {
        int l_1 = this.length();
        int l_2 = big.length();

        if(l_1 >= l_2)
            return l_2;
        else
            return l_1;
    }

    public BigInteger decimal_left() {
        int l = this.length();
        int[] temp = new int[l+1];

        for(int i = 0 ; i < l ; i++) {
            temp[i] = this.getNum(i);
        }
        temp[l] = 0;

        BigInteger deci = new BigInteger(temp);

        return deci;
    }

    public BigInteger plus(BigInteger big) {
        int[] result = new int[this.LongLength(big) + 1];

        for(int a = 0 ; a < result.length ; a++) {
            result[a] = 0;
        }

        int i = this.length() - 1;
        int j = big.length() - 1;
        int k = result.length - 1;
        int h = this.ShortLength(big) - 1;
        int temporal;
        //this.printBig();
        while(h >= 0) {
            temporal = this.getNum(i) + big.getNum(j) + result[k];
            if(temporal >= 10) {
                result[k-1] = temporal / 10;
                temporal = temporal % 10;
            }
            result[k] = temporal;
            i--;j--;k--;h--;
        }
        //System.out.printf("%d %d ", j , k);
        if(i >= 0) {
            while(i >= 0) {
                result[k] = result[k] + this.getNum(i);
                k--;i--;
            }
        }
        else if(j >= 0 ) {
            while(j >= 0) {
                result[k] = result[k] + big.getNum(j);
                k--;j--;
            }
        }
        int l_res; int s;

        if(result[0] == 0) {
            l_res = this.LongLength(big);
            s = 1;
        }
        else {
            l_res = this.LongLength(big) + 1;
            s = 0;
        }
        /*
        for(int g = 0 ; g < result.length ; g++ ){
            System.out.printf("%d ", result[g]);
        }
*/
        int[] last = new int[l_res];

        //BigInteger res = new BigInteger();
        for(int u = 0 ; u < l_res ; u++) {
            last[u] = result[u + s];
        }
        BigInteger res = new BigInteger(last);
        return res;
    }

    public BigInteger minus(BigInteger big) { // always |a| > |b| input
        int l_1 = this.length();
        int l_2 = big.length();

        if(this.absLarge(big) == 0) {
            BigInteger res = new BigInteger(0);
            return res;
        }

        else {
            int[] result = new int[l_1];
            int i = l_1 - 1;
            int j = l_2 - 1;
            int k = i;
            int temporal;

            while(j >= 0) {
                temporal = this.getNum(i) - big.getNum(j);
                if (temporal < 0) {
                    temporal = temporal + 10;
                    this.setNum((i - 1), this.getNum(i - 1) - 1);
                }
                result[k] = temporal;
                i--;
                j--;
                k--;
            }
            while(i >= 0) {
                result[k] = this.getNum(i);
                i--;
                k--;
            }
            while(j >= 0) {
                result[k] = this.getNum(j);
                j--;k--;
            }
            int u = 0;
            while(true) {
                if(result[u] != 0)
                    break;
                u++;
            }
            int l_res = l_1 - u;

            int[] last = new int[l_res];
            for(int s = 0 ; s < l_res ; s++) {
                last[s] = result[s + u];
            }

            BigInteger res = new BigInteger(last);
            return res;
        }
    }

    public BigInteger add(BigInteger big) {
        if(this.getSign() == big.getSign()) { // +(a + b) or -(a + b)
            BigInteger res = this.plus(big);
            if(this.getSign() == '-')
                res.setSign('-');
            return res;
        }
        else { // (a - b) or -(a - b)
            if(this.absLarge(big) == -1) { // A < B
                BigInteger res = big.minus(this);
                if(this.getSign() == '+') // +A + - B
                    res.setSign('-');
                return res;
            }
            else if(this.absLarge(big) == 1){ // A > B
                BigInteger res = this.minus(big);
                if(this.getSign() == '-')
                    res.setSign('-');
                return res;
            }
            else {
                BigInteger res = new BigInteger(0);
                return res;
            }
        }
    }

    public BigInteger subtract(BigInteger big) {
        if (this.getSign() != big.getSign()) { // a - -b or -a - + b
            BigInteger res = this.plus(big);
            if (this.getSign() == '-')
                res.setSign('-');
            return res;
        }
        else { // a - b or -a - - b = -a + b
            if (this.absLarge(big) == -1) { //a < b
                BigInteger res = big.minus(this);
                if(this.getSign() == '+') {
                    res.setSign('-');
                }
                return res;
            }
            else if(this.absLarge(big) == 1) { // a > b
                BigInteger res = this.minus(big);
                if(this.getSign() == '-') {
                    res.setSign('-');
                }
                return res;
            }
            else {
                BigInteger res = new BigInteger(0);
                return res;
            }
        }
    }

    public BigInteger multiply(BigInteger big) {
        BigInteger res = new BigInteger(0);
        if(this.getNum(0) == 0 || big.getNum(0) == 0) {
            return res;
        }
        else {
            int i = big.length() - 1;
            int e = 0; //how many times should be shifted
            while(i >= 0) {
                int[] last = new int[this.length()];
                for(int w = 0 ; w < this.length(); w++) {
                    last[w] = this.getNum(w);
                    //tempt.setNum(w, this.getNum(w));
                }
                BigInteger tempt = new BigInteger(last);
                tempt.setSign(this.getSign());
                int times = big.getNum(i);
                if(times == 0) {
                    tempt = new BigInteger(0);
                }
                else if(times > 1) {
                    for(int j = 1 ; j < times ; j++) {
                        //System.out.printf("%d /" , j);
                        tempt = tempt.plus(this);
                        //tempt.printBig();
                    }
                } //each line
                //tempt.printBig();
                if(e != 0) {
                    for(int r = 0 ; r < e; r++) {
                        tempt = tempt.decimal_left();
                    }
                }
                res = res.plus(tempt); //sum of previous result
                i--; e++;
            }
            if(this.getSign() == big.getSign())
                res.setSign('+');
            else
                res.setSign('-');
            return res;
        }
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        if (this.getSign() == '-')
            sb.append('-');
        for (int i = 0; i < this.length(); i++)
            sb.append(this.getNum(i));
        return sb.toString();
    }
/*
    @Override
    public boolean equals(Object o) {
        if (o instanceof BigInteger) {

        }
        return false;
    }
*/
    static BigInteger evaluate(String input) throws IllegalArgumentException
    {
        int l = input.length();
        int j = 0;
        int k = 0;
        char[] inputP = new char[205]; //string without blank

        while(j < l) { //skip blank until proper input
            if(input.charAt(j) == ' ') { //blank
                j++;
                continue;
            }
            else {
                inputP[k++] = input.charAt(j++);
            }
        }

        int l_inputPure = k;

        char[] inputPure = new char[l_inputPure];

        for(int q = 0 ; q < l_inputPure ; q++) {
            inputPure[q] = inputP[q];
        }

        char[] sign_oper = new char[3];

        int[] num_1 = new int[100]; //first num input
        int[] num_2 = new int[100]; //second num input
        int num1_length = 0;
        int num2_length = 0;

        k = 0;

        if(inputPure[k] == '+' || inputPure[k] == '-') {
            sign_oper[0] = inputPure[k];
            k++;
        }

        else {
            sign_oper[0] = '+';
        }

        while('0' <= inputPure[k] && inputPure[k] <= '9') {
            num_1[num1_length++] = Character.getNumericValue(inputPure[k]);
            k++;
        }

        int[] num_1_real = new int[num1_length];

        for(int f = 0 ; f < num1_length ; f++) {
            num_1_real[f] = num_1[f];
        }

        sign_oper[1] = inputPure[k++];

        if(inputPure[k] == '+' || inputPure[k] == '-') {
            sign_oper[2] = inputPure[k];
            k++;
        }

        else {
            sign_oper[2] = '+';
        }

        //System.out.println(k);

        while('0' <= inputPure[k] && inputPure[k] <= '9') {
            num_2[num2_length] = Character.getNumericValue(inputPure[k]);
            //System.out.println(num_2[num2_length]);
            num2_length++;
            k++;
            if(k == l_inputPure)
                break;
        }
        int[] num_2_real = new int[num2_length];

        for(int f = 0 ; f < num2_length ; f++) {
            num_2_real[f] = num_2[f];

        }

        if(sign_oper[0] == '-') {
            num_1_real[0] = -num_1_real[0];
        }

        if(sign_oper[2] == '-') {
            num_2_real[0] = -num_2_real[0];
        }

        BigInteger firstNum = new BigInteger(num_1_real);
        BigInteger secondNum = new BigInteger(num_2_real);
        if(sign_oper[1] == '*') {//multiply do not classify cases
            BigInteger res = firstNum.multiply(secondNum);
            return res;
        }

        else if(sign_oper[1] == '+') {
            BigInteger res = firstNum.add(secondNum);
            return res;
        }

        else {
            BigInteger res = firstNum.subtract(secondNum);
            return res;
        }
        // implement here
        // parse input
        // using regex is allowed

        // One possible implementation
        // BigInteger num1 = new BigInteger(arg1);
        // BigInteger num2 = new BigInteger(arg2);
        // BigInteger result = num1.add(num2);
        // return result;
    }

    public static void main(String[] args) throws Exception
    {
        try (InputStreamReader isr = new InputStreamReader(System.in))
        {
            try (BufferedReader reader = new BufferedReader(isr))
            {
                boolean done = false;
                while (!done)
                {
                    String input = reader.readLine();

                    try
                    {
                        done = processInput(input);
                    }
                    catch (IllegalArgumentException e)
                    {
                        System.err.println(MSG_INVALID_INPUT);
                    }
                }
            }
        }
    }

    static boolean processInput(String input) throws IllegalArgumentException
    {
        boolean quit = isQuitCmd(input);

        if (quit)
        {
            return true;
        }
        else
        {
            BigInteger result = evaluate(input);
            System.out.println(result.toString());

            return false;
        }
    }

    static boolean isQuitCmd(String input)
    {
        return input.equalsIgnoreCase(QUIT_COMMAND);
    }
}
