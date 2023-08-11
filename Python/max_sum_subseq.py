class multiset:
    def __init__(self):
        self.d = dict()
        self.usd = set()
        self.sz = 0

    def insert(self, x):
        if(x not in self.usd):
            self.usd.add(x)
            self.d[x] = 0
            self.sz += 1
        self.d[x] += 1

    def erase(self, x):
        if(self.d[x] == 1):
            self.usd.remove(x)
            self.sz -= 1
        self.d[x] -= 1

    def min(self):
        return min(self.usd)

    def __len__(self):
        return self.sz

#ans[i] : max sum of k elements in [0 : i]
def main():
    n, k = 5, 3
    a = [1, 2, -3, 4, 5]
    cnt = multiset()
    ans = [None] * n
    ans[0] = a[0]
    cnt.insert(a[0])
    cur_sum = a[0]
    for i in range(1, k):
        cur_sum += a[i]
        cnt.insert(a[i])
        ans[i] = cur_sum
    print(ans)
    for i in range(k, n):
        m = cnt.min()
        if(a[i] > m):
            cur_sum += a[i]
            cur_sum -= m
            cnt.insert(a[i])
            cnt.erase(m)
        ans[i] = cur_sum
    print(ans)
main()
