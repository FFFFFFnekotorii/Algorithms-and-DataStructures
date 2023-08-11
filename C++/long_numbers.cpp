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

#define INF   1000000007
#define INF64 1000000000000000003LL
#define LMT   1000000
#define INPUT ios::sync_with_stdio(false);cin.tie(0);

#define FST   first
#define SND   second

#define MOD   998244353LL

#ifdef LOCAL
#define cout cerr
#endif

struct big_integer {
    const static long long int log10base = 6, base = 1000000;

    vector<long long int> digits;
    bool is_neg;

    big_integer() {
        digits.clear();
        is_neg = false;
    }

    string stringify() {
        string ans, res;
        int i;
        if (is_neg == true) {
            ans += '-';
        }
        ans += to_string(digits.back());
        for (i = digits.size() - 2; i > -1; i--) {
            res = to_string(digits[i]);
            reverse(res.begin(), res.end());
            while (res.size() < log10base) {
                res.push_back('0');
            }
            reverse(res.begin(), res.end());
            ans += res;
        }
        return ans;
    }

    void remove_leading_zeroes() {
        while (digits.size() > 0 && digits.back() == 0) {
            digits.pop_back();
        }
        if (digits.size() == 0) {
            digits.push_back(0);
            is_neg = false;
        }
    }

    bool is_even() {
        return (digits.at(0) % 2 == 0);
    }

    big_integer operator/(long long int d) {
        big_integer ans;
        int i;
        long long int res, carry;

        ans = (*this);

        for (i = ans.digits.size() - 1, carry = 0; i > 0; i--) {
            ans.digits[i] = (digits[i] + carry) / d;
            carry = base * ((digits[i] + carry) % d);
        }

        ans.digits[0] = (digits[0] + carry) / d;

        ans.remove_leading_zeroes();

        return ans;
    }

    big_integer operator/(big_integer d) {
        big_integer l, r, m;

        l = 0;
        r = (*this);
        while (r - l > 1) {
            m = (l + r) / 2;
            if (d * m < (*this) || d * m == (*this)) {
                l = m;
            }
            else {
                r = m;
            }
        }

        l.remove_leading_zeroes();

        return l;
    }

    void operator=(long long int val) {
        digits.clear();
        if (val < 0) {
            val = -val;
            is_neg = true;
        }
        else {
            is_neg = false;
        }

        for (; val > 0; val /= base) {
            digits.push_back(val % base);
        }

        remove_leading_zeroes();
    }

    void operator=(big_integer val) {
        digits.clear();
        digits.assign(val.digits.begin(), val.digits.end());
        is_neg = val.is_neg;

        remove_leading_zeroes();
    }

    void operator=(string& str) {
        int i;
        string res;

        digits.clear();

        if (str[0] == '-') {
            str.erase(str.begin());
            is_neg = true;
        }
        else {
            is_neg = false;
        }

        for (i = str.size() - 1; i > -1; i--) {
            res += str[i];
            if (res.size() == log10base) {
                reverse(res.begin(), res.end());
                digits.push_back(stoi(res));
                res = "";
            }
        }
        if (res.size() > 0) {
            reverse(res.begin(), res.end());
            digits.push_back(stoi(res));
        }

        remove_leading_zeroes();
    }

    big_integer operator-(big_integer n) {
        int i, max_size;
        long long int carry, res;
        big_integer ans;

        if (is_neg == true && n.is_neg == false) {
            (*this).is_neg = false;
            ans = (*this) + n;
            ans.is_neg = true;
            return ans;
        }

        if (is_neg == true && n.is_neg == true) {
            ans = n - (*this);
            return ans;
        }

        if (is_neg == false && n.is_neg == true) {
            ans = n + (*this);
            return ans;
        }

        if ((*this) < n) {
            ans = n - (*this);
            ans.is_neg = true;
            return ans;
        }
        else {
            ans.is_neg = false;
        }

        if (digits.size() < n.digits.size()) {
            max_size = n.digits.size();
            digits.resize(n.digits.size(), 0);
        }
        else {
            max_size = digits.size();
            n.digits.resize(digits.size(), 0);
        }

        ans.digits.resize(max_size + 1, 0);
        digits.push_back(0);
        n.digits.push_back(0);

        for (i = 0, carry = 0; i < max_size + 1; i++) {
            res = digits[i] - n.digits[i] + carry;
            if (res < 0) {
                res += base;
                carry = -1;
            }
            else {
                carry = 0;
            }
            ans.digits[i] = res;
        }

        ans.remove_leading_zeroes();

        return ans;
    }

