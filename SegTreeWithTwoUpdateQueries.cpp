#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <cstring>
#include <deque>
#include <map>

#define iter vector<long long int>::iterator
#define input() ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

typedef long long int ll;

struct mod_query{

    ll type = 0, val = 0;
    // type = 0 => nothing to do
    // type = 1 => add val
    // type = 2 => set val

};

struct SegTree{

    vector<ll> tree;
    vector<mod_query> mod;

    SegTree(ll n){
        tree.resize(4 * n);
        mod.resize(4 * n);
    }

    void build(ll v, ll l, ll r, vector<ll> const & a){
        if(r - l == 1){
            tree[v] = a[l];
            mod[v] = {0, 0};
        }else{
            ll m = (l + r) / 2;
            build(2 * v, l, m, a);
            build(2 * v + 1, m, r, a);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        }
    }

    void push(ll v, ll l, ll r){
        if(r - l == 1){
            mod[v] = {0, 0};
        }
        if(mod[v].type == 0){
            return ;
        }
        ll m = (l + r) / 2;
        if(mod[v].type == 1){
            if(mod[2 * v].type == 0){
                mod[2 * v].type = 1;
                mod[2 * v].val = mod[v].val;
                tree[2 * v] += mod[v].val * (m - l);
            }else if(mod[2 * v].type == 1){
                mod[2 * v].val += mod[v].val;
                tree[2 * v] += mod[v].val * (m - l);
            }else if(mod[2 * v].type == 2){
                mod[2 * v].val += mod[v].val;
                tree[2 * v] = mod[2 * v].val * (m - l);
            }
            if(mod[2 * v + 1].type == 0){
                mod[2 * v + 1].type = 1;
                mod[2 * v + 1].val = mod[v].val;
                tree[2 * v + 1] += mod[v].val * (r - m);
            }else if(mod[2 * v + 1].type == 1){
                mod[2 * v + 1].val += mod[v].val;
                tree[2 * v + 1] += mod[v].val * (r - m);
            }else if(mod[2 * v + 1].type == 2){
                mod[2 * v + 1].val += mod[v].val;
                tree[2 * v + 1] = mod[2 * v + 1].val * (r - m);
            }
        }else{
            mod[2 * v].val = mod[v].val;
            mod[2 * v + 1].val = mod[v].val;
            mod[2 * v].type = 2;
            mod[2 * v + 1].type = 2;
            tree[2 * v] = mod[2 * v].val * (m - l);
            tree[2 * v + 1] = mod[2 * v + 1].val * (r - m);
        }
        mod[v] = {0, 0};
    }

    void add(ll v, ll l, ll r, ll ql, ll qr, ll val){
        if(r <= ql || qr <= l){
            return ;
        }
        push(v, l, r);
        if(ql <= l && r <= qr){
            mod[v] = {1, val};
            tree[v] += (r - l) * val;
            return ;
        }
        ll m = (l + r) / 2;
        add(2 * v, l, m, ql, qr, val);
        add(2 * v + 1, m, r, ql, qr, val);
        tree[v] = tree[2 * v] + tree[2 * v + 1];
    }

    void upd(ll v, ll l, ll r, ll ql, ll qr, ll val){
        if(r <= ql || qr <= l){
            return ;
        }
        push(v, l, r);
        if(ql <= l && r <= qr){
            mod[v] = {2, val};
            tree[v] = (r - l) * val;
            return ;
        }
        ll m = (l + r) / 2;
        upd(2 * v, l, m, ql, qr, val);
        upd(2 * v + 1, m, r, ql, qr, val);
        tree[v] = tree[2 * v] + tree[2 * v + 1];
    }

    ll get(ll v, ll l, ll r, ll ql, ll qr){
        if(r <= ql || qr <= l){
            return 0;
        }
        push(v, l, r);
        if(ql <= l && r <= qr){
            return tree[v];
        }
        ll m = (l + r) / 2;
        ll res = get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
        return res;
    }

};

int main(){
    input();
    ll n, q, i, t, l, r, x;
    cin >> n >> q;
    vector<ll> a(n);
    for(i = 0; i < n; i++){
        cin >> a[i];
    }
    SegTree st = SegTree(n);
    st.build(1, 0, n, a);
    for(i = 0; i < q; i++){
        cin >> t >> l >> r;
        l--;
        if(t == 1){
            cin >> x;
            st.add(1, 0, n, l, r, x);
        }else if(t == 2){
            cin >> x;
            st.upd(1, 0, n, l, r, x);
        }else{
            cout << st.get(1, 0, n, l, r) << "\n";
        }
    }
    return 0;
}
