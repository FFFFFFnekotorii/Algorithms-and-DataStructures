#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <deque>
#include <fstream>
#include <bitset>
#include <random>

#include <chrono>
#include <cassert>

using namespace std;

typedef long long int ll;
typedef long double ld;

#define    INF 1000000007
#define  INF64 1000000000000000003LL
#define    LMT 1000000
#define  INPUT ios::sync_with_stdio(false); cin.tie(0);

#define    FST first
#define    SND second

#define    MOD 998244353LL

#ifdef LOCAL
    #define cout cerr
#endif

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

void solve() {
	
}

int main() {
 
    #ifndef LOCAL
        INPUT;
    #endif
	
    int t;
 
    for (t = 1; t; t--) {
        solve();
    }
 
    #ifdef LOCAL
        cerr << '\n';
        system("pause");
    #endif
 
    return 0;
}
