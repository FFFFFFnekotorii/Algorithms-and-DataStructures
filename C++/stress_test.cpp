#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <deque>
#include <fstream>
#include <sstream>

using namespace std;

typedef long long int ll;
typedef long double ld;

#define INF 1000000007
#define BIGINF 100000000700000
#define LMT 1000000
#define INPUT ios::sync_with_stdio(false);cin.tie(0);

namespace debug{

    void cause_runtime_error_if(const bool &f){
        vector<bool> v;
        if(f == true){
            v.at(727) = 0;
        }
    }

    void cause_time_limit_exceeding_if(const bool &f){
        if(f == true){
            for(int t = 1; t > 0; t++);
        }
    }

}

namespace test_generator{

    void rec(ll n, set<ll> u, string test, vector<string> &res){

        if(u.size() == 0){
            res.push_back(test);
            return ;
        }

        string new_test;
        set<ll> new_u;

        for(ll i : u){
            if(u.count(i) == 1){
                new_test = test + char('0' + i);
                if(u.size() > 1){
                    new_test += ' ';
                }
                new_u = u;
                new_u.erase(i);
                rec(n, new_u, new_test, res);
            }
        }

    }

    vector<string> generate_tests(){

        string test;
        vector<string> res;
        set<ll> u;
        ll n, i;

        n = 8;

        for(i = 1; i < n + 1; i++){
            u.insert(i);
        }

        test += to_string(n);
        test += '\n';

        rec(n, u, test, res);

        return res;

    }

}

namespace data_structures{

    struct segment_tree{

        vector<ll> tree_min;

        segment_tree(){}

        void resize(ll n){
            tree_min.resize(4 * n, INF);
        }

        void build(ll v, ll l, ll r, const vector<ll> &a){
            if(r - l == 1){
                tree_min.at(v)= a.at(l);
                return ;
            }
            ll m = (l + r) / 2;

            build(2 * v, l, m, a);
            build(2 * v + 1, m, r, a);

            tree_min.at(v) = min(tree_min.at(2 * v), tree_min.at(2 * v + 1));
        }

        ll get_min(ll v, ll l, ll r, ll ql, ll qr) const {
            if(r <= ql || qr <= l){
                return INF;
            }
            if(ql <= l && r <= qr){
                return tree_min.at(v);
            }
            ll m = (l + r) / 2;

            return min(get_min(2 * v, l, m, ql, qr), get_min(2 * v + 1, m, r, ql, qr));
        }

    };

}

namespace solutions{

    namespace fast_solution{

        void rec(ll l, ll r, vector<vector<ll>> &q, vector<ll> &a, vector<ll> &ind_of, data_structures::segment_tree &e_tree, data_structures::segment_tree &o_tree, ll pid, ll &id, vector<pair<ll, ll>> &ed){

            debug::cause_time_limit_exceeding_if(r < l);
            debug::cause_time_limit_exceeding_if((r - l) % 2 == 1);

            if(r - l == 0){
                return ;
            }
            if(r - l == 2){
                q.push_back({id, a.at(l), a.at(l + 1)});
                if(pid != id && pid != -1){
                    ed.emplace_back(pid, id);
                }
                id++;
                return ;
            }
            ll i, ind1, ind2, n, h;

            n = a.size();

            if(l % 2 == 0){
                ind1 = ind_of.at(e_tree.get_min(1, 0, n, l,        r));
                ind2 = ind_of.at(o_tree.get_min(1, 0, n, ind1 + 1, r));
            }else{
                ind1 = ind_of.at(o_tree.get_min(1, 0, n, l,        r));
                ind2 = ind_of.at(e_tree.get_min(1, 0, n, ind1 + 1, r));
            }

            q.push_back({id, a.at(ind1), a.at(ind2)});
            if(pid != id && pid != -1){
                ed.emplace_back(pid, id);
            }
            id++;

            rec(l,        ind1, q, a, ind_of, e_tree, o_tree, pid,    id, ed);
            rec(ind1 + 1, ind2, q, a, ind_of, e_tree, o_tree, id - 1, id, ed);
            rec(ind2 + 1, r,    q, a, ind_of, e_tree, o_tree, pid,    id, ed);

            return ;

        }

