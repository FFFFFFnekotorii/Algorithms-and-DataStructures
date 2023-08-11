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

struct binominal{
    ll a, b, p;
    binominal(ll _a, ll _b, ll _p){
        a = _a;
        b = _b;
        p = _p;
    }
};

struct trinominal{
    ll a, b, c, p;
    trinominal(ll _a, ll _b, ll _c, ll _p){
        a = _a;
        b = _b;
        c = _c;
        p = _p;
    }
};

trinominal mul(binominal f, binominal g){
    return trinominal((f.a * g.a) % f.p, (f.a * g.b + f.b * g.a) % f.p, (f.b * g.b) % f.p, f.p);
}

binominal mod(trinominal f, trinominal g){
    return binominal((((f.b - f.a * g.b) % f.p) + f.p) % f.p, (((f.c - f.a * g.c) % f.p) + f.p) % f.p, f.p);
}

binominal binpow(binominal f, ll n, trinominal g){
    if(n == 1){
        return f;
    }
    if(n % 2 == 0){
        binominal h = binpow(f, n / 2, g);
        return mod(mul(h, h), g);
    }
    binominal h = binpow(f, n - 1, g);
    return mod(mul(h, f), g);
}

ll binpow(ll a, ll n, ll p){
    if(n == 0){
        return 1;
    }
    if(n % 2 == 0){
        ll h = binpow(a, n / 2, p);
        return (h * h) % p;
    }
    ll h = binpow(a, n - 1, p);
    return (a * h) % p;
}

ll Legendre(ll a, ll p){
    return binpow(a, (p - 1) / 2, p);
}

void solve(){
    ll a, p, i, x1, x2;
    cin >> a >> p;
    a %= p;
    if(p == 2){
        cout << a << "\n";
        return ;
    }
    if(Legendre(a, p) != 1){
        cout << "No root\n";
        return ;
    }
    for(i = 0; i < 20; i++){
        binominal f = binpow(binominal(1, i, p), (p - 1) / 2, trinominal(1, 0, -a, p));
        if(f.a != 0){
            f.b -= 1;
            x1 = ((f.b * binpow(f.a, p - 2, p) % p) + p) % p;
            x2 = p - x1;
            if(x1 > x2){
                swap(x1, x2);
            }
            if(binpow(x1, 2, p) == a){
                cout << x1 << " " << x2 << "\n";
                return ;
            }
        }
    }
}

int main(){
    input();
    ll t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
