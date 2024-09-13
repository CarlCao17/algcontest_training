#include<bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef unsigned long long u64;
typedef __int128 i128;

typedef std::pair<long long, long long> PLL;
const int mod = 998244353;
const int N = static_cast<const int>(2e6+1000);
const int INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-6;

string disqualify_score = "DQ";
int DQ_SCORE = -1;

struct Player {
    string name;
    int scores[4]{};
    bool amateur;
    double prize_p;
    int first;
    int total;

    Player() : scores{}, amateur(false), prize_p(0.0), first(0), total(0) {
        fill(scores, scores+4, DQ_SCORE);
    }
};

std::string trim_space(const std::string& s) {
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) ++start;
    auto end = s.end();
    do {
        --end;
    } while(end != start && std::isspace(*end));
    return std::string(start, end+1);
}

int cal_scores(int s[4], int b, int e) {
    int total = 0;
    for(int i = b; i < e; i++) {
        if(s[i] == DQ_SCORE) { total = numeric_limits<int>::max(); break; }
        total += s[i];
    }
    return total;
}

void read_player(const string& s, Player &p) {
    string name = trim_space(s.substr(0,20));
    if(name[name.length()-1] == '*') {
        p.amateur = true;
        name = name.substr(0, name.length()-1);
    }
    p.name = name;

    stringstream ss(s.substr(20,s.length()));
    for(int i = 0; i < 4; i++) {
        string score_str;
        ss >> score_str;
        if(score_str == disqualify_score) {
            break;
        }
        int score = stoi(score_str);
        p.scores[i] = score;
    }
    p.first = cal_scores(p.scores, 0, 2);
    p.total = cal_scores(p.scores, 0, 4);
}

// 将 ranks(0..num) 按照 comp 排序，并且取前 rd 名（包含并列）
// rank 从 0 开始
template<typename Func>
pair<map<int, vector<int>>, int> rank_and_truncate(const Player p[], vector<int>& ranks, int num, int rd, Func getter) {
    sort(ranks.begin(), ranks.begin()+num, [&p, getter](const int p1, const int p2) {
        return getter(p[p1]) < getter(p[p2]);
    });

    map<int, vector<int>> rank_ties;
    int i = 1;
    int r = 1;
    rank_ties[0] = {ranks[0]};

    for(; i < num && r < rd; i++) {
        int pid = ranks[i];
        if(getter(p[pid]) == DQ_SCORE) break;
        if(getter(p[pid]) != getter(p[ranks[i-1]])) {
            ++r;
            rank_ties[r-1].emplace_back();
        }
        rank_ties[r-1].push_back(ranks[i]);
    }
    return pair<map<int, vector<int>>, int>(rank_ties,i);
}

void cal_prize(const Player p[], vector<vector<int>>& ranks_ties, int num_have_prize_ties, double percent[]) {
    for(int i = 0; i < num_have_prize_ties; i++) {
        vector<int> curr_rank_ids = ranks_ties[i];
        if(curr_rank_ids.size() > 1) {

        }
    }
}

void print_result(const Player p[], int n) {

}

const int max_num_players = 200;
//const int num_have_prize = 70;
const int num_have_prize = 6;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    double percent;
    double total_prizes;
    int num_players;
    vector<double> percents;
    Player players[max_num_players];
    string line;

    cin >> n;
    while(n--) {
        vector<int> ranks;

        cin >> total_prizes;
        for(int i = 0; i < num_have_prize; i++) {
            cin >> percent;
            percents.push_back(percent);
        }
        cin >> num_players;
        getline(cin, line);
        for(int i = 0; i < num_players; i++) {
            getline(cin, line);
            read_player(line, players[i]);
            ranks.push_back(i);
        }
        pair<map<int, vector<int>>, int> res1 = rank_and_truncate(players, ranks, num_players, num_have_prize, [](const Player& p) {
            return p.first;
        });
        pair<map<int, vector<int>>, int> res2 = rank_and_truncate(players, ranks, res1.second, num_have_prize, [](const Player& p) {
            return p.total;
        });
//        cal_prize(players, ranks, num_pass, percent, num_have_prize);
//        print_result(players);
    }

    return 0;
}