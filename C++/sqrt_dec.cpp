#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <deque>
#include <fstream>

using namespace std;

typedef long long int ll;
typedef long double ld;

#define INF 1000000007
#define BIGINF 100000000700000
#define LMT 1000000
#define INPUT ios::sync_with_stdio(false);cin.tie(0);

//#define DEBUG

namespace debug{

    void cause_runtime_error_if(const bool &f){
        vector<int> v;
        if(f == true){
            v.at(727);
        }
    }

    void cause_time_limit_exceeding_if(const bool &f){
        if(f == true){
            for(int t = 1; t > 0; t++);
        }
    }

}

struct sqrt_dec{

    ll bsize = 200, elems;
    vector<vector<ll>> blocks;
    vector<vector<ll>> cnt;
    vector<ll> sz;

    sqrt_dec(){}

    void resize(ll n){
        elems = n;
        blocks.resize((n + bsize - 1) / bsize);
        cnt.resize((n + bsize - 1) / bsize, vector<ll>(26));
        sz.resize((n + bsize - 1) / bsize, 0);
    }

    void init(vector<ll>::iterator fst, vector<ll>::iterator lst){
        ll i;
        for(i = 0; fst != lst; fst++, i++){
            blocks[i / bsize].push_back(*fst);
            cnt[i / bsize][*fst]++;
            sz[i / bsize]++;
        }
    }

    void show(){
        ll i, j;
        for(i = 0; i < blocks.size(); i++){
            for(j = 0; j < blocks[i].size(); j++){
                cout << blocks[i][j] << ' ';
            }
            cout << '\n';
        }
    }

    ll front(){
        while(sz.front() == 0){
            blocks.erase(blocks.begin());
            cnt.erase(cnt.begin());
            sz.erase(sz.begin());
        }
        return blocks.front().front();
    }

    ll back(){
        while(sz.back() == 0){
            blocks.pop_back();
            cnt.pop_back();
            sz.pop_back();
        }
        return blocks.back().back();
    }

    void pop_ind(ll ind){
        ll i, n, c;

        n = blocks.size(), c = 0;
        for(i = 0; i < n; i++){
            if(ind - c < sz[i]){
                cnt[i][blocks[i][ind - c]]--;
                sz[i]--;
                blocks[i].erase(blocks[i].begin() + (ind - c));
                elems--;
                return ;
            }
            c += sz[i];
        }

    }

    ll find_left(ll k){
        ll i, j, n, c;

        n = blocks.size(), c = 0;
        for(i = 0; i < n; i++){
            if(cnt[i][k] > 0){
                for(j = 0; j < sz[i]; j++){
                    if(blocks[i][j] == k){
                        return c + j;
                    }
                }

                return -1;
            }
            c += sz[i];
        }

        return -1;
    }

    ll find_right(ll k){
        ll i, j, n, c;

        n = blocks.size(), c = 0;
        for(i = n - 1; i > -1; i--){
            if(cnt[i][k] > 0){
                for(j = sz[i] - 1; j > -1; j--){
                    if(blocks[i][j] == k){
                        return elems - c - sz[i] + j;
                    }
                }
                return -1;
            }
            c += sz[i];
        }

        return -1;
    }

};

void solve(){



}

int main(){

    INPUT;

    ll t;

    t = 1;

    while(t--){
        solve();
    }

    return 0;
}
