#pragma once

// :-)

struct FastMod{
	long long b, m;
	FastMod(long long _b) : b(_b), m(-1ULL / b) {}
	ll reduce(long long a) { 
		if(a < b && a >= 0)return a;
		a = a - (unsigned long long)((__uint128_t(m) * a) >> 64) * b;
		if(a >= b) a -= b;
		return a;
	}
};
