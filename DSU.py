class dsu:
    def __init__(self, sz):
        self.sz = sz
        self.par = [i for i in range(sz)]
        self.rk = [0] * sz
    def find(self, a):
        if(self.par[a] == a):
            return a
        v = self.find(self.par[a])
        self.par[a] = v
        return v
    def merge(self, a, b):
        a = self.find(a)
        b = self.find(b)
        if(a == b):
            return False
        if(self.rk[a] > self.rk[b]):
            a, b = b, a
        self.par[a] = b
        self.rk[b] += 1
        return True
