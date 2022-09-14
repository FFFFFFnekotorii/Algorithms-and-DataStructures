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

#define FST first
#define SND second

#define BASE 1000000000

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

struct big_integer{
    vector<int> digits;

    big_integer(){
        digits.clear();
        digits.push_back(0);
    }

    void add(int n){
        int i, carry;
        for(i = 0, carry = 0; n > 0; i++, n /= BASE){
            if(i == digits.size()){
                digits.push_back(0);
            }
            if(digits.at(i) + (n % BASE) + carry >= BASE){
                digits.at(i) = digits.at(i) + (n % BASE) + carry - BASE;
                carry = 1;
            }else{
                digits.at(i) = digits.at(i) + (n % BASE) + carry;
                carry = 0;
            }
        }
    }

    void add(big_integer p){
        int i, carry;
        digits.push_back(0);
        if(digits.size() < p.digits.size()){
            digits.resize(p.digits.size(), 0);
        }else{
            p.digits.resize(digits.size(), 0);
        }

        for(i = 0, carry = 0; i < min(digits.size(), p.digits.size()); i++){
            if(digits.at(i) + p.digits.at(i) + carry >= BASE){
                digits.at(i) = digits.at(i) + p.digits.at(i) + carry - BASE;
                carry = 1;
            }else{
                digits.at(i) = digits.at(i) + p.digits.at(i) + carry;
                carry = 0;
            }
        }

        while(digits.size() > 0 && digits.back() == 0){
            digits.pop_back();
        }
        if(digits.size() == 0){
            digits.push_back(0);
        }

    }

    void sub(big_integer p){

        int i, carry;
        if(p.digits.size() <= digits.size()){
            p.digits.resize(digits.size(), 0);
        }else{
            //debug::cause_time_limit_exceeding_if(true);
        }

        for(i = 0, carry = 0; i < digits.size(); i++){
            if(digits.at(i) - p.digits.at(i) - carry < 0){
                digits.at(i) = digits.at(i) - p.digits.at(i) - carry + BASE;
                carry = 1;
            }else{
                digits.at(i) = digits.at(i) - p.digits.at(i) - carry;
                carry = 0;
            }
        }
        while(digits.size() > 0 && digits.back() == 0){
            digits.pop_back();
        }
        if(digits.size() == 0){
            digits.push_back(0);
        }

    }


    string stringify(){
        int i;
        string s, t;
        s = to_string(digits.back());
        for(i = digits.size() - 2; i > -1; i--){
            t = to_string(digits.at(i));
            while(t.size() < 9){
                t = '0' + t;
            }
            s += t;
        }
        return s;
    }

};

void solve(){

    int n, k, i;
    vector<big_integer> dp, pref_sum;

    cin >> n >> k;

    dp.resize(n + 1, big_integer());
    pref_sum.resize(n + 2, big_integer());

    dp.at(0).add(1);
    pref_sum.at(0);
    pref_sum.at(1).add(1);

    for(i = 1; i < k + 1; i++){
        dp.at(i - 1).digits.clear();
        //delete(&dp.at(i - 1));

        dp.at(i).add(pref_sum.at(i));
        dp.at(i).add(1);

        pref_sum.at(i + 1).add(pref_sum.at(i));
        pref_sum.at(i + 1).add(dp.at(i));

    }

    for(i = k + 1; i < n + 1; i++){
        dp.at(i - 1).digits.clear();
        //delete(&dp.at(i - 1));

        dp.at(i).add(pref_sum.at(i));
        dp.at(i).sub(pref_sum.at(i - (k + 1)));

        pref_sum.at(i - (k + 1)).digits.clear();
        //delete(&pref_sum.at(i - (k + 1)));

        pref_sum.at(i + 1).add(pref_sum.at(i));
        pref_sum.at(i + 1).add(dp.at(i));
    }


    #ifdef DEBUG

    for(i = 0; i < n + 1; i++){
        cout << dp.at(i).stringify() << ' ';
    }cout << '\n';

    #endif // DEBUG

    cout << dp.at(n).stringify();
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
