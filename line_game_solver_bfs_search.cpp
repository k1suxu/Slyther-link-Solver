// #pragma GCC target("avx")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

using ll = long long;

void print_grid(ll h, ll w, vector<vector<ll>> g) {
    cout << "+";
    for(int i = 0; i < w; i++) cout << "-+";
    cout << "\n";
    for(int i = 0; i < h; i++) {
        cout << "|";
        for(int j = 0; j < w; j++) {
            if(g[i][j] != -1) cout << g[i][j];
            else cout << " ";
            cout << "|";
        }
        cout << "\n";
        cout << "+";
        for(int i = 0; i < w; i++) cout << "-+";
        cout << "\n";
    }
}

bool valid(ll &h, ll &w, vector<vector<ll>> &g, ll &sol, vector<pair<int, int>> &target) {
    for(auto e : target) {
        int x, y;
        tie(x, y) = e;

        int cnt = 0;

        if(sol>>(x*w+y)&1) {
            for(int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if(nx < 0 || nx >= h || ny < 0 || ny >= w || (bool)(!(sol>>(nx*w+ny)&1))) ++cnt;
            }
        }else {
            for(int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if(nx < 0 || nx >= h || ny < 0 || ny >= w) continue;
                if(sol>>(nx*w+ny)&1) ++cnt;
            }
        }

        if(cnt != g[x][y]) {
            return false;
        }
    }

    return true;
}

ll solution_count = 0;

void print_solution(ll h, ll w, ll sol) {
    ++solution_count;
    cerr << ">> [FOUND ONE SOLUTION]: (" << solution_count << ")\n";
    cout << "\n[SOLUTION]: (" << solution_count << ")\n";
    cout << "+";
    for(int j = 0; j < w; j++) cout << "-+";
    cout << "\n";
    for(int i = 0; i < h; i++) {
        cout << "|";
        for(int j = 0; j < w; j++) {
            if(sol>>(i*w+j)&1) cout << "#";
            else cout << " ";
            cout << "|";
        }
        cout << "\n";
        cout << "+";
        for(int j = 0; j < w; j++) cout << "-+";
        cout << "\n";
    }
}

void my_sleep(const ll millisec) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millisec));
}

void solve() {
    ll h, w;
    cin >> h;
    cin >> w;
    vector<vector<ll>> g(h, vector<ll>(w));
    for(int i = 0; i < h; i++) for(int j = 0; j < w; j++) cin >> g[i][j];

    vector<pair<int, int>> target;
    for(int i = 0; i < h; i++) for(int j = 0; j < w; j++) if(g[i][j] != -1) target.emplace_back(i, j);

    print_grid(h, w, g);

    set<ll> st;
    queue<ll> que;

    // int i = (1LL<<0) + (1LL<<2) + (1LL<<6) + (1LL<<7) + (1LL<<12);
    // st.insert(i);
    // que.push(i);

    for(int i = 0; i < h*w; i++) {
        st.insert(1LL<<i);
        que.push(1LL<<i);
    }

    ll cnt = 0;

    cerr << "\n>> [exec. status]: BFS Start\n";

    while(!que.empty()) {
        ll v = que.front();
        que.pop();

        if(valid(h, w, g, v, target)) {
            print_solution(h, w, v);
        }

        ++cnt;
        if(cnt%500000==0) cerr << ">> [bfs step]: " << cnt << endl;

        for(int i = 0; i < h*w; i++) {
            if(v>>i&1) {
                ll x = i/w, y = i%w;
                for(int d = 0; d < 4; d++) {
                    ll nx = x + dx[d], ny = y + dy[d];

                    if(nx < 0 || nx >= h || ny < 0 || ny >= w) {
                        continue;
                    }

                    // if(nx*w+ny == 1 || nx*w+ny == 30 || nx*w+ny == 31 || nx*w+ny == 32 || nx*w+ny == 35) {
                    //     continue;
                    // }

                    if(!(v>>(nx*w+ny)&1)) {
                        ll nv = v | (1LL<<(nx*w+ny));
                        if(st.find(nv) == st.end()) {
                            st.insert(nv);
                            que.push(nv);
                        }
                    }
                }
            }
        }
    }

    cerr << "[exec. status]: FINAL_CNT (number of states) = " << cnt << endl;
}

signed main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    solve();
    return 0;
}
