#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

using ll = long long int;

struct merge_sort_tree {
    vector<vector<int>> tree;

    void resize(int n) {
        tree.resize(4 * n);
    }

    void build(int v, int l, int r, const vector<vector<int>>& a) {
        if (r - l == 1) {
            tree[v] = a[l];
            sort(begin(tree[v]), end(tree[v]));
            return ;
        }
        int m = (l + r) / 2;

        build(2 * v + 1, l, m, a);
        build(2 * v + 2, m, r, a);

        merge(begin(tree[2 * v + 1]), end(tree[2 * v + 1]), begin(tree[2 * v + 2]), end(tree[2 * v + 2]), back_inserter(tree[v]));
    }

    void print(int v, int l, int r) {
        cout << v << ' ' << l << ' ' << r << '\n';
        for (auto x : tree[v]) {
            cout << x << ' ';
        } cout << "\n\n";
        if (r - l == 1) {
            return ;
        }
        int m = (l + r) / 2;

        print(2 * v + 1, l, m);
        print(2 * v + 2, m, r);
    }

    void count_in_interval(int v, int l, int r, int ql, int qr, int lb, int rb, int& ans) {
        if (r <= ql || qr <= l) {
            return ;
        }
        if (ql <= l && r <= qr) {
            ans += distance(upper_bound(begin(tree[v]), end(tree[v]), rb),
                            lower_bound(begin(tree[v]), end(tree[v]), lb));
            return ;
        }
        int m = (l + r) / 2;

        count_in_interval(2 * v + 1, l, m, ql, qr, lb, rb, ans);
        count_in_interval(2 * v + 2, m, r, ql, qr, lb, rb, ans);
    }
};

auto solve() -> void {

    int n, q;
    vector<pair<ll, ll>> p;
    vector<ll> coord;
    vector<pair<char, ll>> dirs;
    map<ll, int> comp;

    cin >> n;

    p.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;

        coord.push_back(p[i].first);
        coord.push_back(p[i].second);
    }

    coord.push_back(0);

    cin >> q;

    dirs.resize(q);
    ll xcur = 0, ycur = 0;
    for (int i = 0; i < q; i++) {
        cin >> dirs[i].first >> dirs[i].second;

        if (dirs[i].first == 'U') {
            ycur += dirs[i].second;
        }
        if (dirs[i].first == 'D') {
            ycur -= dirs[i].second;
        }
        if (dirs[i].first == 'L') {
            xcur -= dirs[i].second;
        }
        if (dirs[i].first == 'R') {
            xcur += dirs[i].second;
        }

        coord.push_back(xcur);
        coord.push_back(ycur);
    }

    sort(begin(coord), end(coord));
    coord.erase(unique(begin(coord), end(coord)), end(coord));

    for (int i = 0; i < coord.size(); i++) {
        comp[coord[i]] = i;
    }

    merge_sort_tree xtree, ytree;
    vector<vector<int>> xtree_build((int)coord.size()), ytree_build((int)coord.size());

    xtree.resize((int)coord.size());
    ytree.resize((int)coord.size());
/*
    cout << "===\n";
*/
    for (int i = 0; i < n; i++) {
        int x1 = comp[p[i].first];
        int y1 = comp[p[i].second];
/*
        cout << x1 << ' ' << y1 << '\n';
*/
        xtree_build[x1].push_back(y1);
        ytree_build[y1].push_back(x1);
    }
/*
    cout << "---\n";
*/
    xtree.build(0, 0, (int)coord.size(), xtree_build);
    ytree.build(0, 0, (int)coord.size(), ytree_build);

    xcur = 0;
    ycur = 0;
    for (int i = 0; i < q; i++) {
        ll xnext = xcur;
        ll ynext = ycur;

        if (dirs[i].first == 'U') {
            ynext += dirs[i].second;
        }
        if (dirs[i].first == 'D') {
            ynext -= dirs[i].second;
        }
        if (dirs[i].first == 'L') {
            xnext -= dirs[i].second;
        }
        if (dirs[i].first == 'R') {
            xnext += dirs[i].second;
        }

        int uwu = 0;
        int owo = 0;

        int x1 = comp[xcur];
        int x2 = comp[xnext];
        int y1 = comp[ycur];
        int y2 = comp[ynext];

        if (x1 > x2) {
            swap(x1, x2);
        }
        if (y1 > y2) {
            swap(y1, y2);
        }

        xtree.count_in_interval(0, 0, (int)coord.size(), x1, x2 + 1, y1, y2, uwu);
        ytree.count_in_interval(0, 0, (int)coord.size(), y1, y2 + 1, x1, x2, owo);
/*
        cout << xcur << ' ' << xnext << '\n';
        cout << ycur << ' ' << ynext << '\n';

        cout << comp[xcur] << ' ' << comp[xnext] << '\n';
        cout << comp[ycur] << ' ' << comp[ynext] << '\n';

        cout << uwu << ' ' << owo << '\n';
*/
        if (owo || uwu) {
            cout << "Stop " << i + 1;
            return ;
        }
/*
        cout << '\n';
*/
        xcur = xnext;
        ycur = ynext;
    }

    cout << "Complete";
}

auto main() -> int {

    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    solve();

    return 0;
}
