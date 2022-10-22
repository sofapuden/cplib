#pragma once

// :-)

template <typename A> constexpr A phi(A x) noexcept{
	A res = x;
	if(~x&1){
		while(~x&1){
			x>>=1;
		}
		res >>= 1;
	}
	for(A p = static_cast<A>(3); p * p <= x; p += 2){
		if(!(x % p)) {
			while(!(x % p)) {
				x /= p;
			}
			res -= res / p;
		}
	}
	if(x > static_cast<A>(1)){
		return res - res / x;
	}
	return res;
}
