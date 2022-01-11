#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <cstring>
#include <deque>
#include <map>

#define iter vector<long long int>::iterator
#define input() ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

typedef long long int ll;

ll inf = 1000000007;

struct SegTree{
    vector<ll> tree, mod;

    void init(ll n){
        tree.resize(4 * n);
        mod.resize(4 * n);
    }

    void build(ll v, ll l, ll r, vector<ll> const & a){
        if(r - l == 1){
            tree[v] = a[l];
        }else{
            ll m = (l + r) / 2;
            build(2 * v, l, m, a);
            build(2 * v + 1, m, r, a);
            tree[v] = min(tree[2 * v], tree[2 * v + 1]);
        }
    }

    ll get_min(ll v, ll l, ll r, ll ql, ll qr){
        if(ql <= l && r <= qr){
            return tree[v];
        }
        if(r <= ql || qr <= l){
            return inf;
        }
        ll m = (l + r) / 2;
        return min(get_min(2 * v, l, m, ql, qr), get_min(2 * v + 1, m, r, ql, qr));
    }

    void upd(ll v, ll l, ll r, ll ind, ll val){
        if(r - l == 1){
            tree[v] = val;
        }else{
            ll m = (l + r) / 2;
            if(ind < m){
                upd(2 * v, l, m, ind, val);
            }else{
                upd(2 * v + 1, m, r, ind, val);
            }
            tree[v] = min(tree[2 * v], tree[2 * v + 1]);
        }
    }

    ll find_first_less(ll v, ll l, ll r, ll val){
        if(r - l == 1){
            return tree[v];
        }else{
            ll m = (l + r) / 2;
            if(tree[2 * v] < val){
                return find_first_less(2 * v, l, m, val);
            }else{
                return find_first_less(2 * v + 1, m, r, val);
            }
        }
    }

};

int main(){
    input();
    return 0;
}
