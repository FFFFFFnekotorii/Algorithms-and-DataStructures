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

ll binpow(ll a, ll n, ll m){
    if(n == 0){
        return 1;
    }
    if(n % 2 == 0){
        ll res = binpow(a, n / 2, m);
        return (res * res) % m;
    }
    if(n % 2 ==  1){
        return (a * binpow(a, n - 1, m)) % m;
    }
}

ll Legendre(ll a, ll p){
    if(a % p == 0){
        return 0;
    }
    return binpow(a, (p - 1) / 2, p);
}

int main(){
    input();
    ll t, n, p;
    cin >> t;
    while(t--){
        cin >> n >> p;
        n %= p;
        if(Legendre(n, p) == 1){
            ll x1, x2;
            if(p % 4 == 3){
                x1 = binpow(n, (p + 1) / 4, p);
            }else{
                ll q = 2, s, t = 0, a, b, d, h, k, i;
                while(Legendre(q, p) != p - 1){
                    q++;
                }
                s = p - 1;
                while(s % 2 == 0){
                    s /= 2;
                    t += 1;
                }
                a = binpow(q, s, p);
                b = binpow(n, s, p);
                h = 1;
                for(i = 1; i < t; i++){
                    d = binpow(b, binpow(2, t - 1 - i, p - 1), p);
                    if(d == 1){
                        k = 0;
                    }else{
                        k = 1;
                    }
                    b = (b * binpow(a, 2 * k, p)) % p;
                    h = (h * binpow(a, k, p)) % p;
                    a = binpow(a, 2, p);
                }
                x1 = (binpow(n, (s + 1) / 2, p) * h) % p;
            }
            x2 = p - x1;
            if(x1 > x2){
                swap(x1, x2);
            }
            if(x1 == x2){
                cout << x1 << "\n";
            }else{
                cout << x1 << " " << x2 << "\n";
            }
        }else{
            cout << "No root\n";
        }
    }
    return 0;
}
