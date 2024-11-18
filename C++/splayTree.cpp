#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()

using ld = long double;
using ll = long long;

const ll INF64 = 1000000000000000003LL;
const int INF = 1000000007;

struct splay_tree {
    inline static const int nullnode = -1;
    struct node {
        int lt = nullnode, rt = nullnode, par = nullnode;
        int key, sz = 0, cnt = 0;

        node() {}

        node(int key) : key(key), sz(1), cnt(1) {}
    };

    vector<node> nodes;
    int root = nullnode;

    int new_node(int key) {
        int newid = nodes.size();
        nodes.push_back(node(key));

        return newid;
    }

    int sz(int x) {
        return (x == nullnode ? 0 : nodes[x].sz);
    }

    void upd(int x) {
        assert(x != nullnode);

        nodes[x].sz = nodes[x].cnt + sz(nodes[x].lt) + sz(nodes[x].rt);
    }

    splay_tree() {
        nodes.clear();
    }

    int link(int p, int v, bool is_right) {
        assert(p != nullnode);
        if (is_right) nodes[p].rt = v;
        else nodes[p].lt = v;

        if (v != nullnode) nodes[v].par = p;

        upd(p);
        return v;
    }

    void unlink(int p, int v, bool is_right) {
        assert(p != nullnode && v != nullnode);
        if (is_right) nodes[p].rt = nullnode;
        else nodes[p].lt = nullnode;

        upd(p);
        nodes[v].par = nullnode;
    }

    int is_right(int x) {
        assert(x != nullnode && nodes[x].par != nullnode);
        return x == nodes[nodes[x].par].rt;
    }

    void zig(int x) {
        assert(x != nullnode && nodes[x].par != nullnode);
        int y = nodes[x].par;
        int y_par = nodes[y].par;
        int was_right = nodes[y].par == nullnode ? -1 : is_right(y);
        if (is_right(x)) {
            link(y, nodes[x].lt, true);
            link(x, y, false);
        } else {
            link(y, nodes[x].rt, false);
            link(x, y, true);
        }
        if (was_right != -1) link(y_par, x, was_right);
        else nodes[x].par = nullnode;
    }

    int splay(int x) {
        assert(x != nullnode);

        while (true) {
            if (nodes[x].par == nullnode) break;
            if (nodes[nodes[x].par].par == nullnode) {
                zig(x);
                break;
            }
            int zigzag = is_right(x) ^ is_right(nodes[x].par);

            if (zigzag) zig(x);
            else zig(nodes[x].par);

            zig(x);
        }
        return x;
    }

    void print() {
        print(root);
    }

    void print(int x) {
        if (x == nullnode) return;
        cout << "[";
        print(nodes[x].lt);
        cout << nodes[x].key << ' ';
        print(nodes[x].rt);
        cout << "] ";
    }

    int find(int x, int key) {
        if (x == nullnode) return nullnode;

        if (key == nodes[x].key) return x;
        if (key < nodes[x].key) return find(nodes[x].lt, key);
        return find(nodes[x].rt, key);
    }

    int find(int key) {
        return find(root, key);
    }

    void make_root(int r) {
        splay(r);
        root = r;
        nodes[root].par = nullnode;
    }

    int merge(int lt, int rt) {
        if (lt == nullnode) { return rt; }
        if (rt == nullnode) { return lt; }

        //print(lt);print(rt);
        //cout << '\n';

        lt = find(lt, maxlt(lt, INF + 1));
        make_root(lt);
        assert(nodes[lt].rt == nullnode);
        link(lt, rt, true);

        return lt;
    }

    pair<int, int> split(int x, int key) {
        if (x == nullnode) { return {nullnode, nullnode}; }

        if (maxlt(x, key + 1) == -INF) { return {nullnode, x}; }
        int t = find(x, maxlt(x, key + 1));
        make_root(t);
        int rt = nodes[t].rt;
        if (rt != nullnode) unlink(t, rt, true);

        //print(t);
        //cout << "-";
        //print(rt);
        //cout << '\n';
        return {t, rt};
    }

    void insert(int key) {
        int x = find(key);
        if (x != nullnode) {
            nodes[x].cnt += 1;
            nodes[x].sz += 1;
            make_root(x);
            return ;
        }
        auto [lt, rt] = split(root, key);
        root = merge(merge(lt, new_node(key)), rt);
        make_root(find(root, key));
    }

    void erase(int key) {
        int x = find(key);
        nodes[x].cnt -= 1;
        nodes[x].sz -= 1;
        if (nodes[x].cnt != 0) {
            make_root(x);
            return ;
        }
        auto [lt, mt] = split(root, key - 1);
        auto [_, rt] = split(mt, key);
        root = merge(lt, rt);
    }

    int maxlt(int x, int key) {
        if (x == nullnode) { return -INF; }
        if (nodes[x].key < key) {
            return max(nodes[x].key, maxlt(nodes[x].rt, key));
        } else {
            return maxlt(nodes[x].lt, key);
        }
    }

    int maxlt(int key) {
        return maxlt(root, key);
    }

    int mingt(int x, int key) {
        if (x == nullnode) { return INF; }
        if (key < nodes[x].key) {
            return min(nodes[x].key, mingt(nodes[x].lt, key));
        } else {
            return mingt(nodes[x].rt, key);
        }
    }

    int mingt(int key) {
        return mingt(root, key);
    }

    int cntlt(int x, int key) {
        //cout << "cntlt: " << x << '\n';
        if (x == nullnode) return 0;
        if (nodes[x].key < key) {
            return sz(nodes[x].lt) + cntlt(nodes[x].rt, key) + nodes[x].cnt;
        } else {
            return cntlt(nodes[x].lt, key);
        }
    }

    int cntlt(int key) {
        return cntlt(root, key);
    }

    int kth(int x, int k) {
        assert(x != nullnode);
        if (sz(nodes[x].lt) <= k && k < sz(nodes[x].lt) + nodes[x].cnt) return nodes[x].key;

        if (k < sz(nodes[x].lt)) return kth(nodes[x].lt, k);
        return kth(nodes[x].rt, k - sz(nodes[x].lt) - nodes[x].cnt);
    }

    int kth(int k) {
        return kth(root, k);
    }
};

void solve() {
    splay_tree t;
    int q;

    cin >> q;

    for (int i = 0; i < q; i++) {
        string op;
        int k;

        cin >> op >> k;

        if (op == "insert") {
            int x = t.find(k);
            if (x != splay_tree::nullnode) {
                t.make_root(x);
            }

            t.insert(k);
        } else if (op == "erase") {
            t.erase(k);
        } else if (op == "count") {
            int x = t.find(t.maxlt(k + 1));
            if (x == splay_tree::nullnode) {
                cout << 0 << '\n';

                x = t.find(t.mingt(k));
                if (x != splay_tree::nullnode) t.make_root(x);
                continue;
            }
            t.make_root(x);

            cout << t.cntlt(k + 1) - t.cntlt(k) << '\n';
        } else if (op == "kth") {
            int w = t.kth(k - 1);

            t.make_root(t.find(w));

            cout << w << '\n';
        } else {
            int x = t.find(t.maxlt(k));
            if (x == splay_tree::nullnode) {
                cout << 0 << '\n';

                x = t.find(t.mingt(k));
                if (x != splay_tree::nullnode) t.make_root(x);
                continue;
            }
            t.make_root(x);

            cout << t.cntlt(k) << '\n';
        }
        //t.print();
    }

}

int main() {
/*
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
*/
    ios::sync_with_stdio(0);
    cin.tie(0);

    //srand(3456);

    int t = 1;
    //cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
