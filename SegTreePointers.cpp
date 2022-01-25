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

struct SegTree{
    ll tree = 0, mod = 0;
    ll lb, rb;
    SegTree *l = nullptr, *r = nullptr;

    SegTree(ll l, ll r){
        lb = l;
        rb = r;
    }

    void extend(){
        if(l == nullptr){
            ll m = (lb + rb) / 2;
            l = new SegTree(lb, m);
            r = new SegTree(m, rb);
        }
    }

    ll rsq(ll ql, ll qr){
        if(rb <= ql || qr <= lb){
            return 0;
        }
        if(ql <= lb && rb <= qr){
            return tree;
        }
        extend();
        return l->rsq(ql, qr) + r->rsq(ql, qr);
    }

    void add(ll ind, ll val){
        if(rb - lb == 1){
            tree = val;
            return ;
        }
        extend();
        if(ind < l->rb){
            l->add(ind, val);
        }else{
            r->add(ind, val);
        }
        tree = l->tree + r->tree;
    }

};

int main(){
    input();
    ll n, i, q, x, y;
    cin >> n;
    vector<ll> a(n);
    SegTree t = SegTree(0, n);
    for(i = 0; i < n; i++){
        cin >> a[i];
        t.add(i, a[i]);
    }
    cin >> q;
    string s;
    while(q--){
        cin >> s >> x >> y;
        if(s == "u"){
            t.add(x - 1, y);
        }else{
            cout << t.rsq(x - 1, y) << "\n";
        }
    }
    return 0;
}
