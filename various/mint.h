#pragma once

#include <cplib/various/fastmod.h>

// :-)

FastMod mod(1000000007);
//FastMod mod(998244353);

constexpr bool pri_mod = true;

template <typename A> A inverse(A a, A b) {
	a %= b;
	if(!a) {
		return b == 1 ? 0 : -1;
	}
	int c = inverse(b,a);
	return c == -1 ? -1 : ((1LL - (long long)b * (long long)c) / (long long)a) % b;
}

struct Mint {
	int val;
	explicit operator int() const { return val; }
	Mint(int _val = 0) : val(mod.reduce(_val)) {}
	template <typename B = int> Mint(const B& _val) : val(mod.reduce((long long)_val)) {}
	friend bool operator == (const Mint &a, const Mint &b) { return a.val == b.val; }
	friend bool operator != (const Mint &a, const Mint &b) { return !(a == b); }
	friend bool operator < (const Mint &a, const Mint &b) { return a.val < b.val; }
	Mint operator -() const { return Mint(-val); }
	Mint &operator += (const Mint &o) {
		val += o.val;
		if(val >= (int)mod.b)val -= mod.b;
		return *this;
	}
	Mint &operator -= (const Mint &o) {
		val -= o.val;
		if(val < 0)val += mod.b;
		return *this;
	}
	Mint &operator *= (const Mint &o) {
		val = mod.reduce((long long)val * (long long)o.val);
		return *this;
	}
	friend Mint pow(Mint a, long long p) {
		Mint ret = 1;
		while(p) {
			if(p & 1ll)ret *= a;
			p >>= 1;
			a *= a;
		}
		return ret;
	}
	friend Mint inv(const Mint& a) {
		if(pri_mod) return pow(a, mod.b - 2);
		return inverse(a.val, (int)mod.b);
	}
	Mint &operator /= (const Mint &o) {
		(*this) *= inv(o);
		return *this;
	}
	Mint& operator ++ () {
		return *this += 1;
	}
	Mint& operator -- () {
		return *this -= 1;
	}
	friend Mint operator + (Mint a, const Mint& b) {
		return a += b;
	}
	friend Mint operator - (Mint a, const Mint& b) {
		return a -= b;
	}
	friend Mint operator * (Mint a, const Mint& b) {
		return a *= b;
	}
	friend Mint operator / (Mint a, const Mint& b) {
		return a /= b;
	}
	friend istream& operator >> (istream& s, Mint& a) {
		s >> a.val;
		return s;
	}
	friend ostream& operator << (ostream& s, const Mint& a) {
		s << a.val;
		return s;
	}
};
