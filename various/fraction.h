#pragma once

// :-)

template <typename T = long long> struct Fraction {
	T a, b; // (a / b)

	Fraction(T _a = 0, T _b = 1) : a(_a), b(_b) {}
	Fraction reduce(){
		T d = gcd(a,b);
		if(b < 0)d*=-1;
		return Fraction(a/d, b/d);
	}
	friend bool operator == (const Fraction &c, const Fraction &d) { return c.a * d.b == d.a * c.b; }
	friend bool operator != (const Fraction &c, const Fraction &d) { return !(c == d); }
	friend bool operator < (const Fraction &c, const Fraction &d) { return c.a * d.b < d.a * c.b; }
	Fraction operator -() const { return Fraction(-a, b); }
	Fraction &operator += (const Fraction &o) {
		if(b == o.b){
			a += o.a;
			return *this;
		}
		a = a * o.b + o.a * b;
		b *= o.b;
		return (*this) = this->reduce();
	}
	Fraction &operator -= (const Fraction &o) {
		if(b == o.b){
			a -= o.a;
			return *this;
		}
		a = a * o.b - o.a * b;
		b *= o.b;
		return (*this) = this->reduce();
	}
	Fraction &operator *= (const Fraction &o) {
		a *= o.a;
		b *= o.b;
		return (*this) = this->reduce();
	}
	friend Fraction inv(const Fraction& a) {
		return Fraction(a.b,a.a);
	}
	Fraction &operator /= (const Fraction &o) {
		(*this) *= inv(o);
		return *this;
	}
	Fraction& operator ++ () {
		return *this += Fraction(1,1);
	}
	Fraction& operator -- () {
		return *this -= Fraction(1,1);
	}
	friend Fraction operator + (Fraction a, const Fraction& b) {
		return a += b;
	}
	friend Fraction operator - (Fraction a, const Fraction& b) {
		return a -= b;
	}
	friend Fraction operator * (Fraction a, const Fraction& b) {
		return a *= b;
	}
	friend Fraction operator / (Fraction a, const Fraction& b) {
		return a /= b;
	}
	friend istream& operator >> (istream& s, Fraction& a) {
		s >> a.a >> a.b;
		return s;
	}
	friend ostream& operator << (ostream& s, const Fraction& a) {
		s << a.a << ' ' << a.b;
		return s;
	}
};
