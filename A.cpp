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
#include <cmath>

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

void solve() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    vector<int> p(n);
    p[0] = (v[0] == 1);
    for (int i = 1; i < n; ++i) {
        p[i] = p[i - 1] + (v[i] == 1);
    }
    auto get = [&] (int l, int r) {
        if (l == 0) return p[r];
        return p[r] - p[l - 1];
    };
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        if (get(l, r) == r - l + 1) {
            cout << "2\n";
        } else {
            cout << "1\n";
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