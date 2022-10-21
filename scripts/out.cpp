#include<bits/stdc++.h>
#include<bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

typedef long long ll;
typedef long double ld;

template <typename A, typename B = less<A>> using ordered_set = tree<A, null_type, B, rb_tree_tag, tree_order_statistics_node_update>;
template <typename A, typename B, typename C = less<A>> using ordered_map = tree<A, B, C, rb_tree_tag, tree_order_statistics_node_update>;

void prep();
void solve(const int curt);

const int dx4[4] = {0, 0, 1, -1}, dy4[4] = {1, -1, 0, 0};
const int dx8[8] = {0, 0, 1, 1, 1, -1, -1, -1}, dy8[8] = {1, -1, 1, 0, -1, 1, 0, -1};
const bool isT = false;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	prep();

	int t = 1; if(isT){ cin >> t; }
	for(int i = 1; i <= t; ++i)solve(i);
}



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


FastMod mod(1000000007);
//FastMod mod(998244353);

constexpr const bool pri_mod = true;

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
		if(p < 0)return inv(pow(a, -p));
		Mint ret = 1;
		while(p) {
			if(p & 1ll)ret *= a;
			p >>= 1;
			a *= a;
		}
		return ret;
	}
	friend Mint inv(const Mint& a) {
		if constexpr(pri_mod) return pow(a, mod.b - 2);
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


void prep(){

}

void solve(const int curt){
	int n; cin >> n;
	Mint val = 1;
	for(int i = 0; i < n; ++i){
		int x; cin >> x;
		val+=x;
	}
	cout << val << '\n';
}

