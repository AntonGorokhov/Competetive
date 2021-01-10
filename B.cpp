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

const int maxN = 1e3 + 2;
int mas[maxN][maxN];
int usd[maxN][maxN];
int ans[maxN][maxN];

vector<int> dx = {0, 0, 1, -1};
vector<int> dy = {1, -1, 0, 0};

void dfs(int x, int y) {
    if (mas[x][y] == 0) {
        return;
    }
    if (usd[x][y]) return;
    int ret = 1;
    usd[x][y] = 1;
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i], ny = y + dy[i];
        if (mas[nx][ny] == mas[x][y] - 1) {
            dfs(nx, ny);
            ret = max(ret, 1 + ans[nx][ny]);
        }
    }
    ans[x][y] = ret;
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> mas[i][j];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dfs(i, j);
        }
    }
    int answer = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            answer = max(answer, ans[i][j]);
        }
    }
    cout << answer << '\n';
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