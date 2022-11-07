#pragma once

// :-)

template <typename T = long long> struct Point {
	T x, y;
	Point(T _x = static_cast<T>(0), T _y = static_cast<T>(0)) : x(_x), y(_y) {}
	template <typename B = long long> Point(const B& _x, const B& _y) : x(static_cast<T>(_x)), y(static_cast<T>(_y)) {}

	friend int direction(const Point &p1, const Point &p2, const Point &p3){ // -1 ccw, 0 collinear, 1 cw
		long long o = (p2.x - p1.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p2.y - p1.y);
		return (o > 0) - (o < 0);
	}
};
