package BOJ;
import java.util.*;
import java.io.*;

public class P1922 {

    static PriorityQueue<edge> pq ;
    static int N;
    static int M;
    static int[] parent;

    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(br.readLine());
        M = Integer.parseInt(st.nextToken());

        PriorityQueue<edge> pq = new PriorityQueue<edge>();
        parent = new int[N+1];
        for(int i=0;i<=N;i++){
            parent[i]=i;
        }

        for (int i = 1; i <=M ; i++) {
            st = new StringTokenizer(br.readLine());
            int a,b,c;
            a=Integer.parseInt(st.nextToken());
            b=Integer.parseInt(st.nextToken());
            c=Integer.parseInt(st.nextToken());
            edge ip = new edge (a,b,c);
            pq.add(ip);
        }
        int cnt =0;
        int ans = 0;
        while(!pq.isEmpty()){
            edge now = pq.poll();

            if(cnt == N-1) break;//가지 끊기
            if(now.start==now.target) continue ;//같은 컴퓨터 연결 필요 x 문제 예외처리
            if(find(now.start)==find(now.target))continue;
            else {
                Union(now.start, now.target);
                cnt++;
                ans+=now.cost;
            }
        }
        System.out.println(ans);

    }

    static void Union(int a, int b){
        int pa = find(a);
        int pb = find(b);
        parent[pa]=pb;
    }
    static int find(int a){
        if(parent[a]==a) return a;
        return parent[a] = find(parent[a]);
    }

    static class edge implements Comparable<edge>{ // cost순서대로 오름차순으로 정리되게 하는 cmp함수 정의 해야함
        int start,target,cost;

        public edge(int start, int target, int cost) {
            this.start = start;
            this.target = target;
            this.cost = cost;
        }

        @Override
        public int compareTo(edge o) {
            return this.cost-o.cost;//내림차순 비교연산자
        }
    }

}