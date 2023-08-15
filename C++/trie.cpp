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

struct trie {
    vector<vector<int>> to;
	vector<int> term;
	int free_ind;
	
	trie() {
		to.push_back(vector<int>(10, -1));
		term.push_back(-1);
		
		free_ind = 1;
	}
	
	void add(string& s, int x) {
		int cur;
		
		cur = 0;
		for (char c : s) {
			if (to[cur][c - '0'] == -1) {
				to[cur][c - '0'] = free_ind++;
				to.push_back(vector<int>(10, -1));
				term.push_back(-1);
			}
			cur = to[cur][c - '0'];
		}
		term[cur] = x;
	}
	
	int find(string& s) {
		int cur;
		
		cur = 0;
		for (char c : s) {
			if (to[cur][c - '0'] == -1) {
				return 0;
			}
			cur = to[cur][c - '0'];
		}
		return term[cur];
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
