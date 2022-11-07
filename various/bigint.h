#pragma once

// :-)

struct Bigint {
	int base = 1000000;
	vector<int> val;
	bool neg = false;
	Bigint(long long _val = 0) {
		if(_val < 0)neg = true, _val*=-1;
		if(_val > base)val = { _val % base, _val / base };
		else val = {_val};
	}
	Bigint(vector<int> _val, bool _neg) : val(_val), neg(_neg) {}
	friend bool operator == (const Bigint &a, const Bigint &b) { return a.val == b.val; }
	friend bool operator != (const Bigint &a, const Bigint &b) { return !(a == b); }
	friend bool operator < (const Bigint &a, const Bigint &b) {
		if(a.neg != b.neg)return a.neg > b.neg;
		if(a.val.size() != b.val.size())return a.neg ^ (a.val.size() < b.val.size());
		for(int i = static_cast<int>(a.val.size()) - 1; ~i; --i)if(a.val[i] != b.val[i])return a.neg ^ (a.val[i] < b.val[i]);
		return false;
	}
	Bigint operator -() const { return Bigint(val, neg^1); }
	Bigint &operator += (const Bigint &o) {
		if(neg == o.neg){
			ll carry = 0;
			for(int i = 0; i < static_cast<int>(o.val.size()); ++i){
				if(i < val.size())val[i] += o.val[i] + carry;
				else val.push_back(o.val[i] + carry);
				carry = val[i] / base;
				val[i] %= base;
			}
			if(carry){
				for(int i = static_cast<int>(o.val.size()); i < static_cast<int>(val.size()); ++i){
					val[i] += carry;
					carry = val[i] / base;
					val[i] %= base;
				}
				if(carry){
					val.push_back(carry);
				}
			}
		}
		else {
			if((-o) < *this){
				for(int i = 0; i < static_cast<int>(val.size()); ++i){
					val[i] -= (static_cast<int>(o.val.size()) > i ? o.val[i] : 0);
					if(val[i] < 0){
						val[i] += base;
						val[i+1]--;
					}
				}
			}
			else{
				neg^=1;
				for(int i = 0; i < static_cast<int>(o.val.size()); ++i){
					if(static_cast<int>(val.size()) <= i)val.push_back(0);
					val[i] = o.val[i] - val[i];
					if(val[i] < 0){
						val[i] += base;
						if(static_cast<int>(val.size()) <= i + 1)val.push_back(0);
						val[i+1]++;
					}
				}
			}
		}
		while(static_cast<int>(val.size()) > 1 && val.back() == 0)val.pop_back();
		return *this;
	}
	Bigint &operator -= (const Bigint &o) {
		*this += (-o);
		return *this;
	}
	Bigint &operator *= (const Bigint &o) { // need to be optimized with FFT, (mbe something else)
		vector<long long> cu(static_cast<int>(val.size() + o.val.size()));
		for(int i = 0; i < static_cast<int>(val.size()); ++i){
			for(int j = 0; j < static_cast<int>(o.val.size()); ++j){
				cu[i + j] += 1ll * val[i] * o.val[j];
			}
		}
		long long carry = 0;
		for(int i = 0; i < static_cast<int>(cu.size()) || carry; ++i){
			if(i < static_cast<int>(val.size())){
				val[i] = ((i < static_cast<int>(cu.size()) ? cu[i] : 0) + carry) % base;
			}
			else{
				val.push_back(((i < static_cast<int>(cu.size()) ? cu[i] : 0) + carry) % base);
			}
			carry = ((i < static_cast<int>(cu.size()) ? cu[i] : 0) + carry) / base;
		}	
		while(static_cast<int>(val.size()) > 1 && val.back() == 0)val.pop_back();
		return *this;
	}
	// mbe division
	Bigint& operator ++ () {
		return *this += 1;
	}
	Bigint& operator -- () {
		return *this -= 1;
	}
	friend Bigint operator + (Bigint a, const Bigint& b) {
		return a += b;
	}
	friend Bigint operator - (Bigint a, const Bigint& b) {
		return a -= b;
	}
	friend Bigint operator * (Bigint a, const Bigint& b) {
		return a *= b;
	}
	// mbe division
	friend istream& operator >> (istream& s, Bigint& a) {
		string value;
		s >> value;
		a.val.clear();
		while(value.size()){
			if(value.size() <= 6){a.val.push_back(stoi(value)); break;}
			string cu;
			for(int i = 0; i < 6; ++i){
				cu += value.back();
				value.pop_back();
			}
			reverse(cu.begin(),cu.end());
			a.val.push_back(stoi(cu));
		}
		while(static_cast<int>(a.val.size()) > 1 && a.val.back() == 0)a.val.pop_back();
		return s;
	}
	friend ostream& operator << (ostream& s, const Bigint& a) {
		if(a.neg)s << '-';
		for(auto it = a.val.rbegin(); it != a.val.rend(); ++it){
			string cu = to_string(*it);
			if(it != a.val.rbegin())for(int i = 0; i < 6 - static_cast<int>(cu.size()); ++i)cout << 0;
			s << *it;
		}
		return s;
	}
};
