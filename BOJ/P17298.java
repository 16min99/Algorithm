// 풀이 : https://velog.io/@16min99/BOJ-JAVA-17298-%EC%98%A4%ED%81%B0%EC%88%98
import java.io.*;
import java.util.StringTokenizer;

public class P17298 {
    static int N;
    static int[] A;
    static int[] index;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        N = Integer.parseInt(br.readLine());
        A = new int[N + 1];
        index = new int[N + 1];

        StringTokenizer st = new StringTokenizer(br.readLine());
        for (int i = 0; i < N; i++) {
            A[i] = Integer.parseInt(st.nextToken());
        }

        int top = 0;
        index[top] = 0;
        for (int i = 1; i < N; i++) {
            while (true) {
                if (top < 0 || A[index[top]] >= A[i]) break;
                A[index[top--]] = A[i];
            }
            index[++top] = i;
        }

        while (true) {
            if (top < 0) break;
            A[index[top--]] = -1;
        }//스택에 남아있는 친구들 -1로 업데이트

        for (int i = 0; i < N; i++) {
            bw.write(A[i] + " ");
        }
        bw.flush();
        bw.close();
    }
}
