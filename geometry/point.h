#pragma once

// :-)

template <typename T = long long> struct Point {
	T x, y;
	Point(T _x = static_cast<T>(0), T _y = static_cast<T>(0)) : x(_x), y(_y) {}
	template <typename B = long long> Point(const B& _x, const B& _y) : x(static_cast<T>(_x)), y(static_cast<T>(_y)) {}
	friend bool operator ==(const Point &p1, const Point &p2) { return p1.x == p2.x && p1.y == p2.y; }
	friend bool operator <(const Point &p1, const Point &p2) { return (p1.x < p2.x) + (p1.x == p2.x) * (p1.y < p2.y); }
	friend int direction(const Point &p1, const Point &p2, const Point &p3){ // -1 ccw, 0 collinear, 1 cw
		long long o = (p2.x - p1.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p2.y - p1.y);
		return (o > 0) - (o < 0);
	}

	friend T dist(Point &p1, Point &p2) {
		return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
	}

	friend long double realdist(Point &p1, Point &p2) {
		return sqrt((long double)dist(p1, p2));
	}

	friend vector<Point> convexhull(vector<Point> V, bool sorted = 0) {
		int n = V.size();
		if(n < 3)return V;
		if(!sorted)sort(V.begin(),V.end());
		vector<Point<T>> ret; 
		ret.push_back(V[0]);
		ret.push_back(V[1]);
		int x = 2;
		for(int i = 2; i < n; ++i){
			while(x >= 2 && direction(ret[x-2],ret[x-1],V[i]) == -1){
				ret.pop_back();
				x--;
			}
			x++;
			ret.push_back(V[i]);
		}
		ret.push_back(V[n-2]);
		x++;
		for(int i = n-3; ~i; --i){
			while(x >= 2 && direction(ret[x-2],ret[x-1],V[i]) == -1){
				ret.pop_back();
				x--;
			}
			x++;
			ret.push_back(V[i]);
		}
		ret.pop_back();
		return ret;
	}
	friend istream& operator >> (istream& s, Point& a) {
		s >> a.x >> a.y;
		return s;
	}
	friend ostream& operator << (ostream& s, const Point& a) {
		s << a.x << ' ' << a.y;
		return s;
	}

};