    big_integer operator+(big_integer n) {
        int i, max_size;
        long long int carry, res;
        big_integer ans;

        if (is_neg == true && n.is_neg == false) {
            return n - (*this);
        }

        if (is_neg == false && n.is_neg == true) {
            return (*this) - n;
        }

        if (is_neg == true && n.is_neg == true) {
            ans.is_neg = true;
        }
        else {
            ans.is_neg = false;
        }

        if (digits.size() < n.digits.size()) {
            max_size = n.digits.size();
            digits.resize(n.digits.size(), 0);
        }
        else {
            max_size = digits.size();
            n.digits.resize(digits.size(), 0);
        }

        ans.digits.resize(max_size + 1, 0);
        digits.push_back(0);
        n.digits.push_back(0);

        for (i = 0, carry = 0; i < max_size + 1; i++) {
            res = digits[i] + n.digits[i] + carry;
            if (res >= base) {
                res -= base;
                carry = 1;
            }
            else {
                carry = 0;
            }
            ans.digits[i] = res;
        }

        ans.remove_leading_zeroes();

        return ans;
    }

    bool operator==(big_integer n) {
        return ((digits == n.digits) && (is_neg == n.is_neg));
    }

    bool operator<(big_integer n) {
        int i;

        if (digits.size() < n.digits.size()) {
            return true;
        }

        if (digits.size() > n.digits.size()) {
            return false;
        }

        i = digits.size() - 1;

        while (i > -1 && digits[i] == n.digits[i]) {
            i -= 1;
        }

        if (i == -1) {
            return false;
        }

        return (digits[i] < n.digits[i]);
    }

    bool operator<=(big_integer n) {
        return (operator==(n) || operator<(n));
    }

    bool operator>(big_integer n) {
        return n.operator<(*this);
    }

    big_integer operator*(big_integer n) {
        big_integer ans;
        int i, j;
        long long int carry;

        ans.digits.resize(digits.size() + n.digits.size());

        for (i = 0; i < digits.size(); i++) {
            for (j = 0; j < n.digits.size(); j++) {
                ans.digits[i + j] += digits[i] * n.digits[j];
            }
        }

        for (i = 0, carry = 0; i < digits.size() + n.digits.size(); i++) {
            ans.digits[i] += carry;
            carry = ans.digits[i] / base;
            ans.digits[i] %= base;
        }

        while (carry != 0) {
            ans.digits.push_back(0);

            ans.digits.back() += carry;
            carry = ans.digits[i] / base;
            ans.digits.back() %= base;
        }

        if (is_neg != n.is_neg) {
            ans.is_neg = true;
        }
        else {
            ans.is_neg = false;
        }

        ans.remove_leading_zeroes();

        return ans;
    }

    bool operator!=(big_integer n) {
        return (digits != n.digits);
    }

    bool operator<=(long long int n) {
        big_integer big_n;

        big_n = n;

        return operator<=(big_n);
    }

    bool operator<(long long int n) {
        big_integer big_n;

        big_n = n;

        return operator<(big_n);
    }

    bool operator>(long long int n) {
        big_integer big_n;

        big_n = n;

        return operator>(big_n);
    }

    big_integer operator+(long long int n) {
        big_integer big_n;

        big_n = n;

        return operator+(big_n);
    }

    big_integer operator*(long long int n) {
        big_integer big_n;

        big_n = n;

        return operator*(big_n);
    }

    bool operator==(long long int n) {
        big_integer big_n;

        big_n = n;

        return operator==(big_n);
    }

    bool operator!=(long long int n) {
        big_integer big_n;

        big_n = n;

        return operator!=(big_n);
    }

    big_integer pow(long long int n) {
        big_integer b;

        if (n == 1) {
            return (*this);
        }

        if (n % 2 == 0) {
            b = pow(n / 2);
            return b * b;
        }

        b = pow(n - 1);

        return b * (*this);
    }
};

void solve() {
    string input;
    big_integer n, l, r, m;

    cin >> input;

    n = input;

    l = 0;
    r = n;

    while (r - l > 1) {
        m = (l + r) / 2;

        if (m * m <= n) {
            l = m;
        }
        else {
            r = m;
        }
    }
    cout << l.stringify() << ' ' << (n - l * l).stringify();
}

int main()
{

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
