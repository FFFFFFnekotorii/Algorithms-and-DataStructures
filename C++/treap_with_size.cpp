#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <cstring>
#include <deque>
#include <map>
#include <random>

#define iter vector<long long int>::iterator
#define input() ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

typedef long long int ll;

struct Node{
    ll key, prior;
    Node *l = nullptr, *r = nullptr;
    ll sz = 0;

    Node(ll k){
        key = k;
        sz = 1;
        prior = rand();
    }

};

ll size(Node *t){
    if(t == nullptr){
        return 0;
    }
    ll ls = 0, rs = 0;
    if(t->l != nullptr){
        ls = (t->l)->sz;
    }
    if(t->r != nullptr){
        rs = (t->r)->sz;
    }
    return ls + rs + 1;
}

Node* merge(Node *l, Node *r){
    if(l == nullptr){
        return r;
    }
    if(r == nullptr){
        return l;
    }
    if(l->prior > r->prior){
        l->r = merge(l->r, r);
        l->sz = size(l);
        return l;
    }else{
        r->l = merge(l, r->l);
        r->sz = size(r);
        return r;
    }
}

pair<Node*, Node*> split(Node *t, ll val){
    if(t == nullptr){
        return make_pair(nullptr, nullptr);
    }
    if(val <= t->key){
        auto [lt, rt] = split(t->l, val);
        t->l = rt;
        t->sz = size(t);
        return make_pair(lt, t);
    }else{
        auto [lt, rt] = split(t->r, val);
        t->r = lt;
        t->sz = size(t);
        return make_pair(t, rt);
    }
}

Node* insert(Node *t, ll val){
    auto [lt, rt] = split(t, val);
    Node *node = new Node(val);
    return merge(lt, merge(node, rt));
}

ll min(Node *t){
    if(t->l == nullptr){
        return t->key;
    }
    return min(t->l);
}

ll count_less_equal(Node *t, ll val){
    if(t == nullptr){
        return 0;
    }
    if(t->key <= val){
        //all keys in left <= val
        return size(t->l) + count_less_equal(t->r, val) + 1;
    }else{
        //otherwise val < all keys in right
        return count_less_equal(t->l, val);
    }
}

int main(){
    input();
    ll n, i, cur;
    Node *t = nullptr;
    cin >> n;
    for(i = 0; i < n; i++){
        cin >> cur;
        t = insert(t, cur);
    }
    cout << size(t) << "\n";
    cout << min(t) << "\n";
    cout << count_less_equal(t, 5) << "\n";
    return 0;
}
