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

const int maxN = 1e3 + 1;
int mas[maxN][maxN];
int m1[maxN][maxN];
int n, m, k;

int get(int x) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mas[i][j] >= x) {
                m1[i][j] = 1;
            } else {
                m1[i][j] = 0;
            }
        }
    }
    int up[m];
    for (int j = 0; j < m; ++j) {
        up[j] = 0;
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            up[j] = (m1[i][j] == 0 ? 0 : up[j] + 1);
        }
        vector<int> l(m, -1);
        vector<int> r(m, m);
        vector<int> st;
        for (int j = 0; j < m; ++j) {
            while (st.size() > 0 && up[st.back()] > up[j]) {
                r[st.back()] = j;
                st.pop_back();
            }
            st.push_back(j);
        }
        st.clear();
        for (int j = m - 1; j >= 0; --j) {
            while (st.size() > 0 && up[st.back()] > up[j]) {
                l[st.back()] = j;
                st.pop_back();
            }
            st.push_back(j);
        }
        for (int j = 0; j < m; ++j) {
            ans = max(ans, up[j] * (r[j] - l[j] - 1));
        }
    }
    return ans;
}

void solve() {
    cin >> n >> m >> k;
    vector<int> diff;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> mas[i][j];
            diff.push_back(mas[i][j]);
        }
    }
    sort(all(diff));
    diff.erase(unique(all(diff)), diff.end());
    int L = 0, R = (int) diff.size();
    while (L + 1 < R) {
        int M = (L + R) / 2;
        int x = diff[M];
        if (get(x) >= k) {
            L = M;
        } else {
            R = M;
        }
    }
    cout << diff[L] << ' ' << get(diff[L]) << '\n';
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