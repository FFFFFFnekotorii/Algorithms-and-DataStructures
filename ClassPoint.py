class pt:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    def __add__(self, other):
        return pt(self.x + other.x, self.y + other.y)
    def __xor__(self, other):
        return self.x * other.y - self.y * other.x
    def __mul__(self, other):
        return self.x * other.x + self.y * other.y
    def __sub__(self, other):
        return pt(self.x - other.x, self.y - other.y)
    def length(self):
        return pow(self.x ** 2 + self.y ** 2, 0.5)
    def ilength(self):
        return abs(self.x) + abs(self.y)
