#define input() ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
 
using namespace std;
 
typedef long long int ll;
 
struct HashString{
    long long int len, p = 31, q = 1000000007;
    long long int p0 = 27, q0 = 2147483647;
    vector<long long int> pq, hash;
    vector<long long int> pq0, hash0;

    void init(string s){
        len = s.length();
        hash.push_back(0);
        pq.push_back(1);
        hash0.push_back(0);
        pq0.push_back(1);
        for(ll i = 0; i < len; i++){
            hash.push_back((hash[i] * p + (s[i] - 'a' + 1)) % q);
            pq.push_back((pq[i] * p) % q);
            hash0.push_back((hash0[i] * p0 + (s[i] - 'a' + 1)) % q0);
            pq0.push_back((pq0[i] * p0) % q0);
        }
    }
    ll getHash(ll l, ll r){
        return ((hash[r] - hash[l] * pq[r - l]) % q + q) % q;
    }
    ll getHash0(ll l, ll r){
        return ((hash0[r] - hash0[l] * pq0[r - l]) % q0 + q0) % q0;
    }
};
 
int main(){
    input();
    HashString hs;
    hs.init("abacaba");
    cout << hs.getHash(0, 3) << "\n";
    cout << hs.getHash(4, 7) << "\n";
    cout << "\n";
    cout << hs.getHash0(0, 3) << "\n";
    cout << hs.getHash0(4, 7) << "\n";
    return 0;
}
