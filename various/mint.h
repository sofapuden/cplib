#pragma once

#include <cplib/various/fastmod.h>

// :-)

FastMod <1000000007> mod;
//FastMod <998244353> mod;

constexpr const bool pri_mod = true;

template <typename A> A inverse(A a, A b) {
	a %= b;
	if(!a) {
		return b == 1 ? 0 : -1;
	}
	int c = inverse(b,a);
	return c == -1 ? -1 : ((1LL - static_cast<long long>(b) * static_cast<long long>(c)) / static_cast<long long>(a)) % b;
}

struct Mint {
	long long val;
	explicit operator int() const { return val; }
	Mint(long long _val = 0) : val(mod.reduce(_val)) {}
	template <typename B = int> Mint(const B& _val) : val(mod.reduce(static_cast<long long>(_val))) {}
	friend bool operator == (const Mint &a, const Mint &b) { return a.val == b.val; }
	friend bool operator != (const Mint &a, const Mint &b) { return !(a == b); }
	friend bool operator < (const Mint &a, const Mint &b) { return a.val < b.val; }
	Mint operator -() const { return Mint(-val); }
	Mint &operator += (const Mint &o) {
		val += o.val;
		if(val >= static_cast<int>(mod.b))val -= mod.b;
		return *this;
	}
	Mint &operator -= (const Mint &o) {
		val -= o.val;
		if(val < 0)val += mod.b;
		return *this;
	}
	Mint &operator *= (const Mint &o) {
		val = mod.reduce(static_cast<long long>(val) * static_cast<long long>(o.val));
		return *this;
	}
	friend Mint pow(Mint a, long long p) {
		if constexpr(pri_mod){ p = mod.reduce(p); }
		Mint ret = 1;
		while(p) {
			if(p & 1)ret *= a;
			p >>= 1;
			a *= a;
		}
		return ret;
	}
	friend Mint inv(const Mint& a) {
		if constexpr(pri_mod) return pow(a, mod.b - 2);
		return inverse(static_cast<int>(a.val), static_cast<int>(mod.b));
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
		long long value;
		s >> value;
		a.val = mod.reduce(value);
		return s;
	}
	friend ostream& operator << (ostream& s, const Mint& a) {
		s << a.val;
		return s;
	}
};
