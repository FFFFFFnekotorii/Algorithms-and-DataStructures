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
#define    LMT 10000000
#define  INPUT ios::sync_with_stdio(false); cin.tie(0);

#define    FST first
#define    SND second

#define    MOD 998244353LL

#ifdef LOCAL
    #define cout cerr
#endif

template<typename keytype>
struct treap {
	
	treap *l = nullptr, *r = nullptr;
	keytype key;
	int prior, size;
	
	treap(keytype key0) {
		key = key0;
		prior = rand() * rand() + rand();
		size = 1;
	}
	
};

template<typename keytype>
treap<keytype>* merge(treap<keytype>* lt, treap<keytype>* rt) {
	if (lt == nullptr) {
		return rt;
	}
	if (rt == nullptr) {
		return lt;
	}
	
	if (lt->prior < rt->prior) {
		rt->l = merge(lt, rt->l);
		rt->size = size(rt);
		return rt;
	} else {
		lt->r = merge(lt->r, rt);
		lt->size = size(lt);
		return lt;
	}
}

template<typename keytype>
pair<treap<keytype>*, treap<keytype>*> split(treap<keytype>* t, keytype val) {
	if (t == nullptr) {
		return make_pair(nullptr, nullptr);
	}
	
	if (t->key < val) {
		auto [lt, rt] = split(t->r, val);
		t->r = lt;
		t->size = size(t);
		return make_pair(t, rt);
	} else {
		auto [lt, rt] = split(t->l, val);
		t->l = rt;
		t->size = size(t);
		return make_pair(lt, t);
	}
}

template<typename keytype>
treap<keytype>* insert(treap<keytype>* t, keytype val) {
	auto [lt, rt] = split(t, val);
	treap<keytype> *node = new treap<keytype>(val);
	return merge(merge(lt, node), rt);
}

template<typename keytype>
treap<keytype>* erase(treap<keytype>* t, keytype val) {
	auto [lt, mt] = split(t, val);
	auto [_, rt] = split(mt, val + 1);
	return merge(lt, rt);
}

template<typename keytype>
void elems(treap<keytype>* t) {
	if (t == nullptr) {
		return ;
	}
	elems(t->l);
	cout << t->key << ' ';
	elems(t->r);
}

template<typename keytype>
int size(treap<keytype>* t) {
	int ls, rs;
	if (t == nullptr) {
		return 0;
	}
	if (t->l != nullptr) {
		ls = t->l->size;
	} else {
		ls = 0;
	}
	if (t->r != nullptr) {
		rs = t->r->size;
	} else {
		rs = 0;
	}
	return ls + rs + 1;
}

template<typename keytype>
int count_less(treap<keytype>* t, keytype val) {
	if (t == nullptr) {
		return 0;
	}
	if (t->key < val) {
		return size(t->l) + count_less(t->r, val) + 1;
	} else {
		return count_less(t->l, val);
	}
}

template<typename keytype>
int count_greater(treap<keytype>* t, keytype val) {
	if (t == nullptr) {
		return 0;
	}
	if (t->key < val) {
		return count_greater(t->r, val);
	} else {
		return count_greater(t->l, val) + size(t->r) + 1;
	}
}

void solve () {
    
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
