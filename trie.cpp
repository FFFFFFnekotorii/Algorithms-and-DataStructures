#pragma GCC optimize("O3")
#pragma GCC target("avx2")

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <cstring>
#include <deque>
#include <map>

#define iter vector<long long int>::iterator
#define input() ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

typedef long long int ll;

ll inf = 1000000007;

struct node{
    ll term = 0;
    ll exist[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    node* to[26];
};

struct trie{
    node* root = new node();

    void add(string s){
        node* cur = root;
        for(auto i : s){
            ll c = i - 'a';
            if(cur->exist[c] == 0){
                cur->exist[c] = 1;
                cur->to[c] = new node();
            }
            cur = cur->to[c];
        }
        cur->term += 1;
    }
};

int main(){
    return 0;
}
