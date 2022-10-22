#pragma once

#include <cplib/various/fastmod.h>

// :-)

FastMod <1000000007> mod;
//FastMod <998244353> mod;

constexpr const bool pri_mod = true;

template<template <int> typename T, int N>
constexpr int extr(const T<N>&) { return N; }

constexpr const int phi_mod_val = pri_mod ? extr(mod) - 1 : phi(extr(mod));
FastMod <phi_mod_val> phi_mod;

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
		if(val >= extr(mod))val -= extr(mod);
		return *this;
	}
	Mint &operator -= (const Mint &o) {
		val -= o.val;
		if(val < 0)val += extr(mod);
		return *this;
	}
	Mint &operator *= (const Mint &o) {
		val = mod.reduce(val * o.val);
		return *this;
	}
	friend Mint pow(Mint a, long long p) {
		if(p >= phi_mod_val || p < 0)phi_mod.reduce(p);
		p -= (p >= phi_mod_val) * phi_mod_val;
		p += (p < 0) * phi_mod_val;
		Mint ret = 1;
		while(p) {
			if(p & 1)ret *= a;
			p >>= 1;
			a *= a;
		}
		return ret;
	}
	friend Mint inv(const Mint& a) {
		if constexpr(pri_mod) return pow(a, extr(mod) - 2);
		return inverse(static_cast<int>(a.val), extr(mod));
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
