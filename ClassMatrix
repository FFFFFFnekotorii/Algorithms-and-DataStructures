class Matrix:
    def __init__(self, n, m):
        self.M = [[0 for j in range(m)] for i in range(n)]
        self.size = (n, m)
 
    def __repr__(self):
        return "\n".join(["[" + " ".join([str(j) for j in i]) + "]" for i in self.M])
 
    def fill(self, arr):
        n, m = self.size
        for i in range(n):
            for j in range(m):
                self.M[i][j] = arr[i][j]
 
    def __add__(self, other):
        if(self.size != other.size):
            put("---error---")
            put("cant size(%d, %d) add to size(%d, %d)" % (self.size[0], self.size[1], other.size[0], other.size[1]))
            put("-----------")
        else:
            n, m = self.size
            for i in range(n):
                for j in range(m):
                    self.M[i][j] += other.M[i][j]
        return self
 
    def __mul__(self, other):
        n, k1 = self.size
        k2, m = other.size
        if(k1 != k2):
            put("---error---")
            put("cant size(%d, %d) multiply by size(%d, %d)" % (self.size[0], self.size[1], other.size[0], other.size[1]))
            put("-----------")
        else:
            c = Matrix(n, m)
            for i in range(n):
                for j in range(m):
                    for k in range(k1):
                        c.M[i][j] += self.M[i][k] * other.M[k][j]
            return c
