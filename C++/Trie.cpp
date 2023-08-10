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

struct node{
    ll term = 0;
    node* to[26];
};

struct Trie{
    node* root = new node();

    void add(string s){
        node* cur = root;
        for(auto i : s){
            ll c = i - 'a';
            if(cur->to[c] == nullptr){
                cur->to[c] = new node();
            }
            cur = cur->to[c];
        }
        cur->term += 1;
    }

    ll count(string s){
        node* cur = root;
        ll res = 0;
        for(auto i : s){
            ll c = i - 'a';
            if(cur->to[c] == nullptr){
                res = 0;
                break;
            }
            cur = cur->to[c];
            res = cur->term;
        }
        return res;
    }
};

int main(){
    input();
    return 0;
}
