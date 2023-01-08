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

#define    INF 1000000007
#define  INF64 1000000000000000003LL
#define    LMT 1000000
#define  INPUT ios::sync_with_stdio(false); cin.tie(0);

#define    FST first
#define    SND second

#define    MOD 998244353LL

//#define DEBUG
//#define ONLINE_JUDGE

#ifndef ONLINE_JUDGE
    #define cout cerr
#endif

mt19937 rnd(time(0));

struct treap {
	
	struct node {
	
		int key, prior;
		node *lt, *rt;
		
		node() {
			lt = nullptr;
			rt = nullptr;
		}
		
		node(int key0) {
			key = key0;
			prior = rnd();
			lt = nullptr;
			rt = nullptr;
		}
		
	};
	
	node* root;
	
	treap() {
		root = nullptr;
	}
	
	node* merge(node* lt, node* rt) {
		if (lt == nullptr) {
			return rt;
		}
		if (rt == nullptr) {
			return lt;
		}
		if (lt->prior < rt->prior) {
			lt->rt = merge(lt->rt, rt);
			return lt;
		} else {
			rt->lt = merge(lt, rt->lt);
			return rt;
		}
	}
	
	pair<node*, node*> split(node* t, int val) {
		if (t == nullptr) {
			return make_pair(nullptr, nullptr);
		}
		if (val <= t->key) {
			pair<node*, node*> p = split(t->lt, val);
			t->lt = p.SND;
			return make_pair(p.FST, t);
		} else {
			pair<node*, node*> p = split(t->rt, val);
			t->rt = p.FST;
			return make_pair(t, p.SND);
		}
	}
	
	void insert(int val) {
		pair<node*, node*> p = split(root, val);
		node* t = new node(val);
		root = merge(p.FST, merge(t, p.SND));
	}
	
	void erase(int val) {
		pair<node*, node*> p1 = split(root, val + 1);
		pair<node*, node*> p2 = split(p1.FST, val);
		root = merge(p2.FST, p1.SND);
	}
	
	int min_element(node* t) {
		if (t->lt == nullptr) {
			return t->key;
		}
		return min_element(t->lt);
	}
	
	int min_element() {
		return min_element(root);
	}
	
};
