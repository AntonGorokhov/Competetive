#include <iostream>
#include <vector>
#include <bitset>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <random>
#include <queue>
#include <deque>
#include <iomanip>
#include <string>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <utility>
#include <cassert>
#include <cstddef>

using namespace std;
inline void fastio() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

#define int long long
#define ll long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define ld long double

int compress(vector<pair<int, int> > &v) {
    vector<int> x;
    for (int i = 0; i < (int) v.size(); ++i) {
        x.push_back(v[i].first);
        x.push_back(v[i].second);
    }
    sort(all(x));
    x.erase(unique(all(x)), x.end());
    for (int i = 0; i < (int) x.size(); ++i) {
        v[i].first = lower_bound(all(x), v[i].first) - x.begin();
        v[i].second = lower_bound(all(x), v[i].second) - x.begin();
    }
    return (int) x.size();
}

struct event {
    int num;
    bool open;
    int nxt;
    event() {}
    event(int _num, int _open) : num(_num), open(_open) {}
};

const bool operator < (const event &a, const event &b) {
    return a.open > b.open;
}

struct fen {
    int n;
    vector<int> f;
    fen() {}
    fen(int _n) {
        n = _n + 5;
        f.assign(n, 0);
    }
    void add(int x, int y) {
        for (; x < n; x += x & -x) {
            f[x] += y;
        }
    }
    int get(int x) {
        int y = 0;
        for (; x > 0; x -= x & -x) {
            y += f[x];
        }
        return y;
    }
    int get(int l, int r) {
        return get(r) - get(l - 1);
    }
};

vector<int> answer;

void run(const vector<vector<event> > &times) {
    fen F((int) times.size());
    for (int i = 0; i < (int) times.size(); ++i) {
        for (auto &j : times[i]) {
            if (!j.open) {
                F.add(i, -1);
                answer[j.num] += F.get(j.nxt + 1 + 1, i + 1 - 1);
            } else {
                F.add(j.nxt, 1);
            }
        }
    }
}

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int> > v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].first >> v[i].second;
    }
    int x = compress(v);
    vector<pair<int, int> > nv(0);
    vector<int> new_index(n, -1);
    for (int i = 0; i < n; ++i) {
        if (v[i].second - v[i].first > 1) {
            new_index[i] = (int) nv.size();
            nv.push_back(v[i]);
        }
    }
    v.swap(nv);
    n = (int) v.size();
    answer.assign(n, 0);

    vector<vector<event> > times(x);
    for (int i = 0; i < n; ++i) {
        times[v[i].first].push_back(event(i, true));
        times[v[i].first].back().nxt = v[i].second;
        times[v[i].second].push_back(event(i, false));
        times[v[i].second].back().nxt = v[i].first;
    }
    for (int i = 0; i < x; ++i) {
        sort(all(times[i]));
    }
    run(times);
    reverse(all(times));
    for (int i = 0; i < x; ++i) {
        for (auto &j : times[i]) {
            j.num ^= 1;
        }
        reverse(all(times[i]));
    }
    run(times);
    int q;
    cin >> q;
    while (q--) {
        int num;
        cin >> num;
        num--;
        if (new_index[num] == -1) {
            cout << "1\n";
        } else {
            cout << answer[new_index[num]] << '\n';
        }
    }
}

signed main() {
#ifdef lolipop
    freopen("input.txt", "r", stdin);
#else
    fastio();
#endif
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}