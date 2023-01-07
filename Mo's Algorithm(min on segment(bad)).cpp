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

template<int k>
struct queries {
	
	vector<vector<query<k>>> q;
	vector<int> ans;
	
	int cur_min;
	vector<int> cnt;
	vector<int> a;
	
	queries() {}
	
	void add(int ind) {
		cnt[a[ind]]++;
		
		if (a[ind] < cur_min) {
			cur_min = a[ind];
		}
	}
	
	void del(int ind) {
		cnt[a[ind]]--;
		
		if (cnt[a[ind]] == 0 && a[ind] == cur_min) {
			int cur;
			
			for (cur = a[ind]; cnt[cur] == 0; cur++);
			
			cur_min = cur;
		}
	}
	
	void clear() {
		fill(begin(cnt), end(cnt), 0);
	}
	
	void resize(int n) {
		q.resize((n + k - 1) / k);
		cnt.resize(n);
	}
	
	void insert(int lb, int rb, int ind) {
		q[lb / k].emplace_back(lb, rb, ind);
	}
	
	void run() {
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
			cur_min = INF;
			add(lb);
			
			for (j = 0; j < q[i].size(); j++) {
				
				ql = q[i][j].lb;
				qr = q[i][j].rb;
				
				while (rb < qr) {
					rb++;
					add(rb);
				}
				
				while (lb < ql) {
					del(lb);
					lb++;
				}
				
				while (ql < lb) {
					lb--;
					add(lb);
				}
				
				//cout << q[i][j].lb << ' ' << q[i][j].rb << ' ' << cur_min << ' ' << lb << ' ' << rb << '\n';
				
				ans[q[i][j].ind] = cur_min;
				
			}
			
			clear();
			
		}
		
	}
	
};

void solve() {
	
	int n, i, m, lb, rb, last, x;
	vector<int> b, c;
	vector<pair<int, int>> a;
	queries<375> q;
	
	cin >> n;
	
	a.resize(n);
	b.resize(n);
	
	c.reserve(n);
	
	for (i = 0; i < n; i++) {
		cin >> a[i].FST;
		a[i].SND = i;
	}
	
	sort(begin(a), end(a));
	
	last = -1;
	x = -1;
	for (i = 0; i < n; i++) {
		if (a[i].FST != last) {
			x++;
			c.push_back(a[i].FST);
		}
		b[a[i].SND] = x;
		last = a[i].FST;
	}
	
	/*
	for (i = 0; i < n; i++) {
		cout << b[i] << '\n';
	}
	cout << '\n';
	*/
	
	/*
	for (i = 0; i < c.size(); i++) {
		cout << c[i] << ' ';
	}
	cout << '\n';
	*/
	
	cin >> m;
	
	q.resize(n);
	
	for (i = 0; i < m; i++) {
		cin >> lb >> rb;
		lb--, rb--;
		
		q.insert(lb, rb, i);
	}
	
	q.a = b;
	q.ans.resize(m);
	
	q.run();
	
	for (i = 0; i < m; i++) {
		cout << c[q.ans[i]] << ' ';
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

/*
5
1 2 3 4 5
5
1 1
1 4
2 5
4 5
3 3
===
5
1 2 2 3 4
3
1 1
2 3
4 4
*/