        string get_fast_solution(stringstream &input_stream){

            string res;
            ll n, i, j, x, y, id;
            vector<pair<ll, ll>> ed;
            vector<ll> ans, cnt;
            vector<ll> a, ind_of, ev, od;
            vector<vector<ll>> q, g;
            set<vector<ll>> u;
            data_structures::segment_tree e_tree, o_tree;

            input_stream >> n;

            a.resize(n);
            ev.resize(n);
            od.resize(n);
            ind_of.resize(n);

            for(i = 0; i < n; i++){

                input_stream >> a.at(i), a.at(i)--;

                if(i % 2 == 0){
                    ev.at(i) = a.at(i);
                    od.at(i) = INF;
                }else{
                    ev.at(i) = INF;
                    od.at(i) = a.at(i);
                }

                ind_of.at(a.at(i)) = i;
            }

            //debug::cause_time_limit_exceeding_if(n != 200000 && n > 8);
            // n = .at(2, 4, 6, 8)

            e_tree.resize(n);
            e_tree.build(1, 0, n, ev);

            o_tree.resize(n);
            o_tree.build(1, 0, n, od);

            id = 0;
            rec(0, n, q, a, ind_of, e_tree, o_tree, -1, id, ed);

            sort(q.begin(), q.end());

            g.resize(id);
            cnt.resize(id);

            for(i = 0; i < ed.size(); i++){
                g.at(ed.at(i).first).push_back(ed.at(i).second);
                cnt.at(ed.at(i).second)++;
            }

            //for(i = 0; i < q.size(); i++){
            //    cout << q.at(i).at(0) << ' ' << q.at(i).at(1) + 1 << ' ' << q.at(i).at(2) + 1 << endl;
            //}

            for(i = 0; i < id; i++){
                if(cnt.at(i) == 0){
                    u.insert({q.at(i).at(1) + 1, q.at(i).at(2) + 1, i});
                }
            }

            while(u.empty() == false){

                x = u.begin()->at(0);
                y = u.begin()->at(1);
                i = u.begin()->at(2);

                u.erase(u.begin());

                ans.push_back(x);
                ans.push_back(y);

                for(j = 0; j < g.at(i).size(); j++){
                    u.insert({q.at(g.at(i).at(j)).at(1) + 1, q.at(g.at(i).at(j)).at(2) + 1, g.at(i).at(j)});
                }

            }


            for(i = 0; i < ans.size(); i++){
                res += to_string(ans.at(i));
                if(i + 1 < n){
                    res += ' ';
                }
            }

            return res;

        }

    }


    namespace correct_solution{

        void rec(ll n, vector<ll> a, deque<ll> cur, vector<deque<ll>> &res){
            if(n == 2){
                cur.push_front(a[1] + 1);
                cur.push_front(a[0] + 1);
                res.push_back(cur);
                return ;
            }
            ll i;
            vector<ll> new_a;
            deque<ll> new_cur;

            for(i = 0; i < n - 1; i++){
                new_cur = cur;
                new_cur.push_front(a.at(i + 1) + 1);
                new_cur.push_front(a.at(i) + 1);

                new_a = a;
                new_a.erase(new_a.begin() + i);
                new_a.erase(new_a.begin() + i);

                rec(n - 2, new_a, new_cur, res);
            }
        }

        string get_correct_solution(stringstream &input_stream){

            string res;
            ll i, n;
            vector<ll> a;
            deque<ll> cur;
            vector<deque<ll>> p;

            input_stream >> n;

            a.resize(n);

            for(i = 0; i < n; i++){
                input_stream >> a.at(i);
                a.at(i)--;
            }

            rec(n, a, cur, p);

            sort(p.begin(), p.end());

            for(i = 0; i < n; i++){
                res += to_string(p.at(0).at(i));
                if(i + 1 < n){
                    res += ' ';
                }
            }

            return res;

        }

    }

}


int main(){

    string correct_solution, fast_solution;
    vector<string> tests;
    stringstream input_stream;

    tests = test_generator::generate_tests();

    for(string &test : tests){

        input_stream << test << '\n';

        correct_solution = solutions::correct_solution::get_correct_solution(input_stream);
        input_stream.clear();

        input_stream << test << '\n';

        fast_solution = solutions::fast_solution::get_fast_solution(input_stream);
        input_stream.clear();

        if(correct_solution != fast_solution){
            cout << test << endl;
            cout << correct_solution << endl;
            cout << fast_solution << endl;
            break;
        }

    }

    return 0;
}
