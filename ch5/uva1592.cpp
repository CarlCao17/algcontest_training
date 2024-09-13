#include<iostream>
#include<sstream>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

map<string, int> id_cache;
vector<string> data;

int ID(const string& s) {
    if(id_cache.count(s)) return id_cache[s];
    data.push_back(s);
    id_cache[s] = (int)data.size()-1;
    return (int)data.size()-1;
}

void split_by(const string& s, int v[]) {
    stringstream ss(s);
    string item;
    int i = 0;
    while(getline(ss, item, ',')) {
       v[i++] = ID(item);
    }
}

const int maxn = 10000+5;
const int maxm = 10 + 5;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int db[maxn][maxm];
    int n, m;
    string s;

    while(cin >> n >> m) {
        map<pair<int,int>, map<pair<int,int>, int> > mp;
        id_cache.clear();
        data.clear();
        int r1, r2;
        int c1, c2;
        bool is_ptf = true;

        getline(cin, s); // ignore the newline
        for(int i = 0; i < n; i++) {
            getline(cin, s);
            split_by(s, db[i]);
            if(!is_ptf) continue;
            for(int j = 0; j < m; j++) {
                for(int k = j+1; k < m; k++) {
                    map<pair<int,int>,int> &curr = mp[pair<int,int>(j, k)];
                    pair<int,int> p = pair<int,int>(db[i][j], db[i][k]);
                    if(curr.count(p)) {
                        r1 = curr[p], r2 = i;
                        c1 = j, c2 = k;
                        is_ptf = false;
                        goto end;
                    } else {
                        curr[p] = i;
                    }
                }
            }
end:;
        }
        if(!is_ptf) {
            cout << "NO" << endl;
            cout << r1+1 << " " << r2+1 << endl;
            cout << c1+1 << " " << c2+1 << endl;
        } else {
            cout << "YES" << endl;
        }
    }
    return 0;
}