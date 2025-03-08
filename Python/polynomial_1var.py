from sys import stdin, stdout
from math import gcd

def rd():
    return stdin.readline().strip()
def wt(a):
    stdout.write(a)

INF = 10 ** 9 + 7

class rat:

    def __init__(self, line):
        if ("/" not in line):
            self.p = int(line)
            self.q = 1
            return None
        self.p, self.q = map(int, line.split("/"))
        g = gcd(self.p, self.q)
        self.p //= g
        self.q //= g

    def __add__(self, other):
        return rat("%d/%d" % (self.p * other.q + other.p * self.q, self.q * other.q))

    def __sub__(self, other):
        return rat("%d/%d" % (self.p * other.q - other.p * self.q, self.q * other.q))

    def __mul__(self, other):
        return rat("%d/%d" % (self.p * other.p, self.q * other.q))

    def __truediv__(self, other):
        return rat("%d/%d" % (self.p * other.q, self.q * other.p))

    def __repr__(self):
        res = ""
        if (self.p * self.q < 0):
            res += "-"
        res += ("%d/%d" % (abs(self.p), abs(self.q)))
        return res

    def __pow__(self, n):
        return rat("%d/%d" % (self.p ** n, self.q ** n))

    def zero():
        return rat("0/1")


class polynomial:

    def __init__(self, m, ring):
        self.coefs = m[::]
        self.ring = ring
        while (len(self.coefs) > 0 and self.coefs[-1] == self.ring.zero()):
            self.coefs.pop()

    def deg(self):
        return len(self.coefs) - 1

    def __add__(self, other):
        res = polynomial([self.ring.zero() for i in range(max(self.deg(), other.deg()) + 1)], self.ring)
        for i in range(self.deg() + 1):
            res.coefs[i] = res.coefs[i] + self.coefs[i]
        for i in range(other.deg() + 1):
            res.coefs[i] = res.coefs[i] + other.coefs[i]
        return res

    def __mul__(self, other):
        res = polynomial([self.ring.zero() for i in range(self.deg() + other.deg() + 1)], self.ring)
        for i in range(self.deg() + 1):
            for j in range(other.deg() + 1):
                res.coefs[i + j] = res.coefs[i + j] + self.coefs[i] * other.coefs[j]
        return res

    def __call__(self, val):
        res = self.ring.zero()
        
        for i in range(self.deg() + 1):
            res = res + self.coefs[i] * pow(val, i)
        
        return res

    def __str__(self):
        return " ".join(map(str, self.coefs))

def interpolate(kv):
    res = polynomial([], rat)
    n = len(kv)
    for i in range(n):
        kv[i][0] = rat(str(kv[i][0]))
        kv[i][1] = rat(str(kv[i][1]))
    
    for k in range(n):
        prod = polynomial([kv[k][1]], rat)
        for i in range(n):
            if (i != k):
                prod = prod * polynomial([kv[i][0] * rat("-1"), rat("1")], rat)
                prod = prod * polynomial([rat("1") / (kv[k][0] - kv[i][0])], rat)
        #print(str(prod))
        res = res + prod

    return res

def solve():
    pass
    
def main():
    t = 1
    for i in range(t):
        solve()
main()
