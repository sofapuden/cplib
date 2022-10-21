#pragma once

// :-)

/*
 * NODE + NODE -> NODE
 * NODE - LAZY -> NODE
 * LAZY * NODE -> LAZY
 * LAZY / LAZY -> LAZY
 */

struct segmentTree {
	int n;
	vector<node> st;
	vector<node> lazy;

	segmentTree(int sz) : n(sz), st(4*n), lazy(4*n) {}

	void prop(int p){
		st[p] = st[p] - lazy[p];
		if((p<<1|1) < lazy.size()){
			lazy[p<<1] = lazy[p<<1] / lazy[p];
			lazy[p<<1|1] = lazy[p<<1|1] / lazy[p];
		}
		lazy[p] = node();
	}

	void upd(int i, int j, node val, int l = 0, int r = -2, int p = 1){
		if(r == -2)r = n-1;
		prop(p);
		if(l > j || r < i)return;
		if(l >= i && r <= j){
			lazy[p] = lazy[p] * val;
			prop(p);
			return;
		}
		int m = (l + r) / 2;
		upd(i,j,val,l,m,p<<1);
		upd(i,j,val,m+1,r,p<<1|1);
		st[p] = st[p<<1] + st[p<<1|1];
	}

	void upd(int x, node val){
		upd(x,x,val,0,n-1,1);
	}

	node query(int i, int j, int l = 0, int r = -2, int p = 1){
		if(r == -2)r = n-1;
		prop(p);
		if(l >= i && r <= j)return st[p];
		int m = (l + r) / 2;
		if(m >= j)return query(i,j,l,m,p<<1);
		if(m < i)return query(i,j,m+1,r,p<<1|1);
		return query(i,j,l,m,p<<1) + query(i,j,m+1,r,p<<1|1);
	}
};
