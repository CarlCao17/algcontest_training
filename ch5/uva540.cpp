#include<cstdio>
#include<queue>
#include<map>
using namespace std;

const int maxn = 1000+1;
typedef int TeamID_T;
typedef int ElemID_T;

int main() {
    int t, kase = 0;

    while (scanf("%d", &t) == 1 && t) {
        printf("Scenario #%d\n", ++kase);

        int num_elem = 0;
        int elem_id = 0;
        map<ElemID_T, TeamID_T> team;
        for (int tid = 0; tid < t; tid++) {
            scanf("%d", &num_elem);
            for (int i = 0; i < num_elem; i++) {
                scanf("%d", &elem_id);
                team[elem_id] = tid;
            }
        }

        char op[10];
        queue<TeamID_T> q;
        queue<ElemID_T> team_q[maxn];
        while (scanf("%s", op) && op[0] != 'S') {
            if (op[0] == 'E') { scanf("%d", &elem_id); int team_id = team[elem_id]; team_q[team_id].push(elem_id); if (team_q[team_id].size() == 1) q.push(team_id);}
            if (op[0] == 'D') { ElemID_T first = team_q[q.front()].front(); team_q[q.front()].pop(); if (team_q[q.front()].size() == 0) q.pop(); printf("%d\n", first); }
        }
        printf("\n");
    }
}