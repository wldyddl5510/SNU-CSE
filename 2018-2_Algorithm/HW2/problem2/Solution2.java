import java.util.StringTokenizer;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.PrintWriter;

/*
   1. 아래와 같은 명령어를 입력하면 컴파일이 이루어져야 하며, Solution4 라는 이름의 클래스가 생성되어야 채점이 이루어집니다.
       javac Solution2.java -encoding UTF8


   2. 컴파일 후 아래와 같은 명령어를 입력했을 때 여러분의 프로그램이 정상적으로 출력파일 output4.txt 를 생성시켜야 채점이 이루어집니다.
       java Solution2

   - 제출하시는 소스코드의 인코딩이 UTF8 이어야 함에 유의 바랍니다.
   - 수행시간 측정을 위해 다음과 같이 time 명령어를 사용할 수 있습니다.
       time java Solution2
   - 일정 시간 초과시 프로그램을 강제 종료 시키기 위해 다음과 같이 timeout 명령어를 사용할 수 있습니다.
       timeout 0.5 java Solution2   // 0.5초 수행
       timeout 1 java Solution2     // 1초 수행
 */

class Solution2 {

	/*
		** 주의사항
		정답의 숫자가 매우 크기 때문에 답안은 반드시 int 대신 long 타입을 사용합니다.
		그렇지 않으면 overflow가 발생해서 0점 처리가 됩니다.
		Answer[0]을 a의 개수, Answer[1]을 b의 개수, Answer[2]를 c의 개수라고 가정했습니다.
	*/
    static int n;                           // 문자열 길이
    static String s;                        // 문자열
	static long[] Answer = new long[3];     // 정답

    public static long[] operation(String s, int n) {
        long[][][] m = new long[n][n][3];
        for(int i = 0 ; i < n ; i ++) {
            char letter = s.charAt(i);
            if(letter == 'a') {
                m[i][i][0] = 1;
                m[i][i][1] = 0;
                m[i][i][2] = 0;
            }
            else {
                m[i][i][0] = 0;
                if(letter == 'b') {
                    m[i][i][1] = 1;
                    m[i][i][2] = 0;
                }
                else {
                    m[i][i][1] = 0;
                    m[i][i][2] = 1;
                }
            }
        }

        for(int i = 0 ; i < n-1 ; i++) { //define operation behavior
            String frac = s.substring(i, i+2);
            //System.out.println(frac);
            if(frac.equals("ac") || frac.equals("bc") || frac.equals("ca")) {
                m[i][i+1][0] = 1;
                m[i][i+1][1] = 0;
                m[i][i+1][2] = 0;
            }
            else {
                m[i][i+1][0] = 0;
                if(frac.equals("aa") || frac.equals("ab") || frac.equals("bb")) {
                    m[i][i+1][1] = 1;
                    m[i][i+1][2] = 0;
                }
                else {
                    m[i][i+1][1] = 0;
                    m[i][i+1][2] = 1;
                }
            }
        }
        long a1, a2, b1, b2, c1, c2, sum0, sum1, sum2;
        int j;
        for(int r = 2 ; r < n ; r++) {
            for(int i = 0 ; i < n - r ; i++) {
                j = i + r;
                sum0 = 0;
                sum1 = 0;
                sum2 = 0;
                for(int k = i ; k < j ; k++) {
                    long[] former = m[i][k];
                    long[] latter = m[k+1][j];
                    a1 = former[0];
                    a2 = latter[0];
                    b1 = former[1];
                    b2 = latter[1];
                    c1 = former[2];
                    c2 = latter[2];
                    sum0 = sum0 + a1*c2 + b1*c2 + c1*a2;
                    sum1 = sum1 + a1*a2 + a1*b2 + b1*b2;
                    sum2 = sum2 + b1*a2 + c1*b2 + c1*c2;
                }
                m[i][j][0] = sum0;
                m[i][j][1] = sum1;
                m[i][j][2] = sum2;
            }
        }
        return m[0][n-1];
    }

	public static void main(String[] args) throws Exception {
		/*
		   동일 폴더 내의 input2.txt 로부터 데이터를 읽어옵니다.
		   또한 동일 폴더 내의 output4.txt 로 정답을 출력합니다.
		 */
		BufferedReader br = new BufferedReader(new FileReader("input2.txt"));
		StringTokenizer stk;
		PrintWriter pw = new PrintWriter("output2.txt");

		/*
		   10개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
		 */
		for (int test_case = 1; test_case <= 10; test_case++) {
			/*
			   각 테스트 케이스를 파일에서 읽어옵니다.
               첫 번째 행에 쓰여진 문자열의 길이를 n에 읽어들입니다.
               그 다음 행에 쓰여진 문자열을 s에 한번에 읽어들입니다.
			 */
			stk = new StringTokenizer(br.readLine());
			n = Integer.parseInt(stk.nextToken());
			s = br.readLine();

			/////////////////////////////////////////////////////////////////////////////////////////////
            long[] res = operation(s, n);
			/////////////////////////////////////////////////////////////////////////////////////////////
			Answer[0] = res[0];  // a 의 갯수
			Answer[1] = res[1];  // b 의 갯수
			Answer[2] = res[2];  // c 의 갯수


			// output4.txt로 답안을 출력합니다.
			pw.println("#" + test_case + " " + Answer[0] + " " + Answer[1] + " " + Answer[2]);
			/*
			   아래 코드를 수행하지 않으면 여러분의 프로그램이 제한 시간 초과로 강제 종료 되었을 때,
			   출력한 내용이 실제로 파일에 기록되지 않을 수 있습니다.
			   따라서 안전을 위해 반드시 flush() 를 수행하시기 바랍니다.
			 */
			pw.flush();
		}

		br.close();
		pw.close();
	}
}
/**
 * Time complexity Analysis
 * 처음에 행렬의 m[i][i]와 m[i][i+1]을 채우는데는 n loop의 for문이 한번씩만 돌아가므로 둘을 합쳐도 T(n)이 된다.
 * 결국 핵심은 그 다음부터 3번 중첩된 for문에서 수행시간이 결정된다.
 * 해당 for loop에서 r은 T(n), i도 T(n)이며, 각 k마다 상수시간이 걸리므로, k의 loop 횟수에 따라 수행시간이 결정된다.
 * k는 i부터 j까지 loop을 돌며, j = i + r 번씩 돌게 되므로 수행시간은 아래 식과 같다.
 * Sum_(r=1~(n-1)) Sum_(i=1~(n-r)) Sum_(k=i~(j = i+r)) Theta(1)
 * 해당 sigma를 전개하여 풀면 Theta(n^3)이 도출된다.
 */
