#include<cstdio>
#include<cstring>
#include<algorithm>
#define eps 1e-5
#define maxn 110
#define SID_Len 10
#define Name_MAXLEN 20

int n = 0;
struct Student {
    char sid[SID_Len];
    int cid;
    char name[Name_MAXLEN];
    int scores[4];
} students[maxn];

typedef bool (*Predicate)(Student &s);

char subjects[4][20] = {"Chinese", "Mathematics", "English", "Programming"};

bool is_dup(char* sid) {
    for(int i = 1; i <= n; i++)
        if(strncmp(students[i].sid, sid, SID_Len) == 0) return true;
    return false;
}

void add() {
    Student s;
    while(true) {
        printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
        if(scanf("%s", &s.sid) == 0 || (strlen(s.sid) == 1 && s.sid[0] == '0')) return;
        scanf("%d%s", &s.cid, s.name);
        for(int i = 0; i < 4; i++) scanf("%d", &s.scores[i]);
        if(is_dup(s.sid)) { printf("Duplicated SID.\n"); continue; }
        students[++n] = s; // 从 1 开始存储
    }
}

int find_by_name(char *name, int idx[]) {
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(strncmp(students[i].name, name, Name_MAXLEN) == 0) {
            idx[cnt++] = i;
        }
    }
    return cnt;
}

int find_by_cid(int cid, int idx[]) {
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(cid == 0 || students[i].cid == cid) {
            idx[cnt++] = i;
        }
    }
    return cnt;
}

int find_by_sid(char* sid, int idx[]) {
    for(int i = 1; i <= n; i++) {
        if(strncmp(students[i].sid, sid, SID_Len) == 0) {
            idx[0] = i; return 1;
        }
    }
    return 0;
}

void del(int idx[], int cnt) {
    int next = 0;
    for(int i = idx[next++], k = i+1; k <= n; k++) {
        if(next < cnt && k == idx[next]) {
            next++;
        } else {
            students[i++] = students[k];
        }
    }
    n -= cnt;
}

void query_and_take_action(int action(int idx[], int cnt)) {
    char name_or_sid[20];
    int idx[maxn];
    int cnt;

    while(true) {
        printf("Please enter SID or name. Enter 0 to finish.\n");
        if(scanf("%s", name_or_sid) == 0 || (strlen(name_or_sid) == 1 && name_or_sid[0] == '0')) {
            return;
        }
        if(name_or_sid[0] >= 'A' && name_or_sid[0] <= 'Z') {
            cnt = find_by_name(name_or_sid, idx);
        } else if(name_or_sid[0] >= '0' && name_or_sid[0] <= '9') {
            cnt = find_by_sid(name_or_sid, idx);
        }
        action(idx, cnt);
    }
}

int remove_action(int to_remove[], int cnt) {
    if(cnt > 0) del(to_remove, cnt);
    printf("%d student(s) removed.\n", cnt);
    return 0;
}

int cal_total(int i) {
    return students[i].scores[0] + students[i].scores[1] + students[i].scores[2] + students[i].scores[3];
}

struct pair {
    int total;
    int idx;

    pair() {};
    pair(int total, int idx) : total(total), idx(idx) {};

    bool operator <(const pair &a) const {
        return total >= a.total;
    }
};

int rank[maxn];
pair pairs[maxn];

void sort_by_total_scores() {
    for(int i = 1; i <= n; i++) pairs[i] = pair(cal_total(i), i);
    std::sort(pairs+1, pairs+n+1);

    rank[pairs[1].idx] = 1;
    for(int i = 2; i <= n; i++) {
        if(pairs[i].total == pairs[i-1].total) rank[pairs[i].idx] = rank[pairs[i-1].idx];
        else rank[pairs[i].idx] = i;
    }
}

int query_action(int idx[], int cnt) {
    if(cnt == 0) return 0;
    sort_by_total_scores();

    for(int i = 0; i < cnt; i++) {
        int k = idx[i];
        Student &s = students[k];
        int total = cal_total(k);
        double avg = (double) total/4.0;
        printf("%d %s %d %s %d %d %d %d %d %.2lf\n", rank[k], s.sid, s.cid, s.name, s.scores[0], s.scores[1], s.scores[2], s.scores[3], total, avg+eps);
    }
    return 0;
}

