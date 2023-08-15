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

template<int alphabet_size, int default_value = 0>
struct trie {
    vector<vector<int>> to;
	vector<int> term;
	int free_ind;
	
	trie() {
		to.push_back(vector<int>(alphabet_size, -1));
		term.push_back(default_value);
		
		free_ind = 1;
	}
	
	void add(vector<int>& word, int x) {
		int cur;
		
		cur = 0;
		for (int& c : word) {
			if (to[cur][c] == -1) {
				to[cur][c] = free_ind++;
				to.push_back(vector<int>(alphabet_size, -1));
				term.push_back(default_value);
			}
			cur = to[cur][c];
		}
		term[cur] = x;
	}
	
	int find(vector<int>& word) {
		int cur;
		
		cur = 0;
		for (int& c : word) {
			if (to[cur][c] == -1) {
				return 0;
			}
			cur = to[cur][c];
		}
		return term[cur];
	}
	
	int& operator[](vector<int>& word) {
		//creates nodes in any case
		//***
		//trie<cnst> t;
		//t[{1, 3, 3, 7}] = 1
		//int v = t[{1, 0, 0, 0, 0, 0, 0, 0, 0, 7}];
		//***
		//creates 2 words and 14 nodes correspondingly
		int cur;
		
		cur = 0;
		for (int& c : word) {
			if (to[cur][c] == -1) {
				to[cur][c] = free_ind++;
				to.push_back(vector<int>(alphabet_size, -1));
				term.push_back(default_value);
			}
			cur = to[cur][c];
		}
		return term[cur];
	}
};

void solve() {
	
	trie<10> t;
	vector<int> s;
	
	s = {4, 5};
	
	//add, find
	
	t.add(s, 727);
	
	cout << t.find(s) << '\n';
	
	//operator[]
	
	cout << t[s] << '\n';
	
	t[s] = 1337;
	
	cout << t[s] << '\n';
	
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
