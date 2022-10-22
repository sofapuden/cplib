#pragma once

// :-)

template <int MOD> struct FastMod{
    static constexpr const long long m = -1ULL / MOD;
    static constexpr const long long MODPHI = MOD - 1;
    static constexpr const long long mphi = -1ULL / MODPHI;
    static constexpr const long long b = MOD;
    ll reduce(long long a) { 
        if(a < MOD && a >= 0)return a;
        a = a - static_cast <unsigned long long> ((__uint128_t(m) * a) >> 64) * MOD;
        if(a >= MOD) a -= MOD;
        return a;
        //return a % b;
    }
    ll reducephi(long long a) { 
        if(a < MODPHI && a >= 0)return a;
        a = a - static_cast <unsigned long long> ((__uint128_t(mphi) * a) >> 64) * MODPHI;
        if(a >= MODPHI) a -= MODPHI;
        return a;
        //return a % b;
    }
};
