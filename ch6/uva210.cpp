#include<cstdio>
#include<queue>
#include<string>
#include<algorithm>
#include<sstream>
#include<iostream>
#include<vector>
#include<cstdlib>

using namespace std;

std::string trim_space(const std::string& s) {
    std::string ss = s;
    ss.erase(ss.begin(), std::find_if_not(ss.begin(), ss.end(),  [] (unsigned char ch) {
        return std::isspace(ch);
    }));
    ss.erase(std::find_if_not(ss.rbegin(), ss.rend(), [] (unsigned char ch) {
        return std::isspace(ch);
    }).base(), ss.end());
    return ss;
}

std::vector<std::string> split_by(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delimiter)) {
        tokens.push_back(item);
    }
    return tokens;
}

const int maxn = 100;
bool lock;
int vars[26];
int ex_t[5];
int n_prog;
int quantum;

int current;
queue<int> block_queue;
deque<int> ready_queue;

struct Command {
    int type;
    char var;
    int constants;

    Command() : type(0), var('a'), constants(0) {};

    Command(const string s) {
        type = 0;
        var = 'a';
        constants = 0;

        string s1 = trim_space(s);
        if(s1 == "end") {
            type = 4;
        } else if(s1 == "unlock") {
            type = 3;
        } else if(s1 == "lock") {
            type = 2;
        } else if(s1.substr(0,5) == "print") {
            size_t pos = s1.find_first_of(' ');
            type = 1;
            var = s1.at(pos+1);
        } else {
            type = 0;
            vector<string> vs = split_by(s1, '=');
            var = vs[0][0];
            constants = std::stoi(vs[1]);
        }
    }

    bool assign_func() const {
        vars[var-'a'] = constants;
        return true;
    }

    bool output_func() const {
        printf("%d: %d\n", current, vars[var-'a']);
        return true;
    }

    static bool lock_func() {
        if(!lock) {
            lock = true;
            return true;
        } else {
            block_queue.push(current);
            return false;
        }
    }

    static bool unlock_func() {
        lock = false;
        if(!block_queue.empty()) {
            ready_queue.push_front(block_queue.front());
            block_queue.pop();
        }
        return true;
    }

    static bool end_func() {
        return false;
    }

    bool exec() const {
        switch(type) {
            case 0: return assign_func();
            case 1: return output_func();
            case 2: return lock_func();
            case 3: return unlock_func();
            case 4: return end_func();
        }
        return true;
    }
};

struct Program {
    int pid{0};
    int n{0};

    int next{0};
    int left_quota{0};

    Command cmds[100];
    Program() = default;
    Program(int id, int q) : pid(id), n(0), next(0), left_quota(q) {};

    void exec() {
        while(next < n) {
            bool should_next = cmds[next].exec();
            if(!should_next) {
                current = -1; break;
            }
            left_quota -= ex_t[cmds[next++].type];
            if(left_quota <= 0) {
                ready_queue.push_back(current);
                current = -1; break;
            }
        }
    }
} progs[maxn];

void read_into_prog(int n, int q) {
    string s;
    getline(std::cin, s); // 消除空行

    int id = 1;
    while(n--) {
        Program& p = progs[id];
        p = Program(id++, q);
        while(getline(std::cin, s) && !s.empty()) {
            p.cmds[p.n++] = Command(s);
            if(p.cmds[p.n-1].type == 4) break;
        }
    }
}

int get_next() {
    int pid = ready_queue.front();
    ready_queue.pop_front();
    current = pid;
    return current;
}

void execute() {
    while(!ready_queue.empty()) {
        int pid = get_next();
        Program& p = progs[pid];
        p.left_quota = quantum;
        p.exec();
    }
}

int main() {
    int kase;

    scanf("%d", &kase);
    while(kase--) {
        scanf("%d%d%d%d%d%d%d", &n_prog, &ex_t[0], &ex_t[1], &ex_t[2], &ex_t[3], &ex_t[4], &quantum);
        lock = false;
        std::fill_n(vars, sizeof(vars)/sizeof(int), 0);
        current = -1;

        read_into_prog(n_prog, quantum);
        for(int i = 1; i <= n_prog; i++) {
            ready_queue.push_back(i);
        }
        execute();
        if(kase > 0) printf("\n");
    }
}