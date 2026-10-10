#include <bits/stdc++.h>
using namespace std;

long long final_leaf(int D, long long n) {
    long long pos = 1; // root index (1‑based)
    // Need D‑1 decisions to reach a leaf switch.
    for (int i = 0; i < D - 1; ++i) {
        if (n & 1LL) { // odd -> go left
            pos = pos * 2;
            n = (n + 1) / 2;
        } else { // even -> go right
            pos = pos * 2 + 1;
            n = n / 2;
        }
    }
    return pos; // leaf node index (1‑based)
}

// reverse the lowest 'bits' bits of x
void distribute(long long cnt, int level, int leaf_idx, vector<long long> &visits) {
    if (level == 0) {
        visits[leaf_idx] = cnt;
        return;
    }
    long long left = (cnt + 1) / 2; // first ball goes left, then alternating
    long long right = cnt / 2;
    distribute(left, level - 1, leaf_idx * 2, visits);
    distribute(right, level - 1, leaf_idx * 2 + 1, visits);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int D; long long n;
    if (!(cin >> D >> n)) return 0;
    long long leaf_node = final_leaf(D, n);
    cout << leaf_node << "\n";
    int leaf_cnt = 1 << (D - 1);
    vector<long long> visits(leaf_cnt, 0);
    distribute(n, D - 1, 0, visits);
    for (int i = 0; i < leaf_cnt; ++i) {
        int state = visits[i] % 2;
        cout << state;
        if (i + 1 < leaf_cnt) cout << ' ';
    }
    cout << "\n";
    // However, we already modified n. Let's redo correctly.
    return 0;
}
