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

ll func(ll a, ll b){
    return __gcd(a, b);
}

struct SegTree{

    vector<ll> t;

    void init(ll n){
        t.resize(4 * n);
    }

    void build(ll v, ll l, ll r, vector<ll> &a){
        if(r - l == 1){
            t[v] = a[l];
        }else{
            ll m = (l + r) / 2;
            build(2 * v, l, m, a);
            build(2 * v + 1, m, r, a);
            t[v] = func(t[2 * v], t[2 * v + 1]);
        }
    }

    ll get(ll v, ll l, ll r, ll ql, ll qr){
        if(ql <= l && r <= qr){
            return t[v];
        }
        if(r <= ql || qr <= l){
            return 0;
        }
        ll m = (l + r) / 2;
        return func(get(2 * v, l, m, ql, qr), get(2 * v + 1, m, r, ql, qr));
    }

    void upd(ll v, ll l, ll r, ll ind, ll val){
        if(r - l == 1){
            if(l == ind){
                t[v] = val;
            }
        }else{
            ll m = (l + r) / 2;
            if(ind < m){
                upd(2 * v, l, m, ind, val);
            }else{
                upd(2 * v + 1, m, r, ind, val);
            }
            t[v] = func(t[2 * v], t[2 * v + 1]);
        }
    }

};

int main(){
    input();
	ll i, n, q, x, y;
	string c;
	cin >> n;
	vector<ll> a(n);
	for(i = 0; i < n; i++){
        cin >> a[i];
	}
	SegTree t;
	t.init(n);
	t.build(1, 0, n, a);
	cin >> q;
	for(i = 0; i < q; i++){
        cin >> c >> x >> y;
        if(c == "g"){
            ll res = t.get(1, 0, n, x - 1, y);
            cout << res << " ";
        }else{
            t.upd(1, 0, n, x - 1, y);
        }
    }
    return 0;
}
