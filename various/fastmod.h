#pragma once

#include<cplib/various/phi.h>

// :-)

template <int MOD> struct FastMod{
	static constexpr const __uint128_t m = ~1ULL / MOD;
	ll reduce(long long a) { 
		if(a < MOD && a >= 0)return a;
		a = a - static_cast <unsigned long long> ((__uint128_t(m) * a) >> 64) * MOD;
		a += MOD * (a < 0);
		a -= MOD * (a >= MOD);
		return a;
		//return a % b;
	}
};
