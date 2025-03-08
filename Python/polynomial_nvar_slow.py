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

    def __mul__(self, other):
        return rat("%d/%d" % (self.p * other.p, self.q * other.q))

    def __repr__(self):
        res = ""
        if (self.p * self.q < 0):
            res += "-"
        res += ("%d/%d" % (abs(self.p), abs(self.q)))
        return res

    def __pow__(self, n):
        return rat("%d/%d" % (self.p ** n, self.q ** n))

def is_variable(c):
    if(c in "abcdefghijklmnopqrstuvwxyz"):
        return True
    return False

class monomial:

    def __init__(self, s):
        #print("got1:", s)
        a = s.replace(" ", "").split("*")
        self.coef = rat("1")
        
        if(a[0][0] == "-"):
            self.coef = rat("-1")
            a[0] = a[0][1 : ]
        #print(s)
        if(not is_variable(a[0][0])):
            self.coef *= rat(a[0])
            a.pop(0)

        self.variables = dict()

        zero = 1
        for c in a:
            zero = 0
            if("^") in c:
                var, p = c.split("^")
            else:
                var, p = c, 1
            if(int(p) == 0):
                continue
            self.variables[var] = self.variables.get(var, 0) + int(p)
        if (zero):
            self.variables["$"] = 1
        #print("got2:", s, self.variables)
        #self.variables["$"] = 0
        #const

    def __mul__(self, other):
        new = monomial("1")

        new.coef *= self.coef
        new.coef *= other.coef

        if(new.coef == 0):
            return new

        for var in self.variables:
            p = self.variables[var]
            new.variables[var] = new.variables.get(var, 0) + p

        for var in other.variables:
            p = other.variables[var]
            new.variables[var] = new.variables.get(var, 0) + p

        new.variables["$"] = 1
        return new

    def uwu(self):
        a = []
        for v in self.variables:
            p = self.variables[v]
            if(p < 2):
                a += [v]
            else:
                a += [v + "^" + str(p)]
        a.sort()
        return "*".join(a)

    def uwu0(self):
        a = []
        order = sorted(list(self.variables.keys()))
        for v in order:
            p = self.variables[v]
            if(p == 0):
                continue
            elif(p == 1):
                a += [v]
            else:
                a += [v + "^" + str(p)]
        a.sort()
        return "*".join(a)

    def __repr__(self):
        if(self.coef == 1):
            if(len(self.variables) == 1):
                return "1"
            else:
                return self.uwu0()
        elif(self.coef == 0):
            return "0"
        elif(self.coef == -1):
            if(len(self.variables) == 1):
                return "-1"
            else:
                return "-" + self.uwu0()
        elif(len(self.variables) == 0):
            return str(self.coef)
        else:
            #print("owo", str(self.coef) + "*" + self.uwu0(), self.variables)
            return str(self.coef) + "*" + self.uwu0()

    def calc(self, **kvar):
        res = self.coef
        kvar["$"] = rat("1")

        for v in self.variables:
            res *= pow(kvar[v], self.variables[v])

        return res

class polynomial:

    def __init__(self, line):
        #print("line:", line)
        line = line.replace(" ", "").replace("+", " ").replace("-", " -").strip()
        self.monomials = [monomial(x) for x in line.split()]
        #print("print:", self)

    def __mul__(self, other):
        if (isinstance(other, rat)):
            new = polynomial("0")
            for m in self.monomials:
                new.monomials += [m]
            #print("old", new)
            for i in range(len(new.monomials)):
                new.monomials[i].coef = new.monomials[i].coef * other
            #print("new", new)
            return new
        d = dict()

        #print("p1:", self.monomials)
        #print("p2:", other.monomials)

        for m1 in self.monomials:
            for m2 in other.monomials:
                new = m1 * m2
                k = new.uwu()
                #print("m1 * m2", new, k)
                d[k] = d.get(k, rat("0")) + new.coef
        #print(d)

        #for k in d:
        #    print("iwi", (str(d[k]) + "*" + k))
        new = polynomial(" + ".join([monomial(str(d[k]) + "*" + k).__repr__() for k in d]))
        return new

    def __add__(self, other):
        def hsh(w):
            res = []
            for k in w:
                res += [(k, w)]
            res.sort()
            return str(res)
        
        d = dict()
        new = polynomial("0")

        for m1 in self.monomials:
            found = False
            for m2 in other.monomials:
                if (hsh(m1.variables) == hsh(m2.variables)):
                    found = True
        return polynomial(" + ".join([self.__repr__(), other.__repr__()]))

    def __repr__(self):
        n = len(self.monomials)
        
        if(n == 0):
            return "0"

        a = []
        for i in range(n):
            if(self.monomials[i].coef != 0):
                sp = sum(list(self.monomials[i].variables.values()))
                p = [self.monomials[i].variables.get(v, 0) for v in "abcdefghijklmnopqrstuvwxyz"]
                cmp = (sp, p)
                a += [(cmp, self.monomials[i])]

        a.sort(key = lambda x: x[0], reverse = True)

        if(len(a) == 0):
            return "0"
        s = "+".join(i[1].__repr__() for i in a)

        s = s.replace("-", " - ")
        s = s.replace("+", " + ")
        s = s.replace("+  -", "-")
        s = s.strip()
        
        if(s[0] == '-'):
            s = s.replace("- ", "-", 1)
        return s
    
    def calc(self, **kvar):
        res = rat("0")
        for m in self.monomials:
            res += m.calc(**kvar)
        return res

def interpolate(kv):
    res = polynomial("0")
    n = len(kv)
    for k in range(n):
        prod = polynomial("%d" % (kv[k][1]))
        for i in range(n):
            if (i != k):
                #print("prod1", prod)
                prod = prod * polynomial("x - %d" % (kv[i][0]))
                #print("prod2", prod)
                prod = prod * rat("1/%d" % (kv[k][0] - kv[i][0]))
                pass
        #print("[", res, "]")
        #print("[", prod, "]")
        res = res + prod

    return res

def solve():
    k = int(rd())
    kv = []
    s = 0
    for x in range(1, k + 3):
        s += pow(x, k)
        kv += [(x, s)]

    p = interpolate(kv)
    print(p.calc(x=rat("10")))

    #for m in p.monomials:
    #    print(m.coef, m.variables)
    
def main():
    t = 1
    for i in range(t):
        solve()
main()
