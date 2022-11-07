#pragma once

// :-)

template <typename T = long long> struct Func{
	T a, b;
	template <typename A> T eval(A x){
		return a * x + b;
	}
};
