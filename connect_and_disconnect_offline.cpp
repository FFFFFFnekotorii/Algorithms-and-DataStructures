#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <deque>
#include <fstream>
#include <bitset>

using namespace std;

typedef long long int ll;
typedef long double ld;

#define    INF 1000000007
#define BIGINF 100000000700000
#define    LMT 1000000
#define  INPUT ios::sync_with_stdio(false);cin.tie(0);

#define    FST first
#define    SND second

//#define DEBUG
#ifndef ONLINE_JUDGE
	#define cout cerr
#else
	ifstream fin;
	ofstream fout;
	#define cin fin
	#define cout fout
#endif

namespace debug{

    void cause_runtime_error_if(const bool &f){
        vector<bool> v;
        if(f == true){
            v.at(727);
        }
    }

    void cause_time_limit_exceeding_if(const bool &f){
        if(f == true){
            for(int t = 1; t > 0; t++);
        }
    }

	template<typename T>
	void print_line(const vector<T>& a){
        for(auto elem : a){
			cout << elem << ' ';
		}
		cout << '\n';
    }
}

template<typename T>
void checkmin(T& a, const T& b){
	if(b < a){
		a = b;
	}
}

template<typename T>
void checkmax(T& a, const T& b){
	if(a < b){
		a = b;
	}
}

struct disjoint_set_union{
	vector<int> info;
	//info.at(i) >= 0 => info.at(i) = par.at(i)
	//info.at(i) < 0 => info.at(i) = rk.at(i)
	vector<pair<int, int>> changes;
	//info.at(FST) was SND

	void resize(int n){
		info.resize(n + 1);
		info.at(n) = n;
	}

	void make_set(int v){
		info.at(v) = -1;
	}

    void rollback(int k){
		while(changes.size() > k){
			info.at(changes.back().FST) = changes.back().SND;
			changes.pop_back();
		}
	}

	int find(int v){
		if(info.at(v) < 0){
			return v;
		}
		return find(info.at(v));
	}

	bool merge(int v, int u){
		int a, b;
		a = find(v);
		b = find(u);
		
		if(a == b){
			return false;
		}

		if(-info.at(a) < -info.at(b)){
			swap(a, b);
		}

		changes.push_back(make_pair(a, info.at(a)));
		changes.push_back(make_pair(b, info.at(b)));
		changes.push_back(make_pair(info.size() - 1, info.back()));
		info.at(a)--;
		info.at(b) = a;
		info.back()--;
		return true;
	}

	int components(){
		return info.back();
	}
};

struct event{
	int v, u, begin, end;

	event(){}
};

void process(int l, int r, vector<event>& events, disjoint_set_union& dsu){

	//cout << l << ' ' << r << '\n';
	//debug::print_line(dsu.info);
    
    if(r - l < 1){
        return ;
    }

	if(r - l == 1){
		if(events.at(l).v == -1){
		    //debug::print_line(dsu.info);
			cout << dsu.components() << '\n';
		}
		return ;
	}

	int m, i, cur_changes_count;
	m = (l + r) / 2;

	cur_changes_count = dsu.changes.size();

	for(i = m; i < r; i++){
		if(events.at(i).begin < l && events.at(i).end == i){
			dsu.merge(events.at(i).v, events.at(i).u);
		}
	}
	process(l, m, events, dsu);

	dsu.rollback(cur_changes_count);

	for(i = l; i < m; i++){
		if(events.at(i).begin == i && r <= events.at(i).end){
			dsu.merge(events.at(i).v, events.at(i).u);
		}
	}
	process(m, r, events, dsu);

    dsu.rollback(cur_changes_count);
}

void solve(){

	int n, q, i, v, u;
	vector<event> events;
	map<pair<int, int>, int> didnt_end;
	char ch;
	disjoint_set_union dsu;

	cin >> n >> q;

	dsu.resize(n);

	for(i = 0; i < n; i++){
		dsu.make_set(i);
	}

	events.resize(q);

	for(i = 0; i < q; i++){
		cin >> ch;
		if(ch == '?'){
			events.at(i).v = -1;
			events.at(i).u = -1;
			events.at(i).begin = i;
			events.at(i).end = i;
		}else{
			cin >> v >> u;
			v--, u--;

			if(v > u){
				swap(v, u);
			}
			events.at(i).v = v;
			events.at(i).u = u;

			if(ch == '+'){
				events.at(i).begin = i;
				events.at(i).end = q;
				didnt_end[make_pair(v, u)] = i;
			}else{
				events.at(didnt_end.at(make_pair(v, u))).end = i;
				events.at(i).begin = events.at(didnt_end.at(make_pair(v, u))).begin;
				events.at(i).end = i;
			}
		}
	}
	didnt_end.clear();

	process(0, q, events, dsu);

}

int main(){

    INPUT;

    int t;

	#ifdef ONLINE_JUDGE
		fin.open("connect.in");
		fout.open("connect.out");
	#endif

    for(t = 1; t; t--){
        solve();
    }

	#ifdef ONLINE_JUDGE
		fin.close();
		fout.close();
	#endif

	#ifndef ONLINE_JUDGE
		cerr << '\n';
		system("pause");
	#endif

    return 0;
}
