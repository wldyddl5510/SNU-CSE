import java.util.StringTokenizer;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.PrintWriter;

/*
   1. 아래와 같은 명령어를 입력하면 컴파일이 이루어져야 하며, Solution5 라는 이름의 클래스가 생성되어야 채점이 이루어집니다.
       javac Solution5.java -encoding UTF8


   2. 컴파일 후 아래와 같은 명령어를 입력했을 때 여러분의 프로그램이 정상적으로 출력파일 output5.txt 를 생성시켜야 채점이 이루어집니다.
       java Solution5

   - 제출하시는 소스코드의 인코딩이 UTF8 이어야 함에 유의 바랍니다.
   - 수행시간 측정을 위해 다음과 같이 time 명령어를 사용할 수 있습니다.
       time java Solution5
   - 일정 시간 초과시 프로그램을 강제 종료 시키기 위해 다음과 같이 timeout 명령어를 사용할 수 있습니다.
       timeout 0.5 java Solution5   // 0.5초 수행
       timeout 1 java Solution5     // 1초 수행
 */

class Solution5 {
	static final int max_n = 1000;

	static int n, H;
	static int[] h = new int[max_n], d = new int[max_n-1];
	static int Answer;

    static int towerHeight(int[] h, int[] d, int n, int H) {
        int[][] t1 = new int[n][H+1];
        int[][] t2 = new int[n][H+1];

        for(int j = 1 ; j <= H ; j++) {
            if(j >= h[0])
                t1[0][j]++;
            t2[1][j] = t1[0][j];
        }
        for(int i = 1 ; i < n ; i++) {
            for(int j = 1 ; j <= H ; j++) {
                if(j >= h[i] - d[i-1])
                    t1[i][j] += t1[i-1][j-(h[i]-d[i-1])]%1000000;
                if(j >= h[i])
                    t1[i][j] += (t2[i-1][j-h[i]] + 1)%1000000;
                t2[i][j] = (t1[i-1][j] + t2[i-1][j])%1000000;
            }
        }

        return (t1[n-1][H] + t2[n-1][H]) %1000000;
    }

	public static void main(String[] args) throws Exception {
		/*
		   동일 폴더 내의 input5.txt 로부터 데이터를 읽어옵니다.
		   또한 동일 폴더 내의 output5.txt 로 정답을 출력합니다.
		 */
		BufferedReader br = new BufferedReader(new FileReader("input5.txt"));
		StringTokenizer stk;
		PrintWriter pw = new PrintWriter("output5.txt");

		/*
		   10개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
		 */
		for (int test_case = 1; test_case <= 10; test_case++) {
			/*
			   각 테스트 케이스를 표준 입력에서 읽어옵니다.
			   먼저 블록의 개수와 최대 높이를 각각 n, H에 읽어들입니다.
			   그리고 각 블록의 높이를 h[0], h[1], ... , h[n-1]에 읽어들입니다.
			   다음 각 블록에 파인 구멍의 깊이를 d[0], d[1], ... , d[n-2]에 읽어들입니다.
			 */
			stk = new StringTokenizer(br.readLine());
			n = Integer.parseInt(stk.nextToken()); H = Integer.parseInt(stk.nextToken());
			stk = new StringTokenizer(br.readLine());
			for (int i = 0; i < n; i++) {
				h[i] = Integer.parseInt(stk.nextToken());
			}
			stk = new StringTokenizer(br.readLine());
			for (int i = 0; i < n-1; i++) {
				d[i] = Integer.parseInt(stk.nextToken());
			}


			/////////////////////////////////////////////////////////////////////////////////////////////
			/*
			   이 부분에서 여러분의 알고리즘이 수행됩니다.
			   문제의 답을 계산하여 그 값을 Answer에 저장하는 것을 가정하였습니다.
			 */
			/////////////////////////////////////////////////////////////////////////////////////////////
			Answer = towerHeight(h, d, n, H);


			// output5.txt로 답안을 출력합니다.
			pw.println("#" + test_case + " " + Answer);
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
 * Time Complexity Analysis & Memory Analysis
 * initial 값들을 세팅하는 첫 번째 for loop은 Theha(H)의 시간을 소요한다.
 * 이후 실질적인 코드 동작은 2개의 for loop의 중첩에서 이루어지는데, 각 for loop는 각각 n번, H번씩 loop를 돈다.
 * 해당 loop 안에서는 행렬 특정한 원소에 접근 및 덧셈과 나머지 연산만 진행하기에 Theta(1)의 시간이 든다.
 * 따라서 Theta(1)의 작업을 nH번 반복하므로 time complexity는 Theta(nH)가 된다.
 *
 * 아울러 공간의 경우는 max n인 1000, max (H + 1) 인 10001을 곱한 int형 10001000크기의 행렬을 2개 만들게 된다.
 * 이에 추가적으로 선언되는 변수의 개수는 한정적이다.
 * 반면, 128MB는 128 * 1024 * 1024 = 134217728 Byte이고, int 1개는 4 Byte이므로,
 * 128MB에는 33554432개의 int형을 담을 수 있다.
 * 따라서 1001000 * 2개의 행렬을 선언하더라도 메모리의 여유가 있다.
 */

