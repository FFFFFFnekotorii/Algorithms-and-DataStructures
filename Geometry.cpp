#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef long double ld;

namespace Geometry {
    
    template<typename T>
    struct Vector2D {

        T x, y;

        Vector2D(T x0, T y0) {
            x = x0;
            y = y0;
        }

        Vector2D() {
            x = 0;
            y = 0;
        }

        Vector2D operator+(const Vector2D<T>& b) {
            return Vector2D(x + b.x, y + b.y);
        }
        
        Vector2D operator-(const Vector2D<T>& b) {
            return Vector2D(x - b.x, y - b.y);
        }
        
        T operator^(const Vector2D<T>& b) {
            return x * b.y - y * b.x;
        }
        
        T operator*(const Vector2D<T>& b) {
            return x * b.x + y * b.y;
        }
        
        bool operator==(const Vector2D<T>& b) {
            return ((x == b.x) && (y == b.y));
        }
        
        bool operator!=(const Vector2D<T>& b) {
            return ((x != b.x) || (y != b.y));
        }
        
        T length2() {
            return x * x + y * y;
        }
        
        ld length () {
            return sqrtl(length2());
        }
    };
    
    template<typename T>
    struct Line2D {

        T a, b, c;

        Line2D(const Vector2D<T>& p, const Vector2D<T>& t) {
            a = t.y - p.y;
            b = p.x - t.x;
            c = p.x * t.y - p.y * t.x;
        }
		
		Line2D(T a0, T b0, T c0) {
            a = a0;
            b = b0;
            c = c0;
        }
        
        Line2D() {
			a = 0;
			b = 0;
			c = 0;
		}

        string show()
        {
            string output = to_string(a) + "*x + " + to_string(b) + "*y + " + to_string(c) + " = 0\n";
            return output;
        }
        
        Vector2D<double> operator^(const Line2D<T>& other) {
            double num, denom, x, y;
            num = other.c * b - c * other.b;
            denom = other.a * b - a * other.b;
            x = num / denom;
            num = other.c * a - c * other.a;
            denom = a * other.b - other.a * b;
            y = num / denom;
            return Vector2D<double>(x, y);
        }
		
		bool contains(const Vector2D<T>& pt)
		{
			return (a * pt.x + b * pt.y + c == 0);
		}
    };
}

int main()
{
    return 0;
}
