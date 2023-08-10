struct disjoint_set_union {
    vector<int> par, sz;

    disjoint_set_union() {}

    void resize(int size) {
        par.resize(size);
        sz.resize(size);
    }

    void make_set(int x) {
        par[x] = -1;
        sz[x] = 1;
    }

    int find(int x) {
        if (par[x] == -1) {
            return x;
        }
        par[x] = find(par[x]);
        return par[x];
    }

    bool merge(int a, int b) {
        int v, u;

        v = find(a), u = find(b);

        if (v == u) {
            return false;
        }

        if (sz[v] < sz[u]) {
            swap(v, u);
        }

        sz[v] += sz[u];
        par[u] = v;

        return true;
    }
};