void ranklist() {
    printf("Showing the ranklist hurts students' self-esteem. Don't do that.\n");
}

int count(int idx[], int cnt, bool pred(Student &s)) {
    int res = 0;
    for(int i = 0; i < cnt; i++) {
        Student &s = students[idx[i]];
        if(pred(s)) res++;
    }
    return res;
}

#define PASS_SCORE 60

int get_num_pass_subject(Student &s) {
    int res = 0;
    for(int i = 0; i < 4; i++) {
        if(s.scores[i] >= PASS_SCORE) res++;
    }
    return res;
}

bool pass_chinese(Student &s) {
    return s.scores[0] >= PASS_SCORE;
}
bool pass_math(Student &s) {
    return s.scores[1] >= PASS_SCORE;
}
bool pass_english(Student &s) {
    return s.scores[2] >= PASS_SCORE;
}
bool pass_programming(Student &s) {
    return s.scores[3] >= PASS_SCORE;
}

Predicate get_pass_the_subject_func(int i) {
    switch(i) {
        case 0: return pass_chinese;
        case 1: return pass_math;
        case 2: return pass_english;
        case 3: return pass_programming;
        default: return nullptr;
    }
}

bool pass_all(Student &s) {
    return get_num_pass_subject(s) == 4;
}

bool pass_three_or_more(Student &s) {
    return get_num_pass_subject(s) >= 3;
}

bool pass_two_or_more(Student &s) {
    return get_num_pass_subject(s) >= 2;
}

bool pass_one_or_more(Student &s) {
    return get_num_pass_subject(s) >= 1;
}

bool failed_all(Student &s) {
    return get_num_pass_subject(s) == 0;
}

void stat() {
    int cid;
    int idx[maxn];
    printf("Please enter class ID, 0 for the whole statistics.\n");
    scanf("%d", &cid);
    int cnt = find_by_cid(cid, idx);
    if(cnt == 0) { printf("Invalid class ID.\n"); return ; }

    for(int i = 0; i < 4; i++) {
        int total = 0;
        for(int j = 0; j < cnt; j++) {
            total += students[idx[j]].scores[i];
        }
        double avg = (double)total/(double)cnt;
        printf("%s\n", subjects[i]);
        printf("Average Score: %.2lf\n", avg+eps);
        int pass_num = count(idx, cnt, get_pass_the_subject_func(i));
        printf("Number of passed students: %d\n", pass_num);
        printf("Number of failed students: %d\n\n", cnt-pass_num);
    }
    printf("Overall:\n");
    printf("Number of students who passed all subjects: %d\n", count(idx, cnt, pass_all));
    printf("Number of students who passed 3 or more subjects: %d\n", count(idx, cnt, pass_three_or_more));
    printf("Number of students who passed 2 or more subjects: %d\n", count(idx, cnt, pass_two_or_more));
    printf("Number of students who passed 1 or more subjects: %d\n", count(idx, cnt, pass_one_or_more));
    printf("Number of students who failed all subjects: %d\n\n", count(idx, cnt, failed_all));
}

int main() {
    int cmd;
    while(true) {
        printf("Welcome to Student Performance Management System (SPMS).\n");
        printf("\n");
        printf("1 - Add\n");
        printf("2 - Remove\n");
        printf("3 - Query\n");
        printf("4 - Show ranking\n");
        printf("5 - Show Statistics\n");
        printf("0 - Exit\n");

        scanf("%d", &cmd);
        if(cmd == 0) return 0;
        printf("\n");
        switch(cmd) {
            case 1: { add(); break; }
            case 2: { query_and_take_action(remove_action); break; }
            case 3: { query_and_take_action(query_action); break; }
            case 4: { ranklist(); break; }
            case 5: { stat();  break; }
        }
    }
}