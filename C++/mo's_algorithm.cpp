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
 
#include <cassert>
 
using namespace std;
 
typedef long long int ll;
typedef long double ld;
 
#define    INF 1000000007
#define  INF64 1000000000000000003LL
#define    LMT 15000727
#define  INPUT ios::sync_with_stdio(false); cin.tie(0);
 
#define    FST first
#define    SND second
 
#define    MOD 998244353LL
 
//#define DEBUG
//#define ONLINE_JUDGE
 
#ifndef ONLINE_JUDGE
    #define cout cerr
#endif
 
template<int k>
struct sqrt_dec {
     
    vector<int> sum, values;
     
    void resize(int n) {
        sum.resize((n + k - 1) / k);
        values.resize(n);
    }
    
    void add(int ind, int val) {
        sum[ind / k] += val;
        values[ind] += val;
    }
    
    void clear() {
        fill(begin(sum), end(sum), 0);
        fill(begin(values), end(values), 0);
    }
    
    int find_first_non_zero() {
        int i, j;
        for (i = 0; i < sum.size(); i++) {
            if (sum[i] > 0) {
                for (j = 0; j < k; j++) {
                    if (values[i * k + j] != 0) {
                        return i * k + j;
                    }
                }
                return -1;
            }
        }
        return -1;
    }
    
};

struct cute_data_structure {
    
    vector<int> ind_if_sorted, sorted;
    sqrt_dec<205> owo;
    
    void build(vector<int>& a) {
        int i, n, last, x;
        vector<pair<int, int>> elems;
        
        n = a.size();
        
        elems.resize(n);
        ind_if_sorted.resize(n);
        
        sorted.reserve(n);
    
        for (i = 0; i < n; i++) {
            elems[i].FST = a[i];
            elems[i].SND = i;
        }
        
        sort(begin(elems), end(elems));
        
        last = -1;
        x = -1;
        for (i = 0; i < n; i++) {
            if (elems[i].FST != last) {
                x++;
                sorted.push_back(elems[i].FST);
            }
            ind_if_sorted[elems[i].SND] = x;
            last = elems[i].FST;
        }
        
        owo.resize(sorted.size());
    }
    
    void add(int ind) {
        owo.add(ind_if_sorted[ind], 1);
    }
    
    void del(int ind) {
        owo.add(ind_if_sorted[ind], -1);
    }
    
    int get_ans() {
        return sorted[owo.find_first_non_zero()];
    }
    
    void clear() {
        owo.clear();
    }
    
};
 
template<int k>
struct query {
     
    int lb, rb, ind;
     
    bool operator<(query other) {
        if (rb == other.rb) {
            return lb < other.lb;
        }
        return rb < other.rb;
    }
    
    query(int lb0, int rb0, int ind0) {
        lb = lb0;
        rb = rb0;
        ind = ind0;
    }
    
};
 
template<int k, typename inner_data_structure>
struct queries {
     
    vector<vector<query<k>>> q;
    
    inner_data_structure uwu;
    
    void build_inner_structure(vector<int>& a) {
        uwu.build(a);
    }
    
    void resize(int n) {
        q.resize((n + k - 1) / k);
    }
    
    void insert(int lb, int rb, int ind) {
        q[lb / k].emplace_back(lb, rb, ind);
    }
    
    void run(vector<int>& ans) {
        int lb, rb, i, j, ql, qr;
         
        for (i = 0; i < q.size(); i++) {
            sort(begin(q[i]), end(q[i]));
        }
         
        for (i = 0; i < q.size(); i++) {
             
            if (q[i].empty()) {
                continue;
            }
            
            lb = i * k;
            rb = i * k;
            uwu.add(lb);
            
            for (j = 0; j < q[i].size(); j++) {
                
                ql = q[i][j].lb;
                qr = q[i][j].rb;
                
                while (rb < qr) {
                    rb++;
                    uwu.add(rb);
                }
                
                while (lb < ql) {
                    uwu.del(lb);
                    lb++;
                }
                
                while (ql < lb) {
                    lb--;
                    uwu.add(lb);
                }
                
                ans[q[i][j].ind] = uwu.get_ans();
            }
            
            uwu.clear();
            
        }
        
    }
    
};
 
void solve() {
     
    int n, i, m, lb, rb;
    vector<int> a, ans;
    queries<205, cute_data_structure> q;
    
    cin >> n;
    
    a.resize(n);
    q.resize(n);
    
    for (i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    q.build_inner_structure(a);
    
    cin >> m;
    
    ans.resize(m);
    
    for (i = 0; i < m; i++) {
        cin >> lb >> rb;
        //segments [lb; rb], NOT [lb; rb)
        lb--, rb--;
         
        q.insert(lb, rb, i);
    }
    
    q.run(ans);
    
    for (i = 0; i < m; i++) {
        cout << ans[i] << ' ';
    }
    
}
 
int main() {
 
    #ifdef ONLINE_JUDGE
        INPUT;
    #endif
 
    int t;
 
    for (t = 1; t; t--) {
        solve();
    }
 
    #ifndef ONLINE_JUDGE
        cerr << '\n';
        system("pause");
    #endif
 
    return 0;
}
