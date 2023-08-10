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

struct Point{
    ll x, y, ind = -1;
};

ll operator^(Point a, Point b){
    return a.x * b.y - a.y * b.x;
}

Point operator-(Point a, Point b){
    Point c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return c;
}

bool cmp(Point a, Point b){
    return a.x > b.x;
}

vector<Point> lower_envelope_hull(vector<Point> &q){
    ll n = q.size(), i, k = 0;
    sort(q.begin(), q.end(), cmp);
    vector<Point> st;
    for(i = 0; i < n; i++){
        while(k >= 2){
            if(((q[i] - st[k - 1]) ^ (st[k - 2] - st[k - 1])) > 0){
                st.pop_back();
                k--;
            }else{
                break;
            }
        }
        st.push_back(q[i]);
        k++;
    }
    return st;
}

vector<Point> upper_envelope_hull(vector<Point> &q){
    ll n = q.size(), i, k = 0;
    sort(q.begin(), q.end(), cmp);
    vector<Point> st;
    for(i = 0; i < n; i++){
        while(k >= 2){
            if(((q[i] - st[k - 1]) ^ (st[k - 2] - st[k - 1])) < 0){
                st.pop_back();
                k--;
            }else{
                break;
            }
        }
        st.push_back(q[i]);
        k++;
    }
    return st;
}

vector<Point> build_convex_hull(const vector<Point> &p){
    ll n = p.size(), i, a, b;
    a = 0;
    b = n - 1;
    for(i = 0; i < n; i++){
        if(p[i].x == p[a].x){
            if(p[i].y < p[a].y){
                a = i;
            }
        }
        if(p[i].x < p[a].x){
            a = i;
        }
        if(p[i].x == p[b].x){
            if(p[i].y > p[b].y){
                b = i;
            }
        }
        if(p[i].x > p[b].x){
            b = i;
        }
    }
    vector<Point> upper, lower;
    upper.push_back(p[a]);
    lower.push_back(p[a]);
    for(i = 0; i < n; i++){
        if(((p[i] - p[a]) ^ (p[b] - p[a])) < 0){
            upper.push_back(p[i]);
        }
        if(((p[i] - p[a]) ^ (p[b] - p[a])) > 0){
            lower.push_back(p[i]);
        }
    }
    upper.push_back(p[b]);
    lower.push_back(p[b]);
    vector<Point> lo = lower_envelope_hull(lower);
    vector<Point> up = upper_envelope_hull(upper);
    vector<Point> res;
    for(auto pt : lo){
        res.push_back(pt);
    }
    for(auto pt : up){
        res.push_back(pt);
    }
    return res;
}

int main(){
    input();
    ll c, i, n, k;
    cin >> n;
    vector<Point> p(n);
    for(i = 0; i < n; i++){
        cin >> p[i].x >> p[i].y;
        p[i].ind = i;
    }
    vector<Point> unordered_convex_hull = build_convex_hull(p);
    vector<bool> included(n, false);
    for(Point pt : unordered_convex_hull){
        included[pt.ind] = true;
    }
    k = 0;
    vector<Point> convex_hull;
    for(i = 0; i < n; i++){
        if(included[i] == true){
            k++;
            convex_hull.push_back(p[i]);
        }
    }
    cout << k << "\n";
    for(i = 0; i < k; i++){
        cout << convex_hull[i].x << " " << convex_hull[i].y << "\n";
    }
    return 0;
}
