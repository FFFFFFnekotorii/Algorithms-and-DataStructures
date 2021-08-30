class node:
    def __init__(self):
        self.term = 0
        self.to = [-1] * 26
 
class trie:
    def __init__(self):
        self.root = node()
    def add(self, s):
        p = [ord(i) - 97 for i in s]
        cur = self.root
        for i in p:
            if(cur.to[i] == -1):
                cur.to[i] = node()
            cur = cur.to[i]
        cur.term += 1
    def contain(self, s):
        p = [ord(i) - 97 for i in s]
        cur = self.root
        for i in p:
            if(cur.to[i] == -1):
                return False
            cur = cur.to[i]
        if(cur.term > 0):
            return True
        return False
    def delete(self, s):
        if(self.contain(s) == False):
            return False
        p = [ord(i) - 97 for i in s]
        cur = self.root
        for i in p:
            if(cur.to[i] == -1):
                return False
            cur = cur.to[i]
        cur.term -= 1
        return True
