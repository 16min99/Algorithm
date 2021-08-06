package BOJ;
import java.io.*;
import java.util.*;
//줄세우기
public class P2252 {
    static int N;
    static int M;
    static int[] degree;
    static Queue<Integer> q;
    static ArrayList[] edge;
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        degree = new int[N+1];

        edge = new ArrayList[N+1]; // 간선 리스트로 선언
        for(int i=1;i<=N;i++) edge[i]=new ArrayList<Integer>();

        for(int i=1;i<=M;i++){
            st = new StringTokenizer(br.readLine());
            int a,b;
            a=Integer.parseInt(st.nextToken());
            b=Integer.parseInt(st.nextToken());
            edge[a].add(b);
            degree[b]+=1;
        }
        q = new LinkedList<>();
        for(int i=1;i<=N;i++){
            if(degree[i]==0){
                q.add(i);
            }
        }
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringBuilder sb = new StringBuilder();

        while(!q.isEmpty()) {
            int id = q.poll();
            sb.append(id+" ");

            for(int i=0;i<edge[id].size();i++){
                int target = (int) edge[id].get(i);
                degree[target] -= 1;
                if(degree[target]==0)q.add(target);
            }
        }

        bw.write(sb.toString());
		bw.flush();
		bw.close();
        br.close();

    }

}
