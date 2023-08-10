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

struct Node{
    ll key, prior;
    Node *l = nullptr, *r = nullptr;

    Node(ll k){
        key = k;
        prior = rand();
    }

};

Node* merge(Node* l, Node* r){
    if(l == nullptr){
        return r;
    }
    if(r == nullptr){
        return l;
    }
    if(l->prior > r->prior){
        l->r = merge(l->r, r);
        return l;
    }else{
        r->l = merge(l, r->l);
        return r;
    }
}

pair<Node*, Node*> split(Node* t, ll val){
    if(t == nullptr){
        return make_pair(nullptr, nullptr);
    }
    if(t->key < val){
        auto [lt, rt] = split(t->r, val);
        t->r = lt;
        return make_pair(t, rt);
    }else{
        auto [lt, rt] = split(t->l, val);
        t->l = rt;
        return make_pair(lt, t);
    }
}

ll min(Node* t){
    if(t == nullptr){
        return 0;
    }
    if(t->l == nullptr){
        return t->key;
    }
    return min(t->l);
}

ll max(Node* t){
    if(t == nullptr){
        return 0;
    }
    if(t->r == nullptr){
        return t->key;
    }
    return max(t->r);
}

Node* insert(Node* t, ll val){
    auto [lt, rt] = split(t, val);
    Node *node = new Node(val);
    return merge(lt, merge(node, rt));
}

Node* erase(Node* t, ll val){
    auto [mt, rt] = split(t, val + 1);
    auto [lt, _] = split(mt, val);
    return merge(lt, rt);
}

int main(){
    input();
    Node *t = nullptr;
    t = insert(t, 1);
    t = insert(t, 2);
    t = insert(t, 3);
    t = insert(t, 4);
    t = insert(t, 5);
    t = insert(t, 6);
    t = insert(t, 7);
    cout << t->key << "\n";
    t = erase(t, 5);
    cout << t->key;
    return 0;
}
