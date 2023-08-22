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

#define INF   1000000007
#define INF64 1000000000000000003LL
#define LMT   1000000
#define INPUT ios::sync_with_stdio(false);cin.tie(0);

#define FST   first
#define SND   second

#define MOD   998244353LL

#ifdef LOCAL
    #define cout cerr
#endif

template<typename T>
struct segment_tree {
	
	vector<T> tree, mod;
	vector<int> lt;
	int free_ind;
	
	segment_tree() {
		tree.push_back(0);
		mod.push_back(0);
		lt.push_back(-1);
		free_ind = tree.size();
	}
	
	void extend(int v, int lb, int rb) {
		if (lt[v] == -1) {
			int mid = lb + (rb - lb) / 2;
			
			lt[v] = free_ind;
			//rt[v] = lt[v] + 1
			tree.push_back(0);
			tree.push_back(0);
			mod.push_back(0);
			mod.push_back(0);
			lt.push_back(-1);
			lt.push_back(-1);
			
			free_ind += 2;
		}
	}
	
	void build(int v, int lb, int rb, vector<T>& a) {
		if (rb - lb == 1) {
			tree[v] = a[lb];
			return ;
		}
		extend(v, lb, rb);
		int mid = lb + (rb - lb) / 2;
		
		build(lt[v], lb, mid, a);
		build(lt[v] + 1, mid, rb, a);
		
		tree[v] = tree[lt[v]] + tree[lt[v] + 1];
	}
	
	void push(int v, int lb, int rb) {
		if (rb - lb == 1) {
			mod[v] = 0;
		}
		if (mod[v] == 0) {
			return ;
		}
		int mid = lb + (rb - lb) / 2;
		
		tree[lt[v]] += (mid - lb) * mod[v];
		mod[lt[v]] += mod[v];
		
		tree[lt[v] + 1] += (rb - mid) * mod[v];
		mod[lt[v] + 1] += mod[v];
		
		mod[v] = 0;
	}
	
	void add(int v, int lb, int rb, int ql, int qr, T val) {
		if (qr <= lb || rb <= ql) {
			return ;
		}
		//extend(v, lb, rb);
		push(v, lb, rb);
		if (ql <= lb && rb <= qr) {
			tree[v] += (rb - lb) * val;
			mod[v] = val;
			return ;
		}
		int mid = lb + (rb - lb) / 2;
		
		add(lt[v], lb, mid, ql, qr, val);
		add(lt[v] + 1, mid, rb, ql, qr, val);
		
		tree[v] = tree[lt[v]] + tree[lt[v] + 1];
	}
	
	ll get(int v, int lb, int rb, int ql, int qr) {
		if (qr <= lb || rb <= ql) {
			return 0;
		}
		//extend(v, lb, rb);
		push(v, lb, rb);
		if (ql <= lb && rb <= qr) {
			return tree[v];
		}
		int mid = lb + (rb - lb) / 2;
		
		return get(lt[v], lb, mid, ql, qr) + get(lt[v] + 1, mid, rb, ql, qr);
	}
	
};

void solve() {
	
	int n, q, i, lb, rb;
	ll val;
	char t;
	vector<ll> a;
	segment_tree<ll> st;
	
	cin >> n;
	
	a.resize(n);
	for (i = 0; i < n; i++) {
		cin >> a[i];
	}
	st.build(0, 0, n, a);
	
	for (cin >> q; q; q--) {
		cin >> t >> lb;
		lb--;
		
		if (t == 'g') {
			
			cout << st.get(0, 0, n, lb, lb + 1) << '\n';
		} else {
			cin >> rb >> val;
			
			st.add(0, 0, n, lb, rb, val);
		}
	}
	
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
