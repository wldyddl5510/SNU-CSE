import java.util.*;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.PrintWriter;

/*
   1. 아래와 같은 명령어를 입력하면 컴파일이 이루어져야 하며, Solution2 라는 이름의 클래스가 생성되어야 채점이 이루어집니다.
       javac Solution2.java -encoding UTF8

   2. 컴파일 후 아래와 같은 명령어를 입력했을 때 여러분의 프로그램이 정상적으로 출력파일 output2.txt 를 생성시켜야 채점이 이루어집니다.
       java Solution2

   - 제출하시는 소스코드의 인코딩이 UTF8 이어야 함에 유의 바랍니다.
   - 수행시간 측정을 위해 다음과 같이 time 명령어를 사용할 수 있습니다.
       time java Solution2
   - 일정 시간 초과시 프로그램을 강제 종료 시키기 위해 다음과 같이 timeout 명령어를 사용할 수 있습니다.
       timeout 0.5 java Solution2   // 0.5초 수행
       timeout 1 java Solution2     // 1초 수행
 */

class vertex {
    int du;
    List<Integer> edge;
    int index;

    public vertex(int i) {
        du = Integer.MIN_VALUE;
        edge = new ArrayList<>();
        index = i;
    }

    public int getDu() {
        return du;
    }

    public List<Integer> getEdge() {
        return edge;
    }

    public void setDu(int du) {
        this.du = du;
    }

    public int getIndex() {
        return index;
    }
}

class Solution2 {
    static final int MAX_N = 20000;
    static final int MAX_E = 80000;

    static int N, E;
    static int[] U = new int[MAX_E], V = new int[MAX_E], W = new int[MAX_E];
    static int Answer;

    public static void main(String[] args) throws Exception {
		/*
		   동일 폴더 내의 input2.txt 로부터 데이터를 읽어옵니다.
		   또한 동일 폴더 내의 output2.txt 로 정답을 출력합니다.
		 */
        BufferedReader br = new BufferedReader(new FileReader("input2.txt"));
        StringTokenizer stk;
        PrintWriter pw = new PrintWriter("output2.txt");

		/*
		   10개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
		 */
        for (int test_case = 1; test_case <= 10; test_case++) {
			/*
			   각 테스트 케이스를 표준 입력에서 읽어옵니다.
			   먼저 정점의 개수와 간선의 개수를 각각 N, E에 읽어들입니다.
			   그리고 각 i번째 간선의 양 끝점의 번호를 U[i], V[i]에 읽어들이고, i번째 간선의 가중치를 W[i]에 읽어들입니다. (0 ≤ i ≤ E-1, 1 ≤ U[i] ≤ N, 1 ≤ V[i] ≤ N)
			 */
            stk = new StringTokenizer(br.readLine());
            N = Integer.parseInt(stk.nextToken()); E = Integer.parseInt(stk.nextToken());
            stk = new StringTokenizer(br.readLine());
            for (int i = 0; i < E; i++) {
                U[i] = Integer.parseInt(stk.nextToken());
                V[i] = Integer.parseInt(stk.nextToken());
                W[i] = Integer.parseInt(stk.nextToken());
            }


            /////////////////////////////////////////////////////////////////////////////////////////////
			/*
			   이 부분에서 여러분의 알고리즘이 수행됩니다.
			   문제의 답을 계산하여 그 값을 Answer에 저장하는 것을 가정하였습니다.
			 */
            vertex[] ver = new vertex[N];
            boolean[] visited = new boolean[N];
            for(int i = 0 ; i < N ; i++) {
                ver[i] = new vertex(i);
                visited[i] = false;
            }
            for(int j = 0 ; j < E ; j++) {
                ver[U[j] - 1].getEdge().add(j);
                ver[V[j] - 1].getEdge().add(j);
            }
            ver[0].setDu(0);
            visited[0] = true;

            PriorityQueue<vertex> heap = new PriorityQueue<>(N,(x, y) -> -Integer.compare(x.getDu(), y.getDu()));

            heap.addAll(Arrays.asList(ver));

            vertex u;
            while(!heap.isEmpty()) {
                u = heap.poll();
                visited[u.getIndex()] = true;
                List<Integer> Lu = u.getEdge();
                for(int i = 0 ; i < Lu.size() ; i++) {
                    int k = Lu.get(i);
                    vertex v = ver[V[k] - 1];
                    vertex w = ver[U[k] - 1];
                    if(!visited[v.getIndex()] && (W[k] >= v.getDu())) {
                        heap.remove(v);
                        v.setDu(W[k]);
                        heap.add(v);
                    }
                    if(!visited[w.getIndex()] && (W[k] >= w.getDu())) {
                        heap.remove(w);
                        w.setDu(W[k]);
                        heap.add(w);
                    }
                }
            }
            /////////////////////////////////////////////////////////////////////////////////////////////
            Answer = 0;
            for(int i = 0 ; i < N ; i ++) {
                Answer += ver[i].getDu();
            }

            // output2.txt로 답안을 출력합니다.
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
 * Time complexity
 * Initialize ver, visited, d -> O(V)
 * fill ver by edge -> O(E)
 * Building heap = O(V)
 * polling = while loop -> V times : for each loop, polling from heap is LogV -> polling takes VlogV for all. = O(VlogV)
 * relaxation = while V times, and for each vertex, all edge is used. Therefore E times of some operation
 * for each relaxation, it is equivalent to remove and then insert one element in heap = O(logV)
 * Therefore, relaxation = O(ElogV)
 *
 * Total = O(ElogV)
 */


