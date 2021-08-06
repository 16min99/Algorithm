// 1915 가장 큰 정사각형
package BOJ;
import java.io.*;
import java.util.*;

public class P1915 {

    static BufferedReader br;
    static BufferedWriter bw;
    static StringTokenizer st;

    static int N, M, ans;
    static int[][] map, dp;

    public static void main(String[] args) throws Exception {

        br = new BufferedReader(new InputStreamReader(System.in));
        bw = new BufferedWriter(new OutputStreamWriter(System.out));

        st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());

        map = new int[N+1][M+1];
        dp = new int[N+1][M+1];
        String input;

        for (int i = 1; i <= N; i++) {
            input = br.readLine();
            for (int j = 1; j <= M; j++) {
                dp[i][j] = map[i][j] = input.charAt(j - 1)-'0';
            }
        }       
        
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                if (map[i][j] == 1) {
                    dp[i][j] = check(i, j);
                    ans = ans > dp[i][j]? ans : dp[i][j];
                }
            }
        }
     
        bw.write(String.valueOf(ans*ans));
        
        bw.flush();
        bw.close();
        br.close();
    }

    static int check(int y, int x) {
        // 체크대상 : 1. 좌측 위 대각선 (↖), 2. 좌측 (←),  3. 위(↑)  
    	int check1 =dp[y - 1][x - 1]; 
    	int check2 =dp[y][x - 1]; 
    	int check3 =dp[y - 1][x]; 

    	// 1. 하나라도 0이면 크기 1짜리 정사각형
    	if (check1 == 0 || check2 == 0 || check3 == 0) return 1;
    	
    	// 2. 3개 중에 정사각형이 존재하면 그 최솟값보다 1 큰 정사각형 
    	return Math.min(Math.min(check1, check2), check3) + 1   ;
    }

}