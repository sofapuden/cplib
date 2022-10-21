#pragma once

// :-)

/*
struct node {
	node operator+(node oth)
	{
		//
		// (MERGE)
		//
	}
};
*/

template<typename T> class segmentTree {

public:
	int n;
	vector<T> st, A;

	segmentTree(int sz) : n(sz), st(4*n) {}
	segmentTree(vector<T> in) : segmentTree((int)in.size()) {
		A = in;
		build(0, n-1, 1);
	}

	void upd(int x, T val){
		upd(x,x,val,0,n-1,1);
	}

	T query(int i, int j){ 
		if(i == j)return A[i];
		return query(i,j,0,n-1,1); 
	}

private:

	void build(int l, int r, int p){
		if(l == r){ st[p] = A[l]; return; }
		int m = (l + r) / 2;
		build(l,m,p<<1);
		build(m+1,r,p<<1|1);
		st[p] = st[p<<1] + st[p<<1|1];
	}

	void upd(int x, T val, int l, int r, int p){
		if(l == r){ st[p] = val; return; }
		int m = (l + r) / 2;
		upd(x,val,l,m,p<<1);
		upd(x,val,m+1,r,p<<1|1);
		st[p] = st[p<<1] + st[p<<1|1];
	}

	T query(int i, int j, int l, int r, int p){
		if(l >= i && r <= j)return st[p];
		int m = (l + r) / 2;
		if(m >= j)return query(i,j,l,m,p<<1);
		if(m < i)return query(i,j,m+1,r,p<<1|1);
		return query(i,j,l,m,p<<1) + query(i,j,m+1,r,p<<1|1);
	}
};
